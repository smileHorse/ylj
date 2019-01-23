/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:10
	filename: 	E:\Masf\ylj\common\DBData\DeviceData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	DeviceData
	file ext:	h
	author:		Masf
	
	purpose:	设备数据
*********************************************************************/
#ifndef DEVICEDATA_H
#define DEVICEDATA_H

#include <QtCore/QString>

class DeviceData
{
public:
	DeviceData()
		: devId(-1), ton(-1), id(-1), used(0), lockState(0)
	{}

	int getDevId() const { return devId; }
	void setDevId(int val) { devId = val; }

	QString getDevNote() const { return devNote; }
	void setDevNote(QString val) { devNote = val; }

	QString getManager() const { return manager; }
	void setManager(QString val) { manager = val; }

	int getTon() const { return ton; }
	void setTon(int val) { ton = val; }

	QString getEleCode() const { return eleCode; }
	void setEleCode(QString val) { eleCode = val; }

	QString getCtrlCode() const { return ctrlCode; }
	void setCtrlCode(QString val) { ctrlCode = val; }

	int getId() const { return id; }
	void setId(int val) { id = val; }

	int getUsed() const { return used; }
	void setUsed(int val) { used = val; }

	QString getEleNum() const { return eleNum; }
	void setEleNum(QString val) { eleNum = val; }

	QString getCtrlNum() const { return ctrlNum; }
	void setCtrlNum(QString val) { ctrlNum = val; }

	QString getCommPara() const { return commPara; }
	void setCommPara(QString val) { commPara = val; }

	int getLockState() const { return lockState; }
	void setLockState(int val) { lockState = val; }

	QString getFactory() const { return factory; }
	void setFactory(QString val) { factory = val; }

private:
	int devId;
	QString devNote;
	QString manager;
	int	ton;
	QString eleCode;
	QString ctrlCode;
	int id;
	int used;
	QString eleNum;
	QString ctrlNum;
	QString commPara;
	int	lockState;
	QString factory;
};

#endif