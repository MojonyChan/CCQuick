#ifndef CCQUICKFRAMELESSWINDOW_H
#define CCQUICKFRAMELESSWINDOW_H

#include <QtQuick/private/qquickwindowmodule_p.h>

#include "private/Frameless_p.h"

class CCQuickFramelessWindowPrivate;
class CCQuickFramelessWindow : public QQuickWindowQmlImpl, public Frameless
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(CCQuickFramelessWindow)
    CC_DECLARE_PRIVATE(CCQuickFramelessWindow)

    Q_PROPERTY(QQuickItem *titleBar READ titleBar WRITE setTitleBar NOTIFY titleBarChanged FINAL)
    Q_PROPERTY(QQuickItem *statusBar READ statusBar WRITE setStatusBar NOTIFY statusBarChanged FINAL)
    Q_PROPERTY(QQuickItem *contentItem READ contentItem CONSTANT)
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
//    Q_PRIVATE_PROPERTY(CCQuickFramelessWindow::d_func(), QQmlListProperty<QObject> contentData READ contentData FINAL)

public:
    explicit CCQuickFramelessWindow(QWindow *parent = nullptr);
    ~CCQuickFramelessWindow() override;

    QQuickItem *titleBar() const;
    void setTitleBar(QQuickItem *newTitleBar);

    QQuickItem *statusBar() const;
    void setStatusBar(QQuickItem *newStatusBar);

    QQuickItem *contentItem() const;

    QQuickItem *background() const;
    void setBackground(QQuickItem *newBackgrounbackground);

Q_SIGNALS:
    void titleBarChanged();
    void statusBarChanged();
    void contentItemChanged();
    void backgroundChanged();

protected:
    bool canWindowMove() override;
    bool updateWindowMargins(Qt::WindowState state) override;
};

#endif // CCQUICKFRAMELESSWINDOW_H
