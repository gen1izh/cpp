#include "log.h"

CommandLogger   cmdLog;
CommandLogger   telemetryLog;

ProgressSendingData  sPacketsBar;

CommandLogger::CommandLogger(QObject *parent) :
    QObject(parent) {
}

void CommandLogger::refresh() {
    emit doIt();
}

void CommandLogger::add(QString str) {
    _log.append(str);
}

void CommandLogger::clear() {
    _log.clear();
}

ProgressSendingData::ProgressSendingData(QObject *parent) :
    QObject(parent) {
}

void ProgressSendingData::refresh() {
    emit doIt();
}
