#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QMessageBox>

#include "./ServerManagerDialog/servermanagedialog.h"
#include "./AddServerDialog/addserverdialog.h"

RunServer::RunServer(const ServerInfo& info)
    : QWidget(nullptr)
{
    m_info = info;
    m_client = new QTcpSocket(this);

    {
        QVBoxLayout* verticalLayout = new QVBoxLayout(this);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        QFrame* frame_5 = new QFrame(this);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        QHBoxLayout* horizontalLayout_3 = new QHBoxLayout(frame_5);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        QFrame* frame_3 = new QFrame(frame_5);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        QGridLayout* gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        QLabel* label_4 = new QLabel(frame_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        QLabel* label_7 = new QLabel(frame_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 1, 0, 1, 1);

        QLabel* label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 1, 1, 1, 1);

        QLabel* label_8 = new QLabel(frame_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 2, 0, 1, 1);

        QLabel* label_9 = new QLabel(frame_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 2, 1, 1, 1);


        horizontalLayout_3->addWidget(frame_3);

        QFrame* frame_4 = new QFrame(frame_5);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(frame_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        QSpacerItem* horizontalSpacer_4 = new QSpacerItem(530, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        QPushButton* pushButton = new QPushButton(frame_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        horizontalLayout_3->addWidget(frame_4);


        verticalLayout->addWidget(frame_5);

        QLabel* label = new QLabel(this);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        QTextEdit* textEdit = new QTextEdit(this);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        QLabel* label_2 = new QLabel(this);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        QTextBrowser* textBrowser = new QTextBrowser(this);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        QFrame* frame = new QFrame(this);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        QHBoxLayout* horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        QSpacerItem* horizontalSpacer = new QSpacerItem(674, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        QPushButton* pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        {
            label->setText("输入指令窗口");
            label_2->setText("输出指令窗口");

            label_4->setText(m_info.name);
            label_7->setText("IP");
            label_8->setText("Port");
            label_3->setText(m_info.ip);
            label_9->setText(QString::fromStdString(std::to_string(int(m_info.port))));
        
            pushButton->setText("连接");
            pushButton_2->setText("运行");
        }

        verticalLayout->addWidget(frame);
    }
}

RunServer::~RunServer()
{
    if (m_client->isOpen())
    {
        m_client->close();
    }
}

void RunServer::connectServer()
{

}

void RunServer::disconnectServer()
{

}

void RunServer::sendCommand()
{

}

void RunServer::receiveMessage()
{

}

OpenServer::OpenServer(const ServerInfo& info, QWidget* widget, QVBoxLayout* verticalLayout, QTabWidget* tabWidget)
    : m_info(info),
    m_verticalLayout(verticalLayout),
    m_widget(widget),
    m_tabWidget(tabWidget)
{
    QPushButton* pushButton = new QPushButton(widget);
    pushButton->setText(m_info.name);
    QObject::connect(pushButton, &QPushButton::clicked, this, &OpenServer::openServer);

    verticalLayout->insertWidget(0, pushButton);
}

OpenServer::OpenServer(const OpenServer& open)
{
    this->m_info = open.m_info;
    this->m_verticalLayout = open.m_verticalLayout;
    this->m_widget = open.m_widget;
    this->m_tabWidget = open.m_tabWidget;
}

OpenServer::~OpenServer()
{
}

void OpenServer::openServer()
{
    RunServer* runServer = new RunServer(m_info);
    m_tabWidget->addTab(runServer, m_info.name);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionserver_list, &QAction::triggered, this, &MainWindow::showServerList);
    QObject::connect(ui->actionServer_options, &QAction::triggered, this, &MainWindow::showServerOpinion);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::manageServer);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::addServer);

    QObject::connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

void MainWindow::flashServerList()
{
    auto list = ui->verticalLayout_6->children();

    for (auto i = list.begin(); i != list.end(); i++)
    {
        if (i + 1 == list.end())
            break;
        if (reinterpret_cast<QWidget*>(*i) == nullptr)
            continue;

        ui->verticalLayout_6->removeWidget(reinterpret_cast<QWidget*>(*i));
        delete* i;
    }

    for (auto i = openServers.begin(); i != openServers.end(); i++)
    {
        delete* i;
    }

    for (auto i = serverInfos.begin(); i != serverInfos.end(); i++)
    {
        openServers.push_back(new OpenServer(i->second, this, ui->verticalLayout_6, ui->tabWidget));
    }
}

void MainWindow::insertServer(const ServerInfo& name)
{
    openServers.push_back(new OpenServer(name, this, ui->verticalLayout_6, ui->tabWidget));
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
    if (SMD.exec() == QDialog::Accepted)
    {
        this->flashServerList();
    }
}

void MainWindow::addServer()
{
    ServerInfo serverInfo;
    AddServerDialog ASD(serverInfo);
    if (ASD.exec() != QDialog::Accepted)
    {
        return;
    }

    if (serverInfos.find(serverInfo.name.toLocal8Bit().data()) != serverInfos.end())
    {
        QMessageBox::warning(this, "警告", "已经有此服务器名字");
        return;
    }

    serverInfos[serverInfo.name.toLocal8Bit().data()] = serverInfo;

    this->insertServer(serverInfo);
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}

