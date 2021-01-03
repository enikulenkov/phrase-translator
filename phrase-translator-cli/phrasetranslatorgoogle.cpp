#include "phrasetranslatorgoogle.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString getApiKey()
{
    /* TODO: Correctly handle relative path to the file */
    QFile keyFile("../gcloud/gtranslate_api_key");

    if (!keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    /* TODO: Handle more than one line */
    QByteArray line = keyFile.readLine(40);
    return QString(line);
}

void PhraseTranslatorGoogle::sendTranslateReq(const QString &text)
{
    QString url = "https://translation.googleapis.com/language/translate/v2?key=";
    url.append(m_apiKey);
    QNetworkRequest req(url);
    QJsonObject obj;
    obj["q"] = text;
    obj["source"] = "en";
    obj["target"] = "ru";
    obj["format"] = "text";
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    qDebug() << QString(data);
    qDebug() << url;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_networkManager.post(req, data);
    qDebug() << "Posted" << Qt::endl;
}

PhraseTranslatorGoogle::PhraseTranslatorGoogle(QObject *parent) : PhraseTranslatorBase(parent)
{
    /* TODO: Handle errors */
    m_apiKey = getApiKey();
    Q_ASSERT(!m_apiKey.isEmpty());
    connect(&m_networkManager, &QNetworkAccessManager::finished,
        this, &PhraseTranslatorGoogle::handleNetworkReply);
}

void PhraseTranslatorGoogle::translationStart(const QString &text)
{
    sendTranslateReq(text);
}

void PhraseTranslatorGoogle::handleNetworkReply(QNetworkReply *reply)
{
   qDebug() << "Replied" << Qt::endl;
   if (reply->error() == QNetworkReply::NoError) {
       QJsonDocument doc(QJsonDocument::fromJson(reply->readAll()));
       QJsonObject obj = doc.object();
       QJsonObject data = obj["data"].toObject();
       QJsonArray translations = data["translations"].toArray();
       QJsonObject translation_obj = translations.at(0).toObject();
       m_translation = translation_obj["translatedText"].toString();
       qDebug() << m_translation << Qt::endl;
   } else {
       m_translation = "";
       qDebug() << reply->errorString() << Qt::endl;
   }
   emit translationFinished(m_translation);
   reply->deleteLater();
}
