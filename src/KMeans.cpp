#include "KMeans.hpp"
#include <Centroid.hpp>
#include <stdlib.h>

void KMeans::train(Image* image, std::vector<Centroid*>& centroids) {
    for(int k = 0; k < centroids.size(); k++) {
        (*centroids[k]).clearPoints();
    }

    for(int i = 0; i < (*image).getRows(); i++) {
        for(int j = 0; j < (*image).getColumns(); j++) {
            Vec3 currentPoint = (*image).getPoint(i, j);
            Centroid* currentCentroid = centroids[0];
            float smallestDistance = (*currentCentroid).distance(currentPoint);

            for(int k = 1; k < centroids.size(); k++) {
                float temp = (*centroids[k]).distance(currentPoint);

                if(temp < smallestDistance) {
                    currentCentroid = centroids[k];
                    smallestDistance = temp;
                }
            }

            (*currentCentroid).addPoint(currentPoint);
        }
    }

    for(int k = 0; k < centroids.size(); k++) {
        (*centroids[k]).calculateCentroid();
    }
}

void KMeans::initializeCentroidList(std::vector<Centroid*>& centroids, int k, Image* image) {
    std::srand(time(0));

    for(int i = 0; i < k; i++) {
        centroids.push_back(new Centroid(image -> getPoint(rand() % image -> getRows(), rand() % image -> getColumns())));
    }
}

void KMeans::repaintImage(Image* image, std::vector<Centroid*>& centroids) {
    for(int i = 0; i < (*image).getRows(); i++) {
        for(int j = 0; j < (*image).getColumns(); j++) {
            Vec3 currentPoint = (*image).getPoint(i, j);
            Centroid* currentCentroid = centroids[0];
            float smallestDistance = (*currentCentroid).distance(currentPoint);

            for(int k = 1; k < centroids.size(); k++) {
                float temp = (*centroids[k]).distance(currentPoint);

                if(temp < smallestDistance) {
                    currentCentroid = centroids[k];
                    smallestDistance = temp;
                }
            }

            image -> setPoint(i, j, currentCentroid -> getCentroid());
        }
    }
}

void KMeans::cluster_image(Image* image, int k, int epochs) {
    std::vector<Centroid*> centroids;

    initializeCentroidList(centroids, k, image);
       
    for(int i = 0; i < epochs; i++) {
        train(image, centroids);
    }

    // for(int i = 0; i < centroids.size(); i++) {
    //     (*centroids[i]).getCentroid().print();
    // }

    repaintImage(image, centroids);

    for(int k = 0; k < centroids.size(); k++) {
        free(centroids[k]);
    }
}