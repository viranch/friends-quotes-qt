#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QSystemTrayIcon>

class QDeclarativeView;

class Object : public QObject
{
    Q_OBJECT
    
public:
    Object(QObject *parent = 0);

private slots:
    void toggleMe(QSystemTrayIcon::ActivationReason);
    
private:
    QSystemTrayIcon *tray;
    QDeclarativeView *view;

};

#endif // OBJECT_H
