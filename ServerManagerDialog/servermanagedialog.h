#ifndef SERVERMANAGEDIALOG_H
#define SERVERMANAGEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QLabel>

#include <vector>
#include <unordered_map>
#include <string>

#include "./include/definitions.h"

namespace Ui {
class ServerManageDialog;
}

class Manage : public QObject
{
    Q_OBJECT;

public:
    Manage(ServerInfo info, QFrame* frame, QVBoxLayout* verticalLayout, QLabel* label, QWidget* widget, std::unordered_map<std::string, ServerInfo>* infos, bool& hasChange);

public slots:
    void manageServer();
    void removeServer();

private:
    ServerInfo m_info;
    QFrame* m_frame;
    QVBoxLayout* m_verticalLayout;
    QLabel* m_label;
    QWidget* m_widget;
    std::unordered_map<std::string, ServerInfo>* m_infos;
    bool& m_hasChange;
};

class ServerManageDialog : public QDialog
{
    Q_OBJECT

public:
    ServerManageDialog(std::unordered_map<std::string, ServerInfo>* infos);
    ~ServerManageDialog();

    void addServer();

    void closeEvent(QCloseEvent* event);

protected:
    Manage* addManageServer(QWidget* content, QVBoxLayout* verticalLayout, const ServerInfo& serverInfo);

private:
    Ui::ServerManageDialog *ui;

    std::unordered_map<std::string, ServerInfo>* m_infos;
    std::vector<Manage*> m_infoClasses;
    bool m_hasChange;
};

#endif // SERVERMANAGEDIALOG_H
