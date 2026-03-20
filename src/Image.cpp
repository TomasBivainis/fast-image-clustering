#include "Image.hpp"

Image::Image(cv::Mat image) {
    this -> rows = image.rows;
    this -> columns = image.cols;

    (this -> image) = std::vector<std::vector<Vec3>>(rows, std::vector<Vec3>(columns));

    for(int i = 0; i < image.rows; i++) {
        for(int j = 0; j < image.cols; j++) {
            this -> image[i][j] = Vec3(image.at<cv::Vec3b>(i, j));
        }
    }
}

int Image::getRows() {
    return rows;
}

int Image::getColumns() {
    return columns;
}

std::vector<std::vector<Vec3>>& Image::getImage() {
    return image;
}

Vec3 Image::getPoint(int row, int column) {
    return image[row][column];
}

cv::Mat* Image::convertToMat() {
    cv::Mat* converted_image = new cv::Mat(cv::Size(columns, rows), CV_8UC3);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            converted_image -> at<cv::Vec3b>(i, j) = this -> image[i][j].convertToVec3b();
        }
    }
    
    return converted_image;
}

void Image::setPoint(int row, int column, Vec3 newColor) {
    this -> image[row][column] = newColor;
}