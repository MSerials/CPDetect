#include "stdafx.h"
#include "Common.h"
#include "MSerialsCam.h"
#include "halconcpp.h"


void displayMat(const cv::Mat &image, QLabel *disp_hand, QWidget* widget)
{
#if 1
	QImage img = QImage((const unsigned char*)(image.data),
		image.cols, image.rows,
		image.cols*image.channels(),
		QImage::Format_RGB888);

	disp_hand->setScaledContents(true);
	disp_hand->setPixmap(QPixmap::fromImage(img));
	if (nullptr != widget)	disp_hand->resize(QSize(widget->size()));
	else { disp_hand->resize(QSize(disp_hand->size())); }
	return;


#else
	cv::Mat rgb;
	QImage img;
	if (image.channels() == 3)
	{
		//cvt Mat BGR 2 QImage RGB
		cv::cvtColor(image, rgb, CV_BGR2RGB);
		img = QImage((const unsigned char*)(rgb.data),
			rgb.cols, rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
		img = QImage((const unsigned char*)(image.data),
			image.cols, image.rows,
			image.cols*image.channels(),
			QImage::Format_RGB888);
	}
	disp_hand->setScaledContents(true);
	disp_hand->setPixmap(QPixmap::fromImage(img));

	if (nullptr != widget)	disp_hand->resize(QSize(widget->size()));
	else { disp_hand->resize(QSize(disp_hand->size())); }
	return;
#endif
	//为了节省那么一点速度
	if (NULL == widget)
	{
		cv::Mat resized;
		cv::resize(image,resized,cv::Size(widget->width(),widget->height()));
		cv::Mat rgb;
		QImage img;
		if (resized.channels() == 3)
		{
			//cvt Mat BGR 2 QImage RGB
			cv::cvtColor(resized, rgb, CV_BGR2RGB);
			img = QImage((const unsigned char*)(rgb.data),
				rgb.cols, rgb.rows,
				rgb.cols*rgb.channels(),
				QImage::Format_RGB888);
		}
		else
		{
			img = QImage((const unsigned char*)(resized.data),
				resized.cols, resized.rows,
				resized.cols*resized.channels(),
				QImage::Format_RGB888);
		}
		disp_hand->setScaledContents(true);
		disp_hand->setPixmap(QPixmap::fromImage(img));
		printf("%d %d\n", disp_hand->width(), disp_hand->height());


		//if (!widget)	disp_hand->resize(QSize(widget->size()));
		//else { disp_hand->resize(QSize(widget->size())); }
	}
	else
	{
		cv::Mat rgb;
		QImage img;
		if (image.channels() == 3)
		{
			//cvt Mat BGR 2 QImage RGB
			cv::cvtColor(image, rgb, CV_BGR2RGB);
			img = QImage((const unsigned char*)(rgb.data),
				rgb.cols, rgb.rows,
				rgb.cols*rgb.channels(),
				QImage::Format_RGB888);
		}
		else
		{
			img = QImage((const unsigned char*)(image.data),
				image.cols, image.rows,
				image.cols*image.channels(),
				QImage::Format_RGB888);
		}
		disp_hand->setScaledContents(true);
		disp_hand->setPixmap(QPixmap::fromImage(img));
		printf("%d %d\n", disp_hand->width(), disp_hand->height());
	//	if (!widget)	disp_hand->resize(QSize(widget->size()));
	//	else { disp_hand->resize(QSize(widget->size())); }
	}	
} 



void SnapMat(cv::Mat &Image, int vendor, int cam_num, int delay)
{
	int w = 0;
	int h = 0;
	int ch = 1;
	unsigned char * data = NULL;
	//因为电脑性能不是很好，所以采用这个snap来采取图片
	Snap(w, h, &data, ch, vendor, cam_num, delay);
	if (0 == w || 0 == h || NULL == data)	return;
	cv::Mat src;
	if (1 == ch)
	{ 
		src = cv::Mat(h, w, CV_8UC1);
	}
	else
	{
		src = cv::Mat(h, w, CV_8UC3);
	}
	src.data = data;
	Image = src.clone();
}

void split_color(int width, int height, int ch, uchar* src, uchar** dst)
{
	if (ch > 2) return;

	*dst = (uchar*)malloc(width*height * sizeof(char));
	uchar *s = src; uchar *d = *dst;
	//openmp 
#pragma omp parallel for
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			d[w] = s[w * 3 + ch];
		}
		d += width;
		s += 3 * width;
	}
}

