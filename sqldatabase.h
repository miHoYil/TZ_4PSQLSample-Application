#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtGui>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>

struct FunctionOfDb{
    QPair<QString,int> NameOfFunction;
    QVector<QPair<QString,QString> > ParametrsOfFunction;
};

class sqlDatabase : public QObject
{
    Q_OBJECT
public:
    sqlDatabase(QObject * parent = 0);
public:
    QVector<FunctionOfDb> DbFunctions;

private:

void ConnectToDb(QString DbType, QString HostName, //
                 QString DbName, QString UserName, //
                 QString Password, int Port);

QSqlDatabase Dbase;

public:
void CreateTestDbandTable(QString HostName,QString Username, QString Password,int Port);

};

#endif // SQLDATABASE_H
