CREATE TABLE Analysis (

	ID_Analysis INTEGER PRIMARY KEY,
	Complete INTEGER,
	CreationDate DATE,
	DatasetName VARCHAR(50),
	FOREIGN KEY (DatasetName) REFERENCES Dataset(DatasetName)

);

CREATE TABLE ClusterAlgorithm(

	ID_Algorithm INTEGER PRIMARY KEY,
	AlgorithmName VARCHAR(50),
	ParamValue VARCHAR(30)
);

CREATE TABLE Dataset (

	DatasetName VARCHAR(50),
	GroupName VARCHAR(50),
	CreationDate DATE,
	PRIMARY KEY (DatasetName),
	FOREIGN KEY (GroupName) REFERENCES GroupOfSubject(GroupName)
);

CREATE TABLE Dataset_Protocol (

	DatasetName VARCHAR(50),
	ProtocolName VARCHAR(50),
	PRIMARY KEY (DatasetName, ProtocolName),
	FOREIGN KEY (DatasetName) REFERENCES Dataset(DatasetName),
	FOREIGN KEY (ProtocolName) REFERENCES Protocol(ProtocolName)
);

CREATE TABLE Feature(

	ID_Feature INTEGER PRIMARY KEY,
	FeatureName VARCHAR(50),
	ParamValue VARCHAR(30),
	ProtocolName VARCHAR(50),
	FOREIGN KEY (ProtocolName) REFERENCES Protocol(ProtocolName)
);

CREATE TABLE GroupOfSubject (

	GroupName VARCHAR(50) PRIMARY KEY,
	ImageType VARCHAR(4),
	CreationDate DATE
);

CREATE TABLE Protocol(

	ProtocolName VARCHAR(50) PRIMARY KEY,
	ImageType VARCHAR(4),
	ID_Algorithm INTEGER,
	CreationDate DATE,
	FOREIGN KEY (ID_Algorithm) REFERENCES ClusterAlgorithm(ID_Algorithm)
);

CREATE TABLE Result (

	ID_Result INTEGER PRIMARY KEY,
	ID_Analysis INTEGER,
	ID_Algorithm INTEGER,
	ID_Feature INTEGER,
	SubjectName VARCHAR(50),
	FOREIGN KEY (ID_Analysis) REFERENCES Analysis(ID_Analysis),
	FOREIGN KEY (ID_Algorithm) REFERENCES ClusterAlgorithm(ID_Algorithm),
	FOREIGN KEY (ID_Feature) REFERENCES Feature(ID_Feature),
	FOREIGN KEY (SubjectName) REFERENCES Subject(SubjectName)
);

CREATE TABLE Subject (

	SubjectName VARCHAR(50) PRIMARY KEY,
	Image VARCHAR(100) NOT NULL,
	Mask VARCHAR(100),
	CreationDate DATE
);

CREATE TABLE Subject_Group (

	SubjectName VARCHAR(50),
	GroupName VARCHAR(50),
	FOREIGN KEY (SubjectName) REFERENCES Subject(SubjectName),
	FOREIGN KEY (GroupName) REFERENCES GroupOfSubject(GroupName)
);
