/********************************************************************
	created:	2019/02/09
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\MeterialComboBox.h
	file path:	E:\Masf\ylj\common\UI
	file base:	MeterialComboBox
	file ext:	h
	author:		Masf
	
	purpose:	材质下拉框
*********************************************************************/
#ifndef METERIALCOMBOBOX_H
#define METERIALCOMBOBOX_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "DBData/MeterialData.h"

class MeterialComboBox : public QComboBox
{
	Q_OBJECT 

public:
	explicit MeterialComboBox(bool bShow = false, QWidget* parent = 0);
	~MeterialComboBox();

	// 获取当前所选择的设备
	MeterialData getSelectedData();

	// 是否选择所有设备
	bool isSelectAllData();

	QVector<MeterialData> getDataVector() const { return dataVector; }
	void setDataVector(const QVector<MeterialData>& val);

	bool isShowAll() const { return showAll; }
	void setShowAll(bool val) { showAll = val; }

private:
	bool showAll;
	QVector<MeterialData> dataVector;
};

#endif