
#include <stddef.h>
#include "../include/filter.h"
#include "../include/sort.h"

static int compare_course_difficulty(Course courses[], int i, int j, int ascending) {
    if (courses[i].difficulty < courses[j].difficulty) {
        return ascending ? -1 : 1;
    }
    if (courses[i].difficulty > courses[j].difficulty) {
        return ascending ? 1 : -1;
    }
    return 0;
}

void sort_by_difficulty(Course courses[], int count, int ascending) {
    if (courses == NULL || count <= 1) {
        return;
    }
    for (int i = 0; i < count - 1; ++i) {
        int bestIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (compare_course_difficulty(courses, j, bestIndex, ascending) < 0) {
                bestIndex = j;
            }
        }
        if (bestIndex != i) {
            Course tmp = courses[i];
            courses[i] = courses[bestIndex];
            courses[bestIndex] = tmp;
        }
    }
}