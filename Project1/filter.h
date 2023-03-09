//
//  filter.h
//  Project1
//
//  Created by DB on 2/5/23.
//

int greyscale( cv::Mat &src, cv::Mat &dst );

int opencvGreyscale( cv::Mat &src, cv::Mat &dst );

int blur5x5( cv::Mat &src, cv::Mat &dst );

int sobelX3x3( cv::Mat &src, cv::Mat &dst );

int sobelY3x3( cv::Mat &src, cv::Mat &dst );

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );

int increaseBrightness( cv::Mat &src, cv::Mat&dst );

int decreaseBrightness( cv::Mat &src, cv::Mat&dst );
