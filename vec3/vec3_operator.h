#ifndef H_VEC3_OPERATOR
#define H_VEC3_OPERATOR

#include "vec3_pod.h"

vec3& operator+=(vec3& lhs, const vec3& rhs);
vec3& operator-=(vec3& lhs, const vec3& rhs);

vec3& operator+=(vec3& lhs, const float rhs);
vec3& operator-=(vec3& lhs, const float rhs);
vec3& operator*=(vec3& lhs, const float rhs);
vec3& operator/=(vec3& lhs, const float rhs);

vec3 operator+(const vec3& lhs, const vec3& rhs);
vec3 operator-(const vec3& lhs, const vec3& rhs);

vec3 operator+(const vec3& lhs, const float rhs);
vec3 operator-(const vec3& lhs, const float rhs);
vec3 operator*(const vec3& lhs, const float rhs);
vec3 operator/(const vec3& lhs, const float rhs);

#endif
