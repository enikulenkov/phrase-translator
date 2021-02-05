#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QObject>
#include <QSettings>
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
    void exitWithError(int err, QString err_msg);
    WordList m_wlist;
    QString m_curr_phrase;
    QString m_target_lang;

public slots:
    void run();
    void onTranslationFinished(QString translation);

signals:
    void finished();
};

#endif // CONSOLEUI_H
