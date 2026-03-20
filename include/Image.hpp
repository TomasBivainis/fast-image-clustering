#pragma once

#include <vector>
#include "Vec3.hpp"

class Image {
private:
    int rows;
    int columns;
    std::vector<std::vector<Vec3>> image;
public:
    Image(cv::Mat image);

    int getRows(); 

    int getColumns(); 

    std::vector<std::vector<Vec3>>& getImage(); 

    Vec3 getPoint(int row, int column); 

    cv::Mat* convertToMat(); 

    void setPoint(int row, int column, Vec3 newColor); 
};