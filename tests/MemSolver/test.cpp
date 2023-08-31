#include <iostream>
#include <cassert>
#include "nncv/compiler/Optimizer/MemSolver.hpp"

using namespace nncv::compiler::optimizer;

/*
I use the case below to test:

---
1. cases in paper 'EFFICIENT MEMORY MANAGEMENT FOR DEEP NEURAL NET INFERENCE'
https://arxiv.org/pdf/2001.03288.pdf
---

*/

int testCase1() {
  MemSolver mso;

  mso.registerTensor(0, 1, 32);
  mso.registerTensor(1, 4, 28);
  mso.registerTensor(2, 5, 36);
  mso.registerTensor(3, 5, 16);
  mso.registerTensor(4, 5, 8);
  mso.registerTensor(5, 7, 64);
  mso.registerTensor(6, 8, 10);
  mso.registerTensor(7, 8, 40);

  mso.solve();

  return mso.getTotalConsumption();
}

int main() {
  std::cout << "-- UNIT TEST(MemSolver) --\n"
            << "check test case 1\n";
  assert(testCase1() == 124 && "failed, expect return value 124\n");
}