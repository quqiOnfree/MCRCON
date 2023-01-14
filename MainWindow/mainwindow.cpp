#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QObject>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QHostInfo>
#include <QFileDialog>

#include <fstream>
#include <ctime>
#include <random>
#include <memory>

#include "./ServerManagerDialog/servermanagedialog.h"
#include "./AddServerDialog/addserverdialog.h"
#include "./Json/Json.h"

RunServer::RunServer(const ServerInfo& info)
    : QWidget(nullptr),
    m_loggin(false)
{
    m_info = info;
    m_client = new QTcpSocket(this);

    std::mt19937 mt(std::time(nullptr));
    m_id = mt();

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

            QObject::connect(pushButton, &QPushButton::clicked, this, &RunServer::connectServer);
            pushButton_2->setEnabled(false);

            m_connectPushButton = pushButton;
            m_sendMessagePushButton = pushButton_2;
            m_textEdit = textEdit;
            m_textBrowser = textBrowser;
        }

        verticalLayout->addWidget(frame);
    }

    QObject::connect(m_client, &QAbstractSocket::errorOccurred, this, &RunServer::error);
    QObject::connect(m_client, &QTcpSocket::connected, this, &RunServer::connectedServer);
    QObject::connect(m_client, &QTcpSocket::readyRead, this, &RunServer::receiveMessage);
    QObject::connect(m_sendMessagePushButton, &QPushButton::clicked, this, &RunServer::sendCommand);
}

RunServer::~RunServer()
{
    if (m_client->isOpen())
    {
        m_client->close();
    }
}

void RunServer::writeFunc(const std::string& command, int rcon)
{
    int size = sizeof(int) * 2 + command.size() + 2;

    RCONDataPackage* packet = (RCONDataPackage*)new unsigned char[size + sizeof(int)] {0};

    packet->size = size;
    packet->requestID = m_id;
    packet->type = rcon;

    std::memcpy(packet->data, command.data(), command.size());

    auto str = std::string(reinterpret_cast<char*>(packet), size + sizeof(int));

    m_client->write(str.data(), str.size());

    delete[](unsigned char*)packet;
}

void RunServer::connectServer()
{
    auto ipAddrIsOK = [](const QString & ip)
    {
        if (ip.isEmpty())
        {
            return false;
        }

        QStringList list = ip.split('.');
        if (list.size() != 4)
        {
            return false;
        }

        for (const auto& num : list)
        {
            bool ok = false;
            int temp = num.toInt(&ok);
            if (!ok || temp < 0 || temp > 255)
            {
                return false;
            }
        }

        return true;
    };

    m_connectPushButton->setEnabled(false);
    //m_client->setProxy(QNetworkProxy::NoProxy);
    m_client->connectToHost(m_info.ip, m_info.port);
    if (!m_client->waitForConnected(5000))
    {
        m_client->errorOccurred(QAbstractSocket::SocketError());
        m_client->disconnectFromHost();
    }
}

void RunServer::disconnectServer()
{
    
}

void RunServer::sendCommand()
{
    static bool firstMessage = true;

    if (!firstMessage)
    {
        auto first = m_stringQueue.front();
        m_stringQueue.pop();
        writeFunc(first.toStdString(), 2);
        if (m_stringQueue.empty())
        {
            firstMessage = true;
        }
        return;
    }

    m_textBrowser->clear();

    if (!m_loggin)
    {
        writeFunc(m_info.passWord.toStdString(), 3);
        return;
    }

    auto text = m_textEdit->toPlainText().split("\n");

    m_sendMessagePushButton->setEnabled(false);

    for (auto i = text.begin(); i != text.end(); i++)
    {
        if (i->size())
            m_stringQueue.push(*i);
    }

    if (firstMessage)
    {
        auto first = m_stringQueue.front();
        m_stringQueue.pop();
        writeFunc(first.toStdString(), 2);
        firstMessage = false;
        if (m_stringQueue.empty())
        {
            firstMessage = true;
        }
        return;
    }
}

