#ifndef PHRASETRANSLATORGOOGLE_H
#define PHRASETRANSLATORGOOGLE_H

#include "phrasetranslatorbase.h"
#include <QObject>

class PhraseTranslatorGoogle : public PhraseTranslatorBase
{
    Q_OBJECT
public:
    PhraseTranslatorGoogle();
    virtual QString translate(const QString &text);
};

#endif // PHRASETRANSLATORGOOGLE_H
