#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QObject>
#include <QString>

class ServerInfo : public QDialog
{
    Q_OBJECT
public:
    explicit ServerInfo();

signals:
    void dServer(QString serverip, int myport);

public slots:
    void ok_pushed();
    void cancel_pushed();

private:
    QGridLayout *theLayout;
    QLineEdit *ServerAddress, *ServerPort;
    QLabel *SLabel;
    QLabel *PLabel;
    QPushButton *P_OK;
    QPushButton *P_CANCEL;
};

#endif // SERVERINFO_H
