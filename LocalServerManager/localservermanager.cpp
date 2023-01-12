#include "localservermanager.h"
#include "ui_localservermanager.h"

#include <QMessageBox>

LocalServerManager::LocalServerManager(ServerInfo& info)
	: ui(new Ui::LocalServerManager), m_info(info)
{

}

void LocalServerManager::enter()
{
    if (!ui->lineEdit->text().size()
        || !ui->lineEdit_2->text().size()
        || !ui->lineEdit_4->text().size())
    {
        QMessageBox::warning(this, "警告", "至少有一个是空的");
        return;
    }

    m_info.name = ui->lineEdit->text();
    m_info.ip = ui->lineEdit_2->text();
    m_info.port = static_cast<unsigned short>(ui->spinBox->value());
    m_info.passWord = ui->lineEdit_4->text();

    this->accept();
}

LocalServerManager::~LocalServerManager()
{
    delete ui;
}