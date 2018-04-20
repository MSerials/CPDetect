#include "stdafx.h"
#include "XmlParse.h"
#include <iostream>
#include <fstream>
#include "../../QtCommon/common.h"

XmlParse::XmlParse(QObject *parent)
	: QObject(parent)
{
	
}

XmlParse::~XmlParse()
{
}

void XmlParse::Parse()
{
	
}

void XmlParse::Parse(QXmlStreamReader &reader)
{
	DLOG(LOG_INFO, "Start Parse Xml");
	while (!reader.atEnd()) {
		reader.readNext();
		if (reader.isStartElement()) {  // 开始元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "Blog") == 0) {
				qDebug() << QString::fromLocal8Bit("********** 开始元素<Blog> ********** ");
			}
			else if (QString::compare(strElementName, QStringLiteral("作者")) == 0) {  // 方式一
				reader.readNext();
				if (reader.isCharacters()) {
					qDebug() << QStringLiteral("作者：%1").arg(reader.text().toString());
				}
			}
			else if (QString::compare(strElementName, QStringLiteral("主页")) == 0) {  // 方式二 
				qDebug() << QStringLiteral("主页：%1").arg(reader.readElementText());
			}
			else if (QString::compare(strElementName, QStringLiteral("个人说明")) == 0) {
				qDebug() << QStringLiteral("个人说明：%1").arg(reader.readElementText());
			}
		}
		else if (reader.isEntityReference()) {  // 实体引用
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("EntityReference : %1(%2)").arg(strName).arg(strText);
		}
		else if (reader.isCDATA()) {  // CDATA
			QString strCDATA = reader.text().toString();
			qDebug() << QString("CDATA : %1").arg(strCDATA);

			reader.readNext();
			if (reader.isCharacters()) {
				QString strCharacters = reader.text().toString();
				qDebug() << QString("Characters : %1").arg(strCharacters);
			}
		}
		else if (reader.isEndElement()) {  // 结束元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "Blogs") == 0) {
				qDebug() << QString::fromLocal8Bit("********** 结束元素<Blogs> ********** ");
				break;  // 跳出循环（解析 QXmlStreamReader::EndDocument）
			}
			else if (QString::compare(strElementName, "Blog") == 0) {
				qDebug() << QString::fromLocal8Bit("********** 结束元素<Blog> ********** ");
			}
		}
	}

}

bool XmlParse::Read(QString fileName)
{
	using namespace std;

	QFile file(fileName);
	bool isRead = file.open(QIODevice::ReadOnly | QIODevice::Text);
	DLOG(LOG_INFO, "START TO GET XML");
	if (false == isRead)	return false;
	DLOG(LOG_INFO, "Get Xml file Sucecess!");
	qDebug() << QString::fromLocal8Bit("xml file got!");
		QXmlStreamReader reader(&file);
		
		
	//	qDebug() << QString::fromLocal8Bit("start debugging");
		// 解析 XML，直到结束
		while (!reader.atEnd())
		{

			// 读取下一个元素
			QXmlStreamReader::TokenType nType = reader.readNext();

			switch (nType)
			{
			case QXmlStreamReader::StartDocument: {  // 开始文档
				qDebug() << QString("********** 开始文档（XML 声明） ********** ");
				// XML 声明
				QString strVersion = reader.documentVersion().toString();
				QString strEncoding = reader.documentEncoding().toString();
				bool bAlone = reader.isStandaloneDocument();
				qDebug() << QString::fromLocal8Bit("版本：%1  编码：%2  Standalone：%3")
					.arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
				break;
			}
			case QXmlStreamReader::Comment: {  // 注释
				qDebug() << QString::fromLocal8Bit("********** 注释 ********** ");
				QString strComment = reader.text().toString();
				qDebug() << strComment << "\r\n";
				break;
			}
			case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
				qDebug() << QString::fromLocal8Bit("********** 处理指令 ********** ");
				QString strProcInstr = reader.processingInstructionData().toString();
				qDebug() << strProcInstr << "\r\n";
				break;
			}
			case QXmlStreamReader::DTD: {   // DTD
				qDebug() << QString::fromLocal8Bit("********** DTD ********** ");
				QString strDTD = reader.text().toString();
				QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
				QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
																								// DTD 声明
				QString strDTDName = reader.dtdName().toString();
				QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
				QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
				qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
				qDebug() << QString::fromLocal8Bit("DTD 名称 : %1").arg(strDTDName);
				qDebug() << QString::fromLocal8Bit("DTD 公开标识符 : %1").arg(strDTDPublicId);
				qDebug() << QString::fromLocal8Bit("DTD 系统标识符 : %1").arg(strDTDSystemId);
				qDebug() << "\r\n";

				break;
			}
			case QXmlStreamReader::StartElement: {  // 开始元素
				QString strElementName = reader.name().toString();
				if (QString::compare(strElementName, "Blogs") == 0) {  // 根元素
					qDebug() << QString::fromLocal8Bit("********** 开始元素<Blogs> ********** ");
					QXmlStreamAttributes attributes = reader.attributes();
					if (attributes.hasAttribute("Version")) {
						QString strVersion = attributes.value("Version").toString();
						qDebug() << QString::fromLocal8Bit("属性：Version(%1)").arg(strVersion);
					}

					Parse(reader);
				}
				break;
			}
			case QXmlStreamReader::EndDocument: {  // 结束文档
				qDebug() << QString::fromLocal8Bit("********** 结束文档 ********** ");
				break;
			}
			}
		}
	
		

		if (reader.hasError()) {  // 解析出错
			qDebug() << QString::fromLocal8Bit("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
		}

		file.close();  // 关闭文件
	return false;
}


