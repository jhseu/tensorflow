#include <mutex>
#include <new>

#include "jemalloc/jemalloc.h"

// FIXME(jhseu): exception versions of these calls not yet correct.

void *operator new(std::size_t size) {
  return jemalloc_malloc(size);
}

void *operator new[](std::size_t size) {
  return jemalloc_malloc(size);
}

void *operator new(std::size_t size, const std::nothrow_t&) noexcept {
  return jemalloc_malloc(size);
}

void *operator new[](std::size_t size, const std::nothrow_t&) noexcept {
  return jemalloc_malloc(size);
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
