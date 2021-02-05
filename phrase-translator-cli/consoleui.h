#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QObject>
#include "wordlist.h"

class ConsoleUI : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleUI(QObject *parent = nullptr) : QObject(parent), m_wlist() {}

private:
    void initWlist();
    void genPhrase();
    void translatePhrase();
    WordList m_wlist;
    QString m_curr_phrase;

public slots:
    void run();
    void onTranslationFinished(QString translation);

signals:
    void finished();
};

#endif // CONSOLEUI_H
