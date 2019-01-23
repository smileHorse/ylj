/********************************************************************
	created:	2019/02/03
	created:	3:2:2019   11:06
	filename: 	E:\Masf\ylj\common\DBOper\DBOper.h
	file path:	E:\Masf\ylj\common\DBOper
	file base:	DBOper
	file ext:	h
	author:		Masf
	
	purpose:	数据库操作
*********************************************************************/
#ifndef DBOPER_H
#define DBOPER_H

#include "../DBData/FactoryData.h"
#include "../DBData/UserData.h"
#include "../DBData/MeterialData.h"
#include "../DBData/DeviceData.h"
#include "../DBData/BrickTypeData.h"
#include "../DBData/BrickParamData.h"
#include "../DBData/HisData.h"

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtSql/QtSql>

class SqlLocker
{
public:
	SqlLocker();
	~SqlLocker();

	QSqlDatabase getDb() const { return db; }

private:
	QSqlDatabase db; 
};

class DBOper
{
public:
	static DBOper& getInstance();	// 获取实例
	static void release();			// 释放实例

private:
	DBOper();
	DBOper(const DBOper& other);
	DBOper& operator=(const DBOper& other);

public:
	/************************************************************************/
	/* 分厂操作                                                             */
	/************************************************************************/
	bool selectFactoryDatas(QVector<FactoryData>& datas);

	/************************************************************************/
	/* 用户操作                                                             */
	/************************************************************************/
	bool selectUserDatas(QVector<UserData>& datas);

	/************************************************************************/
	/* 材质操作                                                             */
	/************************************************************************/
	bool selectMeterialDatas(QVector<MeterialData>& datas);

	/************************************************************************/
	/* 设备操作                                                             */
	/************************************************************************/
	bool selectDeviceDatas(QVector<DeviceData>& datas);

	/************************************************************************/
	/* 砖型操作                                                             */
	/************************************************************************/
	bool selectBrickTypeDatas(QVector<BrickTypeData>& datas);
	bool selectBrickTypeDatasByMeterial(QVector<BrickTypeData>& datas, int meterial);

	/************************************************************************/
	/* 砖型参数操作                                                          */
	/************************************************************************/
	bool selectBrickParamDatas(QVector<BrickParamData>& datas);

	/************************************************************************/
	/* 历史数据操作                                                          */
	/************************************************************************/
	bool selectHisDatas(QVector<HisData>& datas, const QString& startTime, const QString& endTime);

private:
	static DBOper* instance;
};
#endif