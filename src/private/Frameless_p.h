#ifndef FRAMELESS_H
#define FRAMELESS_H

#include <QEvent>
#include <QMargins>
#include <QPoint>
#include <QRect>
#include <QString>

#include "CCObject_p.h"

class QWindow;
class QEvent;
class QMouseEvent;
class QFocusEvent;
class FramelessPrivate;
class Frameless : public CCObject
{
    CC_DECLARE_PRIVATE(Frameless)

public:
    Frameless(QWindow *self);

protected:
    enum Direction {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
        LEFTTOP,
        LEFTBOTTOM,
        RIGHTBOTTOM,
        RIGHTTOP,
        NONE
    };

    virtual bool canWindowMove() = 0;
    virtual bool canResize();
    virtual bool updateWindowMargins(Qt::WindowState state) = 0;

    void focusInEvent(QFocusEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e) ;
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *event);
};

#endif // FRAMELESS_H
