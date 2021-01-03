#include <QTextStream>
#include <QNetworkAccessManager>
#include "consoleui.h"
#include "phrasetranslatorgoogle.h"

void ConsoleUI::run()
{
    QString phrase = "Paul likes apples";
    PhraseTranslatorGoogle *translator = new PhraseTranslatorGoogle(this->parent());
    translator->translationStart(phrase);
    connect(translator, &PhraseTranslatorGoogle::translationFinished, this, &ConsoleUI::onTranslationFinished);
}

void ConsoleUI::onTranslationFinished(QString translation)
{
    QTextStream qout(stdout);
    qout << translation << Qt::endl;
    emit finished();
}
