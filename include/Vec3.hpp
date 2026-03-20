#pragma once

#include <opencv2/opencv.hpp>

class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3();

    Vec3(float x, float y, float z);

    Vec3(cv::Vec3b vector);

    float operator[](int i) const; 

    Vec3 operator+(const Vec3 &v) const; 

    Vec3& operator+=(const Vec3 &v); 

    Vec3 operator-(const Vec3 &v) const; 

    Vec3& operator-=(const Vec3 &v); 

    Vec3 operator*(const float &c) const; 

    Vec3& operator*=(const float &c); 
    
    Vec3 operator/(const float &c) const;

    Vec3& operator/=(const float &c); 

    float length() const; 

    Vec3 normalized() const; 

    Vec3& normalize(); 

    cv::Vec3b convertToVec3b(); 

    void print(); 

    float dot(Vec3 v); 
};