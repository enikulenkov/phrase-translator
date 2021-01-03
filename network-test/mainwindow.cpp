#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_button = new QPushButton(this);
    m_textEdit = new QTextEdit(this);
    m_button->setText("GET");
    m_textEdit->setReadOnly(true);
    m_textEdit->setGeometry(0, 50, 500, 500);
    connect(m_button, &QPushButton::clicked, this, &MainWindow::onGetClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGetClicked(bool clicked)
{
    (void)clicked;
    //m_netTest.getStart("http://ya.ru");
    m_netTest.getStart("http://google.com/complete/search?output=toolbar&q=best");
    connect(&m_netTest, &NetTest::getFinished, this, &MainWindow::showReqResult);
}

void MainWindow::showReqResult(QString text)
{
   m_textEdit->setText(text);
}
