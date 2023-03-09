//
//  main.cpp
//  Project1
//
//  Created by DB on 2/4/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "imgDisplay.h"
#include "vidDisplay.h"

int main(int argc,char *argv[]){
    // code execution starts here
    std::printf("Welcome to Project-1\n");
    std::printf("Enter the name of the image you want to import:\n");
    char nameOfImage[256];
    // get user input for image
    std::scanf("%s",nameOfImage);
    cv::Mat src;
    // read image data
    src = cv::imread(nameOfImage);
    // if no data then quit with a message
    if(src.data == NULL){
        std::printf("Incorrect filename: %s\n",nameOfImage);
        exit(-1);
    }
    // call method to display the image in a window
    displayImage(src);
    
    // capturing device for LIVE VIDEO FEED
    cv::VideoCapture *capdev;
    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
            printf("Unable to open video device\n");
            return(-1);
    }
    // liveEnded = 1  ----> not ended
    // liveEnded = 0  ----> ended
    int liveEnded = 1;
    liveEnded = displayLiveVideoFeed(capdev);
    // for loop to keep the program running
    for(;;){
        // check if live ended
        if(liveEnded == 0){
            std::printf("Quitting\n");
            break;
        }
        // wait for a key press
        char key;
        key = (char) cv::waitKey(0);
        // handle quit condition
        if(key == 'q'){
            std::printf("Quitting\n");
            break;
        }
        // handle wrong key stroke
        else{
            std::printf("Wrong Key Entered: %c\n",key);
        }
    }
    cv::destroyAllWindows();
    return 0;
}
