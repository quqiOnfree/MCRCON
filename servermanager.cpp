#include "servermanager.h"
#include "ui_servermanager.h"

ServerManager::ServerManager(std::vector<ServerInfo>* infos) :
    ui(new Ui::ServerManager)
{
    ui->setupUi(this);
}

ServerManager::~ServerManager()
{
    delete ui;
}
