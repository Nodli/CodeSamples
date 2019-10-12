#ifndef H_VEC
#define H_VEC

namespace vec{
    template<typename T>
    struct vec2;
    template<typename T>
    struct vec3;
    template<typename T>
    struct vec4;
}

typedef vec::vec2<bool> bvec2;
typedef vec::vec2<int> ivec2;
typedef vec::vec2<unsigned int> uivec2;
typedef vec::vec2<float> vec2;
typedef vec::vec2<double> dvec2;

typedef vec::vec3<bool> bvec3;
typedef vec::vec3<int> ivec3;
typedef vec::vec3<unsigned int> uivec3;
typedef vec::vec3<float> vec3;
typedef vec::vec3<double> dvec3;

typedef vec::vec4<bool> bvec4;
typedef vec::vec4<int> ivec4;
typedef vec::vec4<unsigned int> uivec4;
typedef vec::vec4<float> vec4;
typedef vec::vec4<double> dvec4;


// ---- vec2 ---- //
template<typename T>
struct vec::vec2{

    vec2() = default;
    vec2(const T v);
    vec2(const T x, const T y);
    vec2(const vec2<T>& vec) = default;
    vec2(vec2<T>&& vec) = default;
    vec2& operator=(const vec2<T>& vec) = default;
    vec2& operator=(vec2<T>&& vec) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
        vec2(const vec2<otherT>& vec);
    template<typename otherT>
        vec2<T>& operator=(const vec2<otherT>& vec);

    vec2<T>& operator++();
    vec2<T> operator++(int);
    vec2<T>& operator--();
    vec2<T> operator--(int);

    vec2<T>& operator+=(const vec2<T>& vec);
    vec2<T>& operator+=(const T v);
    vec2<T>& operator-=(const vec2<T>& vec);
    vec2<T>& operator-=(const T v);
    vec2<T>& operator*=(const vec2<T>& vec);
    vec2<T>& operator*=(const T v);
    vec2<T>& operator/=(const vec2<T>& vec);
    vec2<T>& operator/=(const T v);

    vec2<T> operator+() const;
    vec2<T> operator-() const;

    bool operator==(const vec2<T>& vec) const;

    union{
        T data[2];
        struct{
            T x;
            T y;
        };
        struct{
            T r;
            T g;
        };
        struct{
            T s;
            T t;
        };
    };
};

