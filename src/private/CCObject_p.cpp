#include "CCObject_p.h"
#include "CCObjectPrivate_p.h"

CCObjectPrivate::CCObjectPrivate(CCObject *qq)
    : q_ptr(qq)
{

}

CCObjectPrivate::~CCObjectPrivate()
{

}

CCObject::CCObject(CCObject *)
{

}

CCObject::CCObject(CCObjectPrivate &dd, CCObject *)
    : c_c_ptr(&dd)
{

}

CCObject::~CCObject()
{

}
