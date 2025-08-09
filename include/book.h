#pragma once
#include "libmedia.h"

using namespace std;

class Book_1 : public Media_1
{
  private:
    QString publishingHouse;
    QString isbn;
    int page;

  public:
    Book_1();
    Book_1(int id, QString title, QString author, QString grade, const QString publishingHouse, const QString isbn,
           int page);

    void setPublishingHouse(const QString publishingHouse);
    QString getPublishingHouse() const;

    void setIsbn(const QString isbn);
    QString getIsbn() const;

    void setPage(int page);
    int getPage() const;
};
