#include "CCQuickFramelessWindow.h"
#include "private/CCObjectPrivate_p.h"

#include <private/qquickitem_p.h>
#include <private/qquickitemchangelistener_p.h>

static const QQuickItemPrivate::ChangeTypes ItemChanges = QQuickItemPrivate::Visibility
        | QQuickItemPrivate::Geometry | QQuickItemPrivate::ImplicitWidth | QQuickItemPrivate::ImplicitHeight;

class CCQuickFramelessWindowPrivate : public CCObjectPrivate, public QQuickItemChangeListener
{
    CC_DECLARE_PUBLIC(CCQuickFramelessWindow)
public:
    CCQuickFramelessWindowPrivate(CCQuickFramelessWindow *qq)
        : CCObjectPrivate(qq)
        , titleBar(nullptr)
        , statusBar(nullptr)
        , contentItem(nullptr)
        , background(nullptr)
    {}

    void init();
private:
    QQmlListProperty<QObject> contentData;
    QQuickItem *titleBar = nullptr;
    QQuickItem *statusBar = nullptr;
    QQuickItem *contentItem = nullptr;
    QQuickItem *background = nullptr;
};

void CCQuickFramelessWindowPrivate::init()
{
    CC_Q(CCQuickFramelessWindow);

    contentItem = new QQuickItem;
    QQml_setParent_noEvent(contentItem, q->QQuickWindow::contentItem());
    QQmlEngine::setObjectOwnership(contentItem, QQmlEngine::CppOwnership);
    QQuickItemPrivate *contentItemPrivate = QQuickItemPrivate::get(contentItem);
    contentItemPrivate->window = q;
    contentItemPrivate->windowRefCount = 1;
    contentItemPrivate->flags |= QQuickItem::ItemIsFocusScope;
    contentItem->setSize(q->size());
}

CCQuickFramelessWindow::CCQuickFramelessWindow(QWindow *parent)
    : QQuickWindowQmlImpl(parent)
    , Frameless(this)
{
    setFlags(flags() | Qt::FramelessWindowHint
             | static_cast<Qt::WindowFlags>(Qt::WA_TranslucentBackground));
}

CCQuickFramelessWindow::~CCQuickFramelessWindow()
{
}

bool CCQuickFramelessWindow::canWindowMove()
{
    return true;
}

bool CCQuickFramelessWindow::updateWindowMargins(Qt::WindowState state)
{
    return true;
}

QQuickItem *CCQuickFramelessWindow::titleBar() const
{
    CC_DC(CCQuickFramelessWindow);
    return d->titleBar;
}

void CCQuickFramelessWindow::setTitleBar(QQuickItem *newTitleBar)
{
    CC_D(CCQuickFramelessWindow);
    if (d->titleBar == newTitleBar)
        return;

    if (d->titleBar) {
        QQuickItemPrivate::get(d->titleBar)->removeItemChangeListener(d, ItemChanges);
        d->titleBar->setParentItem(nullptr);
    }

    d->titleBar = newTitleBar;
    if (newTitleBar) {
//        newTitleBar->setParentItem(contentItem());
        QQuickItemPrivate *p = QQuickItemPrivate::get(newTitleBar);
        p->addItemChangeListener(d, ItemChanges);
        if (qFuzzyIsNull(newTitleBar->z()))
            newTitleBar->setZ(1);
    }

//    if (isComponentComplete())
//        d->relayout();

    Q_EMIT titleBarChanged();
}

QQuickItem *CCQuickFramelessWindow::statusBar() const
{
    CC_DC(CCQuickFramelessWindow);
    return d->statusBar;
}

void CCQuickFramelessWindow::setStatusBar(QQuickItem *newStatusBar)
{
    CC_D(CCQuickFramelessWindow);
    if (d->statusBar == newStatusBar)
        return;

    if (d->statusBar) {
        QQuickItemPrivate::get(d->statusBar)->removeItemChangeListener(d, ItemChanges);
        d->statusBar->setParentItem(nullptr);
    }

    d->statusBar = newStatusBar;
    if (newStatusBar) {
        newStatusBar->setParentItem(contentItem());
        QQuickItemPrivate *p = QQuickItemPrivate::get(newStatusBar);
        p->addItemChangeListener(d, ItemChanges);
        if (qFuzzyIsNull(newStatusBar->z()))
            newStatusBar->setZ(1);
    }

    Q_EMIT statusBarChanged();
}

QQuickItem *CCQuickFramelessWindow::contentItem() const
{
    CC_DC(CCQuickFramelessWindow);
    return d->contentItem;
}

QQuickItem *CCQuickFramelessWindow::background() const
{
    return nullptr;
}

void CCQuickFramelessWindow::setBackground(QQuickItem *background)
{
//    CC_D(CCQuickFramelessWindow);
//    if (d->background == background)
//        return;

//    if (!d->background.isExecuting())
//        d->cancelBackground();

//    d->background->setParentItem(nullptr);
//    d->background->setVisible(false);
//    d->background = background;
//    if (background) {
//        background->setParentItem(QQuickWindow::contentItem());
//        if (qFuzzyIsNull(background->z()))
//            background->setZ(-1);
////        if (isComponentComplete())
////            d->relayout();
//    }

//    Q_EMI backgroundChanged();
}
