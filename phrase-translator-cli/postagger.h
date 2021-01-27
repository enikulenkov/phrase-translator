#ifndef POSTAGGER_H
#define POSTAGGER_H

#include <QObject>
#include <meta/sequence/perceptron.h>
#include "postag.h"
#include "wordlist.h"

class POSTagger : public QObject
{
    Q_OBJECT
public:
    explicit POSTagger(QObject *parent = nullptr);
    void posTagsAssign();
    void doTagging(WordList &wlist);
signals:
private:
    meta::sequence::perceptron m_tagger;
};

#endif // POSTAGGER_H
