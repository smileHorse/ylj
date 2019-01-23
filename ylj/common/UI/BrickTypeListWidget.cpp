/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\BrickTypeListWidget.h
	file path:	E:\Masf\ylj\common\UI
	file base:	BrickTypeListWidget
	file ext:	h
	author:		Masf
	
	purpose:	砖型列表
*********************************************************************/

#include "BrickTypeListWidget.h"

#include <QtWidgets/QCheckBox>

BrickTypeListWidget::BrickTypeListWidget(QWidget* parent /*= 0*/)
	: QListWidget(parent)
{

}

void BrickTypeListWidget::setDataVector(const QVector<BrickTypeData>& val)
{
	this->clear();
	dataVector = val;
	Q_FOREACH(BrickTypeData data, dataVector)
	{
		QListWidgetItem* pItem = new QListWidgetItem();
		QCheckBox* pCheckBox = new QCheckBox(data.getName());
		addItem(pItem);
		setItemWidget(pItem, pCheckBox);
	}
}

// 获取勾选的数据
QVector<BrickTypeData> BrickTypeListWidget::getCheckedDatas()
{
	QVector<BrickTypeData> datas;
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
void BrickTypeListWidget::selectAll()
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
void BrickTypeListWidget::cancelSelectAll()
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
void BrickTypeListWidget::revertSelect()
{
	for (int row = 0; row < count(); ++row)
	{
		QListWidgetItem* pItem = item(row);
		QWidget* pWidget = itemWidget(pItem);
		QCheckBox* pCheckBox = (QCheckBox*)pWidget;
		pCheckBox->setChecked(!pCheckBox->isChecked());
	}
}
