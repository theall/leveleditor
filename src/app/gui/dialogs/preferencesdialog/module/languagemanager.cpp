#include "languagemanager.h"

#include <QLocale>
#include <QLibraryInfo>
#include <QDirIterator>
#include <QCoreApplication>

TLanguageManager* TLanguageManager::mInstance = NULL;

TLanguageManager* TLanguageManager::instance()
{
    if (!mInstance)
        mInstance = new TLanguageManager();
    return mInstance;
}

void TLanguageManager::deleteInstance()
{
    if(mInstance)
    {
        delete mInstance;
        mInstance = nullptr;
    }
}

TLanguageManager::TLanguageManager()
    : mQtTranslator(nullptr)
    , mAppTranslator(nullptr)
{
    mTranslationsDir = QCoreApplication::applicationDirPath();
#ifdef Q_OS_WIN32
    mTranslationsDir += QLatin1String("/ts");
#elif defined(Q_OS_MAC)
    mTranslationsDir += QLatin1String("/../ts");
#else
    mTranslationsDir += QLatin1String("/../share/stringex/ts");
#endif
}

TLanguageManager::~TLanguageManager()
{
    if(mQtTranslator)
        delete mQtTranslator;
    if(mAppTranslator)
        delete mAppTranslator;
}

void TLanguageManager::installTranslators(const QString &_language)
{
    // Delete previous translators
    if(mQtTranslator)
        delete mQtTranslator;
    if(mAppTranslator)
        delete mAppTranslator;

    mQtTranslator = new QTranslator;
    mAppTranslator = new QTranslator;

    QString language = _language;
    if (language.isEmpty())
        language = QLocale::system().name();

    const QString qtTranslationsDir =
            QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    if (mQtTranslator->load(QLatin1String("qt_") + language,
                            qtTranslationsDir)) {
        QCoreApplication::installTranslator(mQtTranslator);
    } else {
        delete mQtTranslator;
        mQtTranslator = nullptr;
    }

    if (mAppTranslator->load(language, mTranslationsDir)) {
        QCoreApplication::installTranslator(mAppTranslator);
    } else {
        delete mAppTranslator;
        mAppTranslator = nullptr;
    }
}

QStringList TLanguageManager::languages()
{
    if (mLanguages.isEmpty())
        loadLanguages();
    return mLanguages;
}

void TLanguageManager::loadLanguages()
{
    mLanguages.clear();

    QStringList nameFilters;
    nameFilters.append(QLatin1String("*.qm"));

    QDirIterator iterator(mTranslationsDir, nameFilters,
                          QDir::Files | QDir::Readable);

    while (iterator.hasNext()) {
        iterator.next();
        const QString baseName = iterator.fileInfo().completeBaseName();
        mLanguages.append(baseName);
    }
}
