NNCV Compiler
---

The compiler of NNCV is independent part.

## Unsolved problem

* fms-capability-version is lower then 19.27(uncomment `# include(HandleLLVMOptions)` in cmake lists)
* `Findzstd.cmake` in LLVM is not works due to some errors.