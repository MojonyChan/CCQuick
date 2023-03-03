#ifndef CCOBJECT_P_H
#define CCOBJECT_P_H

#define CC_DECLARE_PRIVATE(Class) Q_DECLARE_PRIVATE_D(qGetPtrHelper(c_c_ptr),Class)
#define CC_DECLARE_PUBLIC(Class) Q_DECLARE_PUBLIC(Class)
#define CC_D(Class) Q_D(Class)
#define CC_Q(Class) Q_Q(Class)
#define CC_DC(Class) Q_D(const Class)
#define CC_QC(Class) Q_Q(const Class)
#define CC_PRIVATE_SLOT(Func) Q_PRIVATE_SLOT(d_func(), Func)

#include <QScopedPointer>

class CCObjectPrivate;
class CCObject
{
protected:
    CCObject(CCObject *parent = nullptr);
    CCObject(CCObjectPrivate &dd, CCObject *parent = nullptr);

    virtual ~CCObject();

    QScopedPointer<CCObjectPrivate> c_c_ptr;

    Q_DISABLE_COPY(CCObject)
    CC_DECLARE_PRIVATE(CCObject)
};

#endif // CCOBJECT_P_H
