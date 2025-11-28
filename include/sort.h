#ifndef SORT_H
#define SORT_H

#include "filter.h"

void sort_by_difficulty(Course* courses, int count, int ascending);
void sort_by_workload(Course* courses, int count, int ascending);
void sort_by_rating(Course* courses, int count, int ascending);
void sort_by_course_code(Course* courses, int count, int ascending);
void sort_by_title(Course* courses, int count, int ascending);

#endif