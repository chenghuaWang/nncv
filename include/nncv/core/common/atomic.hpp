#ifndef NNCV_ATOMIC_HPP
#define NNCV_ATOMIC_HPP

#include <atomic>

#if defined (_linux_)
#define NNCV_ATOMIC_ADD(x, y) 
#elif defined(WIN32)
#define NNCV_ATOMIC_ADD(x, y) atomic_fetch_add((x), (y))
#endif

namespace nncv {

}

#endif //! NNCV_ATOMIC_HPP