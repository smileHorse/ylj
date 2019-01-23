/********************************************************************
	created:	2019/02/03
	created:	3:2:2019   10:46
	filename: 	E:\Masf\ylj\common\DBData\FactoryData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	FactoryData
	file ext:	h
	author:		Masf
	
	purpose:	分厂数据对象
*********************************************************************/
#ifndef FACTORYDATA_H
#define FACTORYDATA_H

#include <QtCore/QString>

class FactoryData
{
public:
	FactoryData()
		: id(""), name("")
	{}

	QString getId() const { return id; }
	void setId(QString val) { id = val; }

	QString getName() const { return name; }
	void setName(QString val) { name = val; }

private:
	QString id;
	QString name;	// 分厂名称
};
#endif