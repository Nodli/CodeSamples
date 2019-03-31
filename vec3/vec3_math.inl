#ifndef T_VEC3_MATH
#define T_VEC3_MATH

template<typename T>
float dot(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T>
vec3_pod<T> cross(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	return {lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x};
}

#endif
