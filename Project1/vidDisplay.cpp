//
//  vidDisplay.cpp
//  Project1
//
//  Created by DB on 2/5/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vidDisplay.h"
#include "filter.h"

int displayLiveVideoFeed(cv::VideoCapture *capdev){
    cv::namedWindow("Live Video", 1);
    cv::Mat originalFrame;
    // filtered frame / modified frame
    cv::Mat filteredFrame;
    // get some properties of the image
   cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                  (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
   printf("Expected size: %d %d\n", refS.width, refS.height);
    
    // turn filter on/off
    bool filterOn;
    // store the char for the filter selected
    char lastFilterSelected;
    filterOn = false;
    // o --> original
    lastFilterSelected = 'o';
    for(;;) {
        *capdev >> originalFrame; // get a new frame from the camera, treat as a stream
        if(originalFrame.empty()) {
            printf("Frame is empty\n");
            break;
        }
        //if filter is on display filter frame
        if (filterOn && lastFilterSelected != 'o') {
            if(lastFilterSelected == 'g'){
                opencvGreyscale(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == 'h'){
                greyscale(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == 'b'){
                blur5x5(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == 'x'){
                sobelX3x3(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == 'y'){
                sobelY3x3(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == 'm'){
                cv::Mat sx,sy;
                sobelX3x3(originalFrame, sx);
                sobelY3x3(originalFrame, sy);
                magnitude(sx, sy, filteredFrame);
            }
            else if (lastFilterSelected == 'i'){
                int levels;
                levels = 10;
                blurQuantize(originalFrame, filteredFrame, levels);
            }
            else if (lastFilterSelected == 'c'){
                int levels, magThreshold;
                levels = 10;
                magThreshold = 20;
                cartoon(originalFrame, filteredFrame, levels, magThreshold);
            }
            else if (lastFilterSelected == '+'){
                increaseBrightness(originalFrame, filteredFrame);
            }
            else if (lastFilterSelected == '-'){
                decreaseBrightness(originalFrame, filteredFrame);
            }
            originalFrame = filteredFrame;
        }
        cv::imshow("Live Video", originalFrame);
        
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if( key == 'q') {
            // to quit
            delete capdev;
            cv::destroyWindow("Live Video");
            return 0;
        }
        else if (key == 's'){
            // to save a frame
            std::string filename;
            filename = currentDateTime();
            filename = filename.append(".jpeg");
            cv::imwrite(filename, originalFrame);
            printf("Screenshot saved!\n");
        }
        // get original feed in color
        else if (key == 'o'){
            filterOn = false;
            lastFilterSelected = key;
        }
        else if (key == 'g'){
            // turning grey filter on and off
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == 'h'){
            // alternative grey filter
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == 'b'){
            // gausian 5x5 blur filter
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == 'x'){
            // X Sobel
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == 'y'){
            // Y Sobel
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == 'm'){
            // color gradient
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if(key == 'i'){
            // blur and qunatize a color image
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if(key == 'c'){
            // blur and qunatize a color image
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '+'){
            // increase brightness by 50
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '-'){
            // decrease brightness by 50
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
    }
    return 0;
}

// method to get current date and time so we can use it name the screenshot and save it.
const std::string currentDateTime() {
    // Current date/time based on current system
    time_t now = time(0);
    struct tm  tstruct;
    char temp[80];
    // Convert now to tm struct for local timezone
    tstruct = *localtime(&now);
    strftime(temp, sizeof(temp), "%Y-%m-%d %X", &tstruct);
    return temp;
}
