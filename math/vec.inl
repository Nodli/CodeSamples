#ifndef INL_VEC
#define INL_VEC

#include <cmath>

// ---- vec2 ---- //
template<typename T>
vec::vec2<T>::vec2(const T v)
: x(v), y(v){
}
template<typename T>
vec::vec2<T>::vec2(const T ix, const T iy)
: x(ix), y(iy){
}

template<typename T>
template<typename otherT>
vec::vec2<T>::vec2(const vec::vec2<otherT>& vec)
: x(vec.x), y(vec.y){
}
template<typename T>
template<typename otherT>
vec::vec2<T>& vec::vec2<T>::operator=(const vec::vec2<otherT>& vec){
    x = vec.x;
    y = vec.y;
}

template<typename T>
vec::vec2<T>& vec::vec2<T>::operator++(){
    ++x;
    ++y;
}
template<typename T>
vec::vec2<T> vec::vec2<T>::operator++(int){
    vec::vec2<T> copy = *this;
    operator++();
    return copy;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator--(){
    --x;
    --y;
}
template<typename T>
vec::vec2<T> vec::vec2<T>::operator--(int){
    vec::vec2<T> copy = *this;
    operator--();
    return copy;
}

template<typename T>
vec::vec2<T>& vec::vec2<T>::operator+=(const vec::vec2<T>& vec){
    x += vec.x;
    y += vec.y;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator+=(const T v){
    x += v;
    y += v;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator-=(const vec::vec2<T>& vec){
    x -= vec.x;
    y -= vec.y;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator-=(const T v){
    x -= v;
    y -= v;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator*=(const vec::vec2<T>& vec){
    x *= vec.x;
    y *= vec.y;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator*=(const T v){
    x *= v;
    y *= v;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator/=(const vec::vec2<T>& vec){
    x /= vec.x;
    y /= vec.y;
    return *this;
}
template<typename T>
vec::vec2<T>& vec::vec2<T>::operator/=(const T v){
    x /= v;
    y /= v;
    return *this;
}

template<typename T>
vec::vec2<T> vec::vec2<T>::operator+() const{
    return *this;
}
template<typename T>
vec::vec2<T> vec::vec2<T>::operator-() const{
    return vec::vec2<T>(-x, -y);
}

template<typename T>
bool vec::vec2<T>::operator==(const vec::vec2<T>& vec) const{
    return (x == vec.x) && (y == vec.y);
}

template<typename T>
vec::vec2<T> operator+(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(lhs) += rhs;
}
template<typename T>
vec::vec2<T> operator-(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(lhs) -= rhs;
}
template<typename T>
vec::vec2<T> operator*(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(lhs) *= rhs;
}
template<typename T>
vec::vec2<T> operator/(const vec::vec2<T>& lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(lhs) /= rhs;
}

template<typename T>
vec::vec2<T> operator+(const vec::vec2<T>& lhs, const T rhs){
    return vec::vec2<T>(lhs) += rhs;
}
template<typename T>
vec::vec2<T> operator-(const vec::vec2<T>& lhs, const T rhs){
    return vec::vec2<T>(lhs) -= rhs;
}
template<typename T>
vec::vec2<T> operator*(const vec::vec2<T>& lhs, const T rhs){
    return vec::vec2<T>(lhs) *= rhs;
}
template<typename T>
vec::vec2<T> operator/(const vec::vec2<T>& lhs, const T rhs){
    return vec::vec2<T>(lhs) /= rhs;
}

template<typename T>
vec::vec2<T> operator+(const T lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(rhs) += lhs;
}
template<typename T>
vec::vec2<T> operator-(const T lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(rhs) -= lhs;
}
template<typename T>
vec::vec2<T> operator*(const T lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(rhs) *= lhs;
}
template<typename T>
vec::vec2<T> operator/(const T lhs, const vec::vec2<T>& rhs){
    return vec::vec2<T>(rhs) /= lhs;
}

template<typename T>
vec::vec2<T> abs(const vec::vec2<T>& vec){
    return vec2(std::abs(vec.x), std::abs(vec.y));
}
template<typename T>
T dot(const vec::vec2<T>& vA, const vec::vec2<T>& vB){
    return vA.x * vB.x + vA.y * vB.y;
}
template<typename T>
T length(const vec::vec2<T>& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
template<typename T>
T sqlength(const vec::vec2<T>& vec){
    return vec.x * vec.x + vec.y * vec.y;
}
template<typename T>
vec::vec2<T> normalize(const vec::vec2<T>& vec){
    return vec / length(vec);
}

// ---- vec::vec3 ---- //

template<typename T>
vec::vec3<T>::vec3(const T v)
: x(v), y(v), z(v){
}

template<typename T>
vec::vec3<T>::vec3(const T ix, const T iy, const T iz)
: x(ix), y(iy), z(iz){
}

template<typename T>
template<typename otherT>
vec::vec3<T>::vec3(const vec::vec3<otherT>& vec)
: x(vec.x), y(vec.y), z(vec.z){
}
template<typename T>
template<typename otherT>
vec::vec3<T>& vec::vec3<T>::operator=(const vec::vec3<otherT>& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

template<typename T>
vec::vec3<T>& vec::vec3<T>::operator++(){
    ++x;
    ++y;
    ++z;
}
template<typename T>
vec::vec3<T> vec::vec3<T>::operator++(int){
    vec::vec3<T> copy = *this;
    operator++();
    return copy;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator--(){
    --x;
    --y;
    --z;
}
template<typename T>
vec::vec3<T> vec::vec3<T>::operator--(int){
    vec::vec3<T> copy = *this;
    operator--();
    return copy;
}

template<typename T>
vec::vec3<T>& vec::vec3<T>::operator+=(const vec::vec3<T>& vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator+=(const T v){
    x += v;
    y += v;
    z += v;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator-=(const vec::vec3<T>& vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator-=(const T v){
    x -= v;
    y -= v;
    z -= v;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator*=(const vec::vec3<T>& vec){
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator*=(const T v){
    x *= v;
    y *= v;
    z *= v;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator/=(const vec::vec3<T>& vec){
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}
template<typename T>
vec::vec3<T>& vec::vec3<T>::operator/=(const T v){
    x /= v;
    y /= v;
    z /= v;
    return *this;
}

template<typename T>
vec::vec3<T> vec::vec3<T>::operator+() const{
    return *this;
}
template<typename T>
vec::vec3<T> vec::vec3<T>::operator-() const{
    return vec::vec3<T>(-x, -y, -z);
}

template<typename T>
bool vec::vec3<T>::operator==(const vec::vec3<T>& vec) const{
    return (x == vec.x) && (y == vec.y) && (z == vec.z);
}

template<typename T>
vec::vec3<T> operator+(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(lhs) += rhs;
}
template<typename T>
vec::vec3<T> operator-(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(lhs) -= rhs;
}
template<typename T>
vec::vec3<T> operator*(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(lhs) *= rhs;
}
template<typename T>
vec::vec3<T> operator/(const vec::vec3<T>& lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(lhs) /= rhs;
}

template<typename T>
vec::vec3<T> operator+(const vec::vec3<T>& lhs, const T rhs){
    return vec::vec3<T>(lhs) += rhs;
}
template<typename T>
vec::vec3<T> operator-(const vec::vec3<T>& lhs, const T rhs){
    return vec::vec3<T>(lhs) -= rhs;
}
template<typename T>
vec::vec3<T> operator*(const vec::vec3<T>& lhs, const T rhs){
    return vec::vec3<T>(lhs) *= rhs;
}
template<typename T>
vec::vec3<T> operator/(const vec::vec3<T>& lhs, const T rhs){
    return vec::vec3<T>(lhs) /= rhs;
}

template<typename T>
vec::vec3<T> operator+(const T lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(rhs) += lhs;
}
template<typename T>
vec::vec3<T> operator-(const T lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(rhs) -= lhs;
}
template<typename T>
vec::vec3<T> operator*(const T lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(rhs) *= lhs;
}
template<typename T>
vec::vec3<T> operator/(const T lhs, const vec::vec3<T>& rhs){
    return vec::vec3<T>(rhs) /= lhs;
}

template<typename T>
vec::vec3<T> abs(const vec::vec3<T>& vec){
    return vec3(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z));
}
template<typename T>
T dot(const vec::vec3<T>& vA, const vec::vec3<T>& vB){
    return vA.x * vB.x + vA.y * vB.y + vA.z * vB.z;
}
template<typename T>
vec::vec3<T> cross(const vec::vec3<T>& vA, const vec::vec3<T>& vB){
    return vec::vec3<T>(vA.y * vB.z - vA.z * vB.y,
                vA.z * vB.x - vA.x * vB.z,
                vA.x * vB.y - vA.y * vB.x);
}
template<typename T>
T length(const vec::vec3<T>& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
template<typename T>
T sqlength(const vec::vec3<T>& vec){
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}
template<typename T>
vec::vec3<T> normalize(const vec::vec3<T>& vec){
    return vec / length(vec);
}

// ---- vec::vec4 ---- //

template<typename T>
vec::vec4<T>::vec4(const T v)
: x(v), y(v), z(v), w(v){
}

template<typename T>
vec::vec4<T>::vec4(const T ix, const T iy, const T iz, const T iw)
: x(ix), y(iy), z(iz), w(iw){
}

template<typename T>
template<typename otherT>
vec::vec4<T>::vec4(const vec::vec4<otherT>& vec)
: x(vec.x), y(vec.y), z(vec.z), w(vec.w){
}
template<typename T>
template<typename otherT>
vec::vec4<T>& vec::vec4<T>::operator=(const vec::vec4<otherT>& vec){
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
}

template<typename T>
vec::vec4<T>& vec::vec4<T>::operator++(){
    ++x;
    ++y;
    ++z;
    ++w;
}
template<typename T>
vec::vec4<T> vec::vec4<T>::operator++(int){
    vec::vec4<T> copy = *this;
    operator++();
    return copy;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator--(){
    --x;
    --y;
    --z;
    --w;
}
template<typename T>
vec::vec4<T> vec::vec4<T>::operator--(int){
    vec::vec4<T> copy = *this;
    operator--();
    return copy;
}

template<typename T>
vec::vec4<T>& vec::vec4<T>::operator+=(const vec::vec4<T>& vec){
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator+=(const T v){
    x += v;
    y += v;
    z += v;
    w += v;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator-=(const vec::vec4<T>& vec){
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator-=(const T v){
    x -= v;
    y -= v;
    z -= v;
    w -= v;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator*=(const vec::vec4<T>& vec){
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator*=(const T v){
    x *= v;
    y *= v;
    z *= v;
    w *= v;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator/=(const vec::vec4<T>& vec){
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    w /= vec.w;
    return *this;
}
template<typename T>
vec::vec4<T>& vec::vec4<T>::operator/=(const T v){
    x /= v;
    y /= v;
    z /= v;
    w /= v;
    return *this;
}

template<typename T>
vec::vec4<T> vec::vec4<T>::operator+() const{
    return *this;
}
template<typename T>
vec::vec4<T> vec::vec4<T>::operator-() const{
    return vec::vec4<T>(-x, -y, -z, -w);
}

template<typename T>
bool vec::vec4<T>::operator==(const vec::vec4<T>& vec) const{
    return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

template<typename T>
vec::vec4<T> operator+(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(lhs) += rhs;
}
template<typename T>
vec::vec4<T> operator-(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(lhs) -= rhs;
}
template<typename T>
vec::vec4<T> operator*(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(lhs) *= rhs;
}
template<typename T>
vec::vec4<T> operator/(const vec::vec4<T>& lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(lhs) /= rhs;
}

template<typename T>
vec::vec4<T> operator+(const vec::vec4<T>& lhs, const T rhs){
    return vec::vec4<T>(lhs) += rhs;
}
template<typename T>
vec::vec4<T> operator-(const vec::vec4<T>& lhs, const T rhs){
    return vec::vec4<T>(lhs) -= rhs;
}
template<typename T>
vec::vec4<T> operator*(const vec::vec4<T>& lhs, const T rhs){
    return vec::vec4<T>(lhs) *= rhs;
}
template<typename T>
vec::vec4<T> operator/(const vec::vec4<T>& lhs, const T rhs){
    return vec::vec4<T>(lhs) /= rhs;
}

template<typename T>
vec::vec4<T> operator+(const T lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(rhs) += lhs;
}
template<typename T>
vec::vec4<T> operator-(const T lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(rhs) -= lhs;
}
template<typename T>
vec::vec4<T> operator*(const T lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(rhs) *= lhs;
}
template<typename T>
vec::vec4<T> operator/(const T lhs, const vec::vec4<T>& rhs){
    return vec::vec4<T>(rhs) /= lhs;
}

template<typename T>
vec::vec4<T> abs(const vec::vec4<T>& vec){
    return vec4(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z), std::abs(vec.w));
}
template<typename T>
T dot(const vec::vec4<T>& vA, const vec::vec4<T>& vB){
    return vA.x * vB.x + vA.y * vB.y + vA.z * vB.z + vA.w * vB.w;
}
template<typename T>
T length(const vec::vec4<T>& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}
template<typename T>
T sqlength(const vec::vec4<T>& vec){
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}
template<typename T>
vec::vec4<T> normalize(const vec::vec4<T>& vec){
    return vec / length(vec);
}

#endif
