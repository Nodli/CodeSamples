#ifndef T_VEC3_OPERATOR
#define T_VEC3_OPERATOR

template<typename T>
vec3_pod<T>& operator+=(vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}

template<typename T>
vec3_pod<T>& operator-=(vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}

template<typename T>
vec3_pod<T>& operator+=(vec3_pod<T>& lhs, const float rhs){
	lhs.x += rhs;
	lhs.y += rhs;
	lhs.z += rhs;

	return lhs;
}

template<typename T>
vec3_pod<T>& operator-=(vec3_pod<T>& lhs, const float rhs){
	lhs.x -= rhs;
	lhs.y -= rhs;
	lhs.z -= rhs;

	return lhs;
}

template<typename T>
vec3_pod<T>& operator*=(vec3_pod<T>& lhs, const float rhs){
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}

template<typename T>
vec3_pod<T>& operator/=(vec3_pod<T>& lhs, const float rhs){
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;

	return lhs;
}

template<typename T>
vec3_pod<T> operator+(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	vec3_pod<T> tmp = lhs;
	tmp += rhs;

	return tmp;
}

template<typename T>
vec3_pod<T> operator-(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs){
	vec3_pod<T> tmp = lhs;
	tmp -= rhs;

	return tmp;
}

template<typename T>
vec3_pod<T> operator+(const vec3_pod<T>& lhs, const float rhs){
	vec3_pod<T> tmp = lhs;
	tmp += rhs;

	return tmp;
}

template<typename T>
vec3_pod<T> operator-(const vec3_pod<T>& lhs, const float rhs){
	vec3_pod<T> tmp = lhs;
	tmp -= rhs;

	return tmp;
}

template<typename T>
vec3_pod<T> operator*(const vec3_pod<T>& lhs, const float rhs){
	vec3_pod<T> tmp = lhs;
	tmp *= rhs;

	return tmp;
}

template<typename T>
vec3_pod<T> operator/(const vec3_pod<T>& lhs, const float rhs){
	vec3_pod<T> tmp = lhs;
	tmp /= rhs;

	return tmp;
}

#endif