template<typename T>
vec::vec2<T> operator+(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator-(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator*(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator/(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs);

template<typename T>
vec::vec2<T> operator+(const vec::vec2<T>& lhs, const T rhs);
template<typename T>
vec::vec2<T> operator-(const vec::vec2<T>& lhs, const T rhs);
template<typename T>
vec::vec2<T> operator*(const vec::vec2<T>& lhs, const T rhs);
template<typename T>
vec::vec2<T> operator/(const vec::vec2<T>& lhs, const T rhs);

template<typename T>
vec::vec2<T> operator+(const T lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator-(const T lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator*(const T lhs, const vec::vec2<T>& rhs);
template<typename T>
vec::vec2<T> operator/(const T lhs, const vec::vec2<T>& rhs);

template<typename T>
vec::vec2<T> abs(const vec::vec2<T>& vec);
template<typename T>
T dot(const vec::vec2<T>& vA, const vec::vec2<T>& vB);
template<typename T>
T length(const vec::vec2<T>& vec);
template<typename T>
T sqlength(const vec::vec2<T>& vec);
template<typename T>
vec::vec2<T> normalize(const vec::vec2<T>& vec);

// ---- vec3 ---- //
template<typename T>
struct vec::vec3{

    vec3() = default;
    vec3(const T v);
    vec3(const T x, const T y, const T z);
    vec3(const vec3<T>& vec) = default;
    vec3(vec3<T>&& vec) = default;
    vec3& operator=(const vec3<T>& vec) = default;
    vec3& operator=(vec3<T>&& vec) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
        vec3(const vec3<otherT>& vec);
    template<typename otherT>
        vec3<T>& operator=(const vec3<otherT>& vec);

    vec3<T>& operator++();
    vec3<T> operator++(int);
    vec3<T>& operator--();
    vec3<T> operator--(int);

    vec3<T>& operator+=(const vec3<T>& vec);
    vec3<T>& operator+=(const T v);
    vec3<T>& operator-=(const vec3<T>& vec);
    vec3<T>& operator-=(const T v);
    vec3<T>& operator*=(const vec3<T>& vec);
    vec3<T>& operator*=(const T v);
    vec3<T>& operator/=(const vec3<T>& vec);
    vec3<T>& operator/=(const T v);

    vec3<T> operator+() const;
    vec3<T> operator-() const;

    bool operator==(const vec3<T>& vec) const;

    union{
        float data[3];
        struct{
            float x;
            float y;
            float z;
        };
        struct{
            float r;
            float g;
            float b;
        };
        struct{
            float s;
            float t;
            float p;
        };
    };
};

template<typename T>
vec::vec3<T> operator+(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator-(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator*(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator/(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs);

template<typename T>
vec::vec3<T> operator+(const vec::vec3<T>& lhs, const T rhs);
template<typename T>
vec::vec3<T> operator-(const vec::vec3<T>& lhs, const T rhs);
template<typename T>
vec::vec3<T> operator*(const vec::vec3<T>& lhs, const T rhs);
template<typename T>
vec::vec3<T> operator/(const vec::vec3<T>& lhs, const T rhs);

template<typename T>
vec::vec3<T> operator+(const T lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator-(const T lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator*(const T lhs, const vec::vec3<T>& rhs);
template<typename T>
vec::vec3<T> operator/(const T lhs, const vec::vec3<T>& rhs);

template<typename T>
vec::vec3<T> abs(const vec::vec3<T>& vec);
template<typename T>
T dot(const vec::vec3<T>& vA, const vec::vec3<T>& vB);
template<typename T>
vec::vec3<T> cross(const vec::vec3<T>& vA, const vec::vec3<T>& vB);
template<typename T>
T length(const vec::vec3<T>& vec);
template<typename T>
T sqlength(const vec::vec3<T>& vec);
template<typename T>
vec::vec3<T> normalize(const vec::vec3<T>& vec);

// ---- vec4 ---- //
template<typename T>
struct vec::vec4{

    vec4() = default;
    vec4(const T v);
    vec4(const T x, const T y, const T z, const T w);
    vec4(const vec4<T>& vec) = default;
    vec4(vec4<T>&& vec) = default;
    vec4& operator=(const vec4<T>& vec) = default;
    vec4& operator=(vec4<T>&& vec) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
        vec4(const vec4<otherT>& vec);
    template<typename otherT>
        vec4<T>& operator=(const vec4<otherT>& vec);

    vec4<T>& operator++();
    vec4<T> operator++(int);
    vec4<T>& operator--();
    vec4<T> operator--(int);

    vec4<T>& operator+=(const vec4<T>& vec);
    vec4<T>& operator+=(const T v);
    vec4<T>& operator-=(const vec4<T>& vec);
    vec4<T>& operator-=(const T v);
    vec4<T>& operator*=(const vec4<T>& vec);
    vec4<T>& operator*=(const T v);
    vec4<T>& operator/=(const vec4<T>& vec);
    vec4<T>& operator/=(const T v);

    vec4<T> operator+() const;
    vec4<T> operator-() const;

    bool operator==(const vec4<T>& vec) const;

    union{
        float data[4];
        struct{
            float x;
            float y;
            float z;
            float w;
        };
        struct{
            float r;
            float g;
            float b;
            float a;
        };
        struct{
            float s;
            float t;
            float p;
            float q;
        };
    };
};

template<typename T>
vec::vec4<T> operator+(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator-(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator*(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator/(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs);

template<typename T>
vec::vec4<T> operator+(const vec::vec4<T>& lhs, const T rhs);
template<typename T>
vec::vec4<T> operator-(const vec::vec4<T>& lhs, const T rhs);
template<typename T>
vec::vec4<T> operator*(const vec::vec4<T>& lhs, const T rhs);
template<typename T>
vec::vec4<T> operator/(const vec::vec4<T>& lhs, const T rhs);

template<typename T>
vec::vec4<T> operator+(const T lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator-(const T lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator*(const T lhs, const vec::vec4<T>& rhs);
template<typename T>
vec::vec4<T> operator/(const T lhs, const vec::vec4<T>& rhs);

template<typename T>
vec::vec4<T> abs(const vec::vec4<T>& vec);
template<typename T>
T dot(const vec::vec4<T>& vA, const vec::vec4<T>& vB);
template<typename T>
vec::vec4<T> cross(const vec::vec4<T>& vA, const vec::vec4<T>& vB);
template<typename T>
T length(const vec::vec4<T>& vec);
template<typename T>
T sqlength(const vec::vec4<T>& vec);
template<typename T>
vec::vec4<T> normalize(const vec::vec4<T>& vec);

#include "vec.inl"

#endif
