#ifndef WIN_H
#define WIN_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QtGui>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QTableView>
#include <QWidget>
#include <QSqlTableModel>

#include "sqldatabase.h"

class myButton : public QPushButton
{
    Q_OBJECT
private:
    int TypeOfFucnForBtn;
public: myButton(int TypeOfFucn, QWidget * parent = 0):QPushButton(parent), TypeOfFucnForBtn(TypeOfFucn)
    {
        connect(this, SIGNAL(clicked()), this, SLOT(ChangeSig()));
    }
signals:
    void myClicked(int TypeOfFucnForBtn);

public slots:
    void ChangeSig()
    {
        emit myClicked(TypeOfFucnForBtn);
    };
};

struct AllForFunctionDisplay
{
   QLabel* NameOfFuncLabel;

   QVector<QLabel*> ParametrsLabel;
   QVector<QLineEdit*> ParametrsEdit;

   myButton* UseFuncButton;

};
class Win : public QWidget
{
    Q_OBJECT
public:
     Win(QWidget *parent = 0);
     void setSQLTableModel(QSqlTableModel* model);
     QSqlTableModel model;

private:
     QLabel* InputUsernameLabel;
     QLineEdit* InputUsernameEdit;

     QLabel* InputPasswordLabel;
     QLineEdit* InputPasswordEdit;

     QLabel* InputLocalhostLabel;
     QLineEdit* InputLocalhostEdit;

     QLabel* InputPortLabel;
     QLineEdit* InputPortEdit;

    QVector<AllForFunctionDisplay> FunctionsDisplay;

     QPushButton* ShowDataBaseButton;
     QPushButton* BackToFunctionsButton;

     QTableView* DatabaseTableView;
     sqlDatabase DatabaseController;

     QHBoxLayout* MainHLayout;
     QVBoxLayout* ButtonVLay;

     QScrollArea* ScrollAreaForParam;


public slots:
     void enterInDatabase();
     void showDataBase();
     void showFunctionsOfDb();
     void useDbFunction(int TypeOfFunc);
signals:

};

#endif // WIN_H
