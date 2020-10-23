#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
    //read image data
    cv::Mat src = cv::imread("photo.jpg", cv::IMREAD_COLOR);
  
    //quit program if image reading failed
    if(src.empty())
    {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }
  
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", src);
    cv::waitKey(0);
    cv::destroyAllWindows();
  
    return 0;
}
