#ifndef T_VEC2_OPERATOR
#define T_VEC2_OPERATOR

template<typename T>
vec2_pod<T>& operator+=(vec2_pod<T>& lhs, const vec2_pod<T>& rhs){
	lhs.x += rhs.x;
	lhs.y += rhs.y;

	return lhs;
}

template<typename T>
vec2_pod<T>& operator-=(vec2_pod<T>& lhs, const vec2_pod<T>& rhs){
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;

	return lhs;
}

template<typename T>
vec2_pod<T>& operator+=(vec2_pod<T>& lhs, const float rhs){
	lhs.x += rhs;
	lhs.y += rhs;

	return lhs;
}

template<typename T>
vec2_pod<T>& operator-=(vec2_pod<T>& lhs, const float rhs){
	lhs.x -= rhs;
	lhs.y -= rhs;

	return lhs;
}

template<typename T>
vec2_pod<T>& operator*=(vec2_pod<T>& lhs, const float rhs){
	lhs.x *= rhs;
	lhs.y *= rhs;

	return lhs;
}

template<typename T>
vec2_pod<T>& operator/=(vec2_pod<T>& lhs, const float rhs){
	lhs.x /= rhs;
	lhs.y /= rhs;

	return lhs;
}

template<typename T>
vec2_pod<T> operator+(const vec2_pod<T>& lhs, const vec2_pod<T>& rhs){
	vec2_pod<T> tmp = lhs;
	tmp += rhs;

	return tmp;
}

template<typename T>
vec2_pod<T> operator-(const vec2_pod<T>& lhs, const vec2_pod<T>& rhs){
	vec2_pod<T> tmp = lhs;
	tmp -= rhs;

	return tmp;
}

template<typename T>
vec2_pod<T> operator+(const vec2_pod<T>& lhs, const float rhs){
	vec2_pod<T> tmp = lhs;
	tmp += rhs;

	return tmp;
}

template<typename T>
vec2_pod<T> operator-(const vec2_pod<T>& lhs, const float rhs){
	vec2_pod<T> tmp = lhs;
	tmp -= rhs;

	return tmp;
}

template<typename T>
vec2_pod<T> operator*(const vec2_pod<T>& lhs, const float rhs){
	vec2_pod<T> tmp = lhs;
	tmp *= rhs;

	return tmp;
}

template<typename T>
vec2_pod<T> operator/(const vec2_pod<T>& lhs, const float rhs){
	vec2_pod<T> tmp = lhs;
	tmp /= rhs;

	return tmp;
}

#endif
