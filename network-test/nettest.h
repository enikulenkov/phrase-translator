#ifndef NETTEST_H
#define NETTEST_H

#include <QObject>
#include <QNetworkAccessManager>

class NetTest : public QObject
{
    Q_OBJECT
public:
    explicit NetTest(QObject *parent = nullptr);
    void getStart(QString url);

public slots:
    void handleNetworkReply(QNetworkReply *reply);

signals:
    void getFinished(QString result);

private:
    QNetworkAccessManager m_networkManager;

};

#endif // NETTEST_H
