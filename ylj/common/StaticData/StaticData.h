/*!
 * \file StaticData.h
 *
 * \author Masf
 * \date 一月 2019
 *
 * 数据统计对象
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

#define VAL_CNT_MINUTE	 1	//每分钟一个点 
struct HistoryData_Hour
{
	unsigned char dataValidFlag[ 60 * VAL_CNT_MINUTE];//每个点的有效标志 1-有效 0无效
	int data[60 * VAL_CNT_MINUTE];
	int type[60 * VAL_CNT_MINUTE];
	int param[60 * VAL_CNT_MINUTE];
	HistoryData_Hour(void )
	{
		memset(this,0,sizeof( HistoryData_Hour)) ;
	}
};

// 小时数据
class CHourData
{
public:
	CHourData();

	// 统计这一个小时的数据
	int staticHourData();

	// 设置分钟的值
	void setMinuteData(int minute, int value);

private:
	int minuteData[60];		// 每分钟一个点
};

// 每天数据
class CDayData
{
public:
	CDayData(const QString& date);

	// 统计这一天的数据
	int staticDayData();

	QString getDate() const { return date; }
	void setDate(QString val) { date = val; }
	

	CHourData getHourData(int hour) const { return hourData[hour]; }
	void setHourData(int hour, CHourData val) { hourData[hour] = val; }
private:
	QString date;
	CHourData hourData[24];
};


// 一天的参数打砖量和耗电量数据
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


// 统计操作结果
class CStaticOperResult
{
public:
	CStaticOperResult() {}

	// 添加统计结果
	void addParamResultData(QString date, int devId, int brickId, int paramNo, int hour, int minute, int dzl, int hdl);

	QVector<CParamResultData> getResultDatas() const { return resultDatas; }
	void setResultDatas(QVector<CParamResultData> val) { resultDatas = val; }

private:
	QVector<CParamResultData> resultDatas;
};


// 统计数据显示格式
enum StaticDisplayMode
{
	SDM_HOUR,
	SDM_DAY,
	SDM_MONTH
};

// 统计条件
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

	// 获取开始日期、开始小时值、开始分钟值
	void getStartTimeInfo(QString& date, int& hour, int& minute) const;

	// 获取结束日期、结束小时值、结束分钟值
	void getEndTimeInfo(QString& date, int& hour, int& minute) const;

	// 获取设备字典
	void getDeviceMap(map<int, DeviceData>& deviceMap) const;

	// 获取砖型字典
	void getBrickTypeMap(map<int, BrickTypeData>& brickTypeMap) const;

private:
	QDateTime startTime;	// 开始时间
	QDateTime endTime;		// 结束时间
	StaticDisplayMode displayMode;	// 显示格式
	int minValue;		// 最小打砖量
	QVector<DeviceData> deviceDatas;	// 设备
	QVector<BrickTypeData> brickTypeDatas;	// 砖型
};

// 模式统计数据
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

// 砖型统计数据
class BrickTypeStaticData
{
public:
	BrickTypeStaticData()
		: dzl(0), hdl(0)
	{}

	// 统计打砖量和耗电量总量
	void staticParamStaticDatas();

	// 添加模式统计数据
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

// 设备统计数据
class DeviceStaticData
{
public:
	DeviceStaticData()
		: dzl(0), hdl(0)
	{}

	// 统计打砖量和耗电量总量
	void staticBrickTypeStaticDatas();

	// 添加砖型统计数据
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

// 数值类型
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

// 统计的数值类型
class StaticValueData
{
public:
	
	ValueData getDzlData(int index);
	void setDzlData(int index, long value);

	ValueData getHdlData(int index);
	void setHdlData(int index, long value);

	// 统计打砖量
	long staticDzl();

	// 统计耗电量
	long staticHdl();

private:
	ValueData dzlData[60];
	ValueData hdlData[60];
};

// 参数的数值类型
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

	// 是否为同一对象
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
	QString date;		// 日期
	DeviceData deviceData;	// 设备
	BrickTypeData brickTypeData;	// 砖型
	BrickParamData brickParamData;	// 模式
	map<int, StaticValueData> hourValueMap;	// 小时值
};


// 统计数据操作
class CStaticOper
{
public:
	// 统计一段时间范围内所有参数的数据
	bool staticRangeData(QDateTime startTime, QDateTime endTime, CStaticOperResult& operResult);

	// 统计一段时间范围内某种参数的数据
	bool staticRangeData(QDateTime startTime, QDateTime endTime, int devId, int brickId, CStaticOperResult& operResult);
	
	// 统计数据
	bool staticData(const StaticCondition& condition, QVector<DeviceStaticData>& staticDatas);

public:
	static void parseStr2HisData(QString& strVal, HistoryData_Hour& hisDataH);

private:
	// 将历史数据转换为参数数值数据
	void addParamValueData(const ParamValueData& valueData, int hour, int minute, int dzl, int hdl, QVector<ParamValueData>& valueDatas);

	// 按小时统计数据,得到日期和打砖量、耗电量数据
	void staticHourData(const ParamValueData& paramValueData, QVector<ParamStaticData>& paramStaticDatas);

	// 按天统计数据
	void staticDayData(const ParamValueData& paramValueData, ParamStaticData& data);

	// 按月统计数据
	void staticMonthData(const ParamValueData& paramValueData, ParamStaticData& data);

	// 添加压机统计数据
	void addDeviceStaticData(const DeviceData& deviceData, const BrickTypeData& brickData, const ParamStaticData& paramStaticData,
		QVector<DeviceStaticData>& staticDatas);
};

#endif