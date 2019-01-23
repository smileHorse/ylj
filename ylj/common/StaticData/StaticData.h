/*!
 * \file StaticData.h
 *
 * \author Masf
 * \date һ�� 2019
 *
 * ����ͳ�ƶ���
 */

#ifndef STATICDATA_H
#define STATICDATA_H

#include <QVector>
#include <map>
using namespace std;

#include "DBData/BrickTypeData.h"
#include "DBData/BrickParamData.h"
#include "DBData/DeviceData.h"

#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <QtCore/QVector>

#define VAL_CNT_MINUTE	 1	//ÿ����һ���� 
struct HistoryData_Hour
{
	unsigned char dataValidFlag[ 60 * VAL_CNT_MINUTE];//ÿ�������Ч��־ 1-��Ч 0��Ч
	int data[60 * VAL_CNT_MINUTE];
	int type[60 * VAL_CNT_MINUTE];
	int param[60 * VAL_CNT_MINUTE];
	HistoryData_Hour(void )
	{
		memset(this,0,sizeof( HistoryData_Hour)) ;
	}
};

// Сʱ����
class CHourData
{
public:
	CHourData();

	// ͳ����һ��Сʱ������
	int staticHourData();

	// ���÷��ӵ�ֵ
	void setMinuteData(int minute, int value);

private:
	int minuteData[60];		// ÿ����һ����
};

// ÿ������
class CDayData
{
public:
	CDayData(const QString& date);

	// ͳ����һ�������
	int staticDayData();

	QString getDate() const { return date; }
	void setDate(QString val) { date = val; }
	

	CHourData getHourData(int hour) const { return hourData[hour]; }
	void setHourData(int hour, CHourData val) { hourData[hour] = val; }
private:
	QString date;
	CHourData hourData[24];
};


// һ��Ĳ�����ש���ͺĵ�������
class CParamResultData
{
public:
	CParamResultData();

	QString getDate() const { return date; }
	void setDate(QString val) { date = val; }

	int getDevId() const { return devId; }
	void setDevId(int val) { devId = val; }

	int getBrickId() const { return brickId; }
	void setBrickId(int val) { brickId = val; }

	int getParamNo() const { return paramNo; }
	void setParamNo(int val) { paramNo = val; }

	CDayData getDzlData() const { return dzlData; }
	void setDzlData(CDayData val) { dzlData = val; }

	CDayData getHdlData() const { return hdlData; }
	void setHdlData(CDayData val) { hdlData = val; }

	void setDzlDataValue(int hour, int minute, int value);
	void setHdlDataValue(int hour, int minute, int value);

private:
	QString date;
	int devId;
	int brickId;
	int paramNo;
	CDayData dzlData;
	CDayData hdlData;
};


// ͳ�Ʋ������
class CStaticOperResult
{
public:
	CStaticOperResult() {}

	// ���ͳ�ƽ��
	void addParamResultData(QString date, int devId, int brickId, int paramNo, int hour, int minute, int dzl, int hdl);

	QVector<CParamResultData> getResultDatas() const { return resultDatas; }
	void setResultDatas(QVector<CParamResultData> val) { resultDatas = val; }

private:
	QVector<CParamResultData> resultDatas;
};


// ͳ��������ʾ��ʽ
enum StaticDisplayMode
{
	SDM_HOUR,
	SDM_DAY,
	SDM_MONTH
};

// ͳ������
class StaticCondition
{
public:
	StaticCondition()
	{}

	QDateTime getStartTime() const { return startTime; }
	void setStartTime(QDateTime val) { startTime = val; }

	QDateTime getEndTime() const { return endTime; }
	void setEndTime(QDateTime val) { endTime = val; }

	StaticDisplayMode getDisplayMode() const { return displayMode; }
	void setDisplayMode(StaticDisplayMode val) { displayMode = val; }

	int getMinValue() const { return minValue; }
	void setMinValue(int val) { minValue = val; }

