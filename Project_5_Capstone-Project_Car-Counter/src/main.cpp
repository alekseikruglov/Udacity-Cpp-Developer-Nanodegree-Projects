#include <string>

#include "VideoProcessing.h"

int main() 
{

    VideoProcessing vp("../data/0-10s_.mp4");    
    vp.startVideoProcessing();

    cv::waitKey(0);

    return 0;
}