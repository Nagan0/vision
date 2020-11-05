#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, const char* argv[])
{
  double kval = 0.2 /* 0.08 */;
  int cmargin = 6;
  int coffset =127;
  double cgain = 1 /* 1 */;


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

  Mat harris_image(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));

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

  waitKey(100);
 
  double cov;
  for(int y=cmargin; y < gray_image.rows-cmargin; y++) {
    for(int x=cmargin; x < gray_image.cols-cmargin; x++) {
      double cov[] = {0, 0, 0};
        for (int i = -cmargin; i <= cmargin; i++) {
          for (int j = -cmargin; j <= cmargin; j++) {
            cov[0] += (double)(conv_image[0].at<unsigned char>(y+i, x+j)-offset)*(double)(conv_image[0].at<unsigned char>(y+i, x+j)-offset)*0.001;
            cov[1] += (double)(conv_image[1].at<unsigned char>(y+i, x+j)-offset)*(double)(conv_image[1].at<unsigned char>(y+i, x+j)-offset)*0.001;
            cov[2] += (double)(conv_image[0].at<unsigned char>(y+i, x+j)-offset)*(double)(conv_image[1].at<unsigned char>(y+i, x+j)-offset)*0.001;
          }
      }
       //cout << cov[0] << "\t" << cov[1] << "\t" << cov[2] << "\t" << 127+cgain*((cov[0]*cov[1]-cov[2]*cov[2])-kval*(cov[0]+cov[1])*(cov[0]+cov[1])) << endl;
      int temp = coffset+cgain*((cov[0]*cov[1]-cov[2]*cov[2])-kval*(cov[0]+cov[1])*(cov[0]+cov[1]));
       if (temp < 0) temp = 0;
       if (temp > 255) temp = 255;
      harris_image.at<unsigned char>(y, x) = temp;
    }
  }


  namedWindow("Harris",  CV_WINDOW_AUTOSIZE);
  imshow("Harris", harris_image);
   


  waitKey(0);
  destroyAllWindows();
  return 0;
}
