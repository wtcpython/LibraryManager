#include "VideoCD.h"
#include <iostream>
using namespace std;

VideoCD_2::VideoCD_2()
{
	this->name = "";
	this->ProductionYear = 0;
	this->VideoDuration = 0;
}

VideoCD_2::VideoCD_2(
	int id, QString title, QString author, QString grade,
	QString name, int PrioductionYear, int VideoDuration)
	: Media_1(id, title, author, grade), name(name), ProductionYear(PrioductionYear), VideoDuration(VideoDuration)
{}

void VideoCD_2::setName(const QString name)
{
	this->name = name;
}

void VideoCD_2::setProductionYear(int ProductionYear)
{
	this->ProductionYear = ProductionYear;
}

void VideoCD_2::setVideoDuration(int VideoDuration)
{
	this->VideoDuration = VideoDuration;
}

QString VideoCD_2::getName()
{
	return this->name;
}

int VideoCD_2::getProductionYear()
{
	return this->ProductionYear;
}

int VideoCD_2::getVideoDuration()
{
	return this->VideoDuration;
}
