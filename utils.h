#pragma once
#include "book.h"
#include "Picture.h"
#include "VideoCD.h"
#include <iostream>
#include <optional>
#include <QString>
#include <vector>

class Utils
{
private:
	int SIZE = 20;
	Book_1 lastbook;
	VideoCD_2 lastcd;
	Picture_2 lastpic;

	std::vector<int> sum = std::vector<int>(4);//sum[0]总数量  sum[1]book的数量 sum[2]cd的数量  sum[3]pic的数量
	std::vector<Book_1> books = std::vector<Book_1>(SIZE);
	std::vector<VideoCD_2> cds = std::vector<VideoCD_2>(SIZE);
	std::vector<Picture_2> pics = std::vector<Picture_2>(SIZE);

public:

	Book_1 getLastbook();
	VideoCD_2 getLastcd();
	Picture_2 getLastpic();
	bool addBookItem(Book_1 books);
	bool addCDItem(VideoCD_2 cd);
	bool addPicItem(Picture_2 pic);

	std::vector<Book_1> getBooks();
	std::vector<VideoCD_2> getCds();
	std::vector<Picture_2> getPics();

	std::vector<int> statistic();
	bool IdExist(int index);
	bool searchBookItem(int id);
	bool searchCDItem(int id);
	bool searchPicItem(int id);
	bool searchBookItem(QString title);
	bool searchCDItem(QString title);
	bool searchPicItem(QString title);
	bool isFull();
	bool deleteItem(int id);
};
