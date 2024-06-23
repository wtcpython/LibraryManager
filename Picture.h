#pragma once
#include "libmedia.h"
#include <QString>

class Picture_2 : public Media_1
{
private:
	QString ProductionNationality; // 出品国籍
	int length;
	int width; // 图片的长和宽

public:
	Picture_2();
	Picture_2(int id, QString title, QString author, QString grade, QString ProductionNationality, int length, int width);

	void setProductionNationality(QString ProductionNationality);
	QString getProductionNationality();

	void setLength(int length);
	int getLength();

	void setWidth(int width);
	int getWidth();
};