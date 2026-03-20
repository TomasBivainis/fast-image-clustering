#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "Vec3.hpp"
#include "Image.hpp"
#include "Centroid.hpp"
#include "KMeans.hpp"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Not enough arguments" << std::endl;

        std::cin.get();
        return -1;
    } 
    
    char *filename = argv[1];

    cv::Mat opencv_image = cv::imread(filename);

    Image *image = new Image(opencv_image);

    KMeans::cluster_image(image, 8, 3);

    cv::imshow("image", *image -> convertToMat());
    cv::waitKey(0);

    free(image); 

    return 0;
}