#include "nettest.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

NetTest::NetTest(QObject *parent) : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &NetTest::handleNetworkReply);
}

void NetTest::getStart(QString url)
{
    QNetworkRequest req(url);
    m_networkManager.get(req);
}

void NetTest::handleNetworkReply(QNetworkReply *reply)
{
    QString res;
    if (reply->error() == QNetworkReply::NoError) {
        res = reply->readAll();
    } else {
        res = reply->errorString();
    }
    emit getFinished(res);
}
