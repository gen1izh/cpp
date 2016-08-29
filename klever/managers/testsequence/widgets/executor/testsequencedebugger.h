#ifndef TESTSEQUENCE_DEBUGGER_H
#define TESTSEQUENCE_DEBUGGER_H

#include <QObject>
#include <QAction>

#include <QScriptEngine>
#include <QScriptEngineDebugger>

class TestSequenceDebugger : public QScriptEngineDebugger
{
    Q_OBJECT
public:
    TestSequenceDebugger(QScriptEngine *engine = 0, QObject *parent = 0);
    ~TestSequenceDebugger();

    void setEngine(QScriptEngine *engine) { m_engine = engine; }
    void setProgram(const QString content, const QString path);

    QScriptValue result() const { return m_result; }

public slots:
    void exec();

signals:
    void finished();

private:
    QScriptValue    m_result;

    QString         m_content;
    QString         m_path;
    QScriptEngine  *m_engine;
};

#endif // TESTSEQUENCE_DEBUGGER_H
