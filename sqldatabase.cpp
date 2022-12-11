
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtGui>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

#include "sqldatabase.h"

sqlDatabase::sqlDatabase(QObject * parent):QObject(parent)
{

}


void sqlDatabase::ConnectToDb(QString DbType,QString HostName,QString DbName,QString UserName,QString Password,int Port)
{
    Dbase = QSqlDatabase::addDatabase(DbType);
    Dbase.setHostName(HostName);
    Dbase.setDatabaseName(DbName);
    Dbase.setUserName(UserName);
    Dbase.setPassword(Password);
    Dbase.setPort(Port);
}

void sqlDatabase::CreateTestDbandTable(QString Localhost = "localhost",QString Username = "postgres",QString Password = "admin",int Port = 5432)
{
    ConnectToDb("QPSQL",Localhost,"postgres", //
                Username,Password,Port);

    QString dbName = "mydb";
    QSqlQuery query;
    bool sr=false;

    if (!Dbase.open())
        qDebug() << QObject::trUtf8("Бд не найдена") <<"\n"<< Dbase.lastError().text();

    if(query.exec("SELECT datname FROM pg_database;")){
        while (query.next())
            if(query.value(0).toString() == dbName)
                sr = true;
    }
    else qDebug()<<query.lastError();

    if(!sr)
    {
        sr = query.exec("CREATE DATABASE mydb");
        if (!sr) {
            qDebug()<<QObject::tr("Database Error")+" "+query.lastError().text();
        }
    }

    Dbase.close();

    Dbase.setDatabaseName(dbName);
    sr = Dbase.open();
    if (!sr) {
        qDebug()<<QObject::tr("Database Error")+" "+query.lastError().text();
    }
    sr = query.exec("CREATE TABLE IF NOT EXISTS accounts" \
                       "(user_id SERIAL PRIMARY KEY, "\
                       "username VARCHAR(50) UNIQUE NOT NULL, "\
                       "password VARCHAR(50) NOT NULL, "\
                       "email VARCHAR(255) UNIQUE NOT NULL, "\
                       "created_on TIMESTAMP NOT NULL, "\
                       "last_login TIMESTAMP);");

    if (!sr) {
        qDebug()<<QObject::tr("Database Error")+" "+query.lastError().text();
    }

    query.prepare("INSERT INTO accounts (username, password, email, created_on, last_login) " \
                  "VALUES (?, ?, ?, ?, ?) " \
                  "ON CONFLICT DO NOTHING" );

    query.addBindValue("J.C. Denton");
    query.addBindValue("bionicman");
    query.addBindValue("jcd@gmail.com");
    query.addBindValue(QDateTime(QDate(2052,4,12),QTime(22,14)));
    query.addBindValue(QDateTime(QDate(2052,8,14),QTime(13,14)));
    query.exec();

    query.addBindValue("Garrett");
    query.addBindValue("taffer");
    query.addBindValue("oneeyedthief@gmail.com");
    query.addBindValue(QDateTime(QDate(2012,5,24),QTime(13,46)));
    query.addBindValue(QDateTime(QDate(2014,6,11),QTime(23,22)));
    query.exec();

    query.addBindValue("Konaree");
    query.addBindValue("markgon");
    query.addBindValue("Konaree@gmail.com");
    query.addBindValue(QDateTime(QDate(2020,5,5),QTime(14,23)));
    query.addBindValue(QDateTime(QDate(2022,12,10),QTime(15,41)));
    query.exec();

    query.addBindValue("Aroz");
    query.addBindValue("amirpid");
    query.addBindValue("Arozm@mail.ru");
    query.addBindValue(QDateTime(QDate(2021,6,6),QTime(15,42)));
    query.addBindValue(QDateTime(QDate(2022,12,8),QTime(16,53)));
    query.exec();

    query.addBindValue("CrasHoYil");
    query.addBindValue("poexyin");
    query.addBindValue("ligagov@mail.ru");
    query.addBindValue(QDateTime(QDate(2020,2,29),QTime(5,32)));
    query.addBindValue(QDateTime(QDate(2022,12,7),QTime(18,14)));
    query.exec();

    query.exec("CREATE OR REPLACE FUNCTION updatePassword( userForChange VARCHAR(50), newpas VARCHAR(50) ) " \
               "RETURNS void " \
               "LANGUAGE SQL " \
               "AS $$ " \
               "UPDATE accounts SET password = newpas WHERE username = userForChange "
               "$$;"\
    );

    query.exec("CREATE OR REPLACE FUNCTION addAccount( " \
                      "newusername VARCHAR(50), " \
                       "newpassword VARCHAR(50), " \
                       "newemail VARCHAR(255), " \
                       "newcreated_on TIMESTAMP ) " \
               "RETURNS void " \
               "LANGUAGE SQL " \
               "AS $$ " \
               "INSERT INTO accounts(username, password, email, created_on) " \
               "VALUES (newusername, newpassword, newemail, newcreated_on) " \
               "$$;"\
    );

    query.exec("CREATE OR REPLACE FUNCTION deleteAccount( delusername VARCHAR(50) ) " \
               "RETURNS void " \
               "LANGUAGE SQL " \
               "AS $$ " \
               "DELETE FROM accounts WHERE username = delusername " \
               "$$;"\
    );

    if (!sr) {
        qDebug()<<QObject::tr("Database Error")+" "+query.lastError().text();
    }

}
