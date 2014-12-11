#ifndef SERVINFO_H
#define SERVINFO_H

#include <QMainWindow>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class servinfo : public QMainWindow
{
    Q_OBJECT
public:
    explicit servinfo(QWidget *parent = 0);

signals:
    void dServer(QString serverip, int myport);

public slots:
    void OK_PUSHED();
    void CANCEL_PUSHED();

private:
    QGridLayout *theLayout;
    QLineEdit *ServerAddress, *ServerPort;
    QLabel *SLabel;
    QLabel *PLabel;
    QPushButton *P_OK;
    QPushButton *P_CANCEL;
};

#endif // SERVINFO_H
