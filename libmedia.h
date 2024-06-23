#pragma once
#include <iostream>
#include <QString>

using namespace std;

class Media_1
{
private:
	int id = 0;
	QString title;
	QString author;
	QString grade;

public:
	Media_1();
	Media_1(int id, QString title, QString author, QString grade);
	virtual ~Media_1() {}

	void setId(int id);
	int getId();

	void setTitle(const QString title);
	QString getTitle();

	void setAuthor(const QString author);
	QString getAuthor();

	void setGrade(QString grade);
	QString getGrade();
};
