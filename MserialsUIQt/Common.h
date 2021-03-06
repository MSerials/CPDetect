
#pragma once

#include "opencv.hpp"

#ifndef __COMMON__TOOLS__
#define __COMMON__TOOLS__

//��������˹��ߣ������ȡ��Ϣʲô��
class Tools {

public:
	void GetScreenInfo(int &g_nActScreenX, int &g_nActScreenY, int &g_nScreenCount)
	{
		QDesktopWidget* desktopWidget = QApplication::desktop();
		//��ȡ���������С
		QRect deskRect = desktopWidget->availableGeometry();
		//��ȡ�豸��Ļ��С
		QRect screenRect = desktopWidget->screenGeometry();

		g_nActScreenX = screenRect.width();
		g_nActScreenY = screenRect.height();
		//g_nActScreenX = deskRect.width();
		//g_nActScreenY = deskRect.height();

		//��ȡϵͳ���õ���Ļ��������Ļ������ʽ��ֵΪ1��
		g_nScreenCount = desktopWidget->screenCount();
	}
	//˵�����˳�������¶���Ļ���óɿ�����ʽʱ����ȡ����Ļ�ĸ�����һ����ֻ�����ó���չʱ�ŷ��ض����

	//��ӡ��Ļ�ֱ��ʺ͸�����Ϣ��
	void printscreeninfo()
	{
		QDesktopWidget *dwsktopwidget = QApplication::desktop();
		QRect deskrect = dwsktopwidget->availableGeometry();
		QRect screenrect = dwsktopwidget->screenGeometry();
	//	QDesktopWidget *dwsktopwidget = QApplication::desktop();
	//	QRect deskrect = dwsktopwidget->availableGeometry();
	//	QRect screenrect = dwsktopwidget->screenGeometry();
		int scrcount = dwsktopwidget->screenCount();
		qCritical("screenrect.w==%s\n", qPrintable(QString::number(screenrect.width())));
		qCritical("screenrect.h==%s\n", qPrintable(QString::number(screenrect.height())));
		qCritical("deskrect.w==%s\n", qPrintable(QString::number(deskrect.width())));
		qCritical("deskrect.h==%s\n", qPrintable(QString::number(deskrect.height())));
		qCritical("scrcount==%s\n", qPrintable(QString::number(scrcount)));

	}
};

//������������ϵͳ��һЩ��Ϣ����
class SystemInfo
{
public:
	static SystemInfo* GetIns()
	{
		static SystemInfo l_si;
		return &l_si;
	}


};


#endif


#ifndef __COMMON__DIS__
#define __COMMON__DIS__

#include "halconcpp.h"
void displayMat(const cv::Mat &src, QLabel *disp_hand, QWidget* widget = NULL);
//as Opencv format to snap
void SnapMat(cv::Mat &Image, int vendor = 0, int cam_num = 0, int delay = 35);
//as halcon format to snap 
void SnapHobj(Halcon::Hobject &Image, int vendor, int cam_num, int delay = 35);
//Opencv To Halcon
void MatToHImage(cv::Mat& pImage, Halcon::Hobject& Hobj);
//Halcon To Opencv
void HImageToMat(Halcon::Hobject &Hobj, cv::Mat& pImage);

void h_disp_obj(const Halcon::Hobject & obj, const Halcon::HTuple & disp_hand);


#endif