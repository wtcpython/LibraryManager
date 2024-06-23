#include "book.h"


Book_1::Book_1() : Media_1(), publishingHouse(""), isbn(""), page(0) {}

Book_1::Book_1(
	int id, QString title, QString author, QString grade,
	const QString publishingHouse, const QString isbn, int page)
	: Media_1(id, title, author, grade), publishingHouse(publishingHouse), isbn(isbn), page(page)
{}

void Book_1::setPublishingHouse(const QString publishingHouse)
{
	this->publishingHouse = publishingHouse;
}

QString Book_1::getPublishingHouse() const
{
	return publishingHouse;
}

void Book_1::setIsbn(const QString isbn)
{
	this->isbn = isbn;
}

QString Book_1::getIsbn() const
{
	return isbn;
}

void Book_1::setPage(int page)
{
	this->page = page;
}

int Book_1::getPage() const
{
	return page;
}