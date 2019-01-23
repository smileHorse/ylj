#include "datastatic.h"

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include <QtPrintSupport/QtPrintSupport>

#include "DBOper/DBOper.h"
#include "UI/DeviceComboBox.h"
#include "UI/MeterialComboBox.h"
#include "UI/BrickTypeComboBox.h"
#include "UI/DeviceListWidget.h"
#include "UI/BrickTypeListWidget.h"

#define DISPLAY_HOUR	QStringLiteral("小时")
#define DISPLAY_DAY		QStringLiteral("天")
#define DISPLAY_MONTH	QStringLiteral("月")

DataStatic::DataStatic(QWidget *parent)
	: QMainWindow(parent)
{
	try 
	{
		setWindowIcon(QIcon("images/dataStatic.png"));
		setWindowTitle(QStringLiteral("数据统计"));

		// 创建事件响应
		createActions();

		// 创建窗口控件
		createWidgets();

		// 最大化窗口
		showMaximized();
	}
	catch(...)
	{

	}
}

DataStatic::~DataStatic()
{

}

// 创建窗口控件
void DataStatic::createWidgets()
{
	// 创建菜单栏、工具栏和状态栏
	createMenuBar();
	createToolBar();
	statusBar()->showMessage(QStringLiteral("准备就绪"));

	// 创建界面
	mainSplitter = new QSplitter(Qt::Horizontal);

	equipSplitter = new QSplitter(Qt::Horizontal);
	QGroupBox* group1 = createDeviceGroupBox();
	QGroupBox* group2 = createBrickGroupBox();
	equipSplitter->addWidget(group1);
	equipSplitter->addWidget(group2);
	mainSplitter->addWidget(equipSplitter);
	
	dataTableWidget = new QTableWidget();
	dataTableWidget->setColumnCount(6);
	QStringList headerLabels;
	headerLabels << QStringLiteral("设备") << QStringLiteral("砖号") << QStringLiteral("模式")
		<< QStringLiteral("日期") << QStringLiteral("打砖量") << QStringLiteral("耗电量");
	dataTableWidget->setHorizontalHeaderLabels(headerLabels);
	mainSplitter->addWidget(dataTableWidget);
	mainSplitter->setStretchFactor(0, 0);
	mainSplitter->setStretchFactor(1, 1);
	setCentralWidget(mainSplitter);
}

// 创建菜单栏
void DataStatic::createMenuBar()
{
	QMenu* pMenu = menuBar()->addMenu(QIcon(""), QStringLiteral("操作"));
	pMenu->addAction(queryAction);
	pMenu->addAction(exportAction);
	pMenu->addAction(printAction);
	pMenu->addSeparator();
	pMenu->addAction(quitAction);
}

// 创建工具栏
void DataStatic::createToolBar()
{
	QToolBar* pToolBar = addToolBar(QStringLiteral("操作"));
	pToolBar->setMovable(false);
	pToolBar->setFloatable(false);
	pToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	startTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addDays(-1));
	startTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
	endTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
	endTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
	pToolBar->addWidget(new QLabel(QStringLiteral("开始时间")));
	pToolBar->addWidget(startTimeEdit);
	pToolBar->addWidget(new QLabel(QStringLiteral("结束时间")));
	pToolBar->addWidget(endTimeEdit);

	displayComboBox = new QComboBox();
	displayComboBox->addItem(DISPLAY_HOUR);
	displayComboBox->addItem(DISPLAY_DAY);
	displayComboBox->addItem(DISPLAY_MONTH);
	pToolBar->addWidget(new QLabel(QStringLiteral("显示模式:")));
	pToolBar->addWidget(displayComboBox);

	minValueEdit = new QLineEdit();
	minValueEdit->setText("100");
	pToolBar->addWidget(new QLabel(QStringLiteral("最小值")));
	pToolBar->addWidget(minValueEdit);

	pToolBar->addAction(queryAction);
	pToolBar->addAction(exportAction);
	pToolBar->addAction(printAction);
}

