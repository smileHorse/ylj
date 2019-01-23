/*!
 * \file StaticData.h
 *
 * \author Masf
 * \date 一月 2019
 *
 * 数据统计对象
 */

#include "StaticData.h"
#include "DBOper/DBOper.h"
#include "DBData/HisData.h"
#include <algorithm>

/************************************************************************/
/* 小时数据                                                             */
/************************************************************************/
CHourData::CHourData()
{
	for (int i = 0; i < 60; ++i)
	{
		minuteData[i] = 0;
	}
}

// 统计这一个小时的数据
int CHourData::staticHourData()
{
	int sum  = 0;
	for (int i = 1; i < 60; ++i)
	{
		if (minuteData[i] != 0 && minuteData[i-1] != 0)
		{
			sum += minuteData[i] - minuteData[i - 1];
		}
	}
	return sum;
}

// 设置分钟的值
void CHourData::setMinuteData(int minute, int value)
{
	if (minute >= 0 && minute < 60)
	{
		minuteData[minute] = value;
	}
}

/************************************************************************/
/* 每天数据                                                             */
/************************************************************************/

CDayData::CDayData(const QString& date)
{
	this->date = date;
}

// 统计这一天的数据
int CDayData::staticDayData()
{
	int sum = 0;
	for (int i = 0; i < 24; ++i)
	{
		int hourSum = hourData[i].staticHourData();
		sum += hourSum;
	}
	return sum;
}

/************************************************************************/
/* 参数结果类                                                           */
/************************************************************************/
CParamResultData::CParamResultData()
	: dzlData(""), hdlData("")
{
}

void CParamResultData::setDzlDataValue(int hour, int minute, int value)
{
	CHourData hourData = dzlData.getHourData(hour);
	hourData.setMinuteData(minute, value);
	dzlData.setHourData(hour, hourData);
}

void CParamResultData::setHdlDataValue(int hour, int minute, int value)
{
	CHourData hourData = hdlData.getHourData(hour);
	hourData.setMinuteData(minute, value);
	hdlData.setHourData(hour, hourData);
}


/************************************************************************/
/* 统计操作结果类                                                           */
/************************************************************************/
// 添加统计结果
void CStaticOperResult::addParamResultData(QString date, int devId, int brickId, int paramNo, int hour, int minute,
	int dzl, int hdl)
{
	for (size_t i = 0; i < resultDatas.size(); ++i)
	{
		if (resultDatas[i].getDate() == date && resultDatas[i].getDevId() == devId
			&& resultDatas[i].getBrickId() == brickId && resultDatas[i].getParamNo() == paramNo)
		{
			resultDatas[i].setDzlDataValue(hour, minute, dzl);
			resultDatas[i].setHdlDataValue(hour, minute, hdl);
			return;
		}
	}

	CParamResultData resultData;
	resultData.setDate(date);
	resultData.setDevId(devId);
	resultData.setBrickId(brickId);
	resultData.setParamNo(paramNo);
	resultData.setDzlDataValue(hour, minute, dzl);
	resultData.setHdlDataValue(hour, minute, hdl);
	resultDatas.push_back(resultData);
}

