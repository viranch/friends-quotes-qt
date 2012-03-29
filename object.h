#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QPoint>

class QDeclarativeView;

class Object : public QObject
{
    Q_OBJECT
    
public:
    Object(QObject *parent = 0);

private slots:
    void toggleMe(QSystemTrayIcon::ActivationReason reason = QSystemTrayIcon::Trigger);
    void showMe();
    
private:
    QSystemTrayIcon *tray;
    QDeclarativeView *view;
    QPoint pos;

};

#endif // OBJECT_H
