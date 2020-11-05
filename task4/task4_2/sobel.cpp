#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
  double gain = 0.2;
  int offset = 127;

  int kernel_size = 3;
  double kernel[2][3][3] = {
     { {-2, -4, -2},
     {0, 0, 0},
     {2, 4, 2}},


     { {-2, 0, 2},
     {-4, 0, 4},
     {-2, 0, 2}}

     };
  string filename;

  cout <<"Open File Name >";
  cin >> filename;

  //read image file
  Mat color_image = cv::imread(filename, cv::IMREAD_COLOR);

  if (color_image.empty()) {
    cerr << "Failed to open image file." << endl;
    return -1;
  }

  Mat gray_image;
  cvtColor(color_image, gray_image,CV_BGR2GRAY);

  namedWindow("Image", CV_WINDOW_AUTOSIZE);
  imshow("Image", color_image);

  namedWindow("grayImage",  CV_WINDOW_AUTOSIZE);
  imshow("grayImage", gray_image);

  waitKey(100);

  Mat conv_image[2];
  conv_image[0] = Mat(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));
  conv_image[1] = Mat(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));

  int margin = kernel_size/2;

  for(int y=margin; y < gray_image.rows-margin; y++) {
    for(int x=margin; x < gray_image.cols-margin; x++) {
      for(int k = 0; k < 2; k++) {
        double conv = 0;
        for (int i = -margin; i <= margin; i++) {
          for (int j = -margin; j <= margin; j++) {
              conv += (double)gray_image.at<unsigned char>(y+i, x+j)*kernel[k][i+margin][j+margin];
            }
          }
         conv = offset + conv*gain;
         if(conv < 0) conv = 0;
         if(conv > 255) conv = 255;
         conv_image[k].at<unsigned char>(y, x) = conv;
        }
    }
  }

  namedWindow("Horiz",  CV_WINDOW_AUTOSIZE);
  namedWindow("Vert",  CV_WINDOW_AUTOSIZE);
  imshow("Horiz", conv_image[0]);
  imshow("Vert", conv_image[1]);

  ofstream fout;
  fout.open((filename+"_sobel.txt").c_str());
 
  for(int y=margin; y < gray_image.rows-margin; y++) {
    for(int x=margin; x < gray_image.cols-margin; x++) {
      fout << (int)conv_image[0].at<unsigned char>(y, x)-127 << "\t";
      fout << (int)conv_image[1].at<unsigned char>(y, x)-127 << endl;
    }
  }
 
  fout.close();

  waitKey(0);
  destroyAllWindows();
  return 0;
}








