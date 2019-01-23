/********************************************************************
	created:	2019/02/07
	created:	7:2:2019   20:04
	filename: 	E:\Masf\ylj\common\UI\BrickTypeListWidget.h
	file path:	E:\Masf\ylj\common\UI
	file base:	BrickTypeListWidget
	file ext:	h
	author:		Masf
	
	purpose:	ש���б�
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

// ��ȡ��ѡ������
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

// ȫ��ѡ��
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

// ȫ��ȡ��
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

// ��ѡ
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
