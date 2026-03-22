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
    if(argc < 4) {
        std::cout << "Not enough arguments" << std::endl;

        return -1;
    } 
    
    char *filename = argv[1];
    int k = std::stoi(argv[2]);
    int epochs = std::stoi(argv[3]);

    cv::Mat opencv_image = cv::imread(filename);

    Image *image = new Image(opencv_image);

    KMeans::cluster_image(image, k, epochs);

    cv::imshow("image", *image -> convertToMat());
    cv::waitKey(0);

    free(image); 

    return 0;
}