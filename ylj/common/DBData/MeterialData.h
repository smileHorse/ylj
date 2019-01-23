/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:20
	filename: 	E:\Masf\ylj\common\DBData\MeterialData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	MeterialData
	file ext:	h
	author:		Masf
	
	purpose:	²ÄÖÊÊý¾Ý
*********************************************************************/
#ifndef METERIALDATA_H
#define METERIALDATA_H

#include <QtCore/QString>

class MeterialData
{
public:
	MeterialData()
		: no(-1)
	{}
	
	int getNo() const { return no; }
	void setNo(int val) { no = val; }

	QString getName() const { return name; }
	void setName(QString val) { name = val; }

private:
	int no;
	QString name;
};

#endif