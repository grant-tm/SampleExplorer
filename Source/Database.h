#ifndef DATABASE_H
#define DATABASE_H

#include <JuceHeader.h>
#include "sqlite3.h"
#include "WavFileReader.h"

//=============================================================================
// Record

class DatabaseRecord
{
public:
    DatabaseRecord();
    DatabaseRecord(juce::String);
    DatabaseRecord(juce::File);
    ~DatabaseRecord(){};

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

    int getNumRecords() const;
    bool filePathUsedAsID(juce::String filePath) const;
    juce::String getPathFromName(juce::String fileName) const;

    void insertRecord(DatabaseRecord &);
    void insertRecords(juce::Array<DatabaseRecord>);

    void scanDirectory (juce::String &directoryPath);
    DatabaseRecord makeRecordFromFile(juce::File);

    juce::Array<DatabaseRecord> searchByName(juce::String searchQuery);

private:
    sqlite3 *sqliteDatabase;
};

#endif // DATABASE_H