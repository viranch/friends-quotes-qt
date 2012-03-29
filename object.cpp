#include "object.h"
#include <QDeclarativeView>
#include <QGraphicsObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>

Object::Object(QObject *parent) :
    QObject(parent)
{
    tray = new QSystemTrayIcon(QIcon(":/qml/images/face-smile-big.png"), this);
    tray->show();

    view = new QDeclarativeView(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    view->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    view->setWindowOpacity(0.7);

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(toggleMe(QSystemTrayIcon::ActivationReason)));
    connect(qobject_cast<QObject*>(view->rootObject()), SIGNAL(updated()), this, SLOT(showMe()));

    QRect screenSize = QApplication::desktop()->screenGeometry();
    pos.setX(screenSize.width() - 500);
    pos.setY(screenSize.height() - 280);

    toggleMe();
}

void Object::toggleMe(QSystemTrayIcon::ActivationReason reason)
{
    if (reason != QSystemTrayIcon::Trigger) return;

    if (view->isVisible()) view->hide();
    else {
        view->show();
        view->move(pos);
    }
}

void Object::showMe()
{
    view->hide();
    QTimer::singleShot(500, this, SLOT(toggleMe()));
}
