#include <QCoreApplication>
#include "moralityserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MoralityServer Server;
    Server.StartServer(9966);
    return a.exec();
}
