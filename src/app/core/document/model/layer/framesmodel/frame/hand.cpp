#include "hand.h"

THand::THand(QObject *parent) :
    QObject(parent)
{

}

THand::~THand()
{

}

void THand::loadFromModel(const Model::THand &hand, void *context)
{
    Q_UNUSED(hand);
    Q_UNUSED(context);
}
