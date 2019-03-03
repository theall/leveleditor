#ifndef KEYCODEEDIT_H
#define KEYCODEEDIT_H

#include <QtWidgets/QLineEdit>

class TKeyCodeEdit : public QLineEdit
{
    Q_OBJECT

public:
    enum Code
    {
        NONE = 0x0,
        UP = 0x1,
        RIGHT = 0x4,
        DOWN = 0x10,
        LEFT = 0x40,

        A = 0x100,
        B = 0x200,
        C = 0x400,
        X = 0x800,
        Y = 0x1000,
        Z = 0x2000,
        L1 = 0x4000,
        L2 = 0x8000,
        L3 = 0x10000,
        R1 = 0x20000,
        R2 = 0x40000,
        R3 = 0x80000,

        UP_RIGHT = UP|RIGHT,
        RIGHT_DOWN = RIGHT|DOWN,
        DOWN_LEFT = DOWN|LEFT,
        LEFT_UP = LEFT|UP,
        CODE_DIR = UP|RIGHT|DOWN|LEFT,
        CODE_ALL=0xffffffff
    };

    TKeyCodeEdit(QWidget *parent=nullptr);
    ~TKeyCodeEdit();

    void add(Code c);
    void popup();
    void removeLast();
    void clear();
    void setHold();
    void setAndMode(bool andMode);

    void setText(const QString &text);

signals:
    void codeChanged(const QString &code, int lastCode);

private slots:

private:
    struct SingleCode
    {
        int code;
        bool hold;
        SingleCode() {
            code = NONE;
            hold = false;
        }
    };

    QList<SingleCode> mCodeList;
    bool mAndMode;
    QList<Code> mCodeSequence;

    void renderCode();
};

#endif // KEYCODEEDIT_H
