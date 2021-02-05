#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include "consoleui.h"

static struct {
    QFile *f;
    QTextStream *s;
} logger_ctx;

void messageLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        *logger_ctx.s << "Debug: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")" << Qt::endl;
        break;
    case QtInfoMsg:
        *logger_ctx.s << "Info: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")" << Qt::endl;
        break;
    case QtWarningMsg:
        *logger_ctx.s << "Warning: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")" << Qt::endl;
        break;
    case QtCriticalMsg:
        *logger_ctx.s << "Critical: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")" << Qt::endl;
        break;
    case QtFatalMsg:
        *logger_ctx.s << "Fatal: " << localMsg.constData() << " (" << context.file << ":" << context.line << ", " << context.function << ")" << Qt::endl;
        abort();
    }
}

void setupLogger()
{
    /* TODO: Make Logger class and assign Application object as its parent to avoid memory leaks. */
    logger_ctx.f = new QFile("./log.txt");
    if (logger_ctx.f->open(QFile::WriteOnly)) {
        logger_ctx.s = new QTextStream(logger_ctx.f);
        qInstallMessageHandler(messageLogger);
    } else {
        abort();
    }
}

int main(int argc, char *argv[])
{
    setupLogger();

    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PhraseTranslator");
    QCoreApplication::setOrganizationDomain("mydomain.com");
    QCoreApplication::setApplicationName("app");
    ConsoleUI *ui = new ConsoleUI(&a);
    QObject::connect(ui, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, ui, SLOT(run()));

    return a.exec();
}
