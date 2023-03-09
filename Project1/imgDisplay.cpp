//
//  imgDisplay.cpp
//  Project1
//
//  Created by DB on 2/4/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "imgDisplay.h"


// method to display a image from the file in a window
// input - image data as a Mat
int displayImage(cv::Mat &src){

    // create a window
    cv::namedWindow("Default Image",1);
    
    // show the window and image
    cv::imshow("Default Image", src);
    
    return 0;
}
