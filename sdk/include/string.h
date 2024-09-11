#pragma once
#include <sol/string.h>

static inline void * memcpy(void *restrict dst, void const *restrict src, size_t n) {
  if (__builtin_constant_p(n) && n<=8)
    return __builtin_memcpy(dst, src, n);
  return sol_memcpy(dst, src, n);
}

static inline void * memset(void *dst, int c, size_t n) {
  if (__builtin_constant_p(n) && n<=8)
    return __builtin_memset(dst, c, n);
  return sol_memset(dst, c, n);
}

#define strlen sol_strlen
