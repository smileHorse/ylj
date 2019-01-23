/********************************************************************
	created:	2019/02/03
	created:	3:2:2019   11:06
	filename: 	E:\Masf\ylj\common\DBOper\DBOper.cpp
	file path:	E:\Masf\ylj\common\DBOper
	file base:	DBOper
	file ext:	cpp
	author:		Masf
	
	purpose:	数据库操作
*********************************************************************/

#include "DBOper.h"
#include "ConnectionPool.h"

#include <QDebug>

SqlLocker::SqlLocker()
{
	db = ConnectionPool::openConnection();
}

SqlLocker::~SqlLocker()
{
	ConnectionPool::closeConnection(db);
}

DBOper* DBOper::instance = NULL;

DBOper& DBOper::getInstance()
{
	if (instance == NULL)
	{
		instance = new DBOper();
	}

	return *instance;
}

void DBOper::release()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}

DBOper::DBOper()
{

}

/************************************************************************/
/* 分厂操作                                                             */
/************************************************************************/
bool DBOper::selectFactoryDatas( QVector<FactoryData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from factory"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		FactoryData data;
		data.setId(query.value("id").toString());
		data.setName(query.value("name").toString());
		datas.push_back(data);
	}

	return true;
}

/************************************************************************/
/* 用户操作                                                             */
/************************************************************************/
bool DBOper::selectUserDatas( QVector<UserData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from tuser"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		UserData data;
		data.setId(query.value("id").toInt());
		data.setPassword(query.value("pwd").toString());
		data.setName(query.value("name").toString());
		data.setUserType(query.value("usertype").toInt());
		data.setUserName(query.value("username").toString());
		data.setFactory(query.value("factory").toString());

		datas.push_back(data);
	}

	return true;
}

/************************************************************************/
/* 材质操作                                                             */
/************************************************************************/
bool DBOper::selectMeterialDatas( QVector<MeterialData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from meterial"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		MeterialData data;
		data.setNo(query.value("no").toInt());
		data.setName(query.value("name").toString());

		datas.push_back(data);
	}

	return true;
}


/************************************************************************/
/* 设备操作                                                             */
/************************************************************************/
bool DBOper::selectDeviceDatas( QVector<DeviceData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from devices"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		DeviceData data;
		data.setDevId(query.value("devID").toInt());
		data.setDevNote(query.value("devnote").toString());
		data.setManager(query.value("manager").toString());
		data.setTon(query.value("ton").toInt());
		data.setEleCode(query.value("elecode").toString());
		data.setCtrlCode(query.value("ctrlcode").toString());
		data.setId(query.value("id").toInt());
		data.setUsed(query.value("used").toInt());
		data.setEleNum(query.value("elenum").toString());
		data.setCtrlNum(query.value("ctrlnum").toString());
		data.setCommPara(query.value("commpara").toString());
		data.setLockState(query.value("lockstate").toInt());
		data.setFactory(query.value("factory").toString());

		datas.push_back(data);
	}

	return true;
}

/************************************************************************/
/* 砖型操作                                                             */
/************************************************************************/
bool DBOper::selectBrickTypeDatas( QVector<BrickTypeData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from tbricktype"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		BrickTypeData data;
		data.setId(query.value("id").toInt());
		data.setBrkNo(query.value("brkno").toInt());
		data.setName(query.value("name").toString());
		data.setCreateTime(query.value("createtime").toString());
		data.setUpdateTime(query.value("updatetime").toString());
		data.setMeterial(query.value("meterial").toInt());
		data.setLength(query.value("length").toInt());
		data.setWidth(query.value("width").toInt());
		data.setHeight(query.value("hight").toInt());
		data.setWeight(query.value("weight").toInt());
		data.setOther1(query.value("other1").toInt());
		data.setOther2(query.value("other2").toInt());
		data.setOther3(query.value("other3").toInt());
		data.setOther4(query.value("other4").toInt());
		data.setRes(query.value("res").toString());

		datas.push_back(data);
	}

	return true;
}


bool DBOper::selectBrickTypeDatasByMeterial(QVector<BrickTypeData>& datas, int meterial)
{
	SqlLocker locker;

	QString sqlQuery = QString("select * from tbricktype where meterial = %1").arg(meterial);
	QSqlQuery query(locker.getDb());
	if(!query.exec(sqlQuery))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		BrickTypeData data;
		data.setId(query.value("id").toInt());
		data.setBrkNo(query.value("brkno").toInt());
		data.setName(query.value("name").toString());
		data.setCreateTime(query.value("createtime").toString());
		data.setUpdateTime(query.value("updatetime").toString());
		data.setMeterial(query.value("meterial").toInt());
		data.setLength(query.value("length").toInt());
		data.setWidth(query.value("width").toInt());
		data.setHeight(query.value("hight").toInt());
		data.setWeight(query.value("weight").toInt());
		data.setOther1(query.value("other1").toInt());
		data.setOther2(query.value("other2").toInt());
		data.setOther3(query.value("other3").toInt());
		data.setOther4(query.value("other4").toInt());
		data.setRes(query.value("res").toString());

		datas.push_back(data);
	}

	return true;
}

/************************************************************************/
/* 砖型参数操作                                                          */
/************************************************************************/
bool DBOper::selectBrickParamDatas( QVector<BrickParamData>& datas )
{
	SqlLocker locker;

	QSqlQuery query(locker.getDb());
	if(!query.exec("select * from brickparam"))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		BrickParamData data;
		data.setId(query.value("id").toString());
		data.setDevId(query.value("devid").toInt());
		data.setBrickId(query.value("brickid").toInt());
		data.setNo(query.value("no").toInt());
		data.setName(query.value("name").toString());
		data.setCreateTime(query.value("createtime").toString());
		data.setParam(query.value("param").toString());

		datas.push_back(data);
	}

	return true;
}

/************************************************************************/
/* 历史数据操作                                                          */
/************************************************************************/
bool DBOper::selectHisDatas(QVector<HisData>& datas, const QString& startTime, const QString& endTime)
{
	SqlLocker locker;

	QString strQuery = QString("select * from hisdata where time >= '%1' and time <= '%2'").arg(startTime).arg(endTime);
	QSqlQuery query(locker.getDb());
	if(!query.exec(strQuery))
	{
		qDebug() << query.lastError() << endl;
		return false;
	}

	while(query.next())
	{
		HisData data;
		data.setDevId(query.value("devID").toInt());
		data.setTime(query.value("time").toString());
		data.setHour(query.value("hour").toInt());
		data.setDzl(query.value("dzl").toString());
		data.setHdl(query.value("hdl").toString());

		datas.push_back(data);
	}

	return true;
}

