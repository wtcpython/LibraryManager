#pragma once
#include "libmedia.h"

// 视频光盘类
class VideoCD_2 : public Media_1
{
  private:
    QString name;       // 出品者名字
    int ProductionYear; // 出品年份
    int VideoDuration;  // 视频时长

  public:
    VideoCD_2();
    VideoCD_2(int id, QString title, QString author, QString grade, QString name, int PrioductionYear,
              int VideoDuration);

    void setName(const QString name);
    void setProductionYear(int PrioductionYear);
    void setVideoDuration(int VideoDuration);

    QString getName();
    int getProductionYear();
    int getVideoDuration();
};