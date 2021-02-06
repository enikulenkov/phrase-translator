#include <QtDebug>
#include <QTextStream>
#include <QNetworkAccessManager>
#include "phrasetranslatorgoogle.h"
#include "postag.h"
#include "postagger.h"
#include "wordlist.h"
#include "phrasepattern.h"
#include "phrasegeneratorrandom.h"
#include "phrasegeneratormarkov.h"
#include "consoleui.h"

void ConsoleUI::initWlist()
{
    QSettings settings;
    auto tagger = POSTagger();
    auto file = settings.value("corpus/data").toString();
    auto corpus_type = settings.value("corpus/type").toString();

    if (file.isEmpty()) {
        exitWithError(1, "corpus/data is not set in configuration!");
    } else {
        if (corpus_type == "untagged_text") {
            m_wlist.readFromTxtFile(file.toStdString());
            tagger.doTagging(m_wlist);
        } else if (corpus_type == "binary") {
            m_wlist.load(file);
        } else if (corpus_type.isEmpty()) {
            exitWithError(1, "corpus/type is not set in configuration!");
        } else {
            exitWithError(1, "Unknown corpus/type setting (" + corpus_type +")");
        }
    }
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

    translator->translationStart(m_curr_phrase, m_target_lang);
    connect(translator, &PhraseTranslatorGoogle::translationFinished, this, &ConsoleUI::onTranslationFinished);
}

void ConsoleUI::exitWithError(int err, QString err_msg)
{
    QTextStream qerr(stderr);

    qCritical() << err_msg << Qt::endl;
    qerr << err_msg << Qt::endl;
    /* TODO: Set exit code somehow... */
    (void)err;
    emit finished();
}

void ConsoleUI::run()
{
    QSettings settings;

    m_target_lang = QSettings().value("translation/languages").toString();
    if (m_target_lang.isEmpty()) {
        exitWithError(1, "translation/languages is not set in configuration!");
    } else {
        initWlist();
        translatePhrase();
    }
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
