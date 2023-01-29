#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QtWidgets/QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTextBrowser>

#include <vector>
#include <unordered_map>
#include <queue>

#include "./Definition/definitions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class RunServer : public QWidget
{
    Q_OBJECT

public:
    RunServer(const ServerInfo& info);
    ~RunServer();

    void writeFunc(const std::string& command, int rcon);

public slots:
    void connectServer();
    void disconnectServer();
    void sendCommand();
    void receiveMessage();
    void error(QAbstractSocket::SocketError);
    void connectedServer();

private:
    QTcpSocket*         m_client;
    ServerInfo          m_info;
    int                 m_id;
    bool                m_loggin;
    std::queue<QString> m_stringQueue;

    QPushButton*        m_connectPushButton;
    QPushButton*        m_sendMessagePushButton;
    QTextEdit*          m_textEdit;
    QTextBrowser*       m_textBrowser;
};

class OpenServer : public QObject
{
    Q_OBJECT

public:
    OpenServer(const ServerInfo& info, QWidget* widget, QVBoxLayout* verticalLayout, QTabWidget* tabWidget);
    OpenServer(const OpenServer& open);
    ~OpenServer();

public slots:
    void openServer();

private:
    ServerInfo      m_info;

    QVBoxLayout*    m_verticalLayout;
    QWidget*        m_widget;
    QTabWidget*     m_tabWidget;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void flashServerList();
    void insertServer(const ServerInfo& name);
    void saveConfig();
    void readConfig();

    void closeEvent(QCloseEvent* event);

public slots:
    void showServerList();
    void showServerOpinion();
    void manageServer();
    void addServer();

    void closeTab(int index);

private:
    Ui::MainWindow *ui;

    std::unordered_map<std::string, ServerInfo> serverInfos;
    std::vector<OpenServer*>                    openServers;
};
#endif // MAINWINDOW_H
