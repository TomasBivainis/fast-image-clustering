#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3() : x(0), y(0), z(0) {
    }

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {
    }

    Vec3(cv::Vec3b vector) : x(static_cast<float>(vector[0])), y(static_cast<float>(vector[1])), z(static_cast<float>(vector[2])) {
    }

    float operator[](int i) const {
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

    Vec3 operator+(const Vec3 &v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3& operator+=(const Vec3 &v) {
        (*this) = Vec3(x + v.x, y + v.y, z + v.z);
        return *this;
    }

    Vec3 operator-(const Vec3 &v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3& operator-=(const Vec3 &v) {
        (*this) = Vec3(x - v.x, y - v.y, z - v.z);
        return *this;
    }

    Vec3 operator*(const float &c) const {
        return Vec3(x * c, y * c, z * c);
    }

    Vec3& operator*=(const float &c) {
        (*this) = Vec3(x * c, y * c, z * c);
        return *this;
    }
    
    Vec3 operator/(const float &c) const {
        return Vec3(x / c, y / c, z / c);
    }

    Vec3& operator/=(const float &c) {
        (*this) = Vec3(x / c, y / c, z / c);
        return *this;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalized() const {
        float len = length();
        return Vec3(x / len, y / len, z / len);
    }

    Vec3& normalize() {
        (*this) /= length();
        return *this;
    }

    cv::Vec3b convertToVec3b() {
        return cv::Vec3b({static_cast<uchar>(x), static_cast<uchar>(y), static_cast<u_char>(z)});
    }

    void print() {
        std::cout << x << " " << y << " " << z << std::endl;
    }

    float dot(Vec3 v) {
        return x * v[0] + y * v[1] + z * v[2];
    }
};

class Image {
private:
    int rows;
    int columns;
    // cv::Mat image;
    std::vector<std::vector<Vec3>> image;
public:
    // Image(std::string filename) {
    //    image = cv::imread(filename, cv::IMREAD_COLOR_BGR); 

    //     if(image.empty()) throw new std::runtime_error("No image found");

    //     width = image.size().width;
    //     height = image.size().height;
    // }

    Image(cv::Mat image) {
        this -> rows = image.rows;
        this -> columns = image.cols;

        (this -> image) = std::vector<std::vector<Vec3>>(rows, std::vector<Vec3>(columns));

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                this -> image[i][j] = Vec3(image.at<cv::Vec3b>(i, j));
            }
        }
    }

    int getRows() {
        return rows;
    }

    int getColumns() {
        return columns;
    }

    std::vector<std::vector<Vec3>>& getImage() {
        return image;
    }

    Vec3 getPoint(int row, int column) {
        return image[row][column];
    }

    cv::Mat* convertToMat() {
        cv::Mat* converted_image = new cv::Mat(cv::Size(columns, rows), CV_8UC3);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                converted_image -> at<cv::Vec3b>(i, j) = this -> image[i][j].convertToVec3b();
            }
        }
        
        return converted_image;
    }

    void setPoint(int row, int column, Vec3 newColor) {
        this -> image[row][column] = newColor;
    }
};

class Centroid {
private:
    std::vector<Vec3> points;
    Vec3 centroid;
public:
    Centroid() : points(std::vector<Vec3>()), centroid(Vec3(0, 0, 0)) {
    }

    Centroid(Vec3 centroid) : centroid(centroid), points(std::vector<Vec3>()){
    }

    void addPoint(Vec3 point) {
        points.push_back(point);
    }

    void setCentroid(Vec3 centroid) {
        this -> centroid = centroid;
    }

    void calculateCentroid() {
        centroid = Vec3(0, 0, 0);

        for(int i = 0; i < points.size(); i++) {
            centroid += points[i];
        }

        if(points.size() > 0) centroid /= static_cast<float>(points.size());
    }

    void clearPoints() {
        points.clear();
    }

    float distance(const Vec3 &point) {
        return std::sqrtf((centroid - point).dot(centroid - point));
    }

    Vec3 getCentroid() {
        return centroid;
    }
};

void train(Image* image, std::vector<Centroid*>& centroids) {
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

void initializeCentroidList(std::vector<Centroid*>& centroids, int k, Image* image) {
    std::srand(time(0));

    for(int i = 0; i < k; i++) {
        centroids.push_back(new Centroid(image -> getPoint(rand() % image -> getRows(), rand() / image -> getColumns())));
    }
}

void repaintImage(Image* image, std::vector<Centroid*>& centroids) {
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

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Not enough arguments" << std::endl;

        std::cin.get();
        return -1;
    } 
    
    char *filename = argv[1];

    cv::Mat opencv_image = cv::imread(filename);

    Image *image = new Image(opencv_image);

    Vec3 point1 = image -> getPoint(0, 0);
    Vec3 point2 = image -> getPoint(0, 1);

    point1.print();
    point2.print();

    point1 += point2;
    
    point1.print();

    point1 = point1 - point2;

    point1.print();

    point1 = point1 * 10;

    point1.print();

    point1.normalize().normalize();

    point1.print();

    std::cout << point1.length() << std::endl;

    std::cout << point1[0] << std::endl;

    ((point1 += point2) - point2).print();
    point1.print(); 

    std::vector<Centroid*> centroids;

    initializeCentroidList(centroids, 3, image);
       
    for(int i = 0; i < 3; i++) {
        std::cout << "train " << i << std::endl;
        train(image, centroids);
    }

    std::cout << "trained" << std::endl;

    for(int i = 0; i < centroids.size(); i++) {
        (*centroids[i]).getCentroid().print();
    }

    std::cout << "Paining" << std::endl;
    repaintImage(image, centroids);

    cv::imshow("image", *image -> convertToMat());
    cv::waitKey(0);

    free(image);
    for(int k = 0; k < centroids.size(); k++) {
        free(centroids[k]);
    }

    return 0;
}