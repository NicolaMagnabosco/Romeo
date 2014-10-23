#include "log.h"
#include "utils.h"

using Romeo::Model::Util::Log::Log;

const QString Log::extension = ".txt";
const int Log::maxLinesPerFile = 500;
bool Log::enable=false;

const QString Log::folderName = "Logs";

const QString Log::fileUserAction = "userAction";
const QString Log::userActionFilePath = Utils::SAVING_FOLDER_PATH+"/"+folderName+"/"+fileUserAction;

const QString Log::fileDatabaseQuery = "dbQuery";
const QString Log::databaseQueryFilePath = Utils::SAVING_FOLDER_PATH+"/"+folderName+"/"+fileDatabaseQuery;

const QString Log::fileAnalysis = "analysis";
const QString Log::analysisFilePath = Utils::SAVING_FOLDER_PATH+"/"+folderName+"/"+fileAnalysis;

Log::Log()
{    
}

void Log::setEnable(bool enableV)
{
    enable=enableV;
}

int Log::countLines(QTextStream &file)
{
    int count = 0;

    while(!file.atEnd()) {
        file.readLine();
        count++;
    }

    return count;
}

void Log::writeLog(Type type, const QString& txt)
{

    if(enable){
        QString path(Utils::SAVING_FOLDER_PATH+"/"+folderName);
        checkPathExistsFromHome(path);

        switch(type) {
            // If type = _USER_ACTION_
            case _USER_ACTION_:
                logWriter(txt, userActionFilePath+extension);
                break;

            // If type = _DATABASE_QUERY_
            case _DATABASE_QUERY_:
                logWriter(txt, databaseQueryFilePath+extension);
                break;

            // If type = _ANALYSIS_
            case _ANALYSIS_:
                logWriter(txt, analysisFilePath+extension);
                break;
        }
    }
}

void Log::logWriter(const QString& txt, QString fileP)
{

    QFile file(fileP);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);

    QString formattedTxt="["+QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT)+"] "+txt;

    if(countLines(stream)<maxLinesPerFile) {
        stream << formattedTxt+"\n";
    }
    else {
        file.copy(fileP+QDateTime::currentDateTime().toString(Utils::DATETIME_FORMAT_FILE)+extension);
        file.open(QIODevice::ReadWrite|QIODevice::Truncate);
        stream << formattedTxt+"\n";
    }

    file.close();
}
