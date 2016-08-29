#include "testsequencedebugger.h"

#include <QMainWindow>
#include <QDebug>

TestSequenceDebugger::TestSequenceDebugger(QScriptEngine *engine, QObject *parent) :
    QScriptEngineDebugger(parent),
    m_engine(engine)
{

}

TestSequenceDebugger::~TestSequenceDebugger()
{

}

void TestSequenceDebugger::setProgram(const QString content, const QString path)
{
    m_content = content;
    m_path = path;
}

void TestSequenceDebugger::exec()
{
    attachTo(m_engine);
    action(QScriptEngineDebugger::InterruptAction)->trigger();

    m_result = m_engine->evaluate(m_content, m_path);

    standardWindow()->close();

    emit finished();
}

