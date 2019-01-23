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

	// 获取勾选的数据
	QVector<BrickTypeData> getCheckedDatas();

	// 全部选择
	void selectAll();

	// 全部取消
	void cancelSelectAll();

	// 反选
	void revertSelect();

private:
	QVector<BrickTypeData> dataVector;
};
#endif