/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\DeviceListWidget.h
	file path:	E:\Masf\ylj\common\UI
	file base:	DeviceListWidget
	file ext:	h
	author:		Masf
	
	purpose:	设备列表
*********************************************************************/
#ifndef DEVICELISTWIDGET_H
#define DEVICELISTWIDGET_H

#include <QtWidgets/QListWidget>
#include <QtCore/QVector>

#include "DBData/DeviceData.h"

class DeviceListWidget : public QListWidget
{
	Q_OBJECT 

public:
	DeviceListWidget(QWidget* parent = 0);
	
	QVector<DeviceData> getDataVector() const { return dataVector; }
	void setDataVector(const QVector<DeviceData>& val);

	// 获取勾选的数据
	QVector<DeviceData> getCheckedDatas();

	// 全部选择
	void selectAll();

	// 全部取消
	void cancelSelectAll();

	// 反选
	void revertSelect();

private:
	QVector<DeviceData> dataVector;
};
#endif