void RunServer::receiveMessage()
{
    auto readFunc = [this](const std::string& data, bool* get, int* type)
    {
        RCONDataPackage* packet = (RCONDataPackage*)new unsigned char[data.size() + 1] {0};

        std::memcpy(packet, data.data(), data.size());

        if (packet->requestID == m_id)
        {
            *get = true;
        }
        else
        {
            *get = false;
        }

        *type = packet->type;

        std::string reString(reinterpret_cast<char*>(packet->data), data.size() - sizeof(int) * 3 - 2);
        delete[] reinterpret_cast<unsigned char*>(packet);

        return reString;
    };

    auto buffer = m_client->readAll();
    bool a;
    int b;

    m_sendMessagePushButton->setEnabled(true);

    if (m_loggin)
    {
        std::string get = readFunc(std::string(buffer.data(), buffer.size()), &a, &b);
        if (get.empty() && a)
        {
            m_textBrowser->append("true");
        }
        else
        {
            m_textBrowser->append(get.data());
        }
    }
    else
    {
        readFunc(std::string(buffer.data(), buffer.size()), &a, &b);
        if (a)
        {
            m_loggin = true;
            QMessageBox::information(this, "信息", "连接RCON成功");
        }
        else
        {
            QMessageBox::warning(this, "警告", "密码错误！");
        }
    }

    if (!m_stringQueue.empty())
    {
        RunServer::sendCommand();
    }
   
}

void RunServer::error(QAbstractSocket::SocketError)
{
    m_client->disconnectFromHost();
    QMessageBox::warning(this, "警告", "无法连接到服务器：" + m_client->errorString());
    m_connectPushButton->setEnabled(true);
    m_sendMessagePushButton->setEnabled(false);
}

void RunServer::connectedServer()
{
    m_sendMessagePushButton->setEnabled(true);
    RunServer::sendCommand();
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

    QObject::connect(ui->actionsave_configure, &QAction::triggered, this, &MainWindow::saveConfig);
    QObject::connect(ui->actionopen_configure, &QAction::triggered, this, &MainWindow::readConfig);

    QObject::connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->tab_2));
}

void MainWindow::flashServerList()
{
    size_t size = ui->verticalLayout_6->layout()->count();

    for (size_t i = 0; i < size - 1; i++)
    {
        auto item = ui->verticalLayout_6->layout()->itemAt(i);
        auto itemWidget = item->widget();
        ui->verticalLayout_6->removeItem(item);
        delete itemWidget;
    }

    for (auto i = 0; i < !openServers.empty();)
    {
        delete openServers[i];
        openServers.erase(openServers.begin());
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

void MainWindow::saveConfig()
{
    auto str = QFileDialog::getSaveFileUrl(this, "保存配置文件", QUrl("./"), "json files (*.json)").toString();
    if (str.isEmpty())
        return;
    std::ofstream outfile(str.toLocal8Bit().data() + 8);

    qjson::JObject json(qjson::JValueType::JList);

    for (auto i = serverInfos.begin(); i != serverInfos.end(); i++)
    {
        qjson::JObject locJson;
        locJson["name"] = i->second.name.toLocal8Bit().data();
        locJson["ip"] = i->second.ip.toLocal8Bit().data();
        locJson["port"] = int(i->second.port);
        locJson["password"] = i->second.passWord.toLocal8Bit().data();

        json.push_back(locJson);
    }

    outfile << qjson::JWriter::fastFormatWrite(json);

    QMessageBox::information(this, "信息", "保存成功！");
}

void MainWindow::readConfig()
{
    auto str = QFileDialog::getOpenFileUrl(this, "打开配置文件", QUrl("./"), "json files (*.json)").toString();
    if (str.isEmpty())
        return;
    std::ifstream infile(str.toLocal8Bit().data() + 8);

    infile.seekg(0, std::ios_base::end);
    size_t size = infile.tellg();
    infile.seekg(0, std::ios_base::beg);
    char* buffer = new char[size + 1] {0};
    infile.read(buffer, size);
    infile.close();

    try
    {
        std::unordered_map<std::string, ServerInfo> locServerInfos;
        qjson::JObject json = qjson::JParser::fastParse(buffer);

        qjson::list_t& list = json.getList();

        for (auto i = list.begin(); i != list.end(); i++)
        {
            ServerInfo& info = locServerInfos[(*i)["name"]];
            info.name = QString::fromLocal8Bit((*i)["name"].getString().c_str());
            info.ip = QString::fromLocal8Bit((*i)["ip"].getString().c_str());
            info.port = static_cast<unsigned short>(int((*i)["port"]));
            info.passWord = QString::fromLocal8Bit((*i)["password"].getString().c_str());
        }

        serverInfos = std::move(locServerInfos);
        this->flashServerList();
        QMessageBox::information(this, "信息", "读取成功！");
    }
    catch (const std::exception&)
    {
        QMessageBox::warning(this, "警告", "读取配置文件失败！");
    }

    delete[] buffer;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    auto get = QMessageBox::question(this, "询问", "是否保存配置文件？", "是", "否");
    if (get == 0)
    {
        this->saveConfig();
    }
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
    for (auto i = 0; !openServers.empty();)
    {
        delete openServers[i];
        openServers.erase(openServers.begin());
    }

    delete ui;
}

