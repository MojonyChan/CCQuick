#ifndef CCOBJECTPRIVATE_P_H
#define CCOBJECTPRIVATE_P_H

#include <qglobal.h>

class CCObject;
class CCObjectPrivate
{
public:
    virtual ~CCObjectPrivate();

protected:
    CCObjectPrivate(CCObject *qq);

    CCObject *q_ptr;

    Q_DECLARE_PUBLIC(CCObject)
};

#endif // CCOBJECTPRIVATE_P_H
