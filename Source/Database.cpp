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

//-----------------------------------------------------------------------------
// CONSTRUCTORS

Database::Database() 
{
    sqliteDatabase = nullptr;

    const auto flags = 
        SQLITE_OPEN_READWRITE |
        SQLITE_OPEN_CREATE |
        SQLITE_OPEN_FULLMUTEX;

    int sqliteResult = sqlite3_open_v2("SampleExplorerDatabase", &sqliteDatabase, flags, NULL);
    jassert(sqliteResult == SQLITE_OK);
    
    // Set the encoding to UTF-8
    const char *pragmaSql = "PRAGMA encoding = \"UTF-16\";";
    sqlite3_stmt *pragmaStmt;
    sqliteResult = sqlite3_prepare_v2(sqliteDatabase, pragmaSql, -1, &pragmaStmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);
    jassert(sqlite3_step(pragmaStmt) == SQLITE_DONE);

    const char *sql = "CREATE TABLE IF NOT EXISTS audio_files ("\
        "filePath TEXT16 PRIMARY KEY,"\
        "fileName TEXT16 NOT NULL"\
        ");";

    char *err_msg = nullptr;
    sqliteResult = sqlite3_exec(sqliteDatabase, sql, nullptr, nullptr, &err_msg);
    if (sqliteResult != SQLITE_OK)
    {
        sqlite3_free(err_msg);
        jassert(false);
    }
}

//=============================================================================
// GETTERS

int Database::getNumRecords() const
{
    // prepare statement to select the count of all rows in the table
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM audio_files";
    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);
    jassert(sqlite3_step(stmt) == SQLITE_ROW);

    // run select statement and return result if successful
    const int row_count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return row_count;
}

bool Database::filePathUsedAsID(juce::String filePath) const
{
    // prepare the SQL statement to select 1 entry with matching filePath
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1 FROM audio_files WHERE filePath = ? LIMIT 1;";
    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);

    // bind the filePath parameter to the select statment
    sqliteResult = sqlite3_bind_text16(stmt, 1, filePath.toUTF16(), -1, SQLITE_TRANSIENT);
    jassert(sqliteResult == SQLITE_OK);

    // execute the SQL statement and return result
    const bool fileExists = (sqlite3_step(stmt) == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return fileExists;
}

//=============================================================================
// INSERT

void Database::insertRecord(DatabaseRecord &record)
{
    // create statement to insert all members of explorer file struct
    const char *sql = "INSERT OR IGNORE INTO audio_files ("\
        "filePath,"\
        "fileName"\
        ") VALUES (?, ?)";
    sqlite3_stmt *stmt = nullptr;
    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);

    // bind the FileRecord data to the INSERT statement arguments
    sqlite3_bind_text16(stmt, 1, record.filePath.toUTF16(), -1, SQLITE_STATIC);
    sqlite3_bind_text16(stmt, 2, record.fileName.toUTF16(), -1, SQLITE_STATIC);
    
    sqliteResult = sqlite3_step(stmt);
    jassert(sqliteResult == SQLITE_DONE);
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
    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);

    // insert files in a single transaction
    sqlite3_exec(sqliteDatabase, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    for (const auto &record : records)
    {
        sqlite3_bind_text16(stmt, 1, record.filePath.toUTF16(), -1, SQLITE_STATIC);
        sqlite3_bind_text16(stmt, 2, record.fileName.toUTF16(), -1, SQLITE_STATIC);

        sqliteResult = sqlite3_step(stmt);
        jassert(sqliteResult == SQLITE_DONE);
        sqlite3_reset(stmt);
    }
    sqlite3_exec(sqliteDatabase, "COMMIT;", nullptr, nullptr, nullptr);
    sqlite3_finalize(stmt);
}

//=============================================================================
// SCAN

void Database::scanDirectory (juce::String &directoryPath)
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
}

DatabaseRecord Database::makeRecordFromFile(juce::File file)
{
    DatabaseRecord record;
    record.filePath = file.getFullPathName();
    record.fileName = file.getFileName();
    return record;
}

//=============================================================================
// GET FILES LIKE NAME

juce::Array<DatabaseRecord> Database::searchByName(juce::String searchQuery)
{

    // prepare sql statement
    sqlite3_stmt *stmt;
    const char *sql;
    // fetch records matching the search query
    sql = "SELECT filePath, fileName FROM audio_files WHERE fileName LIKE ? ORDER BY fileName;";

    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);

    // bind the search query with wildcard characters for pattern matching
    juce::String searchPattern("%");
    searchPattern.append(searchQuery, 64);
    searchPattern.append("%", 1);
    sqliteResult = sqlite3_bind_text16(stmt, 1, searchPattern.toUTF16(), -1, SQLITE_STATIC);
    jassert(sqliteResult == SQLITE_OK);


    // Execute the statement and process the results
    juce::Array<DatabaseRecord> records;
    int numFound = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        DatabaseRecord record;

        const void *filePathRawData = sqlite3_column_text16(stmt, 0);
        const void *fileNameRawData = sqlite3_column_text16(stmt, 1);

        auto filePathUTF16 = static_cast<const juce::CharPointer_UTF16::CharType *>(filePathRawData);
        auto fileNameUTF16 = static_cast<const juce::CharPointer_UTF16::CharType *>(fileNameRawData);

        juce::String filePath = (filePathUTF16 != nullptr) ? juce::String(filePathUTF16) : "NULL_PATH";
        juce::String fileName = (fileNameUTF16 != nullptr) ? juce::String(fileNameUTF16) : "NULL_NAME";

        record.filePath = filePath;
        record.fileName = fileName;

        if (filePath != "" && fileName != "")
        {
            records.add(record);
            ++numFound;
        }
    }

    sqlite3_finalize(stmt);
    DBG("RESULTS FOUND: " << numFound);
    return records;
}

//=============================================================================

juce::String Database::getPathFromName(juce::String fileName) const
{
    // prepare sql statement
    const char *sql = "SELECT filePath FROM audio_files WHERE fileName = ? ";
    sqlite3_stmt *stmt;
    int sqliteResult = sqlite3_prepare_v2(sqliteDatabase, sql, -1, &stmt, nullptr);
    jassert(sqliteResult == SQLITE_OK);
    
    sqliteResult = sqlite3_bind_text16(stmt, 1, fileName.toUTF16(), -1, SQLITE_STATIC);
    jassert(sqliteResult == SQLITE_OK);

    juce::String returnPath("");
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const void *filePathRawData = sqlite3_column_text16(stmt, 0);
        auto filePathUTF16 = static_cast<const juce::CharPointer_UTF16::CharType *>(filePathRawData);
        returnPath = (filePathUTF16 != nullptr) ? juce::String(filePathUTF16) : "NULL_PATH";
    }
    sqlite3_finalize(stmt);
    return returnPath;
}