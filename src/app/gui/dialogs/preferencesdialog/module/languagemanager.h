#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QTranslator>

class TLanguageManager
{
public:
    static TLanguageManager* instance();
    static void deleteInstance();

    /**
     * Installs the translators on the application for Qt and Tiled. Should be
     * called again when the language changes.
     */
    void installTranslators(const QString &language=QString());

    /**
     * Returns the available languages as a list of country codes.
     */
    QStringList languages();

private:
    TLanguageManager();
    ~TLanguageManager();

    void loadLanguages();

    QString mTranslationsDir;
    QStringList mLanguages;
    QTranslator *mQtTranslator;
    QTranslator *mAppTranslator;

    static TLanguageManager *mInstance;
};

#endif // LANGUAGEMANAGER_H
