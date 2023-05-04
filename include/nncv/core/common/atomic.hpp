#ifndef NNCV_ATOMIC_HPP
#define NNCV_ATOMIC_HPP

#if defined(__clang__) && (__clang_major__ >= 3) && !defined(__CUDACC__)
#ifdef __ATOMIC_ACQ_REL
#define NNCV_ATOMIC_ADD(x, y) __c11_atomic_fetch_add((_Atomic(int)*)(x), y, __ATOMIC_ACQ_REL)
#else
#define NNCV_ATOMIC_ADD(x, y) __atomic_fetch_add((_Atomic(int)*)(x), y, 4)
#endif
#elif defined(_MSC_VER) && !defined(RC_INVOKED)
#define NNCV_ATOMIC_ADD(x, y) (int)_InterlockedExchangeAdd((long volatile*)x, y)
#endif

namespace nncv {}

#endif  //! NNCV_ATOMIC_HPP