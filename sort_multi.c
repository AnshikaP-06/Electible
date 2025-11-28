#include <stddef.h>
#include "../include/sort.h"

/* Simple stub: just sort by the first criterion */
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria) {
    if (courses == NULL || count <= 1 || criteria == NULL || num_criteria <= 0) {
        return;
    }

    int ascending = (criteria[0].order == ASCENDING) ? 1 : 0;

    switch (criteria[0].field) {
        case SORT_BY_DIFFICULTY:
            sort_by_difficulty(courses, count, ascending);
            break;
        case SORT_BY_WORKLOAD:
            sort_by_workload(courses, count, ascending);
            break;
        case SORT_BY_RATING:
            sort_by_rating(courses, count, ascending);
            break;
        case SORT_BY_COURSE_CODE:
            sort_by_course_code(courses, count, ascending);
            break;
        case SORT_BY_TITLE:
            sort_by_title(courses, count, ascending);
            break;
    }
}
