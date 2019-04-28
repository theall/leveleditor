#include "enemy.h"
#include "../../base/tr.h"

static const QString P_POS = T("Position");
static const QString P_DIR = T("Dir");
static const QString P_LIFE = T("Life");
static const QString P_LIVES = T("Lives");
static const QString P_TEAM = T("Team");
static const QString P_DAMAGE = T("Damage");
static const QString P_AI_LEVEL = T("Ai level");
static const QString P_CATEGORY = T("Category");
static const QString P_TYPE = T("Type");
static const QString P_DELAY = T("Delay");
static const QString P_DEAD_EVENT = T("Dead event");
static const QString P_WAIT_EVENT = T("Wait event");
static const QString P_CHUNK = T("Chunk");
static const QString P_SOUND = T("Sound");
static const QString P_VAR1 = T("Var1");
static const QString P_VAR2 = T("Var2");
static const QString P_VAR3 = T("Var3");
static const QString P_VAR4 = T("Var4");
static const QString P_VAR5 = T("Var5");

TEnemy::TEnemy(QObject *parent) :
    TObject(TObject::ENEMY, parent)
{
    initPropertySheet();
}

void TEnemy::saveToStream(QDataStream &stream) const
{

}

void TEnemy::readFromStream(QDataStream &stream)
{
    int x;
    int y;
    int dir;
    int life;
    int lives;
    int team;
    int damage;
    int aiLevel;
    int category;
    int type;
    int delay;
    int deadEvent;
    int waitEvent;
    int chunk;
    int sound;
    int var1;
    int var2;
    int var3;
    int var4;
    int var5;
    stream >> x;
    stream >> y;
    stream >> dir;
    stream >> life;
    stream >> lives;
    stream >> team;
    stream >> damage;
    stream >> aiLevel;
    stream >> team;
    stream >> category;
    stream >> type;
    stream >> delay;
    stream >> deadEvent;
    stream >> waitEvent;
    stream >> chunk;
    stream >> sound;
    stream >> var1;
    stream >> var2;
    stream >> var3;
    stream >> var4;
    stream >> var5;
    mPropertySheet->setValue(PID_ENEMY_POS, QPoint(x,y));
    mPropertySheet->setValue(PID_ENEMY_DIR, dir);
    mPropertySheet->setValue(PID_ENEMY_LIFE, life);
    mPropertySheet->setValue(PID_ENEMY_LIVES, lives);
    mPropertySheet->setValue(PID_ENEMY_DAMAGE, damage);
    mPropertySheet->setValue(PID_ENEMY_AI_LEVEL, aiLevel);
    mPropertySheet->setValue(PID_ENEMY_TEAM, team);
    mPropertySheet->setValue(PID_ENEMY_CATEGORY, category);
    mPropertySheet->setValue(PID_ENEMY_TYPE, type);
    mPropertySheet->setValue(PID_ENEMY_DELAY, delay);
    mPropertySheet->setValue(PID_ENEMY_DEAD_EVENT, deadEvent);
    mPropertySheet->setValue(PID_ENEMY_WAIT_EVENT, waitEvent);
    mPropertySheet->setValue(PID_ENEMY_CHUNK, chunk);
    mPropertySheet->setValue(PID_ENEMY_SOUND, sound);
    mPropertySheet->setValue(PID_ENEMY_VAR1, var1);
    mPropertySheet->setValue(PID_ENEMY_VAR2, var2);
    mPropertySheet->setValue(PID_ENEMY_VAR3, var3);
    mPropertySheet->setValue(PID_ENEMY_VAR4, var4);
    mPropertySheet->setValue(PID_ENEMY_VAR5, var5);
}

void TEnemy::initPropertySheet()
{
    mPropertySheet->addProperty(PT_INT, P_POS, PID_ENEMY_POS);
    mPropertySheet->addProperty(PT_INT, P_DIR, PID_ENEMY_DIR);
    mPropertySheet->addProperty(PT_INT, P_LIFE, PID_ENEMY_LIFE);
    mPropertySheet->addProperty(PT_INT, P_LIVES, PID_ENEMY_LIVES);
    mPropertySheet->addProperty(PT_INT, P_DAMAGE, PID_ENEMY_DAMAGE);
    mPropertySheet->addProperty(PT_INT, P_AI_LEVEL, PID_ENEMY_AI_LEVEL);
    mPropertySheet->addProperty(PT_INT, P_TEAM, PID_ENEMY_TEAM);
    mPropertySheet->addProperty(PT_INT, P_CATEGORY, PID_ENEMY_CATEGORY);
    mPropertySheet->addProperty(PT_INT, P_TYPE, PID_ENEMY_TYPE);
    mPropertySheet->addProperty(PT_INT, P_DELAY, PID_ENEMY_DELAY);
    mPropertySheet->addProperty(PT_INT, P_DEAD_EVENT, PID_ENEMY_DEAD_EVENT);
    mPropertySheet->addProperty(PT_INT, P_WAIT_EVENT, PID_ENEMY_WAIT_EVENT);
    mPropertySheet->addProperty(PT_INT, P_CHUNK, PID_ENEMY_CHUNK);
    mPropertySheet->addProperty(PT_INT, P_SOUND, PID_ENEMY_SOUND);
    mPropertySheet->addProperty(PT_INT, P_VAR1, PID_ENEMY_VAR1);
    mPropertySheet->addProperty(PT_INT, P_VAR2, PID_ENEMY_VAR2);
    mPropertySheet->addProperty(PT_INT, P_VAR3, PID_ENEMY_VAR3);
    mPropertySheet->addProperty(PT_INT, P_VAR4, PID_ENEMY_VAR4);
    mPropertySheet->addProperty(PT_INT, P_VAR5, PID_ENEMY_VAR5);
}

QString TEnemy::typeString() const
{
    return T("Enemy");
}

bool TEnemy::isCongener(TObject *) const
{
    return false;
}
