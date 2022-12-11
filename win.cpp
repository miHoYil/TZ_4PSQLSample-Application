
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QTableView>
#include <QtGui>

#include "win.h"



Win::Win(QWidget *parent) : QWidget(parent)
{

    MainHLayout = new QHBoxLayout(this);

    ShowDataBaseButton = new QPushButton("Show DataBase");
    BackToFunctionsButton = new QPushButton("Back to Func");

    DatabaseTableView = new QTableView();


    InputUsernameLabel = new QLabel("Username");
    InputUsernameEdit = new QLineEdit("");

    InputPasswordLabel = new QLabel("Password");
    InputPasswordEdit = new QLineEdit("");


    InputLocalhostLabel = new QLabel("Localhost");
    InputLocalhostEdit = new QLineEdit("");

    InputPortLabel = new QLabel("Port");
    InputPortEdit = new QLineEdit("");

    QGridLayout *EnterScreenLayout = new QGridLayout();

    EnterScreenLayout->addWidget(InputUsernameLabel,0,0,1,1);
    EnterScreenLayout->addWidget(InputPasswordLabel,0,2,1,1);
    EnterScreenLayout->addWidget(InputUsernameEdit,1,0,1,2);
    EnterScreenLayout->addWidget(InputPasswordEdit,1,2,1,2);

    EnterScreenLayout->addWidget(InputLocalhostLabel,2,0,1,1);
    EnterScreenLayout->addWidget(InputPortLabel,2,2,1,1);
    EnterScreenLayout->addWidget(InputLocalhostEdit,3,0,1,2);
    EnterScreenLayout->addWidget(InputPortEdit,3,2,1,2);

    MainHLayout->addLayout(EnterScreenLayout);

    this->resize(300,100);


    DatabaseTableView->setVisible(false);
    ShowDataBaseButton->setVisible(false);
    BackToFunctionsButton->setVisible(false);

    connect(InputUsernameEdit,SIGNAL(returnPressed()),this,SLOT(enterInDatabase()));
    connect(InputPasswordEdit,SIGNAL(returnPressed()),this,SLOT(enterInDatabase()));
    connect(InputLocalhostEdit,SIGNAL(returnPressed()),this,SLOT(enterInDatabase()));
    connect(InputPortEdit,SIGNAL(returnPressed()),this,SLOT(enterInDatabase()));

    connect(ShowDataBaseButton,SIGNAL(clicked(bool)),this,SLOT(showDataBase()));
    connect(BackToFunctionsButton,SIGNAL(clicked(bool)),this,SLOT(showFunctionsOfDb()));
}

