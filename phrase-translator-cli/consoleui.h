#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <QObject>

class ConsoleUI : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleUI(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void run();
    void onTranslationFinished(QString translation);

signals:
    void finished();
};

#endif // CONSOLEUI_H
