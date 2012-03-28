#include "object.h"
#include <QDeclarativeView>

Object::Object(QObject *parent) :
    QObject(parent)
{
    tray = new QSystemTrayIcon(QIcon(":/qml/images/face-smile-big.png"), this);
    tray->show();

    view = new QDeclarativeView(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    view->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    view->setWindowOpacity(0.7);
    view->show();

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(toggleMe(QSystemTrayIcon::ActivationReason)));
}

void Object::toggleMe(QSystemTrayIcon::ActivationReason reason)
{
    if (reason != QSystemTrayIcon::Trigger) return;

    if (view->isVisible()) view->hide();
    else view->show();
}
