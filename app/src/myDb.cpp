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

    if (!query.exec("SELECT * FROM users")) {
        query.exec("create table if not exists users (id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                                      name varchar(255),\
                                                      login varchar(255) NOT NULL UNIQUE,\
                                                      password varchar(255));\
                    ");
        query.exec("create table if not exists songs (id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                                      name varchar(255),\
                                                      path varchar(255));\
                    ");
        query.exec("create table if not exists playlists (id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                                          name varchar(255),\
                                                          user_id INTEGER,\
                                                          FOREIGN KEY (user_id) REFERENCES users (id));\
                    ");
        query.exec("create table if not exists playlist_content (id INTEGER PRIMARY KEY AUTOINCREMENT,\
                                                                 playlist_id INTEGER,\
                                                                 song_id INTEGER,\
                                                                 FOREIGN KEY (playlist_id) REFERENCES playlists (id),\
                                                                 FOREIGN KEY (song_id) REFERENCES songs (id));\
                    ");
        query.exec("CREATE INDEX song_id_index ON songs (id);");
        qDebug() << "Creating new Db";
    }
    else {
        qDebug() << "Opening existing Db";
    }
}