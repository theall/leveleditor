#include "enemyfactory.h"
#include "../../base/tr.h"

static const QString P_CURRENT_FRAME = T("Current frame");
static const QString P_DELAY = T("Delay");
static const QString P_EVENT = T("Event");
static const QString P_LOOP = T("Loop");

TEnemyFactory::TEnemyFactory(QObject *parent) :
    TObject(TObject::ENEMY, parent)
{
    initPropertySheet();
}

TEnemyFactory::~TEnemyFactory()
{

}

TEnemyList TEnemyFactory::enemyList() const
{
    return mEnemyList;
}

TEnemy *TEnemyFactory::getEnemy(int index) const
{
    return mEnemyList.at(index);
}

void TEnemyFactory::setEnemyList(const TEnemyList &enemyList)
{
    mEnemyList = enemyList;
}

void TEnemyFactory::saveToStream(QDataStream &stream) const
{
    stream << mPropertySheet->getValue(PID_ENEMY_FACTORY_CURRENT_FRAME).toInt();
    stream << mPropertySheet->getValue(PID_ENEMY_FACTORY_DELAY).toInt();
    stream << mPropertySheet->getValue(PID_ENEMY_FACTORY_EVENT).toInt();
    stream << mEnemyList.size();
    stream << mPropertySheet->getValue(PID_ENEMY_FACTORY_LOOP).toInt();

    for(TEnemy *enemy : mEnemyList) {
        enemy->saveToStream(stream);
    }
}

void TEnemyFactory::readFromStream(QDataStream &stream)
{
    int currentFrame;
    int delay;
    int event;
    int factoryAmount;
    int loop;
    stream >> currentFrame;
    stream >> delay;
    stream >> event;
    stream >> factoryAmount;// 。
    stream >> loop;
    mEnemyList.clear();
    for(int i=0;i<factoryAmount;i++) {
        TEnemy *enemy = new TEnemy(this);
        enemy->readFromStream(stream);
        mEnemyList.append(enemy);
    }
    mPropertySheet->setValue(PID_ENEMY_FACTORY_CURRENT_FRAME, currentFrame);
    mPropertySheet->setValue(PID_ENEMY_FACTORY_DELAY, delay);
    mPropertySheet->setValue(PID_ENEMY_FACTORY_EVENT, event);
    mPropertySheet->setValue(PID_ENEMY_FACTORY_LOOP, loop);
}

void TEnemyFactory::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_CURRENT_FRAME, PID_ENEMY_FACTORY_CURRENT_FRAME);
    mPropertySheet->addProperty(PT_INT, P_DELAY, PID_ENEMY_FACTORY_DELAY);
    mPropertySheet->addProperty(PT_INT, P_EVENT, PID_ENEMY_FACTORY_EVENT);
    mPropertySheet->addProperty(PT_BOOL, P_LOOP, PID_ENEMY_FACTORY_LOOP);
}

QString TEnemyFactory::typeString() const
{
    return T("EnemyFactory");
}

bool TEnemyFactory::isCongener(TObject *) const
{
    return false;
}
