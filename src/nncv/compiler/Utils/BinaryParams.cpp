#include "nncv/compiler/Utils/BinaryParams.hpp"
#include <cassert>
#include <fstream>

namespace nncv::utils {

void MemRefFlatBuffer::addMemRefIndexer(const MemRefIndexer& indexer, void* data) {
  m_indexer.push_back(indexer);
  m_data.push_back(data);
}

bool MemRefFlatBuffer::read(const std::string& path) {
  std::ifstream inf(path, std::ifstream::binary);
  if (inf.good()) return false;

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
    void* tmp = nullptr;
    size_t eleLen = 1;
    for (size_t idx = 0; idx < item.dims; ++idx) { eleLen *= item.shape[idx]; }
    inf.read(reinterpret_cast<char*>(tmp), item.eleWidth * eleLen);
    m_data.push_back(tmp);
  }

  inf.close();
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
    out.write(reinterpret_cast<const char*>(m_data[i]), (m_indexer[i].eleWidth) * eleLen);
    delete (char*)m_data[i];
  }

  out.close();
  return true;
}
}  // namespace nncv::utils