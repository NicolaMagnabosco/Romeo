#include "adatabase.h"

using Romeo::Model::Util::DAO::ADatabase;

ADatabase::ADatabase() : dbName("Romeo.sqlite")
{

    checkPathExistsFromHome(Utils::SAVING_FOLDER_PATH);

    connection.setDatabaseName(Utils::SAVING_FOLDER_PATH+"/"+dbName);
    if (!connection.isOpen())
        connect();
}

bool ADatabase::connect()
{

    connection.open();
    QSqlQuery query_foreign_key("PRAGMA foreign_keys=on", connection);
    if(connection.tables().isEmpty()) {
        QStringList queryes = getCreationSchema();

        for(int i=0; i<queryes.size(); ++i) {
            QSqlQuery query;
            query.exec(queryes.at(i));
        }
    }
    return connection.isOpen();
}

bool ADatabase::disconnect()
{

    connection.close();
    QSqlDatabase::removeDatabase(Utils::SAVING_FOLDER_PATH+"/"+dbName);
    return !(connection.isOpen());
}

QSqlDatabase* ADatabase::getConnection()
{

    return const_cast<QSqlDatabase*>(&connection);
}

QStringList ADatabase::getCreationSchema() const
{
    QStringList ret;

    ret.append("DROP TABLE IF EXISTS Subject");
    ret.append("DROP TABLE IF EXISTS GroupOfSubject");
    ret.append("DROP TABLE IF EXISTS Subject_Group");
    ret.append("DROP TABLE IF EXISTS Analysis");
    ret.append("DROP TABLE IF EXISTS ClusterAlgorithm");
    ret.append("DROP TABLE IF EXISTS Dataset");
    ret.append("DROP TABLE IF EXISTS Protocol");
    ret.append("DROP TABLE IF EXISTS Dataset_Protocol");
    ret.append("DROP TABLE IF EXISTS Feature");

    ret.append("CREATE TABLE Analysis ("
                   "\n\tID_Analysis INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "\n\tComplete INTEGER DEFAULT 0,"
                   "\n\tCreationDate DATE,"
                   "\n\tDatasetName VARCHAR(200),"
                   "\n\tFOREIGN KEY (DatasetName) REFERENCES Dataset(DatasetName) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE ClusterAlgorithm("
                   "\n\tID_Algorithm INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "\n\tAlgorithmName VARCHAR(200),"
                   "\n\tParamValue VARCHAR(200)"
               "\n)");
    ret.append("CREATE TABLE Dataset ("
                   "\n\tDatasetName VARCHAR(200),"
                   "\n\tGroupName VARCHAR(200),"
                   "\n\tCreationDate DATE,"
                   "\n\tPRIMARY KEY (DatasetName),"
                   "\n\tFOREIGN KEY (GroupName) REFERENCES GroupOfSubject(GroupName) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE Dataset_Protocol ( "
                   "\n\tDatasetName VARCHAR(200),"
                   "\n\tProtocolName VARCHAR(200),"
                   "\n\tPRIMARY KEY (DatasetName, ProtocolName),"
                   "\n\tFOREIGN KEY (DatasetName) REFERENCES Dataset(DatasetName) ON DELETE CASCADE,"
                   "\n\tFOREIGN KEY (ProtocolName) REFERENCES Protocol(ProtocolName) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE Feature("
                   "\n\tID_Feature INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "\n\tFeatureName VARCHAR(200),"
                   "\n\tParamValue VARCHAR(200),"
                   "\n\tProtocolName VARCHAR(200),"
                   "\n\tFOREIGN KEY (ProtocolName) REFERENCES Protocol(ProtocolName) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE GroupOfSubject ("
                   "\n\tGroupName VARCHAR(200) PRIMARY KEY,"
                   "\n\tImageType VARCHAR(10),"
                   "\n\tCreationDate DATE"
               "\n)");
    ret.append("CREATE TABLE Protocol("
                   "\n\tProtocolName VARCHAR(200) PRIMARY KEY,"
                   "\n\tImageType VARCHAR(10),"
                   "\n\tID_Algorithm INTEGER,"
                   "\n\tCreationDate DATE,"
                   "\n\tFOREIGN KEY (ID_Algorithm) REFERENCES ClusterAlgorithm(ID_Algorithm) ON DELETE SET NULL"
               "\n)");
    ret.append("CREATE TABLE Subject ("
                   "\n\tSubjectName VARCHAR(200) PRIMARY KEY,"
                   "\n\tImage VARCHAR(200) NOT NULL,"
                   "\n\tMask VARCHAR(200),"
                   "\n\tImageType VARCHAR(10) NOT NULL,"
                   "\n\tCreationDate DATE"
               "\n)");
    ret.append("CREATE TABLE Subject_Group ("
                   "\n\tSubjectName VARCHAR(200),"
                   "\n\tGroupName VARCHAR(200),"
                   "\n\tPRIMARY KEY (SubjectName, GroupName),"
                   "\n\tFOREIGN KEY (SubjectName) REFERENCES Subject(SubjectName) ON DELETE CASCADE,"
                   "\n\tFOREIGN KEY (GroupName) REFERENCES GroupOfSubject(GroupName) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE Analysis_Subject ("
                   "\n\tID_Analysis INTEGER,"
                   "\n\tSubjectName VARCHAR(200),"
                   "\n\tPRIMARY KEY (SubjectName, ID_Analysis),"
                   "\n\tFOREIGN KEY (SubjectName) REFERENCES Subject(SubjectName) ON DELETE CASCADE,"
                   "\n\tFOREIGN KEY (ID_Analysis) REFERENCES Analysis(ID_Analysis) ON DELETE CASCADE"
               "\n)");
    ret.append("CREATE TABLE Analysis_Features_Save_Show ("
                   "\n\tID INTEGER PRIMARY KEY,"
                   "\n\tID_Analysis INTEGER,"
                   "\n\tID_Feature INTEGER,"
                   "\n\tSave INTEGER DEFAULT 0,"
                   "\n\tShow INTEGER DEFAULT 0,"
                   "\n\tFOREIGN KEY (ID_Feature) REFERENCES Feature(ID_Feature) ON DELETE CASCADE,"
                   "\n\tFOREIGN KEY (ID_Analysis) REFERENCES Analysis(ID_Analysis) ON DELETE CASCADE"
               "\n)");

    return ret;
}

ADatabase::~ADatabase()
{
}

QSqlDatabase ADatabase::connection = QSqlDatabase::addDatabase("QSQLITE");
