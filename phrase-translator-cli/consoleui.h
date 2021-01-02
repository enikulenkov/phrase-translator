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

signals:
    void finished();

};

#endif // CONSOLEUI_H
