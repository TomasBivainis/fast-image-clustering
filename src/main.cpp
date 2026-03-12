#include <iostream>
#include <stdexcept>
#include <vector>
#include <opencv2/opencv.hpp>

class Vec3 {
public:
    int x;
    int y;
    int z;

    Vec3() : x(0), y(0), z(0) {
    }

    Vec3(int x, int y, int z) : x(x), y(y), z(z) {
    }

    Vec3(cv::Vec3b vector) : x(vector[0]), y(vector[1]), z(vector[2]) {
    }

    int operator[](int i){
        switch (i){
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw new std::runtime_error("Index out of bounds");
        }
    }

    Vec3 operator+(const Vec3 &v) {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3 &v) {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(const float &c) {
        return Vec3(static_cast<int>(static_cast<float>(x) * c), static_cast<int>(static_cast<float>(y) * c), static_cast<int>(static_cast<float>(z) * c));
    }

    Vec3 operator/(const float &c) {
        return Vec3(static_cast<int>(static_cast<float>(x) / c), static_cast<int>(static_cast<float>(y) / c), static_cast<int>(static_cast<float>(z) / c));
    }

    float length() {
        return 
    }

    Vec3 normalize() {

    }

    void print() {
        std::cout << x << " " << y << " " << z << std::endl;
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

    Vec3 getPoint(int row, int column) {
        return Vec3(image.at<cv::Vec3b>(row, column));
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

    Vec3 point1 = image -> getPoint(0, 0);
    Vec3 point2 = image -> getPoint(0, 1);

    point1.print();
    point2.print();

    point1 = point1 + point2;
    
    point1.print();

    point1 = point1 - point2;

    point1.print();

    point1 = point1 * 10;

    point1.print();

    std::cout << point1[0] << std::endl;

    cv::imshow("image", image -> getImage());
    cv::waitKey(0);

    return 0;
}