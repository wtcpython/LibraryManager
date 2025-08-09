#include "Picture.h"

Picture_2::Picture_2()
{
    this->ProductionNationality = "";
    this->length = 0;
    this->width = 0;
}

Picture_2::Picture_2(int id, QString title, QString author, QString grade, QString ProductionNationality, int length,
                     int width)
    : Media_1(id, title, author, grade), ProductionNationality(ProductionNationality), length(length), width(width)
{
}

QString Picture_2::getProductionNationality()
{
    return this->ProductionNationality;
}

int Picture_2::getLength()
{
    return this->length;
}

int Picture_2::getWidth()
{
    return this->width;
}

void Picture_2::setProductionNationality(QString ProductionNationality)
{
    this->ProductionNationality = ProductionNationality;
}

void Picture_2::setLength(int length)
{
    this->length = length;
}

void Picture_2::setWidth(int width)
{
    this->width = width;
}
