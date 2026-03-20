#pragma once
#include <vector>
#include "Vec3.hpp"
#include "Centroid.hpp"
#include "Image.hpp"

namespace KMeans {
    void train(Image* image, std::vector<Centroid*>& centroids); 
    void initializeCentroidList(std::vector<Centroid*>& centroids, int k, Image* image); 
    void repaintImage(Image* image, std::vector<Centroid*>& centroids); 
    void cluster_image(Image* image, int k, int epochs); 
}