void Win::enterInDatabase()
{
    DatabaseController.CreateTestDbandTable(InputLocalhostEdit->text(),InputUsernameEdit->text(), //
                                            InputPasswordEdit->text(),InputPortEdit->text().toInt());
    //DatabaseController.CreateTestDbandTable("localhost","postgres","admin",5432);

    InputUsernameLabel->close();
    InputUsernameEdit->close();
    InputPasswordLabel->close();
    InputPasswordEdit->close();
    InputLocalhostLabel->close();
    InputLocalhostEdit->close();
    InputPortLabel->close();
    InputPortEdit->close();

    this->resize(800,300);

    QSqlQuery query;

    query.exec("SELECT routine_name " \
    "FROM information_schema.routines " \
    "WHERE routine_type = 'FUNCTION' " \
    "AND routine_schema = 'public';");

    QSqlQuery query2;
    int i = 0;
    QPair<QString,int> x;
    QPair<QString,QString> x2;
    DatabaseController.DbFunctions.reserve(query.size());
     DatabaseController.DbFunctions.resize(query.size());
    while(query.next())
    {
        x.first = query.value(0).toString();
        query2.prepare("SELECT oid FROM pg_proc WHERE proname=? ");
        query2.addBindValue(x.first);
        query2.exec();
        query2.next();
        x.second = query2.value(0).toInt();
        DatabaseController.DbFunctions[i].NameOfFunction = x;
        i++;
    }

    for (i = 0; i< DatabaseController.DbFunctions.size();i++)
    {
        query2.prepare("SELECT pg_get_function_identity_arguments(?);");
        query2.addBindValue(DatabaseController.DbFunctions[i].NameOfFunction.second);
        query2.exec();
        query2.next();
        QString AllParametr = " " + query2.value(0).toString();
        QString Parametr;
        int NumOfParametrs = AllParametr.count(',')+1;
        DatabaseController.DbFunctions[i].ParametrsOfFunction.reserve(NumOfParametrs);
        DatabaseController.DbFunctions[i].ParametrsOfFunction.resize(NumOfParametrs);
        for (int j = 0; j < NumOfParametrs; j++){
                Parametr = AllParametr.section(',',j,j);
                Parametr.remove(0,1);
                x2.first = Parametr.section(" ",0,0);
                x2.second = Parametr.section(" ",1);
                DatabaseController.DbFunctions[i].ParametrsOfFunction[j] = x2;
            }

     }

    MainHLayout->addWidget(DatabaseTableView);

    FunctionsDisplay.reserve(DatabaseController.DbFunctions.size());
    FunctionsDisplay.resize(DatabaseController.DbFunctions.size());


   QVBoxLayout* FuncDisplayLay = new QVBoxLayout();

  // FuncDisplayLay->setSizeConstraint(QLayout::SetMinAndMaxSize);

    ScrollAreaForParam = new QScrollArea();

    QWidget* ScrolableArea = new QWidget();

    ScrollAreaForParam->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ScrollAreaForParam->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ScrollAreaForParam->setWidgetResizable(true);
    ScrollAreaForParam->setWidget(ScrolableArea);

   for (int i = 0; i < DatabaseController.DbFunctions.size();i++)
   {
       QVBoxLayout* OneParamLay = new QVBoxLayout();

       FunctionsDisplay[i].NameOfFuncLabel = new QLabel(DatabaseController.DbFunctions[i].NameOfFunction.first);
       FunctionsDisplay[i].NameOfFuncLabel->setStyleSheet("font-weight: bold");
       OneParamLay->addWidget(FunctionsDisplay[i].NameOfFuncLabel);

       FunctionsDisplay[i].NameOfFuncLabel->setVisible(false);

       FunctionsDisplay[i].ParametrsLabel.reserve(DatabaseController.DbFunctions[i].ParametrsOfFunction.size());
       FunctionsDisplay[i].ParametrsLabel.resize(DatabaseController.DbFunctions[i].ParametrsOfFunction.size());

       FunctionsDisplay[i].ParametrsEdit.reserve(DatabaseController.DbFunctions[i].ParametrsOfFunction.size());
       FunctionsDisplay[i].ParametrsEdit.resize(DatabaseController.DbFunctions[i].ParametrsOfFunction.size());

       for (int j = 0; j < DatabaseController.DbFunctions[i].ParametrsOfFunction.size();j++)
       {
           FunctionsDisplay[i].ParametrsLabel[j] = new QLabel(DatabaseController.DbFunctions[i].ParametrsOfFunction[j].first+":");
           FunctionsDisplay[i].ParametrsEdit[j] = new QLineEdit();

           FunctionsDisplay[i].ParametrsLabel[j]->setMinimumSize(150,5);
          // FunctionsDisplay[i].ParametrsEdit[j]->setMaximumSize(50,25);

           QHBoxLayout* LabelBindEdit = new QHBoxLayout();
           LabelBindEdit->addWidget(FunctionsDisplay[i].ParametrsLabel[j]);
           LabelBindEdit->addWidget(FunctionsDisplay[i].ParametrsEdit[j]);

           FunctionsDisplay[i].ParametrsLabel[j]->setVisible(false);
           FunctionsDisplay[i].ParametrsEdit[j]->setVisible(false);

           OneParamLay->addLayout(LabelBindEdit);
       }
       FunctionsDisplay[i].UseFuncButton = new myButton(i);
       FunctionsDisplay[i].UseFuncButton->setText("Apply");
       OneParamLay->addWidget(FunctionsDisplay[i].UseFuncButton);
       FunctionsDisplay[i].UseFuncButton->setVisible(false);
       FuncDisplayLay->addLayout(OneParamLay);
       connect( FunctionsDisplay[i].UseFuncButton,SIGNAL(myClicked(int)),this,SLOT(useDbFunction(int)));
   }

    FuncDisplayLay->addStretch();
    ScrolableArea->setLayout(FuncDisplayLay);
    MainHLayout->addWidget(ScrollAreaForParam);

    ButtonVLay = new QVBoxLayout();
    ButtonVLay->addWidget(ShowDataBaseButton);
    ButtonVLay->addWidget(BackToFunctionsButton);

    MainHLayout->addLayout(ButtonVLay);

    ShowDataBaseButton->setVisible(true);
    BackToFunctionsButton->setVisible(true);
    BackToFunctionsButton->setEnabled(false);
    ScrollAreaForParam->setVisible(false);

}

