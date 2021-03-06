#pragma once
//#include "global.h"
#include <fstream>
#include <iostream>
#include <QDir>


#ifndef __DEBUGINFO__
#define __DEBUGINFO__

#ifdef _DEBUG
#define _DEBUG_PRINT
#endif

#ifdef _DEBUG_PRINT  
#define DEBUGPRINT DEBUGInfo printinfo(__FILE__, __LINE__, __FUNCTION__);  
#else  
#define DEBUGPRINT  
#endif  


class DEBUGInfo
{
	///
	/*
	usage:
	void init()
	{
	DEBUGPRINT
	}

	
	*/
public:
	DEBUGInfo(QString file, int line, QString func)
		:fileName(file)
		,fileLine(line)
		,funcName(func)
	{
		QString result = "";
		QString beginTime = QDateTime::currentDateTime().toString("[yyyy-dd-MM hh:mm:ss.zzz] ");
		result += beginTime + "Enter:{" + fileName + ":" + QString::number(fileLine) + "---" + funcName + "}";
		qDebug() << result.toStdString().c_str();
	}
	~DEBUGInfo()
	{
		QString result = "";
		QString beginTime = QDateTime::currentDateTime().toString("[yyyy-dd-MM hh:mm:ss.zzz] ");
		result += beginTime + "Leave:{" + fileName + ":" + QString::number(fileLine) + "---" + funcName + "}";
		qDebug() << result.toStdString().c_str();
	};

private:
	QString fileName;
	int fileLine;
	QString funcName;
};  

#endif



#ifndef __LOG_WRITE__
#define __LOG_WRITE__



enum LOGLEVEL {
	LOG_DEBUG = 0,      /**< Debug >**/
	LOG_INFO,           /**< Info >**/
	LOG_WARN,           /**< Warn >**/
	LOG_ERROR           /**< Error >**/
};

#define _LOG 1
#ifdef _LOG
#define DLOG(level,content)	do{LogWriter::getLogCenter()->SaveFileLog(level, content);\
printf("%s\n",content);}while(0);
#else
#define DLOG(level,content)
#endif


class LogWriter {

public:


	static LogWriter* getLogCenter()
	{
		static LogWriter lw;
		return &lw;
/*
		if (_logCenter == NULL)
			_logCenter = new LogWriter;
		return _logCenter;
		*/
	}

	void PrintLog(LOGLEVEL level, const char* msg, ...)
	{
		if (level < _logLevel)  return;     //low level  
		char logBuffer[8192] = { 0 };
		va_list vl_fmt;                     //buffer  
		va_start(vl_fmt, msg);
		vsprintf(logBuffer, msg, vl_fmt);
		va_end(vl_fmt);

		QString fileTime = "";
		QString logTime = "";
		QString logLevel = getLevelStr(level);
		fileTime = QDateTime::currentDateTime().toString("yyyyddMM");
		logTime = QDateTime::currentDateTime().toString("yyyy-dd-MM hh:mm:ss.zzz");
		qDebug("[%s] [%s] {%s}", logTime.toStdString().c_str(), logLevel.toStdString().c_str(), logBuffer);
	}

	void SaveFileLog(LOGLEVEL level, const char* msg, ...)
	{
		if (level < _logLevel)  return;  //low level  
		char logBuffer[8192] = { 0 };
		va_list vl_fmt;                  //buff  
		va_start(vl_fmt, msg);
		vsprintf(logBuffer, msg, vl_fmt);
		va_end(vl_fmt);

		QString logTime = "";
		QString fileTime = "";
		fileTime = QDateTime::currentDateTime().toString("yyyyddMM");
		logTime = QDateTime::currentDateTime().toString("[yyyy-dd-MM hh:mm:ss.zzz]");
		QString logLevel = getLevelStr(level);
		QString logFile = _logPath;
		if (logFile.right(1) != "/") {
			logFile += "/";
		}
		QDir mDir(logFile);
		if (!mDir.exists()) {
			mDir.mkpath(logFile);
		}
		logFile += "isoft_";
		logFile += fileTime;
		logFile += ".log";

		QFile file(logFile);
		file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
		QTextStream out(&file);
		out << logTime << " [" << logLevel << "] " << "{" << logBuffer << "}" << endl;
		file.close();
	}

	void setLogPath(QString logPath)         //defalut: current path
	{
		_logPath = logPath;
	}

	void setLogLevel(LOGLEVEL logLevel)      //defalut: LOG_DEBUG  
	{
		_logLevel = logLevel;
	}

private:
	//static LogWriter * _logCenter;
	explicit LogWriter()
	{
		_logLevel = LOG_DEBUG;
		_logPath = QDir::currentPath();
	}
	~LogWriter()
	{
		/*
		if (_logCenter) {
			delete _logCenter;
			_logCenter = NULL;
		}
		*/
	}
private:
	QString _logPath;
	LOGLEVEL _logLevel;
private:
	QString getLevelStr(LOGLEVEL level)
	{
		switch (level) {
		case LOG_DEBUG: return "LOG_DEBUG"; break;
		case LOG_INFO: return "LOG_INFO"; break;
		case LOG_WARN: return "LOG_WARN"; break;
		case LOG_ERROR: return "LOG_ERROR"; break;
		default :return "LOG_ERROR";
		}
		
	}
};






#endif