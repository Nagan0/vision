#include <opencv2/opencv.hpp>

#include <iostream>



void drawHist(int hist[][256], cv::Mat hist_image, int *center, double *slope);

void scaleShiftColor(cv::Mat in_image, cv::Mat out_image, int *center, double *slope);



int main(int argc, const char* argv[])

{

  std::string filename;

  

  std::cout << "Open File Name >";

  std::cin >> filename;

  

  //read image data

  cv::Mat color_image = cv::imread(filename, cv::IMREAD_COLOR);

  

  //display images

  cv::namedWindow("color image", cv::WINDOW_AUTOSIZE);

  cv::imshow("color image", color_image);

  cv::waitKey(100);

  

  //quit program if image reading failed

  if(color_image.empty()) {

    std::cerr << "Failed to open image file." << std::endl;

    return -1; 

  }

  

  cv::Mat cshift_image(cv::Size(color_image.cols, color_image.rows), CV_8UC3, cv::Scalar(0)); //for rescaled image

  cv::Mat hist_image(cv::Size(532, 400), CV_8UC3, cv::Scalar(0));  //for histgram



  cv::namedWindow("cshift image", cv::WINDOW_AUTOSIZE);

  cv::imshow("cshift image", cshift_image);

  cv::namedWindow("hist image", cv::WINDOW_AUTOSIZE);

  cv::imshow("hist image", hist_image);  

  cv::waitKey(100);

  

  //histgram data

  

  int hist[3][256];



  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 256; j++) {

      hist[i][j] = 0;

    }

  }



  for(int y=0; y < color_image.rows; y++) {

    for(int x=0; x < color_image.cols; x++) {

      hist[0][color_image.at<cv::Vec3b>(y, x)[0]]++;

      hist[1][color_image.at<cv::Vec3b>(y, x)[1]]++;

      hist[2][color_image.at<cv::Vec3b>(y, x)[2]]++;

    }

  }

  

  int key = 1;

  int center[] = {128, 128, 128};

  double slope[] = {1, 1, 1};





  //key 

  

  while(1) { 

    std::cout<<5<<std::endl;

    

    /*if (key == 'a') {

      for (int i = 0; i < 3; i++) {

      autoScale(gray_image, hist[i], &center[i], &slope[i]);

      }  else */

    if (key == 32) {

      std::cout << "Mode(0=Blue 1=Green 2=Red)->";

      

      int mode;    

      std::cin >> mode;

      

      if ( mode >=0 && mode <=2) {

        std::cout << "Center(default = 128)->";

        std::cin >> center[mode];

        std::cout << "Slope(default = 1)->";

        std::cin >> slope[mode];

      }

    }



    std::cout << "ESC=Quit  SPACE=Re-scale  s=Save&Quit\n";



    //draw histgram

    drawHist(hist, hist_image, center, slope);

    cv::imshow("hist image", hist_image);

    scaleShiftColor(color_image, cshift_image, center, slope);

    cv::imshow("cshift image", cshift_image);

 

    while(1) {

      key = cvWaitKey(100);

      key = key % 256;

      if (key == 32 ) break; //SPACE

      if (key == 27 ) break; //ESC

      if (key == 's') {  //file output

        std::string outputname;

        outputname = "cshift_" + filename;

        cv::imwrite(outputname, cshift_image);

        break;

      }

    }



    if (key == 27  || key == 's' ) break; //ESC

  }



  cv::destroyAllWindows();



  return 0;

}







void drawHist(int hist[][256], cv::Mat hist_image, int *center, double *slope)

{

  cv::rectangle(hist_image, cv::Point(0,0), cv::Point(532, 400), cv::Scalar(100,100,100), -1, 4);



  for (int j = 0; j < 3; j++) {

    for (int i = 0; i < 256; i++) {

      cv::line(hist_image, cv::Point(10+i*2,399-j*120), cv::Point(10+i*2,399-hist[j][i]/40-j*120), cv::Scalar(((j == 0 || j == 3)*255),(j == 1 || j == 3)*255,(j == 2 || j == 3)*255), 1, 8);

    } 

  }



  for (int j = 0; j < 3; j++) {

    cv::line(hist_image, cv::Point(10,399-256/4-j*120), cv::Point(522,399-256/4-j*120), cv::Scalar(255, 255, 0), 1, 8);

    for (int i = 0; i < 256; i++) {



      int k = 128+(i-center[j])*slope[j];

      if (k > 255) k = 255;

      if (k < 0) k = 0;



      k /= 4;



      cv::line(hist_image, cv::Point(10+i*2,399-k-j*120), cv::Point(10+i*2,399-k-j*120), cv::Scalar(0, 255, 255), 2, 8);

    }  

  }

}







void scaleShiftColor(cv::Mat in_image, cv::Mat out_image, int *center, double *slope)

{

  int x, y, i;



 for(int y=0; y < in_image.rows; y++) {

   for(int x=0; x < in_image.cols; x++) {

     for (int i = 0; i < 3; i++ ) {

       int pix = (in_image.at<cv::Vec3b>(y, x)[i] - center[i])*slope[i] + 128;

       if (pix > 255) pix = 255;

       if (pix < 0) pix = 0;

       out_image.at<cv::Vec3b>(y, x)[i] = pix;

      }

    }

  }

}
