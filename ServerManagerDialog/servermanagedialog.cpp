#include "servermanagedialog.h"
#include "ui_servermanagedialog.h"

#include <QMessageBox>
#include <QObject>

#include "./AddServerDialog/addserverdialog.h"

ServerManageDialog::ServerManageDialog(std::vector<ServerInfo>* infos) :
    ui(new Ui::ServerManageDialog)
{
    ui->setupUi(this);
    m_infos = infos;

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ServerManageDialog::addServer);
}

void ServerManageDialog::addServer()
{
    ServerInfo serverInfo;
    AddServerDialog ASD(serverInfo);
    if (ASD.exec() != QDialog::Accepted)
    {
        return;
    }

    QMessageBox::information(this, "信息", "OK");
}

ServerManageDialog::~ServerManageDialog()
{
    delete ui;
}
