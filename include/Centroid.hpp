#pragma once

#include <vector>
#include "Vec3.hpp"

class Centroid {
private:
    std::vector<Vec3> points;
    Vec3 centroid;
public:
    Centroid();

    Centroid(Vec3 centroid);

    void addPoint(Vec3 point);

    void setCentroid(Vec3 centroid); 

    void calculateCentroid(); 

    void clearPoints(); 

    float distance(const Vec3 &point);

    Vec3 getCentroid(); 
};