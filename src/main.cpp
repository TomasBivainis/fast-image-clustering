#include <iostream>
#include <stdexcept>
#include <vector>
#include <opencv2/opencv.hpp>

class Helper {
public:
    static void printPoint(std::vector<int> point) {
        for(int i = 0; i < point.size(); i++) {
            std::cout << point[i] << " ";
        }

        std::cout << std::endl;
    }
};

class Image {
private:
    int width;
    int height;
    cv::Mat image;
public:
    Image(std::string filename) {
       image = cv::imread(filename, cv::IMREAD_COLOR_BGR); 

        if(image.empty()) throw new std::runtime_error("No image found");

        width = image.size().width;
        height = image.size().height;
    }

    Image(cv::Mat image) {
        this -> image = image;
        width = image.size().width;
        height = image.size().height;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    cv::Mat getImage() {
        return image;
    }

    std::vector<int> getPoint(int row, int column) {
        cv::Vec3b point = image.at<cv::Vec3b>(row, column);
        std::vector<int> castedPoint(3);
        
        for(size_t i = 0; i < 3; i++) {
            castedPoint[i] = static_cast<int>(point[i]);
        }

        return castedPoint; 
    }
};

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Not enough arguments" << std::endl;

        std::cin.get();
        return -1;
    } 
    
    char *filename = argv[1];

    Image *image = new Image(filename);

    Helper::printPoint((image -> getPoint(0, 0)));

    cv::imshow("image", image -> getImage());
    cv::waitKey(0);

    return 0;
}