// 创建设备分组
QGroupBox* DataStatic::createDeviceGroupBox()
{
	QGroupBox* group = new QGroupBox();
	deviceListWidget = new DeviceListWidget();

	deviceComboBox = new DeviceComboBox(true);
	connect(deviceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(deviceComboBoxChanged()));
	QVector<DeviceData> deviceDatas;
	if (DBOper::getInstance().selectDeviceDatas(deviceDatas))
	{
		deviceComboBox->setDataVector(deviceDatas);
	}

	deviceSelAllBtn = new QPushButton(QStringLiteral("全部选择"));
	connect(deviceSelAllBtn, SIGNAL(clicked()), this, SLOT(doSelectAllDevice()));
	deviceCancelAllBtn = new QPushButton(QStringLiteral("全部取消"));
	connect(deviceCancelAllBtn, SIGNAL(clicked()), this, SLOT(doCancelAllDevice()));
	deviceRevertBtn = new QPushButton(QStringLiteral("反选"));
	connect(deviceRevertBtn, SIGNAL(clicked()), this, SLOT(doRevertSelectDevice()));

	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addWidget(new QLabel(QStringLiteral("设备:")));
	hLayout->addWidget(deviceComboBox, 1);
	QHBoxLayout* hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(deviceSelAllBtn);
	hLayout1->addWidget(deviceCancelAllBtn);
	hLayout1->addWidget(deviceRevertBtn);
	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->addLayout(hLayout);
	vLayout->addWidget(deviceListWidget);
	vLayout->addLayout(hLayout1);
	group->setLayout(vLayout);

	return group;
}

// 创建砖型分组
QGroupBox* DataStatic::createBrickGroupBox()
{
	QGroupBox* group = new QGroupBox();

	brickTypeListWidget = new BrickTypeListWidget();

	brickTypeComboBox = new BrickTypeComboBox(true);
	connect(brickTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(brickTypeComboBoxChanged()));

	meterialComboBox = new MeterialComboBox(true);
	connect(meterialComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(meterialComboBoxChanged()));
	QVector<MeterialData> meterialDatas;
	if (DBOper::getInstance().selectMeterialDatas(meterialDatas))
	{
		meterialComboBox->setDataVector(meterialDatas);
	}

	 
	brickSelAllBtn = new QPushButton(QStringLiteral("全部选择"));
	connect(brickSelAllBtn, SIGNAL(clicked()), this, SLOT(doSelectAllBrickType()));
	brickCancelAllBtn = new QPushButton(QStringLiteral("全部取消"));
	connect(brickCancelAllBtn, SIGNAL(clicked()), this, SLOT(doCancelAllBrickType()));
	brickRevertBtn = new QPushButton(QStringLiteral("反选"));
	connect(brickRevertBtn, SIGNAL(clicked()), this, SLOT(doRevertSelectBrickType()));

	QHBoxLayout* hLayout1 = new QHBoxLayout();
	hLayout1->addWidget(new QLabel(QStringLiteral("材质:")));
	hLayout1->addWidget(meterialComboBox, 1);
	QHBoxLayout* hLayout2 = new QHBoxLayout();
	hLayout2->addWidget(new QLabel(QStringLiteral("砖号:")));
	hLayout2->addWidget(brickTypeComboBox, 1);
	QHBoxLayout* hLayout3 = new QHBoxLayout();
	hLayout3->addWidget(brickSelAllBtn);
	hLayout3->addWidget(brickCancelAllBtn);
	hLayout3->addWidget(brickRevertBtn);
	QVBoxLayout* vLayout = new QVBoxLayout();
	vLayout->addLayout(hLayout1);
	vLayout->addLayout(hLayout2);
	vLayout->addWidget(brickTypeListWidget);
	vLayout->addLayout(hLayout3);
	group->setLayout(vLayout);

	return group;
}

// 创建事件动作
void DataStatic::createActions()
{
	queryAction = new QAction(QIcon("images/query.png"), QStringLiteral("查询"), this);
	connect(queryAction, SIGNAL(triggered()), this, SLOT(doQuery()));
	exportAction = new QAction(QIcon("images/excel.png"), QStringLiteral("导出"), this);
	connect(exportAction, SIGNAL(triggered()), this, SLOT(doExport()));
	printAction = new QAction(QIcon("images/print.png"), QStringLiteral("打印"), this);
	connect(printAction, SIGNAL(triggered()), this, SLOT(doPrint()));
	quitAction = new QAction(QIcon("images/quit.png"), QStringLiteral("退出"), this);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(doQuit()));
}

