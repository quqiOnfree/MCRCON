﻿#ifndef ADDSERVERDIALOG_H
#define ADDSERVERDIALOG_H

#include <QDialog>
#include <vector>

#include "./include/definitions.h"

namespace Ui {
class AddServerDialog;
}

class AddServerDialog : public QDialog
{
    Q_OBJECT

public:
    AddServerDialog(ServerInfo& info);
    ~AddServerDialog();

public slots:
    void enter();

private:
    Ui::AddServerDialog *ui;

    ServerInfo& m_info;
};

#endif // ADDSERVERDIALOG_H
