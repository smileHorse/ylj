#ifndef APPLOGIN_H
#define APPLOGIN_H

#include "DBOper/DBOper.h"

#include <QtCore/QVector>
#include <QtWidgets/QDialog>

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;

class AppLogin : public QDialog
{
	Q_OBJECT

public:
	AppLogin(QWidget *parent = 0);
	~AppLogin();

	virtual QSize sizeHint() const;

	// ��ȡ�ֳ���Ϣ
	void loadFactoryDatas();

	// ��ȡ�û���Ϣ
	void loadUserDatas();

private:
	// ��ʼ���Ի���
	void initDialog();
	
	// �����źŲ�
	void createConnects();

public slots:
	// ��¼
	void login();

private:
	QComboBox* factoryComboBox;
	QLineEdit* userEdit;
	QLineEdit* passwordEdit;
	QLabel* tipLabel;
	QPushButton* loginButton;
	QPushButton* cancelButton;

	QVector<FactoryData> factoryDatas;
	QVector<UserData> userDatas;
};

#endif // APPLOGIN_H
