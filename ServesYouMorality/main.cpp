#include <QCoreApplication>
#include "moralityserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MoralityServer Server;
    Server.StartServer();
    return a.exec();
}
