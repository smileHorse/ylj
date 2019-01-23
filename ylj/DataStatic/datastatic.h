#ifndef DATASTATIC_H
#define DATASTATIC_H

#include <QtWidgets/QMainWindow>

#include "StaticData/StaticData.h"

class QAction;
class QComboBox;
class QDateTimeEdit;
class QGroupBox;
class QLineEdit;
class QListWidget;
class QPushButton;
class QSplitter;
class QTableWidget;
class QPrinter;

class DeviceComboBox;
class MeterialComboBox;
class BrickTypeComboBox;
class DeviceListWidget;
class BrickTypeListWidget;

class DataStatic : public QMainWindow
{
	Q_OBJECT

public:
	DataStatic(QWidget *parent = 0);
	~DataStatic();

private:
	// �������ڿؼ�
	void createWidgets();

	// �����˵���
	void createMenuBar();

	// ����������
	void createToolBar();

	// �����豸����
	QGroupBox* createDeviceGroupBox();

	// ����ש�ͷ���
	QGroupBox* createBrickGroupBox();

	// �����¼�����
	void createActions();

	// ��ȡ������ʾ��ʽ
	StaticDisplayMode getDisplayMode();

private slots:
	void doQuery();
	void doExport();
	void doPrint();
	void doQuit();
	void doSelectAllDevice();
	void doCancelAllDevice();
	void doRevertSelectDevice();
	void doSelectAllBrickType();
	void doCancelAllBrickType();
	void doRevertSelectBrickType();

	void deviceComboBoxChanged();
	void meterialComboBoxChanged();
	void brickTypeComboBoxChanged();

	// ��ӡ����
	void printData(QPrinter* printer);

private:
	QAction* queryAction;
	QAction* exportAction;
	QAction* printAction;
	QAction* quitAction;

	QDateTimeEdit*	startTimeEdit;
	QDateTimeEdit*  endTimeEdit;
	QComboBox* displayComboBox;
	QLineEdit* minValueEdit;
	QSplitter*	mainSplitter;
	QSplitter*  equipSplitter;
	DeviceComboBox*  deviceComboBox;
	MeterialComboBox*  meterialComboBox;
	BrickTypeComboBox*  brickTypeComboBox;
	DeviceListWidget* deviceListWidget;
	BrickTypeListWidget* brickTypeListWidget;
	QTableWidget* dataTableWidget;
	QPushButton* deviceSelAllBtn;
	QPushButton* deviceCancelAllBtn;
	QPushButton* deviceRevertBtn;
	QPushButton* brickSelAllBtn;
	QPushButton* brickCancelAllBtn;
	QPushButton* brickRevertBtn;
};

#endif // DATASTATIC_H
