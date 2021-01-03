#ifndef PHRASETRANSLATORBASE_H
#define PHRASETRANSLATORBASE_H

#include <QObject>

class PhraseTranslatorBase : public QObject
{
    Q_OBJECT
public:
    PhraseTranslatorBase(QObject *parent = nullptr) : QObject(parent) {}
    virtual void translationStart(const QString &text) = 0;

signals:
    void translationFinished(const QString &result);
};

#endif // PHRASETRANSLATORBASE_H
