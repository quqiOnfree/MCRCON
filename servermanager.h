#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QWidget>
#include <QDialog>
#include <vector>

#include "definitions.h"

namespace Ui {
class ServerManager;
}

class ServerManager : public QWidget
{
    Q_OBJECT

public:
    ServerManager(std::vector<ServerInfo>* infos);
    ~ServerManager();

private:
    Ui::ServerManager *ui;

    std::vector<ServerInfo>* m_infos;
};

#endif // SERVERMANAGER_H
