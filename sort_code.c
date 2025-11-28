#include <stddef.h>
#include <string.h>
#include "../include/filter.h"
#include "../include/sort.h"

static int compare_course_code(Course courses[], int i, int j, int ascending){
	int cmp = strcmp(courses[i].course_code, courses[j].course_code);
	if (cmp < 0){
		if (ascending){
			return -1;
		} else {
			return 1;
		}
	}

	return 0;
}

void sort_by_course_code(Course courses[], int count, int ascending){
	if (courses == NULL || count <= 1){
		return;
	}

	for (int i = 0; i < count -1; i++){
		int bestIndex = i;

		for (int j = i+1; j < count; j++){
			if (compare_course_code(courses, j, bestIndex, ascending) < 0){
				bestIndex = j;
			}
		}

		if (bestIndex != i){
			Course temp = courses[i];
			courses[i] = courses[bestIndex];
			courses[bestIndex] = temp;
		}
	}
}