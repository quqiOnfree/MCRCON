#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QMessageBox>

#include "./ServerManagerDialog/servermanagedialog.h"
#include "./AddServerDialog/addserverdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionserver_list, &QAction::triggered, this, &MainWindow::showServerList);
    QObject::connect(ui->actionServer_options, &QAction::triggered, this, &MainWindow::showServerOpinion);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::manageServer);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::addServer);
}

void MainWindow::showServerList()
{
    ui->dockWidget_3->setVisible(true);
}

void MainWindow::showServerOpinion()
{
    ui->dockWidget_2->setVisible(true);
}

void MainWindow::manageServer()
{
    ServerManageDialog SMD(&serverInfos);
    SMD.exec();
}

void MainWindow::addServer()
{
    ServerInfo serverInfo;
    AddServerDialog ASD(serverInfo);
    if (ASD.exec() != QDialog::Accepted)
    {
        return;
    }

    QMessageBox::information(this, "信息", "OK");
}

MainWindow::~MainWindow()
{
    delete ui;
}

