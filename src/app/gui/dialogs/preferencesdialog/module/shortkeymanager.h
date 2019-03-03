#ifndef TSHORTKEYMANAGER_H
#define TSHORTKEYMANAGER_H

#include <QAction>
#include <QSettings>

typedef QList<QAction*> TActionList;
typedef QMap<QString, TActionList*> TActionMap;
typedef QMap<QAction*, QString> TActionClassMap;
typedef QList<QKeySequence> TKeySequences;

class TShortKeyManager : public QObject
{
    Q_OBJECT
public:
    static TShortKeyManager *instance(QObject *parent = 0);
    static void deleteInstance();

    explicit TShortKeyManager(QObject *parent = 0);
    ~TShortKeyManager();

    void registerActions(QString className, TActionList actionList);

    void saveAction(QAction *action);

    void loadShorcuts();

    TActionMap *actionMap();

private:
    static TShortKeyManager *mInstance;
    TActionMap mActionMap;
    TActionClassMap mActionClassMap;
    QSettings mSettings;
    QKeySequence shortcut(QString className, QString key);
    void registerAction(QString className, QAction *action);

signals:

public slots:
};

#endif // TSHORTKEYMANAGER_H
