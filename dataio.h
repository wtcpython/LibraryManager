#pragma once
#include "book.h"
#include "Picture.h"
#include "VideoCD.h"
#include <QDebug>
#include <QObject>
#include <QtSql>

class DatabaseHandler : public QObject
{
	Q_OBJECT
public:
	explicit DatabaseHandler(QObject* parent = nullptr);

	bool openDatabase(const QString& fileName);   // 打开指定名称的数据库
	void closeDatabase();     // 关闭数据库连接

	bool createBooksTable();  // 创建名为 Books 的表格
	bool createCDTable();     // 创建名为 CD 的表格
	bool createPicsTable();   // 创建名为 Pic 的表格

	bool insertCD(VideoCD_2& cd);
	bool insertBook(Book_1& book);
	bool insertPic(Picture_2& pic);

	bool isIdExist(int id, const QString tableName);

	bool deleteLine(int id);
	QString getFileName();

	vector<Book_1> fetchBooksData();               // 查询并返回 Books 表格中的所有数据
	vector<VideoCD_2> fetchVideoCDData();           // 查询并返回 VideoCD 表格中的所有数据
	vector<Picture_2> fetchPictureData();           // 查询并返回 Picture 表格中的所有数据

private:
	QSqlDatabase m_database;                   // 数据库连接对象
	QString fileName;
};