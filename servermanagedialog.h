#ifndef SERVERMANAGEDIALOG_H
#define SERVERMANAGEDIALOG_H

#include <QDialog>
#include <vector>

#include "definitions.h"

namespace Ui {
class ServerManageDialog;
}

class ServerManageDialog : public QDialog
{
    Q_OBJECT

public:
    ServerManageDialog(std::vector<ServerInfo>* infos);
    ~ServerManageDialog();

    void addServer();

private:
    Ui::ServerManageDialog *ui;

    std::vector<ServerInfo>* m_infos;
};

#endif // SERVERMANAGEDIALOG_H
