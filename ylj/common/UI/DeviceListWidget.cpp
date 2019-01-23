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

#include "DeviceListWidget.h"

#include <QtWidgets/QCheckBox>

DeviceListWidget::DeviceListWidget(QWidget* parent /*= 0*/)
	: QListWidget(parent)
{

}

void DeviceListWidget::setDataVector(const QVector<DeviceData>& val)
{
	this->clear();
	dataVector = val;
	Q_FOREACH(DeviceData data, dataVector)
	{
		QListWidgetItem* pItem = new QListWidgetItem();
		QCheckBox* pCheckBox = new QCheckBox(data.getDevNote());
		addItem(pItem);
		setItemWidget(pItem, pCheckBox);
	}
}

// 获取勾选的数据
QVector<DeviceData> DeviceListWidget::getCheckedDatas()
{
	QVector<DeviceData> datas;
	for (int row = 0; row < count(); ++row)
	{
		QListWidgetItem* pItem = item(row);
		QWidget* pWidget = itemWidget(pItem);
		QCheckBox* pCheckBox = (QCheckBox*)pWidget;
		if (pCheckBox->isChecked() && (row >= 0 && row < dataVector.size()))
		{
			datas.push_back(dataVector.at(row));
		}
	}
	return datas;
}

// 全部选择
void DeviceListWidget::selectAll()
{
	for (int row = 0; row < count(); ++row)
	{
		QListWidgetItem* pItem = item(row);
		QWidget* pWidget = itemWidget(pItem);
		QCheckBox* pCheckBox = (QCheckBox*)pWidget;
		pCheckBox->setChecked(true);
	}
}

// 全部取消
void DeviceListWidget::cancelSelectAll()
{
	for (int row = 0; row < count(); ++row)
	{
		QListWidgetItem* pItem = item(row);
		QWidget* pWidget = itemWidget(pItem);
		QCheckBox* pCheckBox = (QCheckBox*)pWidget;
		pCheckBox->setChecked(false);
	}
}

// 反选
void DeviceListWidget::revertSelect()
{
	for (int row = 0; row < count(); ++row)
	{
		QListWidgetItem* pItem = item(row);
		QWidget* pWidget = itemWidget(pItem);
		QCheckBox* pCheckBox = (QCheckBox*)pWidget;
		pCheckBox->setChecked(!pCheckBox->isChecked());
	}
}
