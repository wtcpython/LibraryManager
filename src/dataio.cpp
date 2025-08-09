#include "dataio.h"
#include <QDebug>

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{
}

bool DatabaseHandler::isIdExist(int id, const QString tableName)
{
    QSqlQuery query(m_database);

    query.prepare("SELECT COUNT(*) FROM " + tableName + " WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    if (query.next())
    {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

QString DatabaseHandler::getFileName()
{
    return fileName;
}

bool DatabaseHandler::openDatabase(const QString &fileName)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE"); // 设置数据库类型为 SQLite
    m_database.setDatabaseName(fileName);              // 设置数据库文件名

    if (!m_database.open())
    {
        qDebug() << "Error: unable to open database:" << m_database.lastError().text();
        return false;
    }
    createBooksTable();
    createCDTable();
    return true;
    createPicsTable();
}

void DatabaseHandler::closeDatabase()
{
    m_database.close(); // 关闭数据库连接
}

bool DatabaseHandler::createBooksTable()
{
    QSqlQuery query(m_database);
    QString str = "CREATE TABLE IF NOT EXISTS Books ("
                  "id INTEGER,"
                  "title TEXT, "
                  "author TEXT,"
                  "grade INTEGER,"
                  "publishingHouse TEXT,"
                  "isbn TEXT,"
                  "page INTEGER);";

    if (!query.exec(str))
    {
        qDebug() << "Error creating Books table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::createCDTable()
{
    QSqlQuery query(m_database);
    QString str = "CREATE TABLE IF NOT EXISTS CDs ("
                  "id INTEGER,"
                  "title TEXT,"
                  "author TEXT,"
                  "grade INTEGER,"
                  "name TEXT,"
                  "PrioductionYear INTEGER,"
                  "VideoDuration INTEGER);";

    if (!query.exec(str))
    {
        qDebug() << "Error creating CD table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::createPicsTable()
{
    QSqlQuery query(m_database);
    QString str = "CREATE TABLE IF NOT EXISTS Pics ("
                  "id INTEGER,"
                  "title TEXT,"
                  "author TEXT,"
                  "grade INTEGER,"
                  "ProductionNationality TEXT,"
                  "length INTEGER,"
                  "width INTEGER);";

    if (!query.exec(str))
    {
        qDebug() << "Error creating Pisc table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::insertBook(Book_1 &book)
{
    QSqlQuery query(m_database);

    if (isIdExist(book.getId(), "Books"))
    {
        query.prepare("UPDATE Books SET title = :title, author = :author, grade = :grade, "
                      "publishingHouse = :publishingHouse, isbn = :isbn, page = :page "
                      "WHERE id = :id");
    }
    else
    {
        query.prepare("INSERT INTO Books (id, title, author, grade, publishingHouse, isbn, page) "
                      "VALUES (:id, :title, :author, :grade, :publishingHouse, :isbn, :page)");
    }

    query.bindValue(":id", book.getId());
    query.bindValue(":title", book.getTitle());
    query.bindValue(":author", book.getAuthor());
    query.bindValue(":grade", book.getGrade()); // Use static_cast for clarity
    query.bindValue(":publishingHouse", book.getPublishingHouse());
    query.bindValue(":isbn", book.getIsbn());
    query.bindValue(":page", book.getPage());

    if (!query.exec())
    {
        qDebug() << "Error inserting into Books table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::insertCD(VideoCD_2 &cd)
{
    QSqlQuery query(m_database);

    QString sqlQuery;
    if (isIdExist(cd.getId(), "CDs"))
    {
        sqlQuery = "UPDATE CDs SET title = :title, author = :author, grade = :grade, "
                   "name = :name, PrioductionYear = :PrioductionYear, videoDuration = :videoDuration "
                   "WHERE id = :id";
    }
    else
    {
        sqlQuery = "INSERT INTO CDs (id, title, author, grade, name, PrioductionYear, videoDuration) "
                   "VALUES (:id, :title, :author, :grade, :name, :PrioductionYear, :videoDuration)";
    }

    query.prepare(sqlQuery);
    query.bindValue(":id", cd.getId());
    query.bindValue(":title", cd.getTitle());
    query.bindValue(":author", cd.getAuthor());
    query.bindValue(":grade", cd.getGrade());
    query.bindValue(":name", cd.getName());
    query.bindValue(":PrioductionYear", cd.getProductionYear());
    query.bindValue(":videoDuration", cd.getVideoDuration());

    if (!query.exec())
    {
        qDebug() << "Error inserting into CDs table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseHandler::insertPic(Picture_2 &pic)
{
    QSqlQuery query(m_database);

    QString sqlQuery;
    if (isIdExist(pic.getId(), "Pics"))
    {
        sqlQuery = "UPDATE Pics SET title = :title, author = :author, grade = :grade, "
                   "productionNationality = :productionNationality, length = :length, width = :width "
                   "WHERE id = :id";
    }
    else
    {
        sqlQuery = "INSERT INTO Pics (id, title, author, grade, productionNationality, length, width) "
                   "VALUES (:id, :title, :author, :grade, :productionNationality, :length, :width)";
    }

    query.prepare(sqlQuery);
    query.bindValue(":id", pic.getId());
    query.bindValue(":title", pic.getTitle());
    query.bindValue(":author", pic.getAuthor());
    query.bindValue(":grade", pic.getGrade());
    query.bindValue(":productionNationality", pic.getProductionNationality());
    query.bindValue(":length", pic.getLength());
    query.bindValue(":width", pic.getWidth());

    if (!query.exec())
    {
        qDebug() << "Error inserting into Pics table:" << query.lastError().text();
        return false;
    }

    return true;
}

vector<Book_1> DatabaseHandler::fetchBooksData()
{
    vector<Book_1> books;

    QSqlQuery query("SELECT * FROM Books");

    if (!query.exec())
    {
        // 查询失败，处理错误
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return books;
    }

    // 遍历查询结果集，将每行数据存入 QVariantList，并添加到结果列表中返回
    while (query.next())
    {
        Book_1 book;
        book.setId(query.value(0).toInt());
        book.setTitle(query.value(1).toString());
        book.setAuthor(query.value(2).toString());
        book.setGrade(query.value(3).toString());
        book.setPublishingHouse(query.value(4).toString());
        book.setIsbn(query.value(5).toString());
        book.setPage(query.value(6).toInt());

        books.push_back(book);
    }

    return books;
}

vector<VideoCD_2> DatabaseHandler::fetchVideoCDData()
{
    vector<VideoCD_2> videoCDs;

    QSqlQuery query("SELECT * FROM CDs");

    if (!query.exec())
    {
        // 查询失败，处理错误
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return videoCDs;
    }

    // 遍历查询结果集，将每行数据存入 QVariantList，并添加到结果列表中返回
    while (query.next())
    {
        VideoCD_2 videoCD;
        videoCD.setId(query.value(0).toInt());
        videoCD.setTitle(query.value(1).toString());
        videoCD.setAuthor(query.value(2).toString());
        videoCD.setGrade(query.value(3).toString());
        videoCD.setName(query.value(4).toString());
        videoCD.setProductionYear(query.value(5).toInt());
        videoCD.setVideoDuration(query.value(6).toInt());

        videoCDs.push_back(videoCD);
    }
    return videoCDs;
}

vector<Picture_2> DatabaseHandler::fetchPictureData()
{
    vector<Picture_2> Pics;

    QSqlQuery query("SELECT * FROM Pics");

    if (!query.exec())
    {
        // 查询失败，处理错误
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return Pics;
    }

    // 遍历查询结果集，将每行数据存入 QVariantList，并添加到结果列表中返回
    while (query.next())
    {
        Picture_2 pic;
        pic.setId(query.value(0).toInt());
        pic.setTitle(query.value(1).toString());
        pic.setAuthor(query.value(2).toString());
        pic.setGrade(query.value(3).toString());
        pic.setProductionNationality(query.value(4).toString());
        pic.setLength(query.value(5).toInt());
        pic.setWidth(query.value(6).toInt());

        Pics.push_back(pic);
    }
    return Pics;
}

bool DatabaseHandler::deleteLine(int id)
{
    // 获取所有表的名称
    QStringList tables = m_database.tables();

    // 遍历每个表
    for (const QString &table : tables)
    {
        QSqlQuery query(m_database);
        QString str = QString("DELETE FROM %1 WHERE id = :id;").arg(table);
        query.prepare(str);
        query.bindValue(":id", id);

        if (!query.exec())
        {
            qDebug() << "Error deleting from table" << table << ":" << query.lastError().text();
            // return false; // 或者继续尝试删除其他表中的数据
        }

        qDebug() << "Deleted from table" << table << "for id" << id;
    }

    return true;
}