// 获取数据显示方式
StaticDisplayMode DataStatic::getDisplayMode()
{
	QString text = displayComboBox->currentText();
	if (text == DISPLAY_HOUR)
	{
		return SDM_HOUR;
	}
	else if (text == DISPLAY_DAY)
	{
		return SDM_DAY;
	}
	else if (text == DISPLAY_MONTH)
	{
		return SDM_MONTH;
	}

	return SDM_HOUR;
}

void DataStatic::doQuery()
{
	// 获取开始时间和结束时间
	QDateTime startTime = startTimeEdit->dateTime();
	QDateTime endTime = endTimeEdit->dateTime();
	if (startTime > endTime)
	{
		QMessageBox::information(this, QStringLiteral("错误信息"), QStringLiteral("开始时间应该早于结束时间"));
		return;
	}

	// 获取显示方式
	StaticDisplayMode displayMode = getDisplayMode();

	// 获取打砖量的最小值
	int minValue = minValueEdit->text().toInt();

	// 获取所选择的设备
	QVector<DeviceData> deviceDatas = deviceListWidget->getCheckedDatas();
	if (deviceDatas.isEmpty())
	{
		QMessageBox::information(this, QStringLiteral("错误信息"), QStringLiteral("请选择查询的设备"));
		return;
	}

	// 获取所选择的砖型
	QVector<BrickTypeData> brickTypeDatas = brickTypeListWidget->getCheckedDatas();
	if (brickTypeDatas.isEmpty())
	{
		QMessageBox::information(this, QStringLiteral("错误信息"), QStringLiteral("请选择查询的砖号"));
		return;
	}

	// 开始执行统计操作
	StaticCondition condition;
	condition.setStartTime(startTime);
	condition.setEndTime(endTime);
	condition.setDisplayMode(displayMode);
	condition.setMinValue(minValue);
	condition.setDeviceDatas(deviceDatas);
	condition.setBrickTypeDatas(brickTypeDatas);

	CStaticOper staticOper;
	QVector<DeviceStaticData> staticDatas;
	staticOper.staticData(condition, staticDatas);

	// 显示统计结果
	dataTableWidget->clearContents();
	dataTableWidget->setRowCount(0);

	int row = 0;
	for (QVector<DeviceStaticData>::iterator devIter = staticDatas.begin(); devIter != staticDatas.end(); ++devIter)
	{
		DeviceData deviceData = devIter->getDeviceData();
		QVector<BrickTypeStaticData> brickStaticDatas = devIter->getDatas();
		for (QVector<BrickTypeStaticData>::iterator briIter = brickStaticDatas.begin(); briIter != brickStaticDatas.end();
			++briIter)
		{
			BrickTypeData brickTypeData = briIter->getBrickTypeData();
			QVector<ParamStaticData> paramStaticDatas = briIter->getDatas();
			for (QVector<ParamStaticData>::iterator parIter = paramStaticDatas.begin(); parIter != paramStaticDatas.end();
				++parIter)
			{
				dataTableWidget->insertRow(row);
				QTableWidgetItem* pItem = new QTableWidgetItem(deviceData.getDevNote());
				dataTableWidget->setItem(row, 0, pItem);
				pItem = new QTableWidgetItem(brickTypeData.getName());
				dataTableWidget->setItem(row, 1, pItem);
				pItem = new QTableWidgetItem(parIter->getParamData().getName());
				dataTableWidget->setItem(row, 2, pItem);
				pItem = new QTableWidgetItem(parIter->getDate());
				dataTableWidget->setItem(row, 3, pItem);
				pItem = new QTableWidgetItem(QString("%1").arg(parIter->getDzl()));
				dataTableWidget->setItem(row, 4, pItem);
				pItem = new QTableWidgetItem(QString("%1").arg(parIter->getHdl()));
				dataTableWidget->setItem(row, 5, pItem);

				row++;
			}

			briIter->staticParamStaticDatas();
			dataTableWidget->insertRow(row);

			QTableWidgetItem* pItem = new QTableWidgetItem(deviceData.getDevNote());
			dataTableWidget->setItem(row, 0, pItem);
			pItem = new QTableWidgetItem(brickTypeData.getName());
			dataTableWidget->setItem(row, 1, pItem);
			pItem = new QTableWidgetItem(QStringLiteral("总量"));
			dataTableWidget->setItem(row, 2, pItem);
			pItem = new QTableWidgetItem("");
			dataTableWidget->setItem(row, 3, pItem);
			pItem = new QTableWidgetItem(QString("%1").arg(briIter->getDzl()));
			dataTableWidget->setItem(row, 4, pItem);
			pItem = new QTableWidgetItem(QString("%1").arg(briIter->getHdl()));
			dataTableWidget->setItem(row, 5, pItem);

			row++;
		}

		devIter->staticBrickTypeStaticDatas();
		dataTableWidget->insertRow(row);

		QTableWidgetItem* pItem = new QTableWidgetItem(deviceData.getDevNote());
		dataTableWidget->setItem(row, 0, pItem);
		pItem = new QTableWidgetItem(QStringLiteral("总量"));
		dataTableWidget->setItem(row, 1, pItem);
		pItem = new QTableWidgetItem("");
		dataTableWidget->setItem(row, 2, pItem);
		pItem = new QTableWidgetItem("");
		dataTableWidget->setItem(row, 3, pItem);
		pItem = new QTableWidgetItem(QString("%1").arg(devIter->getDzl()));
		dataTableWidget->setItem(row, 4, pItem);
		pItem = new QTableWidgetItem(QString("%1").arg(devIter->getHdl()));
		dataTableWidget->setItem(row, 5, pItem);

		row++;
	}
	dataTableWidget->resizeColumnsToContents();
}

