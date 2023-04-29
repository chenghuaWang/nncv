#include "nncv/core/common/device.hpp"
namespace nncv {

DevicePool* DevicePool::m_Instance = nullptr;

Device::Device(const DeviceType& dt) : Type(dt), HashValue(-1), GlobalIdx(-1) {}

DevicePool::DevicePool() : m_Cnt4GlobalIdx(0) { m_Instance = this; }

void DevicePool::RegisterDevice(Device& d) {
  if (m_Pool.find(d.GlobalIdx) == m_Pool.end()) {
    d.GlobalIdx = m_Cnt4GlobalIdx++;
    m_Pool[d.GlobalIdx] = d;
  }
}

void DevicePool::RegisterDevice(const DeviceType& dt) {
  auto d = Device(dt);
  d.GlobalIdx = m_Cnt4GlobalIdx++;
  switch (d.Type) {
    case DeviceType::kHost: d.Name = "CPU: " + std::to_string(d.GlobalIdx);
    case DeviceType::kCuda: d.Name = "CUDA: " + std::to_string(d.GlobalIdx);
    case DeviceType::kSelfDefined: d.Name = "Debug: " + std::to_string(d.GlobalIdx);
  }
  m_Pool[d.GlobalIdx] = d;
}

void DevicePool::RemoveDevice(int id) {
  auto iterator_ptr = m_Pool.find(id);
  if (iterator_ptr != m_Pool.end()) { m_Pool.erase(iterator_ptr); }
}

DevicePool* DevicePool::GetInstance() { return m_Instance; }

}  // namespace nncv