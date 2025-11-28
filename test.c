// SE 2XC3 Lab 7.2: Electible
// Super simple test: can we load the CSV?

#include <stdio.h>
#include <stdlib.h>
#include "include/data.h"

int main(void) {
    int count = 0;

    // Try to load the normal data file
    Course *courses = load_courses("data/courses.csv", &count);

    if (courses == NULL || count <= 0) {
        printf("Test failed: could not load courses from data/courses.csv\n");
        return 1;  // non-zero = test failed
    }

    printf("Test passed: loaded %d courses from data/courses.csv\n", count);

    // clean up
    free_courses(courses);

    return 0;  // zero = test passed
}
