#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{

  ofstream fout;
  fout.open("data.csv");

  string filename;


  int x, y, a, b, c, i, j, margin, kernel_size, offset, key;

  double kernel_v[3][3] = {
    {-1, 0, 1}, 
    {-2, 0, 2}, 
    {-1, 0, 1}
  };

double kernel_h[3][3] = {
    {-1, -2, -1}, 
    {0, 0, 0}, 
    {1, 2, 1}
  };

  double d, e, gain, v_total, h_total, v_normal, h_normal;


  while (1){


  cout << "Open File Name >";

  cin >> filename;


  //read image file
  Mat color_image = cv::imread(filename, cv::IMREAD_COLOR);

  if (color_image.empty()) {
    cerr << "Failed to open image file." << endl;
    return -1;
  }

  Mat gray_image;
  cvtColor(color_image, gray_image,CV_BGR2GRAY);

  Mat conv_image[2];
  conv_image[0] = Mat(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));
  conv_image[1] = Mat(cv::Size(gray_image.cols, gray_image.rows), CV_8U, cv::Scalar(0));

  Mat hist_image;
  hist_image = Mat(cv::Size(400, 400), CV_8UC3, cv::Scalar(0));


  cv::namedWindow("ColorImage", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("GrayImage", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("HImage", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("VImage", cv::WINDOW_AUTOSIZE);
  cv::namedWindow("HistImage", cv::WINDOW_AUTOSIZE);



  gain = 0.5; offset = 127;

  kernel_size = 3;

  margin = kernel_size/2;

  v_total = h_total = 0;

  for(y=margin; y < gray_image.rows-margin; y++) {

   for(x=margin; x < gray_image.cols-margin; x++) {

      d = 0; e = 0;

      for (i = -margin; i <= margin; i++) {

       for (j = -margin; j <= margin; j++) {

         d += (double)gray_image.at<unsigned char>(y+i, x+j)*kernel_v[i+margin][j+margin];
         e += (double)gray_image.at<unsigned char>(y+i, x+j)*kernel_h[i+margin][j+margin];

       }

      }

      v_total += abs(d);
      h_total += abs(e);

      d = 127 + d * gain;

      if (d < 0) d = 0;

      if (d > 255) d = 255;

      e = 127 + e * gain;

      if (e < 0) e = 0;

      if (e > 255) e = 255;
      
      conv_image[0].at<unsigned char>(y, x) = d;

      conv_image[1].at<unsigned char>(y, x) = e;

   }

} 


  if (v_total > h_total) {
     v_normal = 1;
     h_normal = h_total/v_total;
  } else {
     h_normal = 1;
     v_normal = v_total/h_total;
  }

  v_total /= (gray_image.cols*gray_image.rows);
  h_total /= (gray_image.cols*gray_image.rows);

  rectangle(hist_image, Point(0,0), Point(532, 400), Scalar(100,100,100), -1, 4);

  rectangle(hist_image, Point(10,400), Point(90, 400-v_total*40), Scalar(0,0,200), -1, 4);
  rectangle(hist_image, Point(110,400), Point(190, 400-h_total*40), Scalar(0,200,200), -1, 4);
  rectangle(hist_image, Point(210,400), Point(290, 400-v_normal*300), Scalar(0,200,0), -1, 4);
  rectangle(hist_image, Point(310,400), Point(390, 400-h_normal*300), Scalar(200,200,0), -1, 4);



  imshow("ColorImage", color_image);

  imshow("GrayImage", gray_image);

  imshow("HImage", conv_image[0]);

  imshow("VImage", conv_image[1]);

  imshow("HistImage", hist_image);



  fout << v_total << ", " << h_total << ", " << v_normal << ", " << h_normal << endl;

  key = cvWaitKey(0);

  if (key != 'a') break;

  }

  fout.close();

  destroyAllWindows();
  return 0;
}
