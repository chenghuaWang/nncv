#include "libnncv/DataType.hpp"
#include <cassert>
#include <cstdio>
#include <fstream>

namespace nncv {
namespace rt /*runtime*/ {

bool MemRefFlatArray::write(const std::string& path) {
  std::ofstream out(path, std::ofstream::binary);
  if (!out.good()) return false;

  // init the head
  m_head.magicNumber = 0x42;
  m_head.numMemRefIndex = m_indexer.size();
  m_head.memRefIndexStartOffset = sizeof(m_head);

  // write the magic head to binary
  out.write(reinterpret_cast<const char*>(&m_head), sizeof(MemRefMagicHead));

  // write the indexer to binary
  size_t dataOffset = m_indexer.size() * sizeof(MemRefIndexer) + sizeof(MemRefMagicHead);
  for (auto& item : m_indexer) {
    item.dataOffset = dataOffset;
    out.write(reinterpret_cast<const char*>(&item), sizeof(MemRefIndexer));
    size_t thisDataOffset = item.eleWidth;
    for (size_t idx = 0; idx < item.dims; ++idx) { thisDataOffset *= item.shape[idx]; }
    dataOffset += thisDataOffset;
  }

  assert(m_data.size() == m_indexer.size() && "the data's size miss match the indxer's size");

  for (size_t i = 0; i < m_indexer.size(); ++i) {
    size_t eleLen = 1;
    for (size_t idx = 0; idx < m_indexer[i].dims; ++idx) { eleLen *= m_indexer[i].shape[idx]; }
    out.write(reinterpret_cast<const char*>(m_data[i]), m_indexer[i].eleWidth * eleLen);
  }

  out.close();
  return true;
}

void MemRefFlatArray::addMemRefIndexer(const MemRefIndexer& indexer, void* data) {
  m_indexer.push_back(indexer);
  m_data.push_back(data);
}

bool MemRefFlatArray::read(const std::string& path) {
  std::ifstream inf(path, std::ifstream::binary);
  if (!inf.good()) return false;

  // read head
  inf.read(reinterpret_cast<char*>(&m_head), sizeof(MemRefMagicHead));

  if (m_head.magicNumber != 0x42) {
    printf("[ Erro ] The magic number of this %s bin file is broken\n", path.c_str());
    inf.close();
    return false;
  }

  // read to MemRefIndexer
  for (size_t i = 0; i < m_head.numMemRefIndex; i++) {
    MemRefIndexer tmp;
    inf.read(reinterpret_cast<char*>(&tmp), sizeof(MemRefIndexer));
    m_indexer.push_back(tmp);
  }

  // read all binary data in a once;
  // 1. get array's length
  size_t acc = 0;
  for (auto item : m_indexer) {
    size_t eleLen = 1;
    for (size_t idx = 0; idx < item.dims; ++idx) { eleLen *= item.shape[idx]; }
    acc += eleLen * item.eleWidth;
  }
  // 2. allocate
  // FIXME: Aligned allocate.
  m_binaryData = new char[acc];
  // 3. read
  inf.read(reinterpret_cast<char*>(m_binaryData), acc);

  inf.close();

  wrap();

  return true;
}

void MemRefFlatArray::wrap() {
  int64_t size_0 = 0;
  for (auto item : m_indexer) {
    size_t eleLen = 1;
    for (size_t idx = 0; idx < item.dims; ++idx) { eleLen *= item.shape[idx]; }
    size_0 += eleLen;
  }
  // wrap to memref<1xtype>
  switch (m_dataType) {
    case dataType::kFloat16: {
      WRAP_FOR_MEMREF_ARRAY(nncvFloat16)
      break;
    }
    case dataType::kFloat32: {
      WRAP_FOR_MEMREF_ARRAY(nncvFloat32)
      break;
    }
    case dataType::kInt16: {
      WRAP_FOR_MEMREF_ARRAY(nncvInt16)
      break;
    }
    case dataType::kInt32: {
      WRAP_FOR_MEMREF_ARRAY(nncvInt32)
      break;
    }
    case dataType::kUnknow: {
      m_wraped = nullptr;
      break;
    }
  }
}

MemRefFlatArray::~MemRefFlatArray() {
  if (m_binaryData) delete m_binaryData;
}

void MemRefFlatBuffer::addMemRefIndexer(const MemRefIndexer& indexer, void* data) {
  m_indexer.push_back(indexer);
  m_data.push_back(data);
}

bool MemRefFlatBuffer::read(const std::string& path) {
  std::ifstream inf(path, std::ifstream::binary);
  if (!inf.good()) return false;

  // read head
  inf.read(reinterpret_cast<char*>(&m_head), sizeof(MemRefMagicHead));

  if (m_head.magicNumber != 0x42) {
    printf("[ Erro ] The magic number of this %s bin file is broken\n", path.c_str());
    inf.close();
    return false;
  }

  // read to MemRefIndexer
  for (size_t i = 0; i < m_head.numMemRefIndex; i++) {
    MemRefIndexer tmp;
    inf.read(reinterpret_cast<char*>(&tmp), sizeof(MemRefIndexer));
    m_indexer.push_back(tmp);
  }

  // read all binary data
  for (auto item : m_indexer) {
    char* tmp;
    size_t eleLen = 1;
    for (size_t idx = 0; idx < item.dims; ++idx) { eleLen *= item.shape[idx]; }

    // allocate a array for tmp
    tmp = new char[item.eleWidth * eleLen];

    inf.read(reinterpret_cast<char*>(tmp), item.eleWidth * eleLen);
    m_data.push_back((void*)tmp);
  }

  inf.close();

  wrap();

  return true;
}

bool MemRefFlatBuffer::write(const std::string& path) {
  std::ofstream out(path, std::ofstream::binary);
  if (!out.good()) return false;

  // init the head
  m_head.magicNumber = 0x42;
  m_head.numMemRefIndex = m_indexer.size();
  m_head.memRefIndexStartOffset = sizeof(m_head);

  // write the magic head to binary
  out.write(reinterpret_cast<const char*>(&m_head), sizeof(MemRefMagicHead));

  // write the indexer to binary
  size_t dataOffset = m_indexer.size() * sizeof(MemRefIndexer) + sizeof(MemRefMagicHead);
  for (auto& item : m_indexer) {
    item.dataOffset = dataOffset;
    out.write(reinterpret_cast<const char*>(&item), sizeof(MemRefIndexer));
    size_t thisDataOffset = item.eleWidth;
    for (size_t idx = 0; idx < item.dims; ++idx) { thisDataOffset *= item.shape[idx]; }
    dataOffset += thisDataOffset;
  }

  assert(m_data.size() == m_indexer.size() && "the data's size miss match the indxer's size");

  for (size_t i = 0; i < m_indexer.size(); ++i) {
    size_t eleLen = 1;
    for (size_t idx = 0; idx < m_indexer[i].dims; ++idx) { eleLen *= m_indexer[i].shape[idx]; }
    out.write(reinterpret_cast<const char*>(m_data[i]), m_indexer[i].eleWidth * eleLen);
  }

  out.close();
  return true;
}

void MemRefFlatBuffer::wrap() {
  // 1. wrap all void* form m_data to unranked memref, such as memref<*xf32>
  assert(m_data.size() == m_indexer.size() && "the data's size miss match the indxer's size");
  for (size_t i = 0; i < m_data.size(); ++i) {
    // get descriptor
    void* descriptor = createMemRefDescriptor(m_indexer[i], m_data[i]);
    // wrap to UnrankedMemRefType
    void* _ptr_unrankedMemRef = createUnarnkedMemRef(m_indexer[i].dims, descriptor);
    // push to Unranked wrap vector
    m_wrapedUnrankMemRef.push_back(_ptr_unrankedMemRef);
  }

  // wrap to memref<dimsxmemref<*xtype>>
  switch (m_dataType) {
    case dataType::kFloat16: {
      WRAP_ALL_TO_ONE_DIM_MEMREF(nncvFloat16)
      break;
    }
    case dataType::kFloat32: {
      WRAP_ALL_TO_ONE_DIM_MEMREF(nncvFloat32)
      break;
    }
    case dataType::kInt16: {
      WRAP_ALL_TO_ONE_DIM_MEMREF(nncvInt16)
      break;
    }
    case dataType::kInt32: {
      WRAP_ALL_TO_ONE_DIM_MEMREF(nncvInt32)
      break;
    }
    case dataType::kUnknow: {
      break;
    }
  }
}

MemRefFlatBuffer::~MemRefFlatBuffer() {
  for (auto item : m_data) { delete (char*)item; }
}

// memref printer. ref from
// https://github.com/llvm/llvm-project/blob/9d3bf9b639eafeded82c6be295031262735d1dac/mlir/include/mlir/ExecutionEngine/RunnerUtils.h
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
extern "C" void _printMemrefF32(UnrankedMemRefType<float>* M) { impl::printMemRef(*M); }

extern "C" void printMemrefF32(int64_t rank, void* ptr) {
  UnrankedMemRefType<float> descriptor = {rank, ptr};
  impl::_printMemrefF32(&descriptor);
}

}  // namespace rt
}  // namespace nncv