#include "CCQuick_plugin.h"

#include "CCQuickFramelessWindow.h"

#include <qqml.h>

void CCQuickPlugin::registerTypes(const char *uri)
{
    // @uri quick.cc.qmlcomponents
    qmlRegisterType<CCQuickFramelessWindow>(uri, 1, 0, "CCWindow");
}

