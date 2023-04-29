#ifndef NNCV_VM_HPP
#define NNCV_VM_HPP

#include "nncv/core/common/device.hpp"
#include "nncv/vm/vm_utils.hpp"

class VirtualMachine {
 public:
  ~VirtualMachine();
  bool Init();

 private:
  nncv::DevicePool* m_DevicePool;
};

#endif  // NNCV_VM_HPP