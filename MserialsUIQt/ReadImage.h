#pragma once
#include "IR.h"
#include <vector>
#include <stdexcept>

class ReadImage :public AObject
{
public:
	ReadImage(std::string name = "read_image") {
		fun_name = name;
		index = ParamMgr::GetIns()->mats.size();
		cv::Mat mat;
		ParamMgr::GetIns()->mats.push_back(mat);
	}
	~ReadImage()
	{
		if (index >= ParamMgr::GetIns()->mats.size())	return;
		std::vector<cv::Mat>::iterator it = ParamMgr::GetIns()->mats.begin() + index;
		ParamMgr::GetIns()->mats.erase(it);
	};

	std::string GetFunName() { return fun_name; }

	int Runnable()
	{

		try
		{
			ParamMgr::GetIns()->mats.at(index) = cv::imread(imagepath, -1);	
		}
		catch (std::out_of_range &exc)
		{
			DLOG(LOG_ERROR, exc.what());
			QMessageBox::information(NULL, tr("fatal error"), QString::fromLocal8Bit("超出图像数组"));
			return PARA_INDEX_ERROR;
		}
		catch (...)
		{
			DLOG(LOG_ERROR, "read image block error");
			QMessageBox::information(NULL, tr("fatal error"), QString::fromLocal8Bit("图像读取模块错误"));
			return PARA_INDEX_ERROR;
		}
		return RUN_OK; 
	}
	int Method()
	{

		QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.tiff)"));
		if (path.length() == 0) return PATH_ERROR;

		QByteArray ba = path.toLatin1();
		try {
			ParamMgr::GetIns()->mats.at(index) = cv::imread(ba.data(), -1);
			imagepath = std::string(ba.data());
		}
		catch (std::out_of_range &exc)
		{
			DLOG(LOG_ERROR, exc.what());
			QMessageBox::information(NULL, tr("fatal error"), QString::fromLocal8Bit("超出图像数组"));
			return PARA_INDEX_ERROR;
		}
		catch (...)
		{
			DLOG(LOG_ERROR,"read image block error");
			QMessageBox::information(NULL, tr("fatal error"), QString::fromLocal8Bit("图像读取模块错误"));
			return PARA_INDEX_ERROR;
		}

		return RUN_OK;
	}
private:
	std::string imagepath;
	std::string fun_name;
	//指向paramgr里图像的指针
	int index = -1;
};



