#ifndef T_VEC2_MATH
#define T_VEC2_MATH

#include <cmath>

template<typename T>
T length(const vec2_pod<T>& vec){
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

template<typename T>
T squared_length(const vec2_pod<T>& vec){
	return vec.x * vec.x + vec.y * vec.y;
}

#endif
