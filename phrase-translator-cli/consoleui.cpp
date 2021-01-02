#include <QTextStream>
#include "consoleui.h"
#include "phrasetranslatorgoogle.h"

void ConsoleUI::run()
{
    QString phrase = "Paul likes apples";
    PhraseTranslatorGoogle translator;
    QTextStream qout(stdout);
    qout << translator.translate(phrase) << Qt::endl;
    emit finished();
}
