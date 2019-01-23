/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:20
	filename: 	E:\Masf\ylj\common\DBData\BrickTypeData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	BrickTypeData
	file ext:	h
	author:		Masf
	
	purpose:	×©ÐÍÊý¾Ý
*********************************************************************/
#ifndef BRICKTYPEDATA_H
#define BRICKTYPEDATA_H

#include <QtCore/QString>

class BrickTypeData
{
public:
	BrickTypeData()
		: id(-1), brkNo(-1), meterial(-1), length(0), width(0), height(0),
		weight(0), other1(0), other2(0), other3(0), other4(0)
	{}
		
	int getId() const { return id; }
	void setId(int val) { id = val; }

	int getBrkNo() const { return brkNo; }
	void setBrkNo(int val) { brkNo = val; }

	QString getName() const { return name; }
	void setName(QString val) { name = val; }

	QString getCreateTime() const { return createTime; }
	void setCreateTime(QString val) { createTime = val; }

	QString getUpdateTime() const { return updateTime; }
	void setUpdateTime(QString val) { updateTime = val; }

	int getMeterial() const { return meterial; }
	void setMeterial(int val) { meterial = val; }

	int getLength() const { return length; }
	void setLength(int val) { length = val; }

	int getWidth() const { return width; }
	void setWidth(int val) { width = val; }

	int getHeight() const { return height; }
	void setHeight(int val) { height = val; }

	int getWeight() const { return weight; }
	void setWeight(int val) { weight = val; }

	int getOther1() const { return other1; }
	void setOther1(int val) { other1 = val; }

	int getOther2() const { return other2; }
	void setOther2(int val) { other2 = val; }

	int getOther3() const { return other3; }
	void setOther3(int val) { other3 = val; }

	int getOther4() const { return other4; }
	void setOther4(int val) { other4 = val; }

	QString getRes() const { return res; }
	void setRes(QString val) { res = val; }

private:
	int id;
	int brkNo;
	QString name;
	QString createTime;
	QString updateTime;
	int meterial;
	int length;
	int width;
	int height;
	int weight;
	int other1;
	int other2;
	int other3;
	int other4;
	QString res;
};

#endif