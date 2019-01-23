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

#include "MeterialComboBox.h"

MeterialComboBox::MeterialComboBox(bool bShowAll, QWidget* parent /*= 0*/ )
	: QComboBox(parent), showAll(bShowAll)
{

}

MeterialComboBox::~MeterialComboBox()
{

}

// 获取当前所选择的设备
MeterialData MeterialComboBox::getSelectedData()
{
	int index = currentIndex();
	if (index >= 0 && index < dataVector.size())
	{
		return dataVector.at(index);
	}

	return MeterialData();
}

// 是否选择所有设备
bool MeterialComboBox::isSelectAllData()
{
	if (isShowAll() && currentIndex() == 0)
	{
		return true;
	}
	return false;
}

void MeterialComboBox::setDataVector( const QVector<MeterialData>& val )
{
	dataVector = val;
	clear();
	if (isShowAll())
	{
		MeterialData data;
		data.setName(QStringLiteral("所有设备"));
		dataVector.push_front(data);
	}
	Q_FOREACH(MeterialData data, dataVector)
	{
		addItem(data.getName());
	}	
	if (count() > 0)
	{
		setCurrentIndex(0);
	}
}
