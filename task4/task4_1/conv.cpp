#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
  std::string filename, outputname;

  double kernel[3][3] = {
    {-1, -1, -1},
    {0, 0, 0},
    {1, 1, 1}
  };

  double d, gain, offset;
  int kernel_size, margin;

  std::cout <<"Open File Name >";
  std::cin >> filename;


  //read image data
  cv::Mat color_image = cv::imread(filename, cv::IMREAD_COLOR);

 //quit program if image reading failed
  if(color_image.empty())
  {
    std::cerr << "Failed to open image file." << std::endl;
    return -1;
  }

  cv::Mat gray_image;
  cvtColor(color_image, gray_image,CV_BGR2GRAY);  //gray scale
  cv::Mat conv_image(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));


  gain = 0.5; offset = 127;
  kernel_size = 3;
  margin = kernel_size/2;

  //convloution

  for(int y=margin; y < gray_image.rows-margin; y++) {
   for(int x=margin; x < gray_image.cols-margin; x++) {

      d = 0;
      for (int j = -margin; j <= margin; j++) {
       for (int i = -margin; i <= margin; i++) {
     d += (double)gray_image.at<unsigned char>(y+j, x+i) * kernel[j+margin][i+margin];
       }
      }
     
      d = offset + d*gain;
      if (d < 0) d = 0;
      if (d > 255) d = 255;
      conv_image.at<unsigned char>(y, x) = d;
    }
  }


  //display images
  cv::namedWindow("color image", cv::WINDOW_AUTOSIZE);
  cv::imshow("color image", color_image);

  cv::namedWindow("gray image", cv::WINDOW_AUTOSIZE);
  cv::imshow("gray image", gray_image);

  cv::namedWindow("conv image", cv::WINDOW_AUTOSIZE);
  cv::imshow("conv image", conv_image);

  outputname = "conv_"+filename;
  cv::imwrite(outputname, conv_image);

 

  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}
