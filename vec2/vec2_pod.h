#ifndef H_VEC2_POD
#define H_VEC2_POD

template<typename T>
struct vec2_pod{
	union{
		T coord[2];

		struct{
			T x;
			T y;
		};

		struct{
			T u;
			T v;
		};
	};
};

// in-place math operators
template<typename T>
vec2_pod<T>& operator+=(vec2_pod<T>& lhs, const vec2_pod<T>& rhs);
template<typename T>
vec2_pod<T>& operator-=(vec2_pod<T>& lhs, const vec2_pod<T>& rhs);

template<typename T>
vec2_pod<T>& operator+=(vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T>& operator-=(vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T>& operator*=(vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T>& operator/=(vec2_pod<T>& lhs, const float rhs);

// copy math operators
template<typename T>
vec2_pod<T> operator+(const vec2_pod<T>& lhs, const vec2_pod<T>& rhs);
template<typename T>
vec2_pod<T> operator-(const vec2_pod<T>& lhs, const vec2_pod<T>& rhs);

template<typename T>
vec2_pod<T> operator+(const vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T> operator-(const vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T> operator*(const vec2_pod<T>& lhs, const float rhs);
template<typename T>
vec2_pod<T> operator/(const vec2_pod<T>& lhs, const float rhs);

#include "vec2_operator.inl"

// math operations
template<typename T>
T length(const vec2_pod<T>& v);

template<typename T>
T squared_length(const vec2_pod<T>& v);

#include "vec2_math.inl"

#endif