/************************************************************************/
/* 统计操作类                                                           */
/************************************************************************/
// 统计数据
bool CStaticOper::staticData(const StaticCondition& condition, QVector<DeviceStaticData>& staticDatas)
{
	// 根据统计条件，从历史库中查询数据
	DBOper& dbOper = DBOper::getInstance();

	// 从条件中获取设备字典、砖型字典、模式字典
	map<int, DeviceData> deviceMap;
	map<int, BrickTypeData> brickTypeMap;
	map<QString, BrickParamData> brickParamMap;
	condition.getDeviceMap(deviceMap);
	condition.getBrickTypeMap(brickTypeMap);

	QVector<BrickParamData> paramDatas;
	dbOper.selectBrickParamDatas(paramDatas);
	for (size_t i = 0; i < paramDatas.size(); ++i)
	{
		BrickParamData paramData = paramDatas[i];
		QString key = QString("%1-%2-%3").arg(paramData.getDevId()).arg(paramData.getBrickId()).arg(paramData.getNo());
		brickParamMap.insert(std::make_pair(key, paramData));
	}

	// 获取时间范围
	QString strStartDate, strEndDate;
	int startHour, startMinute, endHour, endMinute;
	condition.getStartTimeInfo(strStartDate, startHour, startMinute);
	condition.getEndTimeInfo(strEndDate, endHour, endMinute);
	QVector<HisData> hisDatas;
	dbOper.selectHisDatas(hisDatas, strStartDate, strEndDate);

	// 获取打砖量最小值
	int minValue = condition.getMinValue();

	// 循环处理所有查找出来的历史数据,并转换为参数数值数据
	QVector<ParamValueData> paramValueDatas;
	for (size_t i = 0; i < hisDatas.size(); ++i)
	{
		HisData hisData = hisDatas[i];

		// 判断是否为所选择的设备
		int devId = hisData.getDevId();
		map<int, DeviceData>::iterator devIter = deviceMap.find(devId);
		if (devIter == deviceMap.end())
		{
			continue;
		}
		DeviceData deviceData = devIter->second;

		// 判断是否为所选时间段内的数据
		QString strDate = hisData.getTime();
		int hour = hisData.getHour();
		if ((strDate == strStartDate && hour < startHour) || (strDate == strEndDate && hour > endHour))
		{
			continue;
		}

		// 转换打砖量、耗电量数据
		QString strDzl = hisData.getDzl();
		QString strHdl = hisData.getHdl();
		HistoryData_Hour dzlHourData;
		HistoryData_Hour hdlHourData;
		CStaticOper::parseStr2HisData(strDzl, dzlHourData);
		CStaticOper::parseStr2HisData(strHdl, hdlHourData);
		for (int minute = 0; minute < 60; ++minute)
		{
			if ((strDate == strStartDate && hour == startHour && minute < startMinute) || 
				(strDate == strEndDate && hour == endHour && minute > endMinute))
			{
				continue;
			}

			// 判断是否为所选择的砖型
			int brickTypeId = dzlHourData.type[minute];
			map<int, BrickTypeData>::iterator brickIter = brickTypeMap.find(brickTypeId);
			if (brickIter == brickTypeMap.end())
			{
				continue;
			}
			BrickTypeData brickTypeData = brickIter->second;

			// 判断模式是否有效
			int paramNo = dzlHourData.param[minute];
			QString key = QString("%1-%2-%3").arg(devId).arg(brickTypeId).arg(paramNo);
			map<QString, BrickParamData>::iterator paramIter = brickParamMap.find(key);
			if (paramIter == brickParamMap.end())
			{
				continue;
			}
			BrickParamData paramData = paramIter->second;

			if (dzlHourData.dataValidFlag[minute] && hdlHourData.dataValidFlag[minute])
			{
				ParamValueData valueData(strDate, deviceData, brickTypeData, paramData);
				addParamValueData(valueData, hour, minute, dzlHourData.data[minute],
					hdlHourData.data[minute], paramValueDatas);
			}
		}
	}

	// 根据最小打砖量过滤数据,过滤掉每小时打砖量小于指定值的数据
	QVector<ParamValueData> filterParamValueDatas;
	for (QVector<ParamValueData>::iterator iter = paramValueDatas.begin(); iter != paramValueDatas.end(); ++iter)
	{
		map<int, StaticValueData> validDataMap;
		map<int, StaticValueData> dataMap = iter->getHourValueMap();
		for (map<int, StaticValueData>::iterator mapIter = dataMap.begin(); mapIter != dataMap.end(); ++mapIter)
		{
			long dzlValue = mapIter->second.staticDzl();
			if (dzlValue >= minValue)
			{
				validDataMap.insert(std::make_pair(mapIter->first, mapIter->second));
			}
		}
		if (!validDataMap.empty())
		{
			ParamValueData valueData = *iter;
			valueData.setHourValueMap(validDataMap);
			filterParamValueDatas.push_back(valueData);
		}
	}

	// 根据显示方式将参数数值数值转换为压机的统计数据
	if (condition.getDisplayMode() == SDM_HOUR)
	{
		for (QVector<ParamValueData>::iterator iter = filterParamValueDatas.begin(); iter != filterParamValueDatas.end(); ++iter)
		{
			QVector<ParamStaticData> paramStaticDatas;
			staticHourData(*iter, paramStaticDatas);
			for (QVector<ParamStaticData>::iterator stIter = paramStaticDatas.begin(); stIter != paramStaticDatas.end(); ++stIter)
			{
				addDeviceStaticData(iter->getDeviceData(), iter->getBrickTypeData(), *stIter, staticDatas);
			}
		}
	}
	else if (condition.getDisplayMode() == SDM_DAY)
	{
		for (QVector<ParamValueData>::iterator iter = filterParamValueDatas.begin(); iter != filterParamValueDatas.end(); ++iter)
		{
			ParamStaticData staticData;
			staticDayData(*iter, staticData);
			addDeviceStaticData(iter->getDeviceData(), iter->getBrickTypeData(), staticData, staticDatas);
		}
	}
	else if (condition.getDisplayMode() == SDM_MONTH)
	{
		for (QVector<ParamValueData>::iterator iter = filterParamValueDatas.begin(); iter != filterParamValueDatas.end(); ++iter)
		{
			ParamStaticData staticData;
			staticMonthData(*iter, staticData);
			addDeviceStaticData(iter->getDeviceData(), iter->getBrickTypeData(), staticData, staticDatas);
		}
	}
	return true;
}

