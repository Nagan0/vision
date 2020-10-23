#include <opencv2/opencv.hpp>
#include <iostream>


void drawHist(int *hist, cv::Mat hist_image, int center, double slope);
void scaleShift(cv::Mat in_image, cv::Mat out_image, int center, double slope);

int main(int argc, const char* argv[])
{
  std::string filename;
  std::cout << "Open File Name >";
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

  cv::Mat shift_image(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0)); //for rescaled image

  cv::Mat hist_image(cv::Size(532, 400), CV_8UC3, cv::Scalar(0));  //for histgram

  //histgram data
  int hist[256];
  for (int i = 0; i < 256; i++) hist[i] = 0;

  for(int y=0; y < gray_image.rows; y++) {
    for(int x=0; x < gray_image.cols; x++) {
      hist[gray_image.at<unsigned char>(y, x)]++;
    }
  }

  //display images
  cv::namedWindow("color image", cv::WINDOW_AUTOSIZE);
  cv::imshow("color image", color_image);

  cv::namedWindow("gray image", cv::WINDOW_AUTOSIZE);
  cv::imshow("gray image", gray_image);

  cv::namedWindow("shift image", cv::WINDOW_AUTOSIZE);
  cv::imshow("shift image", shift_image);

  cv::namedWindow("hist image", cv::WINDOW_AUTOSIZE);
  cv::imshow("hist image", hist_image);

  int key = 1;
  int center = 128;
  double slope = 1;

  //key wait
  while(1) {
    if (key == 32) {
      std::cout << "Center(default = 128)->";
      std::cin >> center;
      std::cout << "Slope(default = 1)->";
      std::cin >> slope;
    }

    std::cout << "ESC=Quit  SPACE=Re-scale  s=Save&Quit\n";

    //draw histgram
    drawHist(hist, hist_image, center, slope);

    //draw rescaled image
    scaleShift(gray_image, shift_image, center, slope);

    cv::imshow("shift image", shift_image);
    cv::imshow("hist image", hist_image);

    while(1) {
      key = cvWaitKey(100);
      if (key == 32 ) break; //SPACE
      if (key == 27 ) break; //ESC
      if (key == 's') {  //file output
        std::string outputname;
        outputname = "gshift_" + filename;
        cv::imwrite(outputname, shift_image);
        break;
      }
    }
    if (key == 27 || key == 's') break; //ESC
  }

  cv::destroyAllWindows();
  return 0;
}


void drawHist(int *hist, cv::Mat hist_image, int center, double slope)
{
  cv::rectangle(hist_image, cv::Point(0,0), cv::Point(532, 400), cv::Scalar(100,100,100), -1, 4);
  cv::line(hist_image, cv::Point(10,399-256), cv::Point(522,399-256), cv::Scalar(255,255,0), 1, 8);

  for (int i = 0; i < 256; i++) {
    cv::line(hist_image, cv::Point(10+i*2,399), cv::Point(10+i*2,399-hist[i]/10), cv::Scalar(255,255,255), 2, 8);
  }  

  for (int i = 0; i < 256; i++) {
    int j;
    j = 128+(i-center)*slope;

    if (j > 255) j = 255;
    if (j < 0) j = 0;

    cv::line(hist_image, cv::Point(10+i*2,399-j), cv::Point(10+i*2,399-j), cv::Scalar(0,0,255), 2, 8);
  }  
}


void scaleShift(cv::Mat in_image, cv::Mat out_image, int center, double slope)
{
  int pix;

  for(int y=0; y < in_image.rows; y++) {
    for(int x=0; x < in_image.cols; x++) {
      pix = (in_image.at<unsigned char>(y,x)-center)*slope+128;
      if (pix > 255) pix = 255;
      if (pix < 0) pix = 0;

      out_image.at<unsigned char>(y, x) = pix;
    }
  }
}
