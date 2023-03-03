#include "CCObjectPrivate_p.h"
#include "Frameless_p.h"

#include <QWindow>
#include <QMouseEvent>
#include <QRect>
#include <QDebug>

#define PADDING 4

class FramelessPrivate : public CCObjectPrivate
{
    CC_DECLARE_PUBLIC(Frameless)
public:
    FramelessPrivate(QWindow *win, Frameless *qq)
        : CCObjectPrivate(qq)
        , self(win)
        , dir(Frameless::NONE)
        , leftButtonPress(false)
    {}

    void calcResizeDirection(const QPoint &cursorGlobalPoint);
    void updateWindowResizeGeometry(const QPoint &pos);

private:
    QWindow *self;
    QPoint point;
    QPoint dragPosition;
    Frameless::Direction dir;
    bool leftButtonPress;
};

Frameless::Frameless(QWindow *self)
    : CCObject(*new FramelessPrivate(self, this))
{
}

bool Frameless::canResize()
{
    return true;
}

void Frameless::focusInEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
    CC_D(Frameless);

    if (!canResize())
        return;

    d->calcResizeDirection(d->self->cursor().pos());
}

void FramelessPrivate::calcResizeDirection(const QPoint &cursorGlobalPoint)
{
    QRect rect = self->frameGeometry();
    QPoint tl = rect.topLeft();
    QPoint rb = rect.bottomRight();

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();
    Qt::CursorShape cursorShape = Qt::ArrowCursor;

    if (tl.x() + PADDING >= x
            && tl.x() <= x
            && tl.y() + PADDING >= y
            && tl.y() <= y) {
        dir = Frameless::LEFTTOP;
        cursorShape = Qt::SizeFDiagCursor;
    } else if (x >= rb.x() - PADDING
              && x <= rb.x()
              && y >= rb.y() - PADDING
              && y <= rb.y()) {
        dir = Frameless::RIGHTBOTTOM;
        cursorShape = Qt::SizeFDiagCursor;
    } else if (x <= tl.x() + PADDING
              && x >= tl.x()
              && y >= rb.y() - PADDING
              && y <= rb.y()) {
        dir = Frameless::LEFTBOTTOM;
        cursorShape = Qt::SizeBDiagCursor;
    } else if (x <= rb.x()
              && x >= rb.x() - PADDING
              && y >= tl.y()
              && y <= tl.y() + PADDING) {
        dir = Frameless::RIGHTTOP;
        cursorShape = Qt::SizeBDiagCursor;
    } else if (x <= tl.x() + PADDING && x >= tl.x()) {
        dir = Frameless::LEFT;
        cursorShape = Qt::SizeHorCursor;
    } else if ( x <= rb.x() && x >= rb.x() - PADDING) {
        dir = Frameless::RIGHT;
        cursorShape = Qt::SizeHorCursor;
    } else if (y >= tl.y() && y <= tl.y() + PADDING) {
        dir = Frameless::UP;
        cursorShape = Qt::SizeVerCursor;
    } else if (y <= rb.y() && y >= rb.y() - PADDING) {
        dir = Frameless::DOWN;
        cursorShape = Qt::SizeVerCursor;
    } else {
        dir = Frameless::NONE;
        cursorShape = Qt::ArrowCursor;
    }

    self->setCursor(QCursor(cursorShape));
}

void FramelessPrivate::updateWindowResizeGeometry(const QPoint &pos)
{
    QRect rMove = self->frameGeometry();

    QPoint tl = rMove.topLeft();
    QPoint rb = rMove.bottomRight();

    switch (dir) {
    case Frameless::LEFT: {
        if (rb.x() - pos.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(pos.x());
        }
    }
        break;
    case Frameless::RIGHT: {
        if (pos.x() - tl.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(tl.x());
            rMove.setWidth(pos.x() - tl.x());
        }
    }
        break;

    case Frameless::UP: {
        if (rb.y() - pos.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(pos.y());

        }
    }
        break;

    case Frameless::DOWN: {
        if (pos.y() - tl.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(tl.y());
            rMove.setHeight(pos.y() - tl.y());
        }
    }
        break;

    case Frameless::LEFTTOP: {
        if (rb.x() - pos.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(pos.x());
        }

        if (rb.y() - pos.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(pos.y());
        }
    }
        break;

    case Frameless::RIGHTTOP: {
        if (pos.x() - tl.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(tl.x());
            rMove.setWidth(pos.x() - tl.x());
        }

        if (rb.y() - pos.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(pos.y());
        }
    }
        break;

    case Frameless::LEFTBOTTOM: {
        if (rb.x() - pos.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(pos.x());
        }

        if (pos.y() - tl.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(tl.y());
            rMove.setHeight(pos.y() - tl.y());
        }
    }
        break;

    case Frameless::RIGHTBOTTOM: {
        if (pos.x() - tl.x() <= self->minimumWidth()) {
            rMove.setX(tl.x());
        } else {
            rMove.setX(tl.x());
            rMove.setWidth(pos.x() - tl.x());
        }

        if (pos.y() - tl.y() <= self->minimumHeight()) {
            rMove.setY(tl.y());
        } else {
            rMove.setY(tl.y());
            rMove.setHeight(pos.y() - tl.y());
        }
    }
        break;

    default:
        break;
    }

    self->setGeometry(rMove);
}

void Frameless::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton: {
        CC_D(Frameless);

        d->point = event->pos();
        if (d->dir == Frameless::NONE) {
            if (canWindowMove()) {
                d->dragPosition = event->globalPos() - d->self->frameGeometry().topLeft();
                d->self->setCursor(QCursor(Qt::SizeAllCursor));
                d->leftButtonPress = true;
            }
        }

        break;
    }
    default:
        break;
    }

    event->accept();
    return;
}

void Frameless::mouseMoveEvent(QMouseEvent*event)
{
    CC_D(Frameless);

    QPoint gloPoint = event->globalPos();
    if (event->buttons() & Qt::LeftButton) {
        if ((d->dir != NONE) && canResize()) {
            d->updateWindowResizeGeometry(gloPoint);
        } else {
            if (d->self->windowState() == Qt::WindowMaximized) {
                d->self->showNormal();

                double xRatio = event->globalX() * 1.0 / d->self->width();
                double yRatio = event->globalY() * 1.0 / d->self->height();
                int widgetX = d->self->width() * xRatio;
                int widgetY = d->self->height() * yRatio;

                d->self->setPosition(event->globalX() - widgetX, event->globalY() - widgetY);
                updateWindowMargins(d->self->windowState());

                d->dragPosition = event->globalPos() - d->self->frameGeometry().topLeft();
                return;
            }

            const QPoint &pos = event->globalPos() - d->dragPosition;
            d->self->setX(pos.x());
            d->self->setY(pos.y());

            event->accept();
        }
    } else {
        d->calcResizeDirection(gloPoint);
    }
}

void Frameless::mouseReleaseEvent(QMouseEvent *)
{
    CC_D(Frameless);

    d->self->setCursor(QCursor(Qt::ArrowCursor));
    d->leftButtonPress = false;
    d->dir = NONE;
}

void Frameless::leaveEvent(QEvent *)
{
    CC_D(Frameless);

    if (d->leftButtonPress)
        return;

    d->dir = NONE;
    d->self->setCursor(QCursor(Qt::ArrowCursor));
}
