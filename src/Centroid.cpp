#include "Centroid.hpp"

Centroid::Centroid() : points(std::vector<Vec3>()), centroid(Vec3(0, 0, 0)) {
}

Centroid::Centroid(Vec3 centroid) : centroid(centroid), points(std::vector<Vec3>()){
}

void Centroid::addPoint(Vec3 point) {
    points.push_back(point);
}

void Centroid::setCentroid(Vec3 centroid) {
    this -> centroid = centroid;
}

void Centroid::calculateCentroid() {
    centroid = Vec3(0, 0, 0);

    for(int i = 0; i < points.size(); i++) {
        centroid += points[i];
    }

    if(points.size() > 0) centroid /= static_cast<float>(points.size());
}

void Centroid::clearPoints() {
    points.clear();
}

float Centroid::distance(const Vec3 &point) {
    return std::sqrtf((centroid - point).dot(centroid - point));
}

Vec3 Centroid::getCentroid() {
    return centroid;
}