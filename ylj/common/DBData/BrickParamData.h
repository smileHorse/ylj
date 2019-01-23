/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:20
	filename: 	E:\Masf\ylj\common\DBData\BrickParamData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	BrickParamData
	file ext:	h
	author:		Masf
	
	purpose:	×©ÐÍÊý¾Ý
*********************************************************************/
#ifndef BRICKPARAMDATA_H
#define BRICKPARAMDATA_H

#include <QtCore/QString>

class BrickParamData
{
public:
	BrickParamData()
		: devId(-1), brickId(-1), no(-1)
	{}

	QString getId() const { return id; }
	void setId(QString val) { id = val; }

	int getDevId() const { return devId; }
	void setDevId(int val) { devId = val; }

	int getBrickId() const { return brickId; }
	void setBrickId(int val) { brickId = val; }

	int getNo() const { return no; }
	void setNo(int val) { no = val; }

	QString getName() const { return name; }
	void setName(QString val) { name = val; }

	QString getCreateTime() const { return createTime; }
	void setCreateTime(QString val) { createTime = val; }

	QString getParam() const { return param; }
	void setParam(QString val) { param = val; }

private:
	QString id;
	int devId;
	int brickId;
	int no;
	QString name;
	QString createTime;
	QString param;
};

#endif