void SnapHobj(Halcon::Hobject &Image, int vendor, int cam_num, int delay)
{
	using namespace Halcon;
	int w = 0;
	int h = 0;
	int ch = 1;
	unsigned char * img = NULL;
	//因为电脑性能不是很好，所以采用这个snap来采取图片
	Snap(w, h, &img, ch, vendor, cam_num, delay);
	if (0 == w || 0 == h || NULL == img)	return;
	Halcon::set_check("~give_error");

	if (1 == ch)
		Halcon::gen_image1(&Image, "byte", (Hlong)w, (Hlong)h, (Hlong)img);
	else
	{
		uchar * r = NULL, *g = NULL, *b = NULL;
		split_color(w, h, 0, img, &b);
		split_color(w, h, 1, img, &g);
		split_color(w, h, 2, img, &r);
		Halcon::gen_image3(&Image, "byte", (Hlong)w, (Hlong)h, (Hlong)r, (Hlong)g, (Hlong)b);
		free(r);
		free(g);
		free(b);
	}
}




void MatToHImage(cv::Mat& pImage, Halcon::Hobject& Hobj)
{
	//Hobject Hobj = NULL;
	using namespace Halcon;
	if (3 == pImage.channels())
	{
		cv::Mat pImageRed, pImageGreen, pImageBlue;
		std::vector<cv::Mat> sbgr(3);
		cv::split(pImage, sbgr);

		int length = pImage.rows * pImage.cols;
		uchar *dataBlue = new uchar[length];
		uchar *dataGreen = new uchar[length];
		uchar *dataRed = new uchar[length];

		int height = pImage.rows;
		int width = pImage.cols;
		for (int row = 0; row <height; row++)
		{
			uchar* ptr = pImage.ptr<uchar>(row);
			for (int col = 0; col < width; col++)
			{
				dataBlue[row * width + col] = ptr[3 * col];
				dataGreen[row * width + col] = ptr[3 * col + 1];
				dataRed[row * width + col] = ptr[3 * col + 2];
			}
		}

		Halcon::gen_image3(&Hobj, "byte", width, height, (Hlong)(dataRed), (Hlong)(dataGreen), (Hlong)(dataBlue));
		delete[] dataRed;
		delete[] dataGreen;
		delete[] dataBlue;
	}
	else if (1 == pImage.channels())
	{
		int height = pImage.rows;
		int width = pImage.cols;
		uchar *dataGray = new uchar[width * height];
		memcpy(dataGray, pImage.data, width * height);
		gen_image1(&Hobj, "byte", width, height, (Hlong)(dataGray));
		delete[] dataGray;
	}

}



void HImageToMat(Halcon::Hobject &Hobj, cv::Mat& pImage)
{
	using namespace cv;
	using namespace Halcon;
	Hlong htChannels;
	char cType[MAX_STRING];
	Hlong     width, height;
	width = height = 0;
	//转换图像格式  
	convert_image_type(Hobj, &Hobj, "byte");
	count_channels(Hobj, &htChannels);
	if (htChannels == 1)
	{
		unsigned char *ptr;
		get_image_pointer1(Hobj, (Hlong *)&ptr, cType, &width, &height);
		pImage = cv::Mat(static_cast<int>(height), static_cast<int>(width), CV_8UC1);
		memcpy(pImage.data, ptr, width * height);

	}
	else if (htChannels == 3)
	{

		unsigned char *ptrRed, *ptrGreen, *ptrBlue;
		ptrRed = ptrGreen = ptrBlue = NULL;
		Halcon::get_image_pointer3(Hobj, (Hlong *)&ptrRed, (Hlong *)&ptrGreen, (Hlong *)&ptrBlue, cType, &width, &height);
		pImage = cv::Mat(static_cast<int>(height), static_cast<int>(width), CV_8UC3);
		for (int row = 0; row < height; row++)
		{
			uchar* ptr = pImage.ptr<uchar>(row);
			for (int col = 0; col < width; col++)
			{
				ptr[3 * col] = ptrBlue[row * width + col];
				ptr[3 * col + 1] = ptrGreen[row * width + col];
				ptr[3 * col + 2] = ptrRed[row * width + col];
			}
		}

	}
}

void h_disp_obj(const Halcon::Hobject & obj, const Halcon::HTuple & disp_hand)
{
	try
	{
		Halcon::set_check("~give_error");
		Hlong w, h;
		Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
		Halcon::HDevWindowStack::Push(disp_hand);
		Halcon::HDevWindowStack::SetActive(disp_hand);
		Halcon::set_part(disp_hand, NULL, NULL, h, w);
		disp_obj(obj, disp_hand);
	}
	catch (Halcon::HException &except)
	{
		Halcon::set_check("give_error");
		Halcon::set_tposition(disp_hand, 0, 1);
		Halcon::write_string(disp_hand, "no image");
	}
}