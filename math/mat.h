#ifndef H_MAT
#define H_MAT

#include "vec.h"

// TODO(hugo): Make the constructors Row-Major ?

namespace mat{
    template<typename T>
    struct mat2;
    template<typename T>
    struct mat3;
    template<typename T>
    struct mat4;
}

typedef mat::mat2<int> imat2;
typedef mat::mat2<unsigned int> uimat2;
typedef mat::mat2<float> mat2;
typedef mat::mat2<double> dmat2;

typedef mat::mat3<int> imat3;
typedef mat::mat3<unsigned int> uimat3;
typedef mat::mat3<float> mat3;
typedef mat::mat3<double> dmat3;

typedef mat::mat4<int> imat4;
typedef mat::mat4<unsigned int> uimat4;
typedef mat::mat4<float> mat4;
typedef mat::mat4<double> dmat4;

// ---- mat2 ---- //
template<typename T>
struct mat::mat2{

    mat2() = default;
    // NOTE(hugo): Parameters in row-major order
    mat2(const T xx, const T xy,
         const T yx, const T yy);
    mat2(const mat2<T>& mat) = default;
    mat2(mat2<T>&& mat) = default;
    mat2& operator=(const mat2<T>& mat) = default;
    mat2& operator=(mat2<T>&& mat) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
    mat2(const mat2<otherT>& mat);
    template<typename otherT>
    mat2<T>& operator=(const mat2<otherT>& mat);

    mat2<T>& operator+=(const mat2<T>& mat);
    mat2<T>& operator+=(const T& v);
    mat2<T>& operator-=(const mat2<T>& mat);
    mat2<T>& operator-=(const T& v);
    mat2<T>& operator*=(const mat2<T>& mat);
    mat2<T>& operator*=(const T& v);
    mat2<T>& operator/=(const T& v);

    mat2<T> operator+() const;
    mat2<T> operator-() const;

    bool operator==(const mat2<T>& mat) const;

    // NOTE(hugo): OpenGL uses column-major matrices ie faster on the y axis
    union{
        T data[4];
        vec::vec2<T> column[2];
    };
};

template<typename T>
mat::mat2<T> operator+(const mat::mat2<T>& lhs, const mat::mat2<T>& rhs);
template<typename T>
mat::mat2<T> operator-(const mat::mat2<T>& lhs, const mat::mat2<T>& rhs);
template<typename T>
mat::mat2<T> operator*(const mat::mat2<T>& lhs, const mat::mat2<T>& rhs);

template<typename T>
mat::mat2<T> operator+(const mat::mat2<T>& lhs, const T& rhs);
template<typename T>
mat::mat2<T> operator-(const mat::mat2<T>& lhs, const T& rhs);
template<typename T>
mat::mat2<T> operator*(const mat::mat2<T>& lhs, const T& rhs);
template<typename T>
mat::mat2<T> operator/(const mat::mat2<T>& lhs, const T& rhs);

template<typename T>
mat::mat2<T> operator+(const T& lhs, const mat::mat2<T>& rhs);
template<typename T>
mat::mat2<T> operator-(const T& lhs, const mat::mat2<T>& rhs);
template<typename T>
mat::mat2<T> operator*(const T& lhs, const mat::mat2<T>& rhs);
template<typename T>
mat::mat2<T> operator/(const T& lhs, const mat::mat2<T>& rhs);

template<typename T>
T determinant(const mat::mat2<T>& mat);
template<typename T>
mat::mat2<T> transpose(const mat::mat2<T>& mat);
template<typename T>
mat::mat2<T> inverse(const mat::mat2<T>& mat);

template<typename T>
vec::vec2<T> operator*(const mat::mat2<T>& mat, const vec::vec2<T>& vec);

// ---- mat3 ---- //
template<typename T>
struct mat::mat3{

    mat3() = default;
    // NOTE(hugo): Parameters in row-major order
    mat3(const T xx, const T xy, const T xz,
         const T yx, const T yy, const T yz,
         const T zx, const T zy, const T zz);
    mat3(const mat3<T>& mat) = default;
    mat3(mat3<T>&& mat) = default;
    mat3& operator=(const mat3<T>& mat) = default;
    mat3& operator=(mat3<T>&& mat) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
    mat3(const mat3<otherT>& mat);
    template<typename otherT>
    mat3<T>& operator=(const mat3<otherT>& mat);

    mat3<T>& operator+=(const mat3<T>& mat);
    mat3<T>& operator+=(const T& v);
    mat3<T>& operator-=(const mat3<T>& mat);
    mat3<T>& operator-=(const T& v);
    mat3<T>& operator*=(const mat3<T>& mat);
    mat3<T>& operator*=(const T& v);
    mat3<T>& operator/=(const T& v);

    mat3<T> operator+() const;
    mat3<T> operator-() const;

    bool operator==(const mat3<T>& mat) const;

