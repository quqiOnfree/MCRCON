#ifndef LOCALSERVERMANAGER_H
#define LOCALSERVERMANAGER_H

#include <QDialog>

#include "./include/definitions.h"

namespace Ui {
	class LocalServerManager;
}

class LocalServerManager : public QDialog
{
	Q_OBJECT

public:
	LocalServerManager(ServerInfo& info);
	~LocalServerManager();

	void enter();

private:
	Ui::LocalServerManager* ui;

	ServerInfo& m_info;
};

#endif // !LOCALSERVERMANAGER_H
