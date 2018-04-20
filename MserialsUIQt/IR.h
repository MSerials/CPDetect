#pragma once
#include <QObject>
#include <string>
#include <stdio.h>
//#include <hash_map>
#include <stack>
#include <vector>
#include <fstream>
#include <functional>
#include <typeinfo>
#include <new>
#include <tuple>
#include <type_traits>
#include "../../QtCommon/common.h"
#include "ImageMgr.h"

using namespace std;

#ifndef __IR__
#define __IR__








//参数管理
class ParamMgr
{
public:
	ParamMgr() {};
	static ParamMgr * GetIns()
	{
		static ParamMgr l_pm;
		return &l_pm;
	}

	std::vector<cv::Point2d> ponits;
	std::vector<cv::Mat>	mats;
};



class AObject : public QDialog
{
public:
	enum
	{
		RUN_OK,
		PATH_ERROR,
		IMAGE_ERROR,
		PARA_INDEX_ERROR
	};
	AObject() {};
	virtual ~AObject() {};
	std::string fun_name;
	virtual std::string GetFunName() = 0;
	//返回错误代号
	virtual int Runnable() = 0;
	virtual int Method() = 0;
};


//执行序列表而已
class Execuate
{
public:
	Execuate() {};
	static Execuate * GetIns()
	{
		static Execuate l_Ec;
		return &l_Ec;
	}

	std::vector<AObject*> exes;
};







#endif









































