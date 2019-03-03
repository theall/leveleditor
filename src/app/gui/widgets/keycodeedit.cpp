#include "keycodeedit.h"

#include <QtMath>

struct CodeStringMap
{
    int code;
    QString str;
};

const CodeStringMap g_codeStringMap[] = {
    {TKeyCodeEdit::CODE_DIR, QString("↑+→+↓+←")},
    {TKeyCodeEdit::CODE_DIR^TKeyCodeEdit::UP, QString("→+↓+←")},
    {TKeyCodeEdit::CODE_DIR^TKeyCodeEdit::RIGHT, QString("↑+↓+←")},
    {TKeyCodeEdit::CODE_DIR^TKeyCodeEdit::DOWN, QString("↑+→+←")},
    {TKeyCodeEdit::CODE_DIR^TKeyCodeEdit::LEFT, QString("↑+→+↓")},
    {TKeyCodeEdit::UP_RIGHT, QString("↗")},
    {TKeyCodeEdit::RIGHT_DOWN, QString("↘")},
    {TKeyCodeEdit::DOWN_LEFT, QString("↙")},
    {TKeyCodeEdit::LEFT_UP, QString("↖")},
    {TKeyCodeEdit::UP, QString("↑")},
    {TKeyCodeEdit::RIGHT, QString("→")},
    {TKeyCodeEdit::DOWN, QString("↓")},
    {TKeyCodeEdit::LEFT, QString("←")},
    {TKeyCodeEdit::A, QString("A")},
    {TKeyCodeEdit::B, QString("B")},
    {TKeyCodeEdit::C, QString("C")},
    {TKeyCodeEdit::X, QString("X")},
    {TKeyCodeEdit::Y, QString("Y")},
    {TKeyCodeEdit::Z, QString("Z")},
    {TKeyCodeEdit::L1, QString("L1")},
    {TKeyCodeEdit::L2, QString("L2")},
    {TKeyCodeEdit::L3, QString("L3")},
    {TKeyCodeEdit::R1, QString("R1")},
    {TKeyCodeEdit::R2, QString("R2")},
    {TKeyCodeEdit::R3, QString("R3")},
    {TKeyCodeEdit::NONE, ""}
};

TKeyCodeEdit::TKeyCodeEdit(QWidget *parent) :
    QLineEdit(parent)
  , mAndMode(false)
{
    setReadOnly(true);
    setClearButtonEnabled(false);
}

TKeyCodeEdit::~TKeyCodeEdit()
{

}

void TKeyCodeEdit::add(TKeyCodeEdit::Code c)
{
    if(mAndMode)
    {
        if(!mCodeList.isEmpty())
        {
            SingleCode &lastCode = mCodeList.back();
            if(lastCode.code&c)
                return;

            lastCode.code |= c;
        } else {
            SingleCode code;
            code.code = c;
            mCodeList.append(code);
        }
    } else {
        SingleCode code;
        code.code = c;
        mCodeList.append(code);
    }

    renderCode();

    mCodeSequence.append(c);
}

void TKeyCodeEdit::popup()
{
    if(!mCodeList.isEmpty())
    {
        mCodeList.takeLast();
        renderCode();
    }
}

void TKeyCodeEdit::removeLast()
{
    if(!mCodeList.isEmpty())
    {
        SingleCode &c = mCodeList.back();
        if(c.hold)
            c.hold = false;
        else {
            c.code ^= mCodeSequence.takeLast();
            if(c.code==NONE)
                mCodeList.takeLast();
        }
        renderCode();
    }
}

void TKeyCodeEdit::clear()
{
    QLineEdit::clear();
    mCodeList.clear();
    mCodeSequence.clear();
    emit codeChanged(QString(), NONE);
}

void TKeyCodeEdit::setHold()
{
    if(!mCodeList.isEmpty())
    {
        SingleCode &code = mCodeList.back();
        code.hold = true;
        renderCode();
    }
}

void TKeyCodeEdit::setAndMode(bool andMode)
{
    if(andMode==mAndMode)
        return;

    mAndMode = andMode;
    renderCode();
}

void TKeyCodeEdit::setText(const QString &text)
{
    if(text.isEmpty())
        return;

    mCodeSequence.clear();
    mCodeList.clear();

    QMap<QString, int> codeMap;
    for(int i=0;;i++)
    {
        QString t = g_codeStringMap[i].str.toLower();
        if(t.isEmpty())
            break;
        codeMap.insert(t, g_codeStringMap[i].code);
    }
    QStringList keys = codeMap.keys();
    QString commandList = text.toLower();

    QChar endChar;
    for(QChar c : QString("!@#$%^&*()"))
    {
        if(!commandList.contains(c))
        {
            endChar = c;
            break;
        }
    }
    if(endChar.isNull())
        return;

    QString commandShiftList = commandList;
    commandShiftList.remove(0, 1);
    commandShiftList.append(endChar);

    SingleCode command;
    bool andMode = false;
    for(int i=0;i<commandList.size();i++)
    {
        Code code = NONE;
        QChar c = commandList.at(i);
        QChar nextChar = commandShiftList.at(i);
        QString unionStr;
        unionStr.append(c);
        unionStr.append(nextChar);
        if(c.isSpace() || c=='~' || c=='+')
            continue;
        else if(c==endChar)
            break;
        if(keys.contains(unionStr))
        {
            code = (Code)codeMap[unionStr];
        } else if(keys.contains(QString(c))) {
            code = (Code)codeMap[QString(c)];
        }
        if(code != NONE)
        {
            if(andMode)
            {
                command.code |= code;
                andMode = false;
            } else {
                command.code = code;
            }
            if(nextChar=='+') {
                andMode = true;
                i++;
            } else {
                SingleCode t;
                t.code = command.code;
                if(nextChar=='~')
                {
                    t.hold = true;
                    i++;
                }
                mCodeList.append(t);
                command.code = NONE;
                command.hold = false;
            }
            mCodeSequence.append(code);
        }
    }

    if(andMode)
    {
        mCodeList.append(command);
    }
    renderCode();
}

void TKeyCodeEdit::renderCode()
{
    QString codeString;
    int lastCode = NONE;
    if(mCodeList.isEmpty())
    {
        clear();
    } else {
        for(SingleCode sc : mCodeList)
        {
            QStringList codeUnionStringList;
            for(int i=0;;i++)
            {
                CodeStringMap codeStringMap;
                codeStringMap = g_codeStringMap[i];
                if(codeStringMap.code == NONE) {
                    break;
                } else if((codeStringMap.code&sc.code)==codeStringMap.code) {
                    codeUnionStringList.append(codeStringMap.str);
                    sc.code ^= codeStringMap.code;
                }
            }
            if(!codeUnionStringList.isEmpty())
                codeString += codeUnionStringList.join("+");

            if(sc.hold)
                codeString.append('~');
            QLineEdit::setText(codeString);
        }
        lastCode = mCodeList.back().code;
    }

    emit codeChanged(codeString, lastCode);
}
