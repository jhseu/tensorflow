#include <mutex>
#include <new>

#include "jemalloc/jemalloc.h"

void *operator new(std::size_t size);
void *operator new[](std::size_t size);
void *operator new(std::size_t size, const std::nothrow_t&) noexcept;
void *operator new[](std::size_t size, const std::nothrow_t&) noexcept;
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, const std::nothrow_t&) noexcept;

template <bool IsNoExcept>
inline void *newImpl(std::size_t size) noexcept(IsNoExcept)
{
  void* ptr = jemalloc_malloc(size);
  if (ptr != nullptr)
    return (ptr);

  while (ptr == nullptr) {
    std::new_handler handler;
    // GCC-4.8 and clang 4.0 do not have std::get_new_handler.
    {
      static std::mutex mtx;
      std::lock_guard<std::mutex> lock(mtx);

      handler = std::set_new_handler(nullptr);
      std::set_new_handler(handler);
    }
    if (handler == nullptr)
      break;

    handler();
    ptr = jemalloc_malloc(size);
  }

  if (ptr == nullptr && !IsNoExcept)
    std::__throw_bad_alloc();
  return (ptr);
}

void *operator new(std::size_t size) {
  return (newImpl<false>(size));
}

void *operator new[](std::size_t size) {
  return (newImpl<false>(size));
}

void *operator new(std::size_t size, const std::nothrow_t&) noexcept {

  return (newImpl<true>(size));
}

void *operator new[](std::size_t size, const std::nothrow_t&) noexcept {
  return (newImpl<true>(size));
}

void operator delete(void* ptr) noexcept {
  jemalloc_free(ptr);
}

void operator delete[](void* ptr) noexcept {
  jemalloc_free(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept {
  jemalloc_free(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
  jemalloc_free(ptr);
}
