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

//-----------------------------------------------------------------------------

Database::Database() 
{
    sqliteDatabase = nullptr;
    isOpen = false;

    const auto flags = SQLITE_OPEN_READWRITE |
        SQLITE_OPEN_CREATE |
        SQLITE_OPEN_FULLMUTEX;

    if (sqlite3_open_v2("SampleExplorerDatabase", &sqliteDatabase, flags, NULL) != SQLITE_OK)
    {
        DBG("Database::Database: Cannot open database.");
        sqliteDatabase = nullptr;
        jassert(false);
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS audio_files"\
        "("\
        "filePath TEXT PRIMARY KEY,"\
        "fileName TEXT NOT NULL"\
        ");";

    char *err_msg = nullptr;
    if (sqlite3_exec(sqliteDatabase, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
        sqlite3_free(err_msg);
        DBG("Database::Database: Error creating table.");
        jassert(false);
    }
    else {
        DBG("Database::Database: Table created successfully!");
        isOpen = true;
    }

}

int Database::getNumRecords() 
{
    // prepare statement to select the count of all rows in the table
    sqlite3_stmt *stmt;
    char *sql = "SELECT COUNT(*) FROM audio_files";
    if (sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        DBG("Database::num_rows: Failed to prepare statement.\n");
        jassert(false);
    }

    // run select statement and return result if successful
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int row_count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return row_count;
    }
    else {
        sqlite3_finalize(stmt);
        DBG("Database::num_rows: Failed to execute sql statement.\n");
        jassert(false);
    }

    jassert(false);
    return -1;
}

bool Database::filePathUsedAsID(juce::String filePath)
{
    // prepare the SQL statement to select 1 entry with matching filePath
    sqlite3_stmt *stmt;
    char *sql = "SELECT 1 FROM audio_files WHERE filePath = ? LIMIT 1;";
    if (sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        DBG("Database::filePathUsedAsID: Failed to prepare SELECT statement.");
        jassert(false);
        return false;
    }

    // bind the filePath parameter to the select statment
    if (sqlite3_bind_text(stmt, 1, filePath.toUTF8(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
    {
        DBG("Database:filePathUsedAsID: Failed to bind values.");
        jassert(false);
        return false;
    }

    // execute the SQL statement and return result
    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

DatabaseRecord Database::makeRecordFromFile(juce::File file)
{
    DatabaseRecord record;
    record.filePath = file.getFullPathName();
    record.fileName = file.getFileName();
    return record;
}

void Database::insertRecord(DatabaseRecord &record)
{
    // create statement to insert all members of explorer file struct
    const char *sql = "INSERT OR IGNORE INTO audio_files ("\
        "filePath,"\
        "fileName"\
        ") VALUES (?, ?)";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        DBG("Database::insertRecord: Error preparing statement.\n");
        jassert(false);
    }

    // bind the FileRecord data to the INSERT statement arguments
    sqlite3_bind_text(stmt, 1, record.filePath.toUTF8(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.fileName.toUTF8(), -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        DBG("Database::insertRecord: Error inserting data.\n");
        jassert(false);
    }

    // reset the statement for reuse
    sqlite3_reset(stmt); 
}

void Database::insertRecords(juce::Array<DatabaseRecord> records)
{
    // create statement to insert all members of explorer file struct
    const char *sql = "INSERT OR IGNORE INTO audio_files ("\
        "filePath,"\
        "fileName"\
        ") VALUES (?, ?)";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        DBG("Database::insertRecords: Error preparing statement.\n");
        jassert(false);
    }

    // insert files in a single transaction
    sqlite3_exec(sqliteDatabase, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    for (const auto &record : records) {

        sqlite3_bind_text(stmt, 1, record.filePath.toUTF8(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, record.fileName.toUTF8(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            DBG("Database::insertRecords: Error inserting data.\n");
            jassert(false);
        }
        sqlite3_reset(stmt);
    }

    sqlite3_exec(sqliteDatabase, "COMMIT;", nullptr, nullptr, nullptr);
    sqlite3_finalize(stmt);
}

void Database::scanDirectory (juce::String &directoryPath, ScanMode scanMode, ProcessMode procMode)
{
    const double startTime = juce::Time::getMillisecondCounterHiRes();   

    juce::File scanRoot(directoryPath);
    const auto files = scanRoot.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, "*.wav");

    const int batchSize = 2048;
    juce::Array<DatabaseRecord> records;
    records.resize(batchSize);
    
    for (const auto file : files)
    {
        if (filePathUsedAsID(file.getFullPathName()))
        {
            continue;
        }

        records.add(makeRecordFromFile(file));
        if (records.size() >= batchSize)
        {
            insertRecords(records);
            records.clear();
        }
    }

    insertRecords(records);

    const double endTime = juce::Time::getMillisecondCounterHiRes();
    const double elapsedTime = endTime - startTime;
    DBG("Elapsed Timed: " << elapsedTime << " ms");
    DBG("Database Size: " << getNumRecords());

}