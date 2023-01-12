#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "definitions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showServerList();
    void showServerOpinion();
    void manageServer();
    void addServer();

private:
    Ui::MainWindow *ui;

    std::vector<ServerInfo> serverInfos;
};
#endif // MAINWINDOW_H
