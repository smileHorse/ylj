/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\DeviceComboBox.h
	file path:	E:\Masf\ylj\common\UI
	file base:	DeviceComboBox
	file ext:	h
	author:		Masf
	
	purpose:	设备下拉框
*********************************************************************/

#include "DeviceComboBox.h"

DeviceComboBox::DeviceComboBox(bool bShowAll, QWidget* parent /*= 0*/ )
	: QComboBox(parent), showAll(bShowAll)
{

}

DeviceComboBox::~DeviceComboBox()
{

}

// 获取当前所选择的设备
DeviceData DeviceComboBox::getSelectedData()
{
	int index = currentIndex();
	if (index >= 0 && index < dataVector.size())
	{
		return dataVector.at(index);
	}

	return DeviceData();
}

// 是否选择所有设备
bool DeviceComboBox::isSelectAllData()
{
	if (isShowAll() && currentIndex() == 0)
	{
		return true;
	}
	return false;
}

void DeviceComboBox::setDataVector( const QVector<DeviceData>& val )
{
	dataVector = val;
	clear();
	if (isShowAll())
	{
		DeviceData data;
		data.setDevNote(QStringLiteral("所有设备"));
		dataVector.push_front(data);
	}
	Q_FOREACH(DeviceData data, dataVector)
	{
		addItem(data.getDevNote());
	}
	if (count() > 0)
	{
		setCurrentIndex(0);
	}
}
