#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <QDebug>
#include <QFile>
#include <QHash>

//https://github.com/VelazcoJD/QtLogging
class Logger
{
private:
    /// @brief The file object where logs are written to.
    static QFile* logFile;

    /// @brief Whether the logger has being initialized.
    static bool isInit;

    /// @brief The different type of contexts.
    static QHash<QtMsgType, QString> contextNames;

    static QList<QtMsgType> acceptedMsg;

    static QList<QtMsgType> acceptedMsgOrder;

public:
    /// @brief Initializes the logger.
    static void init();

    /// @brief Cleans up the logger.
    static void clean();

    /// @brief The function which handles the logging of text.
    static void messageOutput(QtMsgType type, const QMessageLogContext& context,
        const QString& msg);
    static QList<QtMsgType> getAcceptedMsg();
    static void setAcceptedMsg(const QString &text);
};

#endif // LOGGER_H
