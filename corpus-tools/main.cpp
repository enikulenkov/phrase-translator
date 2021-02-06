#include <QDebug>
#include <QCoreApplication>
#include <QTextStream>
#include <QCommandLineParser>
#include "postagger.h"

int convert(QString src, QString dst)
{
    auto tagger = POSTagger();
    auto wlist = WordList();
    QTextStream qerr(stderr);
    QTextStream qout(stdout);

    if (src.isEmpty() || dst.isEmpty()) {
        qerr << "Empty src/dst!" << Qt::endl;
        return 1;
    }

    wlist.readFromTxtFile(src.toStdString());
    tagger.doTagging(wlist);
    wlist.store(dst);
    qout << "Text file successfully converted!" << Qt::endl;
    qout << "Words count: " << wlist.vec().size() << Qt::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("PhraseTranslator");
    QCoreApplication::setOrganizationDomain("mydomain.com");
    QCoreApplication::setApplicationName("corpus-tools");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    QTextStream qerr(stderr);
    QTextStream qout(stdout);

    parser.setApplicationDescription("Different tools for manipulating corpus data");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("command", "Command to execute. Supported commands: convert");
    parser.parse(QCoreApplication::arguments());
    const QStringList args = parser.positionalArguments();
    const QString command = args.isEmpty() ? QString() : args.first();
    if (command == "convert") {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("convert", "Convert untagged text file to binary corpus data");
        parser.addPositionalArgument("src", "Untagged text file to be converted to binary corpus data");
        parser.addPositionalArgument("dst", "Output file with binary corpus data");
        parser.process(a);
        const QStringList args = parser.positionalArguments();
        Q_ASSERT(args.first() == "convert");
        if (args.count() != 3) {
            qerr << "src and dst should be specified!" << Qt::endl;
            return 1;
        } else {
            return convert(args.at(1), args.at(2));
        }
    } else if (!command.isEmpty()) {
        qerr << "Unknown command " << command << Qt::endl;
        return 1;
    } else {
        parser.process(a);
    }
    return a.exec();
}
