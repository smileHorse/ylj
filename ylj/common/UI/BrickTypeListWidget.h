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
#ifndef BRICKTYPELISTWIDGET_H
#define BRICKTYPELISTWIDGET_H

#include <QtWidgets/QListWidget>
#include <QtCore/QVector>

#include "DBData/BrickTypeData.h"

class BrickTypeListWidget : public QListWidget
{
	Q_OBJECT 

public:
	BrickTypeListWidget(QWidget* parent = 0);
	
	QVector<BrickTypeData> getDataVector() const { return dataVector; }
	void setDataVector(const QVector<BrickTypeData>& val);

	// ��ȡ��ѡ������
	QVector<BrickTypeData> getCheckedDatas();

	// ȫ��ѡ��
	void selectAll();

	// ȫ��ȡ��
	void cancelSelectAll();

	// ��ѡ
	void revertSelect();

private:
	QVector<BrickTypeData> dataVector;
};
#endif