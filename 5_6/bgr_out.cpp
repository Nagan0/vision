#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
  string filename;

  cout <<"Open File Name >";
  cin >> filename;

  //read image file
  Mat color_image = cv::imread(filename, cv::IMREAD_COLOR);

  if (color_image.empty()) {
    cerr << "Failed to open image file." << endl;
    return -1;
  }

  namedWindow("Image", CV_WINDOW_AUTOSIZE);
  imshow("Image", color_image);
  waitKey(100);

  ofstream fout;
  fout.open("bgr.txt");

  for(int y=0; y < color_image.rows; y++) {
    for(int x=0; x < color_image.cols; x++) {
      if ( (y <= color_image.rows/2+50) && (y >= color_image.rows/2-50) && ( x <= color_image.cols/2+50) &&  ( x >= color_image.cols/2-50) ) {
        fout << (int)color_image.at<cv::Vec3b>(y, x)[0] <<"\t";
        fout << (int)color_image.at<cv::Vec3b>(y, x)[1] <<"\t";
        fout << (int)color_image.at<cv::Vec3b>(y, x)[2] <<endl;

      }
    }
  }

  fout.close();

  waitKey(0);
  destroyAllWindows();
  return 0;
}