	QVector<DeviceData> getDeviceDatas() const { return deviceDatas; }
	void setDeviceDatas(const QVector<DeviceData>& val) { deviceDatas = val; }

	QVector<BrickTypeData> getBrickTypeDatas() const { return brickTypeDatas; }
	void setBrickTypeDatas(const QVector<BrickTypeData>& val) { brickTypeDatas = val; }

	// ��ȡ��ʼ���ڡ���ʼСʱֵ����ʼ����ֵ
	void getStartTimeInfo(QString& date, int& hour, int& minute) const;

	// ��ȡ�������ڡ�����Сʱֵ����������ֵ
	void getEndTimeInfo(QString& date, int& hour, int& minute) const;

	// ��ȡ�豸�ֵ�
	void getDeviceMap(map<int, DeviceData>& deviceMap) const;

	// ��ȡש���ֵ�
	void getBrickTypeMap(map<int, BrickTypeData>& brickTypeMap) const;

private:
	QDateTime startTime;	// ��ʼʱ��
	QDateTime endTime;		// ����ʱ��
	StaticDisplayMode displayMode;	// ��ʾ��ʽ
	int minValue;		// ��С��ש��
	QVector<DeviceData> deviceDatas;	// �豸
	QVector<BrickTypeData> brickTypeDatas;	// ש��
};

// ģʽͳ������
class ParamStaticData
{
public:
	ParamStaticData()
		: dzl(0), hdl(0)
	{}

	BrickParamData getParamData() const { return paramData; }
	void setParamData(const BrickParamData& val) { paramData = val; }

	QString getDate() const { return date; }
	void setDate(QString val) { date = val; }

	long getDzl() const { return dzl; }
	void setDzl(long val) { dzl = val; }

	long getHdl() const { return hdl; }
	void setHdl(long val) { hdl = val; }
private:
	BrickParamData paramData;
	QString date;
	long dzl;
	long hdl;
};

// ש��ͳ������
class BrickTypeStaticData
{
public:
	BrickTypeStaticData()
		: dzl(0), hdl(0)
	{}

	// ͳ�ƴ�ש���ͺĵ�������
	void staticParamStaticDatas();

	// ���ģʽͳ������
	void addParamStaticData(const ParamStaticData& paramStaticData);

	BrickTypeData getBrickTypeData() const { return brickTypeData; }
	void setBrickTypeData(const BrickTypeData& val) { brickTypeData = val; }
	
	QVector<ParamStaticData> getDatas() const { return datas; }
	void setDatas(QVector<ParamStaticData> val) { datas = val; }

	long getDzl() const { return dzl; }
	void setDzl(long val) { dzl = val; }

	long getHdl() const { return hdl; }
	void setHdl(long val) { hdl = val; }
private:
	BrickTypeData brickTypeData;
	QVector<ParamStaticData> datas;
	long dzl;
	long hdl;
};

// �豸ͳ������
class DeviceStaticData
{
public:
	DeviceStaticData()
		: dzl(0), hdl(0)
	{}

	// ͳ�ƴ�ש���ͺĵ�������
	void staticBrickTypeStaticDatas();

	// ���ש��ͳ������
	void addBrickTypeStaticData(const BrickTypeData& brickData, const ParamStaticData& paramStaticData);
	
	DeviceData getDeviceData() const { return deviceData; }
	void setDeviceData(const DeviceData& val) { deviceData = val; }

	QVector<BrickTypeStaticData> getDatas() const  { return datas; }
	void setDatas(QVector<BrickTypeStaticData> val) { datas = val; }

	long getDzl() const { return dzl; }
	void setDzl(long val) { dzl = val; }

	long getHdl() const { return hdl; }
	void setHdl(long val) { hdl = val; }
private:
	DeviceData deviceData;
	QVector<BrickTypeStaticData> datas;
	long dzl;
	long hdl;
};

// ��ֵ����
class ValueData
{
public:
	ValueData()
		: valid(false), value(0)
	{}

	bool isValid() const { return valid; }
	void setValid(bool val) { valid = val; }

