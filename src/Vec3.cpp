#include "Vec3.hpp"
#include <stdexcept>
#include <iostream>

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(cv::Vec3b vector) : x(static_cast<float>(vector[0])), y(static_cast<float>(vector[1])), z(static_cast<float>(vector[2])) {}

float Vec3::operator[](int i) const {
    switch (i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::runtime_error("Index out of bounds");
    }
}

Vec3 Vec3::operator+(const Vec3 &v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3& Vec3::operator+=(const Vec3 &v) {
    (*this) = Vec3(x + v.x, y + v.y, z + v.z);
    return *this;
}

Vec3 Vec3::operator-(const Vec3 &v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3& Vec3::operator-=(const Vec3 &v) {
    (*this) = Vec3(x - v.x, y - v.y, z - v.z);
    return *this;
}

Vec3 Vec3::operator*(const float &c) const {
    return Vec3(x * c, y * c, z * c);
}

Vec3& Vec3::operator*=(const float &c) {
    (*this) = Vec3(x * c, y * c, z * c);
    return *this;
}

Vec3 Vec3::operator/(const float &c) const {
    return Vec3(x / c, y / c, z / c);
}

Vec3& Vec3::operator/=(const float &c) {
    (*this) = Vec3(x / c, y / c, z / c);
    return *this;
}

float Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalized() const {
    float len = length();
    return Vec3(x / len, y / len, z / len);
}

Vec3& Vec3::normalize() {
    (*this) /= length();
    return *this;
}

cv::Vec3b Vec3::convertToVec3b() {
    return cv::Vec3b({static_cast<uchar>(x), static_cast<uchar>(y), static_cast<u_char>(z)});
}

void Vec3::print() {
    std::cout << x << " " << y << " " << z << std::endl;
}

float Vec3::dot(Vec3 v) {
    return x * v[0] + y * v[1] + z * v[2];
}