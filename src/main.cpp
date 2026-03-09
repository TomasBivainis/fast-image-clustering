#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Not enough arguments" << std::endl;

        std::cin.get();
        return -1;
    } 
    
    char *filename = argv[1];

    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR_RGB);

    if(image.empty()) {
        std::cout << "Image not found" << std::endl;

        std::cin.get();
        return -1;
    }

    cv::imshow("image", image);
    cv::waitKey(0);

    return 0;
}