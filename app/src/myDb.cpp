#include "myDb.h"

MyDb::MyDb() : appPath(QDir::homePath() + "/.uamp/"),
               dbPath(appPath + "myDb"),
               db(QSqlDatabase::addDatabase("QSQLITE", "myDb"))
{
    checkDir();
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Db openind failed";
        exit(1);
    }
    createIfNotExist();
}

void MyDb::checkDir() {
    if (!QFile::exists(appPath)) {
        QDir appDir;

        appDir.mkpath(appPath);
    }
}

void MyDb::createIfNotExist() {
    QSqlQuery query(QSqlDatabase::database("myDb"));

    if (!query.exec("SELECT * FROM files")) {
        query.exec("CREATE TABLE files (name varchar(255), path varchar(255));");
        qDebug() << "Create new Db";
    }
    else {
        qDebug() << "Open existing Db";
    }
}