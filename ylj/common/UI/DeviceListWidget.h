/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\DeviceListWidget.h
	file path:	E:\Masf\ylj\common\UI
	file base:	DeviceListWidget
	file ext:	h
	author:		Masf
	
	purpose:	�豸�б�
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

	// ��ȡ��ѡ������
	QVector<DeviceData> getCheckedDatas();

	// ȫ��ѡ��
	void selectAll();

	// ȫ��ȡ��
	void cancelSelectAll();

	// ��ѡ
	void revertSelect();

private:
	QVector<DeviceData> dataVector;
};
#endif