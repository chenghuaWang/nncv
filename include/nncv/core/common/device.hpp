#ifndef NNCV_DEVICE_HPP
#define NNCV_DEVICE_HPP

#pragma once

#include "nncv/core/base.hpp"

#include <string>
#include <unordered_map>

namespace nncv {

/**
 * @brief The enum of Device Type, kSelfDefined is for debugging purpose.
 *
 */
enum DeviceType : int {
  kHost = 0,
  kCuda = 1,
  kSelfDefined = 2,
};

struct NNCV_EXPORT_DLL Device {
  Device() = default;
  Device(const DeviceType& dt);
  DeviceType Type;
  std::string Name;
  int HashValue;
  int GlobalIdx;
};

class NNCV_EXPORT_DLL DevicePool {
 public:
  ~DevicePool() = default;
  DevicePool();

  Device& GetDeviceByIdx();
  void RegisterDevice(Device& d);
  void RegisterDevice(const DeviceType& dt);
  void RemoveDevice(int id);

  static DevicePool* GetInstance();

  static DevicePool* m_Instance;  //! this class is using singleton model.

 private:
  int m_Cnt4GlobalIdx;
  std::unordered_map<int, Device> m_Pool;
};

}  // namespace nncv

#endif  // NNCV_DEVICE_HPP