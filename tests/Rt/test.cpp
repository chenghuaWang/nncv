#include "libnncv/DataType.hpp"
#include "libnncv/SystemIo.hpp"

using namespace nncv::rt;

int main() {
  MemRefFlatBuffer params(dataType::kFloat32);
  if (!params.read("model.bin")) { return -1; }
  params.printInfo();
  return 0;
}