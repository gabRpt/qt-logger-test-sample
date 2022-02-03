#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QObject>

#include <iostream>

QFile* Logger::logFile = Q_NULLPTR;
bool Logger::isInit = false;
bool Logger::createCrashLog = true;
QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg,		" Debug  "},
    {QtMsgType::QtInfoMsg,		"  Info  "},
    {QtMsgType::QtWarningMsg,	"Warning "},
    {QtMsgType::QtCriticalMsg,	"Critical"},
    {QtMsgType::QtFatalMsg,		" Fatal  "}
};
QList<QtMsgType> Logger::acceptedMsg = QList<QtMsgType>({QtMsgType::QtDebugMsg,
                                                       QtMsgType::QtInfoMsg,
                                                       QtMsgType::QtWarningMsg,
                                                       QtMsgType::QtCriticalMsg,
                                                       QtMsgType::QtFatalMsg});
QList<QtMsgType> Logger::acceptedMsgOrder = Logger::acceptedMsg;


QList<QtMsgType> Logger::getAcceptedMsg()
{
    return Logger::acceptedMsg;
}

void Logger::setAcceptedMsg(const QString &text)
{
    int indexOfmsg = Logger::acceptedMsgOrder.indexOf(Logger::contextNames.key(text));
    int maxIndex = Logger::acceptedMsgOrder.size()-1;

    Logger::acceptedMsg.clear();
    for(int i=maxIndex ; i>=indexOfmsg; i--){
        acceptedMsg.append(acceptedMsgOrder.value(i));
    }
}

void Logger::init() {
    if (isInit) {
        return;
    }

    // Create log file
    logFile = new QFile;
    logFile->setFileName(QDir::home().filePath("Documents/alize2Logs.log"));
    logFile->open(QIODevice::Append | QIODevice::Text);

    // Redirect logs to messageOutput
    qInstallMessageHandler(Logger::messageOutput);

    // Clear file contents
    logFile->resize(0);

    Logger::isInit = true;
}

void Logger::clean() {
    if (logFile != Q_NULLPTR) {
        logFile->close();
        delete logFile;
    }
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    if(acceptedMsg.contains(type)){
        QString log = QObject::tr("%1 | %2 | %3 | %4 | %5 | %6\n").
            arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
            arg(Logger::contextNames.value(type)).
            arg(context.line).
            arg(QString(context.file).
                section('\\', -1)).			// File name without file path
            arg(QString(context.function).
                section('(', -2, -2).		// Function name only
                section(' ', -1).
                section(':', -1)).
            arg(msg);

        logFile->write(log.toLocal8Bit());
        logFile->flush();
        if(type == QtMsgType::QtFatalMsg && createCrashLog){
            QString date = QDateTime::currentDateTime().toString("dd-MM-yyyy-hh-mm-ss");
            logFile->rename(QString(QDir::home().filePath("Documents/alize2Logs_crash_"+date+".log")));
        }
    }
}
