#ifndef DATABASE_H
#define DATABASE_H

#include <JuceHeader.h>

#include "ThreadSafeFIFO.h"
#include "sqlite3.h"

enum ScanMode
{
    Linear,
    Recursive,
    NumScanModes
};

enum ProcessMode
{
    Index,
    Analyze,
    IndexAndAnalyze,
    NumProcessModes
};

//=============================================================================
// Record

class DatabaseRecord
{
public:
    DatabaseRecord();
    DatabaseRecord(juce::String);
    DatabaseRecord(juce::File);
    ~DatabaseRecord();

    juce::String filePath;
    juce::String fileName;
};

//=============================================================================
// Database

class Database
{
public:
	
    Database();
    Database(juce::String);

    int getNumRecords();

    void scanDirectory (juce::String &directoryPath, ScanMode scanMode, ProcessMode procMode);

    DatabaseRecord makeRecordFromFile(juce::File);

    void insertRecord(DatabaseRecord &);
    void insertRecords(juce::Array<DatabaseRecord>);

private:

    bool isOpen;

    sqlite3 *sqliteDatabase;

};

#endif // DATABASE_H