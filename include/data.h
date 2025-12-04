//
// SE 2XC3 Lab 7.2: Electible - First-Year Elective Finder
// data.h
// Declares data handling functions for course records
// Developer: Khushi Ved
// Date: 2025-12-03
// Version: v2.0.0

#ifndef DATA_H
#define DATA_H

#include "filter.h"

/**
 *
 * Return code used by data handling functions
 *
 */
#define DATA_SUCCESS 0
#define DATA_ERROR_FILE_NOT_FOUND -1 // File could not be opened
#define DATA_ERROR_INVALID_FORMAT -2 // File has invalid format
#define DATA_ERROR_MEMORY -3 // Memory allocation failed
#define DATA_ERROR_VALIDATION -4 // Course validation failed
#define DATA_ERROR_WRITE -5 // Failed to write data to file


/**
 * 
 * Loads course records from a CSV file 
 * 
 * The caller is responsible for freeing the returned array using free_courses on the returned pointer
 *
 */
Course* load_courses(const char* filename, int* count); 


/**
 * 
 * Saves an array of course records to a CSV file
 * 
 * Exisiting contents would be overwritten 
 * 
 */
int save_courses(Course* courses, int count, const char* filename);

/**
 * 
 * Adds a new course record to a dynamic course array
 * 
 * The new_course is validated, if failed, the courses array and count don't change
 * and the function returns DATA_ERROR_VALIDATION
 * 
 */

int add_course(Course** courses, int* count, Course new_course);

/**
 * 
 * Validates a course record
 * 
 * The function checks that all string fields are non-empty
 * and that numeric fields are within acceptable ranges
 * 
 */

int validate_course(Course course);

/**
 * 
 * Frees the dynamic courses array
 * 
 * The helper releases the memory previously allocated for the courses array
 * If the pointer is NULL, the function does nothing
 * 
 */

void free_courses(Course* courses);

/**
 *
 * Returns a human-readable error message for a given error code
 *
 * The function returns a string describing the error corresponding to the DATA_* 
 * return codes
 * Unknown codes are mapped to "Unknown error"
 * 
 */

const char* get_data_error_message(int error_code);

/**
 * 
 * Escapes a CSV field by wrapping in double quotes and doubling internal quotes
 * 
 */

void escape_csv_field(char* dest, const char* src, int max_len);

/**
 * 
 * Parses a CSV line into fields, handling quoted fields with commas
 * 
 */

int parse_csv_line(char* line, char** fields, int max_fields);

#endif
