#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QTextStream>
#include <QtWidgets/QVBoxLayout>

#include <vector>
#include <unordered_map>

#include "./include/definitions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class RunServer : public QWidget
{
    Q_OBJECT

public:
    RunServer(const ServerInfo& info);
    ~RunServer();

public slots:
    void connectServer();
    void disconnectServer();
    void sendCommand();
    void receiveMessage();

private:
    QTcpSocket* m_client;
    ServerInfo  m_info;
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
