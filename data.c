//
// SE 2XC3 Lab 7.2: Electible - First-Year Elective Finder
// data.c
// Implements data handling functions for Course records
// Developer: Khushi Ved
// Date: 2025-12-03
// Version: v2.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/data.h"



static void trim_whitespace(char* str);
static void remove_quotes(char* str);

/**
 * Trims any leading or trailing whitespace from a string
 * 
 * The function modifies the input memory; where if the string is entirely whitespace, it becomes an empty string.
 * 
 */
static void trim_whitespace(char* str) {
	if (str == NULL) return;

	char* start = str;
	while (isspace((unsigned char)*start)) start++;

	if (*start == '\0') {
		*str = '\0';
		return;
	}

	char* end = str + strlen(str) - 1;
	while (end > start && isspace((unsigned char)*end)) end--;

	size_t len = (end - start) + 1;
	memmove(str, start, len);
	str[len] = '\0';
}

/**
 * Removes a single pairs of surrounding double quotes from a string
 * 
 * The function identifies if the first and last characters of the string are double quotes
 * If so, it removes them by shifting the content of the string
 * Otherwise, the string is not unchanged.
 * 
 */
static void remove_quotes(char* str) {
	if (str == NULL) return;

	size_t len = strlen(str);
	if (len >= 2 && str[0] == '"' && str[len-1] == '"') {
		memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}


/**
 * Parses a CSV line into fields
 * 
 * This parser handles fields that can be wrapped in double quotes
 * Commas inside quoted fields are counted as a part of the field
 * 
 */
int parse_csv_line(char* line, char** fields, int max_fields) {
	int field_count = 0;
	int in_quotes = 0;
	char* field_start = line;
	char* p = line;

	while (*p && field_count < max_fields) {
		if (*p == '"') {
			in_quotes = !in_quotes;
		} else if (*p == ',' && !in_quotes) {
			*p = '\0';
			fields[field_count] = field_start;
			trim_whitespace(fields[field_count]);
			remove_quotes(fields[field_count]);
			field_count++;
			field_start = p + 1;
		}
		p++;
	}

	if (field_count < max_fields) {
		fields[field_count] = field_start;
		trim_whitespace(fields[field_count]);
		remove_quotes(fields[field_count]);
		field_count++;

	}

	return field_count;

}


/**
 * Escapes a string field for CSV output
 * 
 * If the source string contains commas, double quotes, or newlines, the result is wrapped 
 * in double quotes, and any internal double quotes are escaped by doubling them
 * Otherwise, the source string is copied as-is
 * 
 */
void escape_csv_field(char* dest, const char* src, int max_len) {
	int needs_quotes = 0;

	for (const char* p = src; *p; p++) {
		if (*p == ',' || *p == '"' || *p == '\n') {
			needs_quotes = 1;
			break;
		}
	}

	if (needs_quotes) {
		int dest_idx = 0;
		dest[dest_idx++] = '"';

        for (const char* p = src; *p && dest_idx < max_len - 3; p++) {
            if (*p == '"') {
                dest[dest_idx++] = '"';
            }
            dest[dest_idx++] = *p;
        }

		dest[dest_idx++] = '"';
		dest[dest_idx] = '\0';

	} else {
		strncpy(dest, src, max_len - 1);
		dest[max_len - 1] = '\0';
	}
}

/**
 * Validates that the fields of a Course struct are in valid ranges
 * 
 * This function checks that each string fields are not empty 
 * and that numeric fields are within expected bounds
 * For example the difficulty and workload between 1 and 5, rating between 0.0 and 5.0
 * 
 */
int validate_course(Course course) {
	if (strlen(course.course_code) == 0) {
		return DATA_ERROR_VALIDATION;
	}

        if (strlen(course.title) == 0) {
                return DATA_ERROR_VALIDATION;
        }

        if (strlen(course.subject_area) == 0) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.difficulty < 1 || course.difficulty > 5) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.workload < 1 || course.workload > 5) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.has_exam != 0 && course.has_exam != 1) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.has_midterm != 0 && course.has_midterm != 1) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.rating < 0.0 || course.rating > 5.0) {
                return DATA_ERROR_VALIDATION;
        }

        if (course.year_offered < 2020 || course.year_offered > 2030) {
                return DATA_ERROR_VALIDATION;
        }

	return DATA_SUCCESS;

}


/**
 * 
 * Loads Course records from a CSV file 
 * 
 * Each line in the file is parsed into a Course struct
 * Lines with insufficient fields or invalid data are skipped with a warning
 * The function returns a dynamically allocated array of Course structs
 * 
 */
Course* load_courses(const char* filename, int* count) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		*count = 0;
		return NULL;
	}

	int capacity = 10;
	Course* courses = (Course*)malloc(capacity * sizeof(Course));
	if (courses == NULL) {
		fclose(file);
		*count = 0;
		return NULL;
	}

	*count = 0 
	char line [2048];
	int line_number = 0;

	if (fgets(line, sizeof(line), file) != NULL) {
		line_number++;
	}

	while (fgets(line, sizeof(line), file) != NULL) {
		line_number++;

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0) continue;

		char* fields[10];
		int field_count = parse_csv_line(line, fields, 10);


        if (field_count < 10) {
	        fprintf(stderr, "Warning: Skipping line %d - insufficient fields\n", line_number);
        	continue;

	}

	if (*count >= capacity) {
		capacity *= 2;
		Course* temp = (Course*)realloc(courses, capacity * sizeof(Course));
		if (temp == NULL) {
                	free(courses);
                	fclose(file);
                	*count = 0;
                	return NULL;
		}

		courses = temp;
	}

	Course course;
	strncpy(course.title, fields[0], sizeof(course.title) - 1);
	course.title[sizeof(course.title) - 1] = '\0';


	strncpy(course.subject_area, fields[2], sizeof(course.subject_area) - 1);
	course.subject_area[sizeof(course.subject_area) - 1] = '\0';

	course.difficulty = atoi(fields[3]);
	course.workload = atoi(fields[4]);
	course.has_exam = atoi(fields[5]);
	course.has_midterm = atoi(fields[6]);
	course.rating = (float)atof(fields[7]);

	strncpy(course.description, fields[8], sizeof(course.description) - 1);
	course.description[sizeof(course.description) - 1] = '\0':

