#pragma once
#include "opencv.hpp"
#include "halconcpp.h"
#include "../MSerialsCommon/common.h"
#include <QObject>

#ifdef _WIN64
#pragma comment(lib,"..\\third_party\\opencv\\x64\\opencv_world320.lib")
#else
#error not support x86
#endif


//using namespace cv;
//using namespace cv::ml;

class ImageMgr 
{
	//Q_OBJECT
	
public:
	ImageMgr();
	~ImageMgr();
	static ImageMgr * GetIns() { static ImageMgr l_im; return &l_im; }
	cv::Mat MImage[MAX_DEVICE_NUM];
	Halcon::Hobject HImage[MAX_DEVICE_NUM];
};