// 统计一段时间范围内所有参数的数据
bool CStaticOper::staticRangeData(QDateTime startTime, QDateTime endTime, CStaticOperResult& operResult)
{
	DBOper& dbOper = DBOper::getInstance();

	QString strStartTime = startTime.toString("yyyy-MM-dd");
	int startHour = startTime.time().hour();
	QString strEndTime = endTime.toString("yyyy-MM-dd");
	int endHour = endTime.time().hour();

	QVector<HisData> hisDatas;
	dbOper.selectHisDatas(hisDatas, strStartTime, strEndTime);
	for (QVector<HisData>::iterator iter = hisDatas.begin(); iter != hisDatas.end(); ++iter)
	{
		QString dataTime = iter->getTime();
		int devId = iter->getDevId();
		int hour = iter->getHour();

		QString strDzl = iter->getDzl();
		QString strHdl = iter->getHdl();
		HistoryData_Hour dzlHistoryData;
		CStaticOper::parseStr2HisData(strDzl, dzlHistoryData);
		HistoryData_Hour hdlHistoryData;
		CStaticOper::parseStr2HisData(strHdl, hdlHistoryData);

		if ((dataTime == strStartTime && hour >= startHour) || (dataTime == strEndTime && hour <= endHour) || 
			(dataTime != strStartTime && dataTime != strEndTime))
		{
			CHourData dzlHourData;
			CHourData hdlHourData;
			for (int i = 0; i < 60; ++i)
			{
				if (dzlHistoryData.dataValidFlag[i])
				{
					operResult.addParamResultData(dataTime, devId, dzlHistoryData.type[i], dzlHistoryData.param[i],
						hour, i, dzlHistoryData.data[i], hdlHistoryData.data[i]);
				}
			}
		}
	}
	return true;
}

// 统计一段时间范围内某种参数的数据
bool CStaticOper::staticRangeData(QDateTime startTime, QDateTime endTime, int devId, int brickId, CStaticOperResult& operResult)
{
	DBOper& dbOper = DBOper::getInstance();

	QString strStartTime = startTime.toString("yyyy-MM-dd");
	int startHour = startTime.time().hour();
	QString strEndTime = endTime.toString("yyyy-MM-dd");
	int endHour = endTime.time().hour();

	QVector<HisData> hisDatas;
	dbOper.selectHisDatas(hisDatas, strStartTime, strEndTime);
	for (QVector<HisData>::iterator iter = hisDatas.begin(); iter != hisDatas.end(); ++iter)
	{
		QString dataTime = iter->getTime();
		int hour = iter->getHour();
		if (iter->getDevId() != devId)
		{
			continue;
		}

		QString strDzl = iter->getDzl();
		QString strHdl = iter->getHdl();
		HistoryData_Hour dzlHistoryData;
		CStaticOper::parseStr2HisData(strDzl, dzlHistoryData);
		HistoryData_Hour hdlHistoryData;
		CStaticOper::parseStr2HisData(strHdl, hdlHistoryData);

		if ((dataTime == strStartTime && hour >= startHour) || (dataTime == strEndTime && hour <= endHour) || 
			(dataTime != strStartTime && dataTime != strEndTime))
		{
			CHourData dzlHourData;
			CHourData hdlHourData;
			for (int i = 0; i < 60; ++i)
			{
				if (dzlHistoryData.dataValidFlag[i] && dzlHistoryData.type[i] == brickId)
				{
					operResult.addParamResultData(dataTime, devId,  brickId, dzlHistoryData.param[i],
						hour, i, dzlHistoryData.data[i], hdlHistoryData.data[i]);
				}
			}
		}
	}
	return true;
}

