#ifndef H_VEC3
#define H_VEC3

#include "vec3_pod.h"

typedef vec3_pod<float> vec3;
typedef vec3_pod<double> dvec3;
typedef vec3_pod<int> ivec3;
typedef vec3_pod<unsigned int> uivec3;

// checking everything is POD
#include <type_traits>
static_assert(std::is_pod<vec3>::value);
static_assert(std::is_pod<dvec3>::value);
static_assert(std::is_pod<ivec3>::value);
static_assert(std::is_pod<uivec3>::value);

#endif
