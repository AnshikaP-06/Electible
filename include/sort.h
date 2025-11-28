
#ifndef SORT_H
#define SORT_H

#include "filter.h"

/* Sort fields (used by UI and SortCriteria) */
typedef enum {
    SORT_BY_DIFFICULTY = 0,
    SORT_BY_WORKLOAD,
    SORT_BY_RATING,
    SORT_BY_COURSE_CODE,
    SORT_BY_TITLE
} SortField;

/* Sort order */
typedef enum {
    ASCENDING = 1,
    DESCENDING = 2
} SortOrder;

/* Sort criteria for multi-field sorting */
typedef struct {
    SortField field;
    SortOrder order;
} SortCriteria;

/* Single-field sort functions (already implemented in old files) */
void sort_by_difficulty(Course* courses, int count, int ascending);
void sort_by_workload(Course* courses, int count, int ascending);
void sort_by_rating(Course* courses, int count, int ascending);
void sort_by_course_code(Course* courses, int count, int ascending);
void sort_by_title(Course* courses, int count, int ascending);

/* Multi-criteria sort (stub for compatibility) */
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria);

#endif