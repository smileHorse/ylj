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

	// 获取分厂信息
	void loadFactoryDatas();

	// 获取用户信息
	void loadUserDatas();

private:
	// 初始化对话框
	void initDialog();
	
	// 创建信号槽
	void createConnects();

public slots:
	// 登录
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