void CStaticOper::parseStr2HisData(QString& strVal,HistoryData_Hour& hisDataH)
{
	QStringList strValues = strVal.split("|");
	for (QStringList::iterator iter = strValues.begin(); iter != strValues.end(); ++iter)
	{
		QString strValue = *iter;
		QStringList subValues = strValue.split(",");
		if (subValues.size() != 4)
		{
			continue;
		}
		int minute = subValues.at(0).toInt();
		if (minute >= 0 && minute <= 59)
		{
			hisDataH.dataValidFlag[ minute ] = 1;
			hisDataH.type[minute] = subValues.at(1).toInt();
			hisDataH.param[minute] = subValues.at(2).toInt();
			hisDataH.data[minute] = subValues.at(3).toInt();
		}
	}  
}

// 将历史数据转换为参数数值数据
void CStaticOper::addParamValueData(const ParamValueData& valueData, int hour, int minute, int dzl, int hdl, 
	QVector<ParamValueData>& valueDatas)
{
	for (QVector<ParamValueData>::iterator iter = valueDatas.begin(); iter != valueDatas.end(); ++iter)
	{
		if (iter->isSameData(valueData))
		{
			iter->getHourValueData(hour).setDzlData(minute, dzl);
			iter->getHourValueData(hour).setHdlData(minute, hdl);
			return;
		}
	}

	ParamValueData paramValueData = valueData;
	paramValueData.getHourValueData(hour).setDzlData(minute, dzl);
	paramValueData.getHourValueData(hour).setHdlData(minute, hdl);
	valueDatas.push_back(paramValueData);
}

// 按小时统计数据,得到日期和打砖量、耗电量数据
void CStaticOper::staticHourData(const ParamValueData& paramValueData, QVector<ParamStaticData>& paramStaticDatas)
{
	map<int, StaticValueData> dataMap = paramValueData.getHourValueMap();
	for (map<int, StaticValueData>::iterator iter = dataMap.begin(); iter != dataMap.end(); ++iter)
	{
		QString date = QString("%1 %2:00 - %3:59").arg(paramValueData.getDate()).arg(iter->first).arg(iter->first);
		long dzl = iter->second.staticDzl();
		long hdl = iter->second.staticHdl();

		ParamStaticData data;
		data.setParamData(paramValueData.getBrickParamData());
		data.setDate(date);
		data.setDzl(dzl);
		data.setHdl(hdl);
		paramStaticDatas.push_back(data);
	}
}

// 按天统计数据
void CStaticOper::staticDayData(const ParamValueData& paramValueData, ParamStaticData& data)
{
	QString date = paramValueData.getDate();
	long dzl = 0, hdl = 0;
	map<int, StaticValueData> dataMap = paramValueData.getHourValueMap();
	for (map<int, StaticValueData>::iterator iter = dataMap.begin(); iter != dataMap.end(); ++iter)
	{		
		dzl += iter->second.staticDzl();
		hdl += iter->second.staticHdl();
	}

	data.setParamData(paramValueData.getBrickParamData());
	data.setDate(date);
	data.setDzl(dzl);
	data.setHdl(hdl);
}

// 按月统计数据
void CStaticOper::staticMonthData(const ParamValueData& paramValueData, ParamStaticData& data)
{
	QString date = paramValueData.getDate();
	long dzl = 0, hdl = 0;
	map<int, StaticValueData> dataMap = paramValueData.getHourValueMap();
	for (map<int, StaticValueData>::iterator iter = dataMap.begin(); iter != dataMap.end(); ++iter)
	{		
		dzl += iter->second.staticDzl();
		hdl += iter->second.staticHdl();
	}

	data.setParamData(paramValueData.getBrickParamData());
	data.setDate(date.left(7));
	data.setDzl(dzl);
	data.setHdl(hdl);
}

// 添加压机统计数据
void CStaticOper::addDeviceStaticData(const DeviceData& deviceData, const BrickTypeData& brickData, const ParamStaticData& paramStaticData, QVector<DeviceStaticData>& staticDatas)
{
	for (QVector<DeviceStaticData>::iterator devIter = staticDatas.begin(); devIter != staticDatas.end(); ++devIter)
	{
		if (devIter->getDeviceData().getDevId() == deviceData.getDevId())
		{
			devIter->addBrickTypeStaticData(brickData, paramStaticData);
			return;
		}
	}

	DeviceStaticData staticData;
	staticData.setDeviceData(deviceData);
	staticData.addBrickTypeStaticData(brickData, paramStaticData);
	staticDatas.push_back(staticData);
}

