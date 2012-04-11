#include "object.h"
#include <QDeclarativeView>
#include <QGraphicsObject>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QMenu>

Object::Object(QObject *parent) :
    QObject(parent)
{
    view = new QDeclarativeView(QUrl("qrc:/qml/main.qml"));
    view->setResizeMode(QDeclarativeView::SizeViewToRootObject);
    view->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    view->setAttribute(Qt::WA_QuitOnClose);
    view->setWindowOpacity(0.7);

    tray = new QSystemTrayIcon(QIcon(":/qml/images/face-smile-big.png"), this);
    QMenu *trayMenu = new QMenu();
    trayMenu->addAction(QIcon(":/qml/images/application-exit.png"), "Quit", view, SLOT(close()));
    tray->setContextMenu(trayMenu);
    tray->show();

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

    if (view->isVisible() && view->isActiveWindow())
        view->hide();
    else
        showMe();
}

void Object::showMe()
{
    view->show();
    view->activateWindow();
    view->raise();
    view->move(pos);
}
