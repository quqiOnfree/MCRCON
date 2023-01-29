#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>

struct ServerInfo
{
    QString name;
    QString ip;
    unsigned short port;
    QString passWord;
};

struct RCONDataPackage
{
    int size;
    int requestID;
    int type;
    unsigned char data[1];
};

#endif // DEFINITIONS_H
