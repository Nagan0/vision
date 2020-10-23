#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
 
  //read image data
  cv::Mat image = cv::imread("chinese_food.jpg", cv::IMREAD_COLOR);

  //quit program if image reading failed
  if(image.empty())
  {
    std::cerr << "Failed to open image file." << std::endl;
    return -1;
  }


  //exchange rgb colors
  for (int i = 0; i < image.cols; i++) {
    for (int j = 0; j < image.rows; j++){
      int temp;
      temp = image.at<cv::Vec3b>(j,i)[0];  //input blue value to temp
      image.at<cv::Vec3b>(j,i)[0] = image.at<cv::Vec3b>(j,i)[1];  //input green value to blue data
      image.at<cv::Vec3b>(j,i)[1] = image.at<cv::Vec3b>(j,i)[2];  //input red value to green data
      image.at<cv::Vec3b>(j,i)[2] = temp;  //input temp(blue value) to red data
    }
  }

  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", image);
 
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
