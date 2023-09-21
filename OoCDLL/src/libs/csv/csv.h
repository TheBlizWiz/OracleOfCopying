/* (c) 2019 Jan Doczy
 * This code is licensed under MIT license (see LICENSE.txt for details) */

/* simple and fast CSV reader:
 * 1. Open CSV file by calling CsvOpen("filename.csv")
 * 2. Read CSV row by calling CsvReadNextRow(csv_handle)
 * 3. Read single CSV line column by calling CsvReadNextCol(returned_row_str, csv_handle)
 */

#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#ifdef OOCDLL_EXPORTS
#define CSV_API_DLLINCLUDE __declspec(dllexport)
#else
#define CSV_API_DLLINCLUDE __declspec(dllimport)
#endif


/* pointer to private handle structure */
CSV_API_DLLINCLUDE typedef struct CsvHandle_ *CsvHandle;

/**
 * openes csv file
 * @filename: pathname of the file
 * @return: csv handle
 * @notes: you should call CsvClose() to release resources
 */
CSV_API_DLLINCLUDE CsvHandle CsvOpen(const wchar_t *filename);
CSV_API_DLLINCLUDE CsvHandle CsvOpen2(const wchar_t *filename, char delim, char quote, char escape);

/**
 * closes csv handle, releasing all resources
 * @handle: csv handle
 */
CSV_API_DLLINCLUDE void CsvClose(CsvHandle handle);

/**
 * reads (first / next) line of csv file
 * @handle: csv handle
 */
CSV_API_DLLINCLUDE char *CsvReadNextRow(CsvHandle handle);

/**
 * get column of file
 * @row: csv row (you can use CsvReadNextRow() to parse next line)
 * @context: handle returned by CsvOpen() or CsvOpen2()
 */
CSV_API_DLLINCLUDE const char *CsvReadNextCol(char *row, CsvHandle handle);

#endif