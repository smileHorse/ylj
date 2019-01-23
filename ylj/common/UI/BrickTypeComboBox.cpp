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

#include "BrickTypeComboBox.h"

BrickTypeComboBox::BrickTypeComboBox(bool bShowAll, QWidget* parent /*= 0*/ )
	: QComboBox(parent), showAll(bShowAll)
{

}

BrickTypeComboBox::~BrickTypeComboBox()
{

}

// 获取当前所选择的设备
BrickTypeData BrickTypeComboBox::getSelectedData()
{
	int index = currentIndex();
	if (index >= 0 && index < dataVector.size())
	{
		return dataVector.at(index);
	}

	return BrickTypeData();
}

// 是否选择所有设备
bool BrickTypeComboBox::isSelectAllData()
{
	if (isShowAll() && currentIndex() == 0)
	{
		return true;
	}
	return false;
}

void BrickTypeComboBox::setDataVector( const QVector<BrickTypeData>& val )
{
	dataVector = val;
	clear();
	if (isShowAll())
	{
		BrickTypeData data;
		data.setName(QStringLiteral("所有设备"));
		dataVector.push_front(data);
	}
	Q_FOREACH(BrickTypeData data, dataVector)
	{
		addItem(data.getName());
	}	
	if (count() > 0)
	{
		setCurrentIndex(0);
	}
}