// 统计打砖量和耗电量总量
void BrickTypeStaticData::staticParamStaticDatas()
{
	dzl = hdl = 0;
	for (size_t i = 0; i < datas.size(); ++i)
	{
		dzl += datas[i].getDzl();
		hdl += datas[i].getHdl();
	}
}

// 添加模式统计数据
void BrickTypeStaticData::addParamStaticData(const ParamStaticData& paramStaticData)
{
	for (QVector<ParamStaticData>::iterator iter = datas.begin(); iter != datas.end(); ++iter)
	{
		if ((iter->getParamData().getNo() == paramStaticData.getParamData().getNo()) && 
			(iter->getDate() == paramStaticData.getDate()))
		{
			iter->setDzl(iter->getDzl() + paramStaticData.getDzl());
			iter->setHdl(iter->getHdl() + paramStaticData.getHdl());
			return;
		}
	}

	datas.push_back(paramStaticData);
}

// 统计打砖量和耗电量总量
void DeviceStaticData::staticBrickTypeStaticDatas()
{
	dzl = hdl = 0;
	for (size_t i = 0; i < datas.size(); ++i)
	{
		datas[i].staticParamStaticDatas();
		dzl += datas[i].getDzl();
		hdl += datas[i].getHdl();
	}
}

// 添加砖型统计数据
void DeviceStaticData::addBrickTypeStaticData(const BrickTypeData& brickData, const ParamStaticData& paramStaticData)
{
	for(QVector<BrickTypeStaticData>::iterator iter = datas.begin(); iter != datas.end(); ++iter)
	{
		if ((iter->getBrickTypeData().getId() == brickData.getId()))
		{
			iter->addParamStaticData(paramStaticData);
			return;
		}
	}

	BrickTypeStaticData data;
	data.setBrickTypeData(brickData);
	data.addParamStaticData(paramStaticData);
	datas.push_back(data);
}

// 获取开始日期、开始小时值、开始分钟值
void StaticCondition::getStartTimeInfo(QString& date, int& hour, int& minute) const 
{
	date = startTime.toString("yyyy-MM-dd");
	hour = startTime.time().hour();
	minute = startTime.time().minute();
}

// 获取结束日期、结束小时值、结束分钟值
void StaticCondition::getEndTimeInfo(QString& date, int& hour, int& minute) const 
{
	date = endTime.toString("yyyy-MM-dd");
	hour = endTime.time().hour();
	minute = endTime.time().minute();
}

// 获取设备字典
void StaticCondition::getDeviceMap(map<int, DeviceData>& deviceMap) const 
{
	size_t size = deviceDatas.size();
	for (size_t i = 0; i < size; ++i)
	{
		deviceMap.insert(std::make_pair(deviceDatas[i].getDevId(), deviceDatas[i]));
	}
}

// 获取砖型字典
void StaticCondition::getBrickTypeMap(map<int, BrickTypeData>& brickTypeMap) const 
{
	size_t size = brickTypeDatas.size();
	for (size_t i = 0; i < size; ++i)
	{
		brickTypeMap.insert(std::make_pair(brickTypeDatas[i].getId(), brickTypeDatas[i]));
	}
}

void StaticValueData::setDzlData(int index, long value)
{
	if (index >= 0 && index < 60)
	{
		dzlData[index].setValid(true);
		dzlData[index].setValue(value);
	}
}

void StaticValueData::setHdlData(int index, long value)
{
	if (index >= 0 && index < 60)
	{
		hdlData[index].setValid(true);
		hdlData[index].setValue(value);
	}
}

// 统计打砖量
long StaticValueData::staticDzl()
{
	long sum = 0;
	for (int i = 1; i < 60; ++i)
	{
		if (dzlData[i].isValid() && dzlData[i - 1].isValid())
		{
			sum += dzlData[i].getValue() - dzlData[i - 1].getValue();
		}
	}
	return sum;
}

// 统计耗电量
long StaticValueData::staticHdl()
{
	long sum = 0;
	for (int i = 1; i < 60; ++i)
	{
		if (hdlData[i].isValid() && hdlData[i - 1].isValid())
		{
			sum += hdlData[i].getValue() - hdlData[i - 1].getValue();
		}
	}
	return sum;
}
