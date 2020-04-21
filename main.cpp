#include <iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

// ADD SALT PEPPER NOISE n DENOISE
void Add_salt_pepper_Noise(Mat& srcArr)

{
    RNG rng; 
    int amount1 = srcArr.rows * srcArr.cols * 0.05;
    int amount2 = srcArr.rows * srcArr.cols * 0.05;
    for (int counter = 0; counter < amount1; ++counter)
    {

        srcArr.at<uchar>(rng.uniform(0, srcArr.rows), rng.uniform(0, srcArr.cols)) = 0;

    }
    for (int counter = 0; counter < amount2; ++counter)
    {
        srcArr.at<uchar>(rng.uniform(0, srcArr.rows), rng.uniform(0, srcArr.cols)) = 255;
    }
}

int main(int argc, char* argv[])
{
    Mat srcArr = imread("D://A5.jpg");


    cvtColor(srcArr, srcArr, COLOR_RGB2GRAY);
    imshow("The original Image", srcArr);

    Mat srcArr1 = srcArr.clone();
    Mat dstArr;

    Add_salt_pepper_Noise(srcArr1);
    imshow("Add salt and pepper noise to image ", srcArr1);
    imwrite("salt&pepper noise image.tif", srcArr1);


    medianBlur(srcArr1, dstArr, 5);
    imshow("The effect after median filter", dstArr);
    imwrite("Median image.tif", dstArr);

    GaussianBlur(srcArr1, dstArr, Size(3,3),1.0);
    imshow("The effect after Gaussian filter", dstArr);
    imwrite("Gaussian image.tif", dstArr);

    
    waitKey(0);
    return 0;
}