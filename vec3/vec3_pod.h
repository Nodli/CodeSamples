#ifndef H_VEC3_POD
#define H_VEC3_POD

template<typename T>
struct vec3_pod{
	union{
		T coord[3];

		struct{
			T x;
			T y;
			T z;
		};

		struct{
			T r;
			T g;
			T b;
		};
	};
};

// in-place math operators
template<typename T>
vec3_pod<T>& operator+=(vec3_pod<T>& lhs, const vec3_pod<T>& rhs);
template<typename T>
vec3_pod<T>& operator-=(vec3_pod<T>& lhs, const vec3_pod<T>& rhs);

template<typename T>
vec3_pod<T>& operator+=(vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T>& operator-=(vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T>& operator*=(vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T>& operator/=(vec3_pod<T>& lhs, const float rhs);

// copy math operators
template<typename T>
vec3_pod<T> operator+(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs);
template<typename T>
vec3_pod<T> operator-(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs);

template<typename T>
vec3_pod<T> operator+(const vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T> operator-(const vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T> operator*(const vec3_pod<T>& lhs, const float rhs);
template<typename T>
vec3_pod<T> operator/(const vec3_pod<T>& lhs, const float rhs);

#include "vec3_operator.inl"

// math operations
template<typename T>
float dot(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs);

template<typename T>
vec3_pod<T> cross(const vec3_pod<T>& lhs, const vec3_pod<T>& rhs);

#include "vec3_math.inl"

#endif