void DataStatic::doExport()
{

}

void DataStatic::doPrint()
{
	QPrintPreviewDialog dialog(this, Qt::Window);
	connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printData(QPrinter*)));
	if (dialog.exec() == QDialog::Accepted)
	{
	}
}

void DataStatic::doQuit()
{

}

void DataStatic::doSelectAllDevice()
{
	deviceListWidget->selectAll();
}

void DataStatic::doCancelAllDevice()
{
	deviceListWidget->cancelSelectAll();
}

void DataStatic::doRevertSelectDevice()
{
	deviceListWidget->revertSelect();
}

void DataStatic::doSelectAllBrickType()
{
	brickTypeListWidget->selectAll();
}

void DataStatic::doCancelAllBrickType()
{
	brickTypeListWidget->cancelSelectAll();
}

void DataStatic::doRevertSelectBrickType()
{
	brickTypeListWidget->revertSelect();
}

void DataStatic::deviceComboBoxChanged()
{
	QVector<DeviceData> datas;
	if (deviceComboBox->isSelectAllData())
	{
		datas = deviceComboBox->getDataVector();
		datas.pop_front();
	}
	else
	{
		datas.push_back(deviceComboBox->getSelectedData());
	}
	deviceListWidget->setDataVector(datas);
}

void DataStatic::meterialComboBoxChanged()
{
	QVector<BrickTypeData> datas;
	if (meterialComboBox->isSelectAllData())
	{
		DBOper::getInstance().selectBrickTypeDatas(datas);
	}
	else
	{
		MeterialData data = meterialComboBox->getSelectedData();
		DBOper::getInstance().selectBrickTypeDatasByMeterial(datas, data.getNo());
	}
	brickTypeComboBox->setDataVector(datas);
}

void DataStatic::brickTypeComboBoxChanged()
{
	QVector<BrickTypeData> datas;
	if (brickTypeComboBox->isSelectAllData())
	{
		datas = brickTypeComboBox->getDataVector();
		datas.pop_front();
	}
	else
	{
		datas.push_back(brickTypeComboBox->getSelectedData());
	}
	brickTypeListWidget->setDataVector(datas);
}

// 打印数据
void DataStatic::printData(QPrinter* printer)
{
	QString html;
	html = "<table border='1'>\n";
	int rowCount = dataTableWidget->rowCount();
	int colCount = dataTableWidget->columnCount();

	html += "<tr>\n";
	for (int col = 0; col < colCount; ++col)
	{
		QTableWidgetItem* pItem = dataTableWidget->horizontalHeaderItem(col);
		html += "<th>";
		html += (pItem->text());
		html += "</th>\n";
	}
	html += "</tr>\n";
	
	for (int row = 0; row < rowCount; ++row)
	{
		html += "<tr>\n";
		for (int col = 0; col < colCount; ++col)
		{
			QTableWidgetItem* pItem = dataTableWidget->item(row, col);
			html += "<td>";
			html += (pItem->text());
			html += "</td>\n";
		}
		html += "</tr>\n";
	}
	html += "</table>";
	QTextDocument textDocument;
	textDocument.setHtml(html);
	textDocument.print(printer);
}
