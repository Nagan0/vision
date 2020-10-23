#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
 
  //read image data
  cv::Mat image = cv::imread("chinese_food.jpg", cv::IMREAD_COLOR);

  //output image data
  cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

  //quit program if image reading failed
  if(image.empty())
  {
    std::cerr << "Failed to open image file." << std::endl;
    return -1;
  }


  //RGB to Gray
  for (int i = 0; i < image.cols; i++) {
    for (int j = 0; j < image.rows; j++){
      out.at<uchar>(j,i) = ( (float)image.at<cv::Vec3b>(j,i)[0] \
                           + (float)image.at<cv::Vec3b>(j,i)[1] \
                           + (float)image.at<cv::Vec3b>(j,i)[2] ) / 3;
    }
  }


  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", out);
 
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
