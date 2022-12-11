#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QTableView>
#include <QtGui>

#include "win.h"
#include "sqldatabase.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Win MainWindow(0);

    MainWindow.show();

    return app.exec();
}