void Win::showDataBase()
{
    QSqlTableModel* model = new QSqlTableModel(this,QSqlDatabase::database("mydb"));
    model->setTable("accounts");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Password"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Created on"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Last Log in"));

    DatabaseTableView->setModel(model);
    DatabaseTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    DatabaseTableView->setVisible(true);

    BackToFunctionsButton->setEnabled(true);
    ShowDataBaseButton->setEnabled(false);

    ScrollAreaForParam->setVisible(false);

    for (int i = 0; i < DatabaseController.DbFunctions.size();i++)
    {

        FunctionsDisplay[i].NameOfFuncLabel->setVisible(false);

        for (int j = 0; j < DatabaseController.DbFunctions[i].ParametrsOfFunction.size();j++)
        {

            FunctionsDisplay[i].ParametrsLabel[j]->setVisible(false);
            FunctionsDisplay[i].ParametrsEdit[j]->setVisible(false);
            FunctionsDisplay[i].ParametrsEdit[j]->clear();
        }
         FunctionsDisplay[i].UseFuncButton->setVisible(false);
    }
}

void Win::showFunctionsOfDb()
{
    ScrollAreaForParam->setVisible(true);

    for (int i = 0; i < DatabaseController.DbFunctions.size();i++)
    {

        FunctionsDisplay[i].NameOfFuncLabel->setVisible(true);

        for (int j = 0; j < DatabaseController.DbFunctions[i].ParametrsOfFunction.size();j++)
        {

            FunctionsDisplay[i].ParametrsLabel[j]->setVisible(true);
            FunctionsDisplay[i].ParametrsEdit[j]->setVisible(true);

        }
         FunctionsDisplay[i].UseFuncButton->setVisible(true);
    }
    DatabaseTableView->setVisible(false);


   BackToFunctionsButton->setEnabled(false);
   ShowDataBaseButton->setEnabled(true);
}

void Win::useDbFunction(int TypeOfFunc)
{

    QSqlQuery query;


    QString PrepareQuer;
    PrepareQuer = "SELECT "+DatabaseController.DbFunctions[TypeOfFunc].NameOfFunction.first+"(";
    for( int i = 0; i<DatabaseController.DbFunctions[TypeOfFunc].ParametrsOfFunction.size();i++)
    {
        PrepareQuer+="?,";
    }
    PrepareQuer.remove(PrepareQuer.size()-1,1);
    PrepareQuer+=");";

    query.prepare(PrepareQuer);

    for( int i = 0; i<DatabaseController.DbFunctions[TypeOfFunc].ParametrsOfFunction.size();i++)
    {
        query.addBindValue(FunctionsDisplay[TypeOfFunc].ParametrsEdit[i]->text());
    }
    bool sr = query.exec();
    if (!sr) {
        qDebug()<<QObject::tr("Database Error")+" "+query.lastError().text();
        QMessageBox msgBox(QMessageBox::Information,"Warning","Invalid input format",QMessageBox::Ok);
        msgBox.exec();
    }
    else
    for( int i = 0; i<DatabaseController.DbFunctions[TypeOfFunc].ParametrsOfFunction.size();i++)
    {
        FunctionsDisplay[TypeOfFunc].ParametrsEdit[i]->clear();
    }
}
