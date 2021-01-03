#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include "nettest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onGetClicked(bool clicked);
    void showReqResult(QString text);
private:
    Ui::MainWindow *ui;
    NetTest m_netTest;
    QPushButton *m_button;
    QTextEdit *m_textEdit;
};
#endif // MAINWINDOW_H
