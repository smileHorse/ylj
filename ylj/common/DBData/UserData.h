/********************************************************************
	created:	2019/02/03
	created:	3:2:2019   10:48
	filename: 	E:\Masf\ylj\common\DBData\UserData.h
	file path:	E:\Masf\ylj\common\DBData
	file base:	UserData
	file ext:	h
	author:		Masf
	
	purpose:	用户对象
*********************************************************************/
#ifndef USERDATA_H
#define USERDATA_H

#include <QtCore/QString>

class UserData
{
public:
	UserData()
		: id(0), password(""), name(""), userType(1), userName(""), factory("")
	{}

	int getId() const { return id; }
	void setId(int val) { id = val; }

	QString getPassword() const { return password; }
	void setPassword(QString val) { password = val; }

	QString getName() const { return name; }
	void setName(QString val) { name = val; }

	int getUserType() const { return userType; }
	void setUserType(int val) { userType = val; }

	QString getUserName() const { return userName; }
	void setUserName(QString val) { userName = val; }

	QString getFactory() const { return factory; }
	void setFactory(QString val) { factory = val; }

private:
	int id;
	QString password;
	QString name;
	int userType;
	QString userName;
	QString factory;
};
#endif