/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\BrickTypeComboBox.h
	file path:	E:\Masf\ylj\common\UI
	file base:	BrickTypeComboBox
	file ext:	h
	author:		Masf
	
	purpose:	转型下拉框
*********************************************************************/
#ifndef BRICKTYPECOMBOBOX_H
#define BRICKTYPECOMBOBOX_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "DBData/BrickTypeData.h"

class BrickTypeComboBox : public QComboBox
{
	Q_OBJECT

public:
	explicit BrickTypeComboBox(bool bShow = false, QWidget* parent = 0);
	~BrickTypeComboBox();

	// 获取当前所选择的设备
	BrickTypeData getSelectedData();

	// 是否选择所有设备
	bool isSelectAllData();

	QVector<BrickTypeData> getDataVector() const { return dataVector; }
	void setDataVector(const QVector<BrickTypeData>& val);

	bool isShowAll() const { return showAll; }
	void setShowAll(bool val) { showAll = val; }

private:
	bool showAll;
	QVector<BrickTypeData> dataVector;
};

#endif