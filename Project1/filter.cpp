//
//  filter.cpp
//  Project1
//
//  Created by DB on 2/5/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "filter.h"

// task 4
int greyscale(cv::Mat &src, cv::Mat &dst){
    // initialize zeros
    dst = cv::Mat::zeros(src.rows,src.cols, CV_8U);
    // we will use the approach of computing the avg of bgr colors to form the greyscale img
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    // apply filter
    for(int i = 0; i < src.rows; i++){
       // iterate over rows
       cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
       uchar *dptr = dst.ptr<uchar>(i);
       // for each col
       for(int j = 0 ; j < src.cols; j++){
           // calculate the avg
           dptr[j] = (rptr[j][0]+rptr[j][1]+rptr[j][2])/3;
       }
    }
    return 0;
}

// task 3
int opencvGreyscale(cv::Mat &src, cv::Mat &dst){
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY );
    return 0;
}

// task 5
int blur5x5( cv::Mat &src, cv::Mat &dst ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    cv::Mat tempFrame;
    src.copyTo(tempFrame);
    src.copyTo(dst);
    // apply filter
    int seperableFilter[] = {1,2,4,2,1};
    // first we apply separable 1x5 filters [1 2 4 2 1] (i.e. Horizontally)
    for(int i = 2; i < src.rows - 2; i++){
        // get src and dst row pointers
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *dptr = tempFrame.ptr<cv::Vec3b>(i);
        for(int j = 2; j < src.cols-2; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptr[j-2][color]*seperableFilter[0]) + (rptr[j-1][color]*seperableFilter[1]) + (rptr[j][color]*seperableFilter[2]) + (rptr[j+1][color]*seperableFilter[3]) + (rptr[j+2][color]*seperableFilter[4]))/10;
            }
        }
    }
    // now we apply seperable filter vertically
    for(int i = 2; i < src.rows-2; i++){
        // get src and dst pointers
        cv::Vec3b *rptrm2 = tempFrame.ptr<cv::Vec3b>(i-2);
        cv::Vec3b *rptrm1 = tempFrame.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *rptr = tempFrame.ptr<cv::Vec3b>(i);
        cv::Vec3b *rptrp1 = tempFrame.ptr<cv::Vec3b>(i+1);
        cv::Vec3b *rptrp2 = tempFrame.ptr<cv::Vec3b>(i+2);
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);
        for(int j = 2; j < src.cols - 2; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptrm2[j][color]*seperableFilter[0]) + (rptrm1[j][color]*seperableFilter[1]) + (rptr[j][color]*seperableFilter[2]) + (rptrp1[j][color]*seperableFilter[3]) + (rptrp2[j][color]*seperableFilter[4]))/10;
            }
        }
    }
    
    return 0;
}

// task 6
int sobelX3x3( cv::Mat &src, cv::Mat &dst ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    // initialize to zero
    dst = cv::Mat::zeros(src.size(), CV_16SC3);
    cv::Mat temp = cv::Mat::zeros(src.size(), CV_16SC3);
    // vertical
    int x_v[] = {1,2,1};
    // horizontal
    int x_h[] = {1,0,-1};
    // apply hoizontal
    for(int i = 1; i < src.rows-1; i++){
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3s *dptr = temp.ptr<cv::Vec3s>(i);
        for(int j = 1; j < src.cols-1; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptr[j-1][color]*x_h[0])+(rptr[j][color]*x_h[1])+(rptr[j+1][color]*x_h[2]));
            }
        }
    }
    // apply vertical
    for(int i = 1; i < src.rows-1; i++){
        cv::Vec3s *rptrm1 = temp.ptr<cv::Vec3s>(i-1);
        cv::Vec3s *rptr = temp.ptr<cv::Vec3s>(i);
        cv::Vec3s *rptrp1 = temp.ptr<cv::Vec3s>(i+1);
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for(int j = 1; j < src.cols-1; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptrm1[j][color]*x_v[0])+(rptr[j][color]*x_v[1])+(rptrp1[j][color]*x_v[2]));
            }
        }
    }
    cv::convertScaleAbs(dst, dst, 2);
    return 0;
}

