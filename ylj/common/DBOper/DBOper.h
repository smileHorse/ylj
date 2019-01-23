/********************************************************************
	created:	2019/02/03
	created:	3:2:2019   11:06
	filename: 	E:\Masf\ylj\common\DBOper\DBOper.h
	file path:	E:\Masf\ylj\common\DBOper
	file base:	DBOper
	file ext:	h
	author:		Masf
	
	purpose:	���ݿ����
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
	static DBOper& getInstance();	// ��ȡʵ��
	static void release();			// �ͷ�ʵ��

private:
	DBOper();
	DBOper(const DBOper& other);
	DBOper& operator=(const DBOper& other);

public:
	/************************************************************************/
	/* �ֳ�����                                                             */
	/************************************************************************/
	bool selectFactoryDatas(QVector<FactoryData>& datas);

	/************************************************************************/
	/* �û�����                                                             */
	/************************************************************************/
	bool selectUserDatas(QVector<UserData>& datas);

	/************************************************************************/
	/* ���ʲ���                                                             */
	/************************************************************************/
	bool selectMeterialDatas(QVector<MeterialData>& datas);

	/************************************************************************/
	/* �豸����                                                             */
	/************************************************************************/
	bool selectDeviceDatas(QVector<DeviceData>& datas);

	/************************************************************************/
	/* ש�Ͳ���                                                             */
	/************************************************************************/
	bool selectBrickTypeDatas(QVector<BrickTypeData>& datas);
	bool selectBrickTypeDatasByMeterial(QVector<BrickTypeData>& datas, int meterial);

	/************************************************************************/
	/* ש�Ͳ�������                                                          */
	/************************************************************************/
	bool selectBrickParamDatas(QVector<BrickParamData>& datas);

	/************************************************************************/
	/* ��ʷ���ݲ���                                                          */
	/************************************************************************/
	bool selectHisDatas(QVector<HisData>& datas, const QString& startTime, const QString& endTime);

private:
	static DBOper* instance;
};
#endif