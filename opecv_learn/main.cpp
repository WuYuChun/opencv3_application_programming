//#include<opencv2\core\core.hpp>
//#include<opencv2\highgui\highgui.hpp>

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h> 

#include<iostream>

#include <windows.h>

void onMouse(int event, int x, int y, int flags, void *param);

int func_1();

cv::Mat function();



using namespace std;
using namespace cv;


int main()
{
#if 0
	time_t nowtime;
	nowtime = time(NULL); //获取日历时间  
	cout << nowtime << endl;  //输出nowtime 

	struct tm tnNormal_1;
	time_t tNormal;
	tnNormal_1.year = 2010 - 1900;
	tnNormal_1.tm_mon = 1 - 1;
	tnNormal_1.tm_mday = 1;
	tnNormal_1.tm_hour = 0;
	tnNormal_1.tm_min = 0;
	tnNormal_1.tm_sec = 0;
	tnNormal_1.tm_isdst = 0;
	tNormal = mktime(&tnNormal_1);
	time_t tcur = time(0);
	long defferent = difftime(tcur,tNormal);

	std::cout << "defferent: " << std::endl;
#endif


#if  1
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		printf("open video failed!\n");
		return 1;
	}

	Mat Frame;

	//设置保存的视频帧数目
	UINT32 frameNum = 60*60*25*30*2;
	//保存视频的路径
	string outputVideoPath = "D:\\test.avi";
	//获取当前摄像头的视频信息
	cv::Size sWH = cv::Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter outputVideo;
	outputVideo.open(outputVideoPath, CV_FOURCC('M', 'P', '4', '2'), 25.0, sWH);

	
	//

	bool is_first= true;
	while (cap.isOpened() && frameNum > 0)
	{
		if (is_first){
			Sleep(1000*60);
			is_first = FALSE;
		}
		cap >> Frame;
		if (Frame.empty()) break;
		outputVideo << Frame;
		frameNum--;

		imshow("img", Frame);
		waitKey(10);

		if (char(waitKey(1)) == 'q') break;
	}

	outputVideo.release();
#endif
}


#if 0
int main(int argc, char *argv[]){

	cv::VideoCapture cap;
	cap.open(0);

	if(!cap.isOpened()){
		std::cout << "open capture err!\n";
		return -1;
	}

	cv::VideoWriter writer("D:\\out.avi", CV_FOURCC('D', 'I', 'V', 'X'), 25.0, cv::Size(480, 480));

	if (!writer.isOpened()){
		std::cout << "can not open writer!\n";
	}
	
	while (1){
		cv::Mat frame;
		cap >> frame;
		std::cout << frame.channels() << std::endl;
		writer << frame;
		cv::imshow("video",frame);
		if (cv::waitKey(20) > 0){
			break;
		}
	}

	cap.release();
	writer.release();


#if 0
	cv::Mat image1(240, 320, CV_8U, 100);
	cv::imshow("Image", image1);
	cv::waitKey(0);

	image1.create(200, 200, CV_8U);
	image1 = 200;

	cv::imshow("Image", image1);
	cv::waitKey(0);

	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));
	cv::imshow("image2", image2);
	cv::waitKey(0);
#endif

	return 0;
}
#endif
void onMouse(int event, int x, int y, int flags, void *param){

	cv::Mat *im = reinterpret_cast<cv::Mat *>(param);

	switch (event){
	
	case cv::EVENT_LBUTTONDOWN:
		std::cout << "at ( " << x << "," << y << ") value is:  " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;
		break;
	default:
		break;
	}
}

cv::Mat function(){
	cv::Mat ima(500, 500, CV_8U, 50);
	return ima;
}

int func_1(){
	cv::Mat image;

	std::cout << "this image is " << image.rows << " x " << image.cols << " y" << std::endl;

	image = cv::imread("D:\\Code\\opecv_learn\\Debug\\33333.jpg", cv::IMREAD_GRAYSCALE);

	if (image.empty()){
		std::cout << "open image err!\n";
		return -1;
	}


	cv::namedWindow("Originanl image");

	cv::imshow("Originanl image", image);

	cv::setMouseCallback("Originanl image", onMouse, reinterpret_cast<void*>(&image));

	cv::Mat result;
	cv::flip(image, result, 1);

	cv::imshow("Output Images", result);

	cv::waitKey(0);
}