#include "shortkeymanager.h"

TShortKeyManager *TShortKeyManager::mInstance = NULL;

TShortKeyManager *TShortKeyManager::instance(QObject *parent)
{
    if(mInstance==NULL)
        mInstance = new TShortKeyManager(parent);
    return mInstance;
}

void TShortKeyManager::deleteInstance()
{
    if(mInstance)
    {
        delete mInstance;
        mInstance = nullptr;
    }
}

TShortKeyManager::TShortKeyManager(QObject *parent) :
    QObject(parent)
{

}

TShortKeyManager::~TShortKeyManager()
{
    for(auto v : mActionMap.values())
    {
        delete v;
    }
    mActionMap.clear();
}

void TShortKeyManager::registerActions(QString className, TActionList actionList)
{
    if(!className.isEmpty())
    {
        for(auto a : actionList)
        {
            registerAction(className, a);
        }
    }
}

void TShortKeyManager::registerAction(QString className, QAction *action)
{
    TActionMap::iterator i = mActionMap.find(className);
    if(i != mActionMap.end())
    {
        i.value()->append(action);
    } else {
        TActionList *actionList = new TActionList();
        actionList->append(action);
        mActionMap.insert(className, actionList);
    }

    mActionClassMap.insert(action, className);
    QKeySequence key = shortcut(className, action->objectName());
    if(!key.isEmpty())
        action->setShortcut(key);
}

void TShortKeyManager::saveAction(QAction *action)
{
    if(mActionClassMap.contains(action))
    {
        mSettings.beginGroup("Shorcut/"+mActionClassMap[action]);
        mSettings.setValue(action->objectName(), action->shortcut().toString());
        mSettings.endGroup();
    }
}

void TShortKeyManager::loadShorcuts()
{
    for(TActionClassMap::iterator i = mActionClassMap.begin();i!=mActionClassMap.end();i++)
    {
        QAction *action = i.key();
        QKeySequence key = shortcut(i.value(), action->objectName());
        if(!key.isEmpty())
            action->setShortcut(key);
    }
}

TActionMap *TShortKeyManager::actionMap()
{
    return &mActionMap;
}

QKeySequence TShortKeyManager::shortcut(QString className, QString key)
{
    QString shortcut;
    mSettings.beginGroup("Shorcut/"+className);
    shortcut = mSettings.value(key).toString();
    mSettings.endGroup();

    return QKeySequence(shortcut);
}
