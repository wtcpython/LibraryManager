#include "libmedia.h"

Media_1::Media_1() : id(0), title(""), author(""), grade("未评级") {}

Media_1::Media_1(int id, QString title, QString author, QString grade)
	: id(id), title(title), author(author), grade(grade)
{}

void Media_1::setId(int id)
{
	this->id = id;
}

int Media_1::getId()
{
	return id;
}

void Media_1::setTitle(const QString title)
{
	this->title = title;
}

QString Media_1::getTitle()
{
	return title;
}

void Media_1::setAuthor(const QString author)
{
	this->author = author;
}

QString Media_1::getAuthor()
{
	return author;
}

void Media_1::setGrade(QString grade)
{
	this->grade = grade;
}

QString Media_1::getGrade()
{
	return grade;
}