	long getValue() const { return value; }
	void setValue(long val) { value = val; }

private:
	bool valid;
	long value;
};

// ͳ�Ƶ���ֵ����
class StaticValueData
{
public:
	
	ValueData getDzlData(int index);
	void setDzlData(int index, long value);

	ValueData getHdlData(int index);
	void setHdlData(int index, long value);

	// ͳ�ƴ�ש��
	long staticDzl();

	// ͳ�ƺĵ���
	long staticHdl();

private:
	ValueData dzlData[60];
	ValueData hdlData[60];
};

// ��������ֵ����
class ParamValueData
{
public:
	ParamValueData()
	{
		hourValueMap.clear();
	}

	ParamValueData(const QString strDate, const DeviceData& device, const BrickTypeData& type,
		const BrickParamData& param)
		: date(strDate), deviceData(device), brickTypeData(type), brickParamData(param)
	{
		hourValueMap.clear();
	}

	QString getDate() const { return date; }
	void setDate(QString val) { date = val; }

	DeviceData getDeviceData() const { return deviceData; }
	void setDeviceData(const DeviceData& val) { deviceData = val; }

	BrickTypeData getBrickTypeData() const { return brickTypeData; }
	void setBrickTypeData(const BrickTypeData& val) { brickTypeData = val; }

	BrickParamData getBrickParamData() const { return brickParamData; }
	void setBrickParamData(const BrickParamData& val) { brickParamData = val; }

	map<int, StaticValueData> getHourValueMap() const { return hourValueMap; }
	void setHourValueMap(map<int, StaticValueData> val) { hourValueMap = val; }

	StaticValueData& getHourValueData(int hour) 
	{
		return hourValueMap[hour];
	}

	// �Ƿ�Ϊͬһ����
	bool isSameData(const ParamValueData& valueData)
	{
		if ((valueData.getDate() == date) && 
			(valueData.getDeviceData().getDevId() == deviceData.getDevId()) &&
			(valueData.getBrickTypeData().getId() == brickTypeData.getId()) && 
			(valueData.getBrickParamData().getNo() == brickParamData.getNo()))
		{
			return true;
		}
		return false;
	}

private:
	QString date;		// ����
	DeviceData deviceData;	// �豸
	BrickTypeData brickTypeData;	// ש��
	BrickParamData brickParamData;	// ģʽ
	map<int, StaticValueData> hourValueMap;	// Сʱֵ
};


// ͳ�����ݲ���
class CStaticOper
{
public:
	// ͳ��һ��ʱ�䷶Χ�����в���������
	bool staticRangeData(QDateTime startTime, QDateTime endTime, CStaticOperResult& operResult);

	// ͳ��һ��ʱ�䷶Χ��ĳ�ֲ���������
	bool staticRangeData(QDateTime startTime, QDateTime endTime, int devId, int brickId, CStaticOperResult& operResult);
	
	// ͳ������
	bool staticData(const StaticCondition& condition, QVector<DeviceStaticData>& staticDatas);

public:
	static void parseStr2HisData(QString& strVal, HistoryData_Hour& hisDataH);

private:
	// ����ʷ����ת��Ϊ������ֵ����
	void addParamValueData(const ParamValueData& valueData, int hour, int minute, int dzl, int hdl, QVector<ParamValueData>& valueDatas);

	// ��Сʱͳ������,�õ����ںʹ�ש�����ĵ�������
	void staticHourData(const ParamValueData& paramValueData, QVector<ParamStaticData>& paramStaticDatas);

	// ����ͳ������
	void staticDayData(const ParamValueData& paramValueData, ParamStaticData& data);

	// ����ͳ������
	void staticMonthData(const ParamValueData& paramValueData, ParamStaticData& data);

	// ���ѹ��ͳ������
	void addDeviceStaticData(const DeviceData& deviceData, const BrickTypeData& brickData, const ParamStaticData& paramStaticData,
		QVector<DeviceStaticData>& staticDatas);
};

#endif