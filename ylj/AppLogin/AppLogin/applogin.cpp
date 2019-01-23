#include "applogin.h"
#include "DBOper/DBOper.h"
#include "MD5/MD5Inc.h"

#include <QtWidgets/QtWidgets>

AppLogin::AppLogin(QWidget *parent)
	: QDialog(parent)
{
	// 设置图标和标题
	this->setWindowIcon(QIcon("image/login.png"));
	this->setWindowTitle(QStringLiteral("用户登录"));
	//this->setFixedSize(QSize(600, 200));

	// 初始化对话框
	initDialog();

	// 创建信号和槽
	createConnects();
}

AppLogin::~AppLogin()
{

}

QSize AppLogin::sizeHint() const
{
	return QSize(400, 100);
}

// 初始化对话框
void AppLogin::initDialog()
{
	factoryComboBox = new QComboBox();
	
	userEdit = new QLineEdit();
	passwordEdit = new QLineEdit();
	passwordEdit->setEchoMode(QLineEdit::Password);
	tipLabel = new QLabel();
	tipLabel->setStyleSheet("color: red");

	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(3, 1);
	gridLayout->addWidget(new QLabel(QStringLiteral("分厂")), 0, 1);
	gridLayout->addWidget(factoryComboBox, 0, 2);
	gridLayout->addWidget(new QLabel(QStringLiteral("用户名")), 1, 1);
	gridLayout->addWidget(userEdit, 1, 2);
	gridLayout->addWidget(new QLabel(QStringLiteral("密码")), 2, 1);
	gridLayout->addWidget(passwordEdit, 2, 2);
	gridLayout->addWidget(tipLabel, 3, 1, 1, 2);

	loginButton = new QPushButton(QStringLiteral("登录"));
	cancelButton = new QPushButton(QStringLiteral("取消"));

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addStretch();
	buttonLayout->addWidget(loginButton);
	buttonLayout->addStretch();
	buttonLayout->addWidget(cancelButton);
	buttonLayout->addStretch();

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addLayout(gridLayout);
	layout->addLayout(buttonLayout);
	setLayout(layout);

	this->setStyleSheet("QDialog{background-image:url(image/background.png)}");
}

// 加载所有分厂数据
void AppLogin::loadFactoryDatas()
{
	DBOper& dbOper = DBOper::getInstance();
	if (!dbOper.selectFactoryDatas(factoryDatas))
	{
		return;
	}
	Q_FOREACH(FactoryData data, factoryDatas)
	{
		factoryComboBox->addItem(data.getName());
	}
}

void AppLogin::loadUserDatas()
{
	DBOper& dbOper = DBOper::getInstance();
	if (!dbOper.selectUserDatas(userDatas))
	{
		return;
	}
}

// 创建信号槽
void AppLogin::createConnects()
{
	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

// 登录
void AppLogin::login()
{
	// 获取录入信息
	QString factoryName = factoryComboBox->currentText();
	QString userName = userEdit->text();
	QString password = passwordEdit->text();
	QString factoryId = "";
	Q_FOREACH(FactoryData data, factoryDatas)
	{
		if (data.getName() == factoryName)
		{
			factoryId = data.getId();
			break;
		}
	}
	CMD5 md5;
	QString md5Password = md5.GetMD5HexString((char*)(password.toStdString().c_str()));

	// 验证用户名和密码准确性
	bool userExisted = false;
	Q_FOREACH(UserData data, userDatas)
	{
		if (data.getFactory() == factoryId && data.getName() == userName)
		{
			userExisted = true;
			if (data.getPassword() == md5Password)
			{
				// 启动压力机程序

				// 退出当前程序
				close();
				return;
			}
			break;
		}
	}

	if (userExisted)
	{
		tipLabel->setText(QStringLiteral("密码输入错误，请重新输入"));
		passwordEdit->setFocus();
	}
	else
	{
		tipLabel->setText(QStringLiteral("用户名不存在，请重新输入"));
		userEdit->setFocus();
	}
}
