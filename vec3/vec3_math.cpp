#include "vec3_math.h"

float dot(const vec3& lhs, const vec3& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3 cross(const vec3& lhs, const vec3& rhs){
	return {lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x};
}
