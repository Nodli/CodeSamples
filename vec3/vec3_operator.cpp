#include "vec3_operator.h"

vec3& operator+=(vec3& lhs, const vec3& rhs){
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}

vec3& operator-=(vec3& lhs, const vec3& rhs){
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}

vec3& operator+=(vec3& lhs, const float rhs){
	lhs.x += rhs;
	lhs.y += rhs;
	lhs.z += rhs;

	return lhs;
}

vec3& operator-=(vec3& lhs, const float rhs){
	lhs.x -= rhs;
	lhs.y -= rhs;
	lhs.z -= rhs;

	return lhs;
}

vec3& operator*=(vec3& lhs, const float rhs){
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}

vec3& operator/=(vec3& lhs, const float rhs){
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;

	return lhs;
}

vec3 operator+(const vec3& lhs, const vec3& rhs){
	vec3 tmp = lhs;
	tmp += rhs;

	return tmp;
}

vec3 operator-(const vec3& lhs, const vec3& rhs){
	vec3 tmp = lhs;
	tmp -= rhs;

	return tmp;
}

vec3 operator+(const vec3& lhs, const float rhs){
	vec3 tmp = lhs;
	tmp += rhs;

	return tmp;
}

vec3 operator-(const vec3& lhs, const float rhs){
	vec3 tmp = lhs;
	tmp -= rhs;

	return tmp;
}

vec3 operator*(const vec3& lhs, const float rhs){
	vec3 tmp = lhs;
	tmp *= rhs;

	return tmp;
}

vec3 operator/(const vec3& lhs, const float rhs){
	vec3 tmp = lhs;
	tmp /= rhs;

	return tmp;
}
