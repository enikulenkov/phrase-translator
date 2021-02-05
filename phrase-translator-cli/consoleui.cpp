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

void ConsoleUI::initWlist()
{
    auto tagger = POSTagger();
    auto file = "/home/egor/src/phrase-translator/data/test/war_and_peace.txt";

    m_wlist.readFromTxtFile(file);
    tagger.doTagging(m_wlist);
}

void ConsoleUI::genPhrase()
{
    PhraseGeneratorMarkov gen;
    POSTag tags[] = {POSTag(POSTagEnum::NNP), POSTag(POSTagEnum::VBD), POSTag(POSTagEnum::TO), POSTag(POSTagEnum::VB)};
    PhrasePattern pattern(tags, sizeof(tags)/sizeof(tags[0]));
    m_curr_phrase = QString::fromStdString(gen.generatePhrase(m_wlist, pattern));
}

void ConsoleUI::translatePhrase()
{
    PhraseTranslatorGoogle *translator = new PhraseTranslatorGoogle(this->parent());
    QTextStream qout(stdout);

    genPhrase();
    qout << "Generated phrase for translation:" << Qt::endl;
    qout << m_curr_phrase << Qt::endl;

    translator->translationStart(m_curr_phrase);
    connect(translator, &PhraseTranslatorGoogle::translationFinished, this, &ConsoleUI::onTranslationFinished);
}

void ConsoleUI::run()
{
    initWlist();
    translatePhrase();
}

void ConsoleUI::onTranslationFinished(QString translation)
{
    QTextStream qout(stdout);
    QTextStream qin(stdin);
    QString user_reply;

    qout << "Press <Enter> to see a translation" << Qt::endl;
    user_reply = qin.readLine();
    (void)user_reply;
    qout << "Translation:" << Qt::endl;
    qout << translation << Qt::endl;
    qout << "One more phrase? [Y/n]" << Qt::endl;
    user_reply = qin.readLine();
    if (user_reply.startsWith('y') || user_reply.startsWith('Y') || user_reply.isEmpty()) {
        translatePhrase();
    } else {
        emit finished();
    }
}
