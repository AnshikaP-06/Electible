/*
 * sort.h
 * Declares sorting interfaces of course arrays, including single field sorts and a stub for multi-criteria sorting (for future extension)
 * Author: Anshika Patel 
 * Date: 2025-12-03
 * version: v2.0.0
*/

#ifndef SORT_H
#define SORT_H

#include "filter.h"

/* 
 * SortField
 * Enumerates the fields that can be used as sort keys 
 * Values are used by the UI and SortCriteria to select sorting behaviour
*/
typedef enum {
    SORT_BY_DIFFICULTY = 0,
    SORT_BY_WORKLOAD,
    SORT_BY_RATING,
    SORT_BY_COURSE_CODE,
    SORT_BY_TITLE
} SortField;

/* 
 * SortOrder
 * Indicates desired sort order 
 */
typedef enum {
    ASCENDING = 1,
    DESCENDING = 2
} SortOrder;

/* 
 * SortCriteria
 * represents one sort directive (field + order) used for multi-criteria sorting 
 * e.g. {sort_by_rating, descending} 
*/
typedef struct {
    SortField field;
    SortOrder order;
} SortCriteria;

/* 
 * sort_by_difficulty 
 * sorts an array of courses by the difficulty field 
 * Paramters: 
 *      - courses: pointer to the first element in the course array 
 *      - count; number of course elements 
 *      - ascending: 1 for ascending order, 0 for descending
*/
void sort_by_difficulty(Course* courses, int count, int ascending);

/* 
 * sort_by_workload 
 * sorts an array of courses by the workload field 
 * Paramters: 
 *      - courses: pointer to the first element in the course array 
 *      - count; number of course elements 
 *      - ascending: 1 for ascending order, 0 for descending
*/
void sort_by_workload(Course* courses, int count, int ascending);

/* 
 * sort_by_rating
 * sorts an array of courses by the rating field (float)
 * Paramters: 
 *      - courses: pointer to the first element in the course array 
 *      - count; number of course elements 
 *      - ascending: 1 for ascending order, 0 for descending
*/
void sort_by_rating(Course* courses, int count, int ascending);

/* 
 * sort_by_course_code
 * sorts an array of courses lexicographically by course_code 
 * Paramters: 
 *      - courses: pointer to the first element in the course array 
 *      - count; number of course elements 
 *      - ascending: 1 for ascending order (A to Z), 0 for descending (Z to A)
*/
void sort_by_course_code(Course* courses, int count, int ascending);

/* 
 * sort_by_title
 * sorts an array of courses lexicographically by title 
 * Paramters: 
 *      - courses: pointer to the first element in the course array 
 *      - count; number of course elements 
 *      - ascending: 1 for ascending order (A to Z), 0 for descending (Z to A)
*/
void sort_by_title(Course* courses, int count, int ascending);

/* 
 * sort_multi_criteria
 * sorts courses using one or more SortCriteria
 * Parameters: 
 *      - courses: pointer to the first element in the course array 
 *      - count: number of course elements 
 *      - criteria: pointer to an array of SortCriteria (at least one element)
 *      - num_criteria: number of criteria provided 
*/
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria);

#endif