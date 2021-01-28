#include <QTextStream>
#include <QNetworkAccessManager>
#include "consoleui.h"
#include "phrasetranslatorgoogle.h"
#include "postag.h"
#include "postagger.h"
#include "wordlist.h"
#include "phrasepattern.h"
#include "phrasegeneratorrandom.h"
#include "phrasegeneratormarkov.h"

void ConsoleUI::run()
{
    auto tagger = POSTagger();
    auto file = "/home/egor/src/phrase-translator/data/test/war_and_peace.txt";
    WordList wlist;
    POSTag tags[] = {POSTag(POSTagEnum::NN), POSTag(POSTagEnum::VBD), POSTag(POSTagEnum::JJ)};
    PhrasePattern pattern(tags, sizeof(tags)/sizeof(tags[0]));
    PhraseGeneratorMarkov gen;

    wlist.readFromTxtFile(file);
    tagger.doTagging(wlist);
    for (int i = 0; i < 10; i++) {
        QString phrase = QString::fromStdString(gen.generatePhrase(wlist, pattern));
        PhraseTranslatorGoogle *translator = new PhraseTranslatorGoogle(this->parent());
        translator->translationStart(phrase);
        connect(translator, &PhraseTranslatorGoogle::translationFinished, this, &ConsoleUI::onTranslationFinished);
    }
}

void ConsoleUI::onTranslationFinished(QString translation)
{
    static auto num = 0;
    QTextStream qout(stdout);
    qout << translation << Qt::endl;
    num++;
    if (num == 10) {
        emit finished();
    }
}
