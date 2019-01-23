#include "applogin.h"
#include "DBOper/DBOper.h"
#include "MD5/MD5Inc.h"

#include <QtWidgets/QtWidgets>

AppLogin::AppLogin(QWidget *parent)
	: QDialog(parent)
{
	// ����ͼ��ͱ���
	this->setWindowIcon(QIcon("image/login.png"));
	this->setWindowTitle(QStringLiteral("�û���¼"));
	//this->setFixedSize(QSize(600, 200));

	// ��ʼ���Ի���
	initDialog();

	// �����źźͲ�
	createConnects();
}

AppLogin::~AppLogin()
{

}

QSize AppLogin::sizeHint() const
{
	return QSize(400, 100);
}

// ��ʼ���Ի���
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
	gridLayout->addWidget(new QLabel(QStringLiteral("�ֳ�")), 0, 1);
	gridLayout->addWidget(factoryComboBox, 0, 2);
	gridLayout->addWidget(new QLabel(QStringLiteral("�û���")), 1, 1);
	gridLayout->addWidget(userEdit, 1, 2);
	gridLayout->addWidget(new QLabel(QStringLiteral("����")), 2, 1);
	gridLayout->addWidget(passwordEdit, 2, 2);
	gridLayout->addWidget(tipLabel, 3, 1, 1, 2);

	loginButton = new QPushButton(QStringLiteral("��¼"));
	cancelButton = new QPushButton(QStringLiteral("ȡ��"));

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

// �������зֳ�����
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

// �����źŲ�
void AppLogin::createConnects()
{
	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

// ��¼
void AppLogin::login()
{
	// ��ȡ¼����Ϣ
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

	// ��֤�û���������׼ȷ��
	bool userExisted = false;
	Q_FOREACH(UserData data, userDatas)
	{
		if (data.getFactory() == factoryId && data.getName() == userName)
		{
			userExisted = true;
			if (data.getPassword() == md5Password)
			{
				// ����ѹ��������

				// �˳���ǰ����
				close();
				return;
			}
			break;
		}
	}

	if (userExisted)
	{
		tipLabel->setText(QStringLiteral("���������������������"));
		passwordEdit->setFocus();
	}
	else
	{
		tipLabel->setText(QStringLiteral("�û��������ڣ�����������"));
		userEdit->setFocus();
	}
}
