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

/*
#include <opencv2/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

float SNR(const Mat& f1, const Mat& f2) {
	float ts=0.0, ms=0.0;
	float t1, t2;
	for(int i=0;i<f1.rows;i++)
		for (int j = 0; j < f1.cols; j++)
		{
			ts += f2.at<uchar>(i, j);
			ts += t1 * t1;
			ms += pow(t1 - f1.at<uchar>(i, j),2.0);
		}
	return ts / ms;
}

int main(int argc, char* argv[])
{
	Mat ima1 = imread(argv[1]);
	Mat im2;
	if (ima1.data == nullptr)
	{
		cout << "Loi doc File!" << argv[1];
		return 1;
	}
	GaussianBlur(ima1, im2, Size(3, 3), 1);
	imshow("Anh vua doc", ima1);
	imshow("Gaussian Blur", im2);
	cout << SNR(ima1, im2);
	waitKey(0);
	return 0;
}
*/
