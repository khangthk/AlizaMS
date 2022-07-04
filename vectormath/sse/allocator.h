#ifndef ALIGNED_ALLOCATOR__H
#define ALIGNED_ALLOCATOR__H

#define VECTORMATH_USE_CPP17_ALIGNED_ALLOC 0

#include <cstdlib>
#if defined(_MSC_VER)
// Visual Studio
#define VECTORMATH_ALIGNED(a) __declspec(align(16)) a
#define VECTORMATH_ALIGNED_PRE  __declspec(align(16))
#define VECTORMATH_ALIGNED_POST
#elif defined(__GNUC__)
// GCC or Clang
#define VECTORMATH_ALIGNED(a) a __attribute__((aligned(16)))
#define VECTORMATH_ALIGNED_PRE
#define VECTORMATH_ALIGNED_POST __attribute__((aligned(16)))
#else
#error "Define alignment for the compiler"
#endif

#if !(defined _MSC_VER && _MSC_VER >= 1400)
#if !(defined VECTORMATH_USE_CPP17_ALIGNED_ALLOC && VECTORMATH_USE_CPP17_ALIGNED_ALLOC == 1)
#include <cstdint>
#endif
#endif

// The behavior is undefined if alignment is not a power of two
static void * aligned__alloc__(size_t size, size_t alignment)
{
#if defined _MSC_VER && _MSC_VER >= 1400
  return _aligned_malloc(size, alignment);
#else
#if defined VECTORMATH_USE_CPP17_ALIGNED_ALLOC && VECTORMATH_USE_CPP17_ALIGNED_ALLOC == 1
  return std::aligned_alloc(alignment, size);
#else
  const uintptr_t tmp0 = alignment - 1;
  const size_t    tmp1 = sizeof(void*) + tmp0;
  void * p = malloc(size + tmp1);
  if (!p) return NULL;
  uintptr_t tmp2 = (uintptr_t)p + tmp1;
  tmp2 &= (~tmp0);
  void * ptr = (void*)tmp2;
  *((void**)ptr - 1) = p;
  return ptr;
#endif
#endif
}

static void aligned__free__(void * ptr)
{
#if defined _MSC_VER && _MSC_VER >= 1400
  if (ptr) _aligned_free(ptr);
#else
#if defined VECTORMATH_USE_CPP17_ALIGNED_ALLOC && VECTORMATH_USE_CPP17_ALIGNED_ALLOC == 1
  if (ptr) std::free(ptr);
#else
  if (ptr) free(*((void**)ptr - 1));
#endif
#endif
}

#define VECTORMATH_ALIGNED16_NEW() \
inline void* operator new(size_t bytes) {return aligned__alloc__(bytes,16);} \
inline void  operator delete(void* ptr) {aligned__free__(ptr);} \
inline void* operator new(size_t, void* ptr) {return ptr; } \
inline void  operator delete(void*, void*) {} \
inline void* operator new[](size_t bytes) {return aligned__alloc__(bytes,16);} \
inline void  operator delete[](void* ptr) {aligned__free__(ptr);} \
inline void* operator new[](size_t, void* ptr) {return ptr;} \
inline void  operator delete[](void*, void*) {}

#endif // ALIGNED_ALLOCATOR__H
