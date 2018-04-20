#pragma once

#include <qxml.h>
#include <qxmlstream.h>
#include <QObject>

class XmlParse : public QObject
{
	Q_OBJECT

public:
	static XmlParse *GetIns()
	{
		static XmlParse lmxl(nullptr);
		return &lmxl;
	}
	XmlParse(QObject *parent);
	~XmlParse();
	bool Read(QString fileName);

private:
	void Parse();
	void Parse(QXmlStreamReader &reader);

private:
	QXmlStreamReader xml;
};