// task 6
int sobelY3x3( cv::Mat &src, cv::Mat &dst ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    // initialize to zero
    dst = cv::Mat::zeros(src.size(), CV_16SC3);
    cv::Mat temp = cv::Mat::zeros(src.size(), CV_16SC3);
    // vertical
    int y_v[] = {1,0,-1};
    // horizontal
    int y_h[] = {1,2,1};
    // apply hoizontal
    for(int i = 1; i < src.rows-1; i++){
        cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
        cv::Vec3s *dptr = temp.ptr<cv::Vec3s>(i);
        for(int j = 1; j < src.cols-1; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptr[j-1][color]*y_h[0])+(rptr[j][color]*y_h[1])+(rptr[j+1][color]*y_h[2]));
            }
        }
    }
    // apply vertical
    for(int i = 1; i < src.rows-1; i++){
        cv::Vec3s *rptrm1 = temp.ptr<cv::Vec3s>(i-1);
        cv::Vec3s *rptr = temp.ptr<cv::Vec3s>(i);
        cv::Vec3s *rptrp1 = temp.ptr<cv::Vec3s>(i+1);
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for(int j = 1; j < src.cols-1; j++){
            for(int color = 0; color < 3; color++){
                dptr[j][color] = ((rptrm1[j][color]*y_v[0])+(rptr[j][color]*y_v[1])+(rptrp1[j][color]*y_v[2]));
            }
        }
    }
    cv::convertScaleAbs(dst, dst);
    return 0;
}

// task 7
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ){
    if(!sx.data){
        std::printf("No data from Video Source Sx!\n");
        return -1;
    }
    if(!sy.data){
        std::printf("No data from Video Source Sy!\n");
        return -1;
    }
    if(sx.size() != sy.size()){
        std::printf("sx and sy do not have same size!\n");
        return -1;
    }
    cv::Mat newSx, newSy;
    sx.convertTo(newSx, CV_16SC3);
    sy.convertTo(newSy, CV_16SC3);
    dst = cv::Mat::zeros(newSx.rows, newSx.cols, CV_16SC3);
    for(int i = 0; i < newSx.rows; i++){
        cv::Vec3s *sxrptr = newSx.ptr<cv::Vec3s>(i);
        cv::Vec3s *syrptr = newSy.ptr<cv::Vec3s>(i);
        cv::Vec3s *drptr = dst.ptr<cv::Vec3s>(i);
        for(int j = 0; j < newSx.cols; j++){
            for(int color = 0; color < 3; color++){
                drptr[j][color] = sqrt((sxrptr[j][color])^2 + (syrptr[j][color])^2);
            }
        }
    }
    cv::convertScaleAbs(dst, dst, 4);
    return 0;
}

// task 8
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    cv::Mat blurFrame;
    // first we blur the frame
    blur5x5(src, blurFrame);
    blurFrame.convertTo(blurFrame, CV_16SC3);
    dst = cv::Mat::zeros(src.rows, src.cols, CV_16SC3);
    int sizeOfBucket = 255/levels;
    for(int i = 0; i < src.rows; i++){
        cv::Vec3s *rptr = blurFrame.ptr<cv::Vec3s>(i);
        cv::Vec3s *dptr = dst.ptr<cv::Vec3s>(i);
        for(int j = 0; j < src.cols; j++){
            for(int color = 0; color < 3; color++){
                double temp = rptr[j][color]/sizeOfBucket;
                dptr[j][color] = temp * sizeOfBucket;
            }
        }
    }
    dst.convertTo(dst, CV_8UC3);
    return 0;
}

// task 9
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    // first we find the gradient magnitude
    cv::Mat sx,sy,grad;
    sobelX3x3(src, sx);
    sobelY3x3(src, sy);
    magnitude(sx, sy, grad);
    // now we will apply blurQuantize
    blurQuantize(src, dst, levels);
    // now we will d quantized image by setting to black any pixels with a gradient
    // magnitude larger than a threshold.
    for(int i = 0; i < src.rows; i++){
        cv::Vec3b *gradptr = grad.ptr<cv::Vec3b>(i);
        cv::Vec3b *rptr = dst.ptr<cv::Vec3b>(i);
        for(int j = 0; j < dst.cols; j++){
            for(int color = 0; color < 3; color++){
                if(gradptr[j][color] > magThreshold){
                    rptr[j][color] = 0;
                }
            }
        }
    }
    dst.convertTo(dst, CV_8UC3);
    return 0;
}

// task 10
int increaseBrightness( cv::Mat &src, cv::Mat&dst ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    cv::Mat imageBrighnessHigh50;
    src.convertTo(dst, -1, 1, 50);
    return 0;
}

// task 10
int decreaseBrightness( cv::Mat &src, cv::Mat&dst ){
    if(!src.data){
        std::printf("No data from Video Source!\n");
        return -1;
    }
    cv::Mat imageBrighnessHigh50;
    src.convertTo(dst, -1, 1, -50);
    return 0;
}
