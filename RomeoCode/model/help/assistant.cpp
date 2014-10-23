#include "assistant.h"
#include <QString>
#include <QDir>
#include <QStringList>
#include <QLibraryInfo>
#include <QByteArray>
#include <QObject>
#include <QMessageBox>

using Romeo::Model::Help::Assistant;

Assistant::Assistant() : process(0)
{
}

bool Assistant::startAssistant()
{

    //if process instance already not exists, crate one
    if(!process)
        process = new QProcess();
    //if process isn't already running start it.
    if(process->state() != QProcess::Running) {
        //app represent the app to start
        QString app =QDir::currentPath() + QDir::separator();
        #if !defined(Q_OS_MAC)
                app += QLatin1String("assistant");
        #else
                app += QLatin1String("Assistant.app/Contents/MacOS/Assistant");
        #endif

     //args represent the arguments for the app
     QStringList args;
     args << QLatin1String("-collectionFile")
          << QLatin1String("./documentation/doc.qhc")
          << QLatin1String("-enableRemoteControl");

     process->start(app, args);
     if(!process->waitForStarted()) {
            QMessageBox::critical(0, QObject::tr("Simple Text Viewer"),
                             QObject::tr("Unable to launch Qt Assistant (%1)").arg(app));
            return false;
     }

    }

    return true;
}

void Assistant::showDocumentation(const QString &file, const QString &anchor)
{
    //exit if the cannot stat the assistant
     if(!startAssistant())
         return;
     QByteArray ba("SetSource ");
     ba.append("qthelp://com.sevenmonkeys.romeo/doc/");

     QString fileE = file;
     fileE.append(QString(".html"));
     if(!anchor.isEmpty()) fileE.append(QString("#")+anchor);
     process->write(ba + fileE.toLocal8Bit() + '\n');
}

Assistant::~Assistant()
{
    //if the process is already running, terminate it
    if (process && process->state() == QProcess::Running) {
           //terminate the process
           process->terminate();
           process->waitForFinished(3000);
       }
    //deallocate the process instance
    delete process;
}
