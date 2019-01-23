/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\DeviceComboBox.h
	file path:	E:\Masf\ylj\common\UI
	file base:	DeviceComboBox
	file ext:	h
	author:		Masf
	
	purpose:	�豸������
*********************************************************************/
#ifndef DEVICECOMBOBOX_H
#define DEVICECOMBOBOX_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "DBData/DeviceData.h"

class DeviceComboBox : public QComboBox
{
	Q_OBJECT

public:
	explicit DeviceComboBox(bool bShow = false, QWidget* parent = 0);
	~DeviceComboBox();

	// ��ȡ��ǰ��ѡ����豸
	DeviceData getSelectedData();

	// �Ƿ�ѡ�������豸
	bool isSelectAllData();

	QVector<DeviceData> getDataVector() const { return dataVector; }
	void setDataVector(const QVector<DeviceData>& val);

	bool isShowAll() const { return showAll; }
	void setShowAll(bool val) { showAll = val; }

private:
	bool showAll;
	QVector<DeviceData> dataVector;
};

#endif