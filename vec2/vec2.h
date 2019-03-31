#ifndef H_VEC2
#define H_VEC2

#include "vec2_pod.h"

typedef vec2_pod<float> vec2;
typedef vec2_pod<double> dvec2;
typedef vec2_pod<int> ivec2;
typedef vec2_pod<unsigned int> uivec2;

// checking everything is POD
#include <type_traits>
static_assert(std::is_pod<vec2>::value);
static_assert(std::is_pod<dvec2>::value);
static_assert(std::is_pod<ivec2>::value);
static_assert(std::is_pod<uivec2>::value);

#endif
