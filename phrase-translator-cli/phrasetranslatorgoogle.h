#ifndef PHRASETRANSLATORGOOGLE_H
#define PHRASETRANSLATORGOOGLE_H

#include "phrasetranslatorbase.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class PhraseTranslatorGoogle : public PhraseTranslatorBase
{
    Q_OBJECT
public:
    PhraseTranslatorGoogle(QObject *parent = nullptr);
    virtual void translationStart(const QString &text, const QString &targetLang);
public slots:
    void handleNetworkReply(QNetworkReply *reply);
private:
    void sendTranslateReq(const QString &text, const QString &targetLang);
    QString m_apiKey;
    QNetworkAccessManager m_networkManager;
    QNetworkReply *m_reply;
    QString m_translation;
};

#endif // PHRASETRANSLATORGOOGLE_H
