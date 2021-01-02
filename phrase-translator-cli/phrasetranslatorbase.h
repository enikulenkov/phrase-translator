#ifndef PHRASETRANSLATORBASE_H
#define PHRASETRANSLATORBASE_H

#include <QObject>

class PhraseTranslatorBase : public QObject
{
    Q_OBJECT
public:
    virtual QString translate(const QString &text) = 0;

signals:

};

#endif // PHRASETRANSLATORBASE_H
