#include <QtDebug>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>
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

int ConsoleUI::initPatterns()
{
    QSettings settings;
    QTextStream qerr(stderr);
    auto patterns_json_file = settings.value("corpus/patterns").toString();
    if (patterns_json_file.isEmpty()) {
        qerr << "No corpus/patterns setting!" << Qt::endl;
        return 1;
    }
    QFile f(patterns_json_file);
    if (!f.open(QIODevice::ReadOnly)) {
        qerr << "Can't open patterns file for reading " << patterns_json_file << Qt::endl;
        return 1;
    }
    QByteArray data = f.readAll();
    f.close();

    QJsonParseError json_err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &json_err);
    if (doc.isNull()) {
        qerr << "Can't parse JSON file " << patterns_json_file << Qt::endl;
        qerr << json_err.errorString() << Qt::endl;
        return 1;
    }

    QJsonArray patterns_array = doc.array();
    if (patterns_array.isEmpty()) {
        qerr << "Patterns array is empty (or root is object, not array)" << Qt::endl;
        return 1;
    }
    for (auto p_ref : patterns_array) {
        QJsonObject p_obj = p_ref.toObject();
        if (p_obj.isEmpty()) {
            qerr << "Wrong object in patterns array (or not object)" << Qt::endl;
            goto failure;
        }
        QJsonArray pos_tags_list = p_obj["pattern"].toArray();
        if (pos_tags_list.isEmpty()) {
            qerr << "Empty POS tags array (or invalid array)" << Qt::endl;
            goto failure;
        }
        size_t tags_num = static_cast<size_t>(pos_tags_list.size());
        POSTag *tags = new POSTag[tags_num];
        auto i = 0;
        for (auto ptag_ref : pos_tags_list) {
            auto ptag_str = ptag_ref.toString();
            tags[i].setTag(ptag_str.toStdString());
            if (tags[i].value() == POSTagEnum::UNK) {
                qerr << "Can't parse POS tag " << ptag_str << Qt::endl;
                delete[] tags;
                goto failure;
            }
            i++;
        }
        m_patterns.append(PhrasePattern(tags, tags_num));
        delete[] tags;
    }

    return 0;

failure:
    m_patterns.clear();
    return 1;
}

void ConsoleUI::genPhrase()
{
    PhraseGeneratorMarkov gen;
    PhrasePattern pattern = m_patterns[QRandomGenerator::global()->bounded(m_patterns.size())];
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
        int ret = initPatterns();
        if (ret != 0) {
            exitWithError(ret, "Can't initialize patterns! Check corpus/patterns configuration");
        }
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
