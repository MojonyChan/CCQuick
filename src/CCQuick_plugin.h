#ifndef CCQUICK_PLUGIN_H
#define CCQUICK_PLUGIN_H

#include <QQmlExtensionPlugin>

class CCQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // CCQUICK_PLUGIN_H
