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
		if (reader.isStartElement()) {  // ��ʼԪ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "Blog") == 0) {
				qDebug() << QString::fromLocal8Bit("********** ��ʼԪ��<Blog> ********** ");
			}
			else if (QString::compare(strElementName, QStringLiteral("����")) == 0) {  // ��ʽһ
				reader.readNext();
				if (reader.isCharacters()) {
					qDebug() << QStringLiteral("���ߣ�%1").arg(reader.text().toString());
				}
			}
			else if (QString::compare(strElementName, QStringLiteral("��ҳ")) == 0) {  // ��ʽ�� 
				qDebug() << QStringLiteral("��ҳ��%1").arg(reader.readElementText());
			}
			else if (QString::compare(strElementName, QStringLiteral("����˵��")) == 0) {
				qDebug() << QStringLiteral("����˵����%1").arg(reader.readElementText());
			}
		}
		else if (reader.isEntityReference()) {  // ʵ������
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
		else if (reader.isEndElement()) {  // ����Ԫ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "Blogs") == 0) {
				qDebug() << QString::fromLocal8Bit("********** ����Ԫ��<Blogs> ********** ");
				break;  // ����ѭ�������� QXmlStreamReader::EndDocument��
			}
			else if (QString::compare(strElementName, "Blog") == 0) {
				qDebug() << QString::fromLocal8Bit("********** ����Ԫ��<Blog> ********** ");
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
		// ���� XML��ֱ������
		while (!reader.atEnd())
		{

			// ��ȡ��һ��Ԫ��
			QXmlStreamReader::TokenType nType = reader.readNext();

			switch (nType)
			{
			case QXmlStreamReader::StartDocument: {  // ��ʼ�ĵ�
				qDebug() << QString("********** ��ʼ�ĵ���XML ������ ********** ");
				// XML ����
				QString strVersion = reader.documentVersion().toString();
				QString strEncoding = reader.documentEncoding().toString();
				bool bAlone = reader.isStandaloneDocument();
				qDebug() << QString::fromLocal8Bit("�汾��%1  ���룺%2  Standalone��%3")
					.arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
				break;
			}
			case QXmlStreamReader::Comment: {  // ע��
				qDebug() << QString::fromLocal8Bit("********** ע�� ********** ");
				QString strComment = reader.text().toString();
				qDebug() << strComment << "\r\n";
				break;
			}
			case QXmlStreamReader::ProcessingInstruction: {  // ����ָ��
				qDebug() << QString::fromLocal8Bit("********** ����ָ�� ********** ");
				QString strProcInstr = reader.processingInstructionData().toString();
				qDebug() << strProcInstr << "\r\n";
				break;
			}
			case QXmlStreamReader::DTD: {   // DTD
				qDebug() << QString::fromLocal8Bit("********** DTD ********** ");
				QString strDTD = reader.text().toString();
				QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // ��������
				QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // ʵ������
																								// DTD ����
				QString strDTDName = reader.dtdName().toString();
				QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD ������ʶ��
				QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD ϵͳ��ʶ��
				qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
				qDebug() << QString::fromLocal8Bit("DTD ���� : %1").arg(strDTDName);
				qDebug() << QString::fromLocal8Bit("DTD ������ʶ�� : %1").arg(strDTDPublicId);
				qDebug() << QString::fromLocal8Bit("DTD ϵͳ��ʶ�� : %1").arg(strDTDSystemId);
				qDebug() << "\r\n";

				break;
			}
			case QXmlStreamReader::StartElement: {  // ��ʼԪ��
				QString strElementName = reader.name().toString();
				if (QString::compare(strElementName, "Blogs") == 0) {  // ��Ԫ��
					qDebug() << QString::fromLocal8Bit("********** ��ʼԪ��<Blogs> ********** ");
					QXmlStreamAttributes attributes = reader.attributes();
					if (attributes.hasAttribute("Version")) {
						QString strVersion = attributes.value("Version").toString();
						qDebug() << QString::fromLocal8Bit("���ԣ�Version(%1)").arg(strVersion);
					}

					Parse(reader);
				}
				break;
			}
			case QXmlStreamReader::EndDocument: {  // �����ĵ�
				qDebug() << QString::fromLocal8Bit("********** �����ĵ� ********** ");
				break;
			}
			}
		}
	
		

		if (reader.hasError()) {  // ��������
			qDebug() << QString::fromLocal8Bit("������Ϣ��%1  �кţ�%2  �кţ�%3  �ַ�λ�ƣ�%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
		}

		file.close();  // �ر��ļ�
	return false;
}


