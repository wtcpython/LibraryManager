#pragma once
#include "Picture.h"
#include "VideoCD.h"
#include "book.h"
#include <QString>
#include <vector>

class Utils
{
  private:
    int SIZE = 20;
    Book_1 lastbook;
    VideoCD_2 lastcd;
    Picture_2 lastpic;

    // sum[0] 是图书馆媒体的总数量
    // sum[1] 是 Book 的数量
    // sum[2] 是 CD 的数量
    // sum[3] 是 Picture 的数量
    std::vector<int> sum = std::vector<int>(4);
    std::vector<Book_1> books = std::vector<Book_1>(SIZE);      // 图书列表
    std::vector<VideoCD_2> cds = std::vector<VideoCD_2>(SIZE);  // CD 列表
    std::vector<Picture_2> pics = std::vector<Picture_2>(SIZE); // 图片列表

  public:
    Book_1 getLastbook();           // 获取上次查询的最后一本书
    VideoCD_2 getLastcd();          // 获取上次查询的最后一张 CD
    Picture_2 getLastpic();         // 获取上次查询的最后一张图片
    bool addBookItem(Book_1 book);  // 添加图书
    bool addCDItem(VideoCD_2 cd);   // 添加 CD
    bool addPicItem(Picture_2 pic); // 添加图片

    std::vector<Book_1> getBooks();   // 获取所有图书
    std::vector<VideoCD_2> getCds();  // 获取所有 CD
    std::vector<Picture_2> getPics(); // 获取所有图片

    std::vector<int> statistic();       // 统计信息
    bool isIdExist(int index);          // 判断 ID 是否存在
    bool searchBookItem(int id);        // 通过 ID 查找图书
    bool searchCDItem(int id);          // 通过 ID 查找 CD
    bool searchPicItem(int id);         // 通过 ID 查找图片
    bool searchBookItem(QString title); // 通过标题查找图书
    bool searchCDItem(QString title);   // 通过标题查找 CD
    bool searchPicItem(QString title);  // 通过标题查找图片
    bool isFull();                      // 判断图书是否已满
    bool deleteItem(int id);            // 根据 ID 删除项
};
