#include "Database.h"

DatabaseRecord::DatabaseRecord()
{
    filePath = "";
}

DatabaseRecord::DatabaseRecord(juce::String path)
{
    filePath = path;
}

DatabaseRecord::DatabaseRecord(juce::File file)
{
    filePath = file.getFullPathName();
}

DatabaseRecord::~DatabaseRecord()
{

}

DatabaseRecord Database::makeRecordFromFile(juce::File file)
{
    DatabaseRecord record;
    record.filePath = file.getFullPathName();
    record.fileName = file.getFileName();
    return record;
}

void Database::scanDirectory (juce::String &directoryPath, ScanMode scanMode, ProcessMode procMode)
{
    double startTime = juce::Time::getMillisecondCounterHiRes();
       
    juce::File file(directoryPath);

    // QUEUE

    if (!file.isDirectory())
    {
        return;
    }

    auto files = file.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, "*.wav");

    const int BATCH_SIZE = 2048;
    juce::Array<DatabaseRecord> records;
    records.resize(BATCH_SIZE);

    int totalInserted = 0;
    for (auto file : files)
    {
        records.add(makeRecordFromFile(file));
        if (records.size() >= BATCH_SIZE)
        {
            DBG("INSERT: " << BATCH_SIZE);
            records.clear();
            totalInserted += BATCH_SIZE;
        }
    }

    DBG("INSERT REMAINING: " << records.size());
    DBG("INSERTED: " << totalInserted);

    double endTime = juce::Time::getMillisecondCounterHiRes();
    double elapsedTime = endTime - startTime;
    DBG("Elapsed Timed: " << elapsedTime << " ms");
}