    // NOTE(hugo): OpenGL uses column-major matrices ie faster on the y axis
    union{
        T data[9];
        vec::vec3<T> column[3];
    };
};

template<typename T>
mat::mat3<T> operator+(const mat::mat3<T>& lhs, const mat::mat3<T>& rhs);
template<typename T>
mat::mat3<T> operator-(const mat::mat3<T>& lhs, const mat::mat3<T>& rhs);
template<typename T>
mat::mat3<T> operator*(const mat::mat3<T>& lhs, const mat::mat3<T>& rhs);

template<typename T>
mat::mat3<T> operator+(const mat::mat3<T>& lhs, const T& rhs);
template<typename T>
mat::mat3<T> operator-(const mat::mat3<T>& lhs, const T& rhs);
template<typename T>
mat::mat3<T> operator*(const mat::mat3<T>& lhs, const T& rhs);
template<typename T>
mat::mat3<T> operator/(const mat::mat3<T>& lhs, const T& rhs);

template<typename T>
mat::mat3<T> operator+(const T& lhs, const mat::mat3<T>& rhs);
template<typename T>
mat::mat3<T> operator-(const T& lhs, const mat::mat3<T>& rhs);
template<typename T>
mat::mat3<T> operator*(const T& lhs, const mat::mat3<T>& rhs);
template<typename T>
mat::mat3<T> operator/(const T& lhs, const mat::mat3<T>& rhs);

template<typename T>
T determinant(const mat::mat3<T>& mat);
template<typename T>
mat::mat3<T> transpose(const mat::mat3<T>& mat);
template<typename T>
mat::mat3<T> inverse(const mat::mat3<T>& mat);

template<typename T>
vec::vec3<T> operator*(const mat::mat3<T>& mat, const vec::vec3<T>& vec);

// ---- mat4 ---- //
template<typename T>
struct mat::mat4{

    mat4() = default;
    // NOTE(hugo): Parameters in row-major order
    mat4(const T xx, const T xy, const T xz, const T xw,
            const T yx, const T yy, const T yz, const T yw,
            const T zx, const T zy, const T zz, const T zw,
            const T wx, const T wy, const T wz, const T ww);
    mat4(const mat4<T>& mat) = default;
    mat4(mat4<T>&& mat) = default;
    mat4& operator=(const mat4<T>& mat) = default;
    mat4& operator=(mat4<T>&& mat) = default;

    // NOTE(hugo): Conversions from another internal type
    template<typename otherT>
    mat4(const mat4<otherT>& mat);
    template<typename otherT>
    mat4<T>& operator=(const mat4<otherT>& mat);

    mat4<T>& operator+=(const mat4<T>& mat);
    mat4<T>& operator+=(const T& v);
    mat4<T>& operator-=(const mat4<T>& mat);
    mat4<T>& operator-=(const T& v);
    mat4<T>& operator*=(const mat4<T>& mat);
    mat4<T>& operator*=(const T& v);
    mat4<T>& operator/=(const T& v);

    mat4<T> operator+() const;
    mat4<T> operator-() const;

    bool operator==(const mat4<T>& mat) const;

    // NOTE(hugo): OpenGL uses column-major matrices ie faster on the y axis
    union{
        T data[16];
        vec::vec4<T> column[4];
    };
};

template<typename T>
mat::mat4<T> operator+(const mat::mat4<T>& lhs, const mat::mat4<T>& rhs);
template<typename T>
mat::mat4<T> operator-(const mat::mat4<T>& lhs, const mat::mat4<T>& rhs);
template<typename T>
mat::mat4<T> operator*(const mat::mat4<T>& lhs, const mat::mat4<T>& rhs);

template<typename T>
mat::mat4<T> operator+(const mat::mat4<T>& lhs, const T& rhs);
template<typename T>
mat::mat4<T> operator-(const mat::mat4<T>& lhs, const T& rhs);
template<typename T>
mat::mat4<T> operator*(const mat::mat4<T>& lhs, const T& rhs);
template<typename T>
mat::mat4<T> operator/(const mat::mat4<T>& lhs, const T& rhs);

template<typename T>
mat::mat4<T> operator+(const T& lhs, const mat::mat4<T>& rhs);
template<typename T>
mat::mat4<T> operator-(const T& lhs, const mat::mat4<T>& rhs);
template<typename T>
mat::mat4<T> operator*(const T& lhs, const mat::mat4<T>& rhs);
template<typename T>
mat::mat4<T> operator/(const T& lhs, const mat::mat4<T>& rhs);

template<typename T>
T determinant(const mat::mat4<T>& mat);
template<typename T>
mat::mat4<T> transpose(const mat::mat4<T>& mat);
template<typename T>
mat::mat4<T> inverse(const mat::mat4<T>& mat);

template<typename T>
vec::vec4<T> operator*(const mat::mat4<T>& mat, const vec::vec4<T>& vec);

#include "mat.inl"

#endif
