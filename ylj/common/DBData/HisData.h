/********************************************************************
	created:	2019/02/10
	created:	7:2:2019   20:20
	filename: 	E:\Masf\ylj\common\DBData\HisData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	HisData
	file ext:	h
	author:		Masf
	
	purpose:	历史数据
*********************************************************************/
#ifndef HISDATA_H
#define HISDATA_H

#include <QtCore/QString>

class HisData
{
public:
	HisData()
		: devId(-1), hour(-1)
	{}


	int getDevId() const { return devId; }
	void setDevId(int val) { devId = val; }

	QString getTime() const { return time; }
	void setTime(QString val) { time = val; }

	int getHour() const { return hour; }
	void setHour(int val) { hour = val; }

	QString getDzl() const { return dzl; }
	void setDzl(QString val) { dzl = val; }

	QString getHdl() const { return hdl; }
	void setHdl(QString val) { hdl = val; }

private:
	int devId;
	QString time;
	int hour;
	QString dzl;
	QString hdl;
};

#endif