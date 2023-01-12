#include "servermanagedialog.h"
#include "ui_servermanagedialog.h"

#include <QMessageBox>
#include <QObject>
#include <QFrame>

#include "./AddServerDialog/addserverdialog.h"
#include "./LocalServerManager/localservermanager.h"

Manage::Manage(ServerInfo info, QFrame* frame, QVBoxLayout* verticalLayout, QLabel* label)
{
    m_info = info;
    m_frame = frame;
    m_verticalLayout = verticalLayout;
    m_label = label;
}

void Manage::manageServer()
{
    ServerInfo serverInfo;
    LocalServerManager LSM(serverInfo);
    if (LSM.exec() != QDialog::Accepted)
    {
        return;
    }


}

void Manage::removeServer()
{

}

ServerManageDialog::ServerManageDialog(std::unordered_map<std::string, ServerInfo>* infos) :
    ui(new Ui::ServerManageDialog), m_infos(infos), m_hasChange(false)
{
    ui->setupUi(this);

    for (auto i = m_infos->begin(); i != m_infos->end(); i++)
    {
        this->addManageServer(ui->scrollAreaWidgetContents, ui->verticalLayout, i->second);
    }

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

    if (m_infos->find(serverInfo.name.toLocal8Bit().data()) != m_infos->end())
    {
        QMessageBox::warning(this, "警告", "已经有此服务器名字");
        return;
    }

    (*m_infos)[serverInfo.name.toLocal8Bit().data()] = serverInfo;

    this->addManageServer(ui->scrollAreaWidgetContents, ui->verticalLayout, serverInfo);
    m_hasChange = true;
}

void ServerManageDialog::addManageServer(QWidget* content, QVBoxLayout* verticalLayout, const ServerInfo& serverInfo)
{
    QFrame* frame = new QFrame(content);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(frame);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QLabel* label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));
    label->setText(serverInfo.name);

    horizontalLayout->addWidget(label);

    QSpacerItem* horizontalSpacer = new QSpacerItem(250, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    QPushButton* pushButton_2 = new QPushButton(frame);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setText("编辑");

    horizontalLayout->addWidget(pushButton_2);

    QPushButton* pushButton = new QPushButton(frame);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setText("删除");

    horizontalLayout->addWidget(pushButton);

    verticalLayout->insertWidget(0, frame);
}

void ServerManageDialog::closeEvent(QCloseEvent* event)
{
    if (m_hasChange)
    {
        this->accept();
    }
    else
    {
        this->reject();
    }
}

ServerManageDialog::~ServerManageDialog()
{
    delete ui;
}
