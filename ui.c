//
//SFWRENG 2XC3 TEAM PROJECT: Electible
//Module D: User Interface and Integration
// Yasmine Abdelmalek, 400560661

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/filter.h"
#include "../include/sort.h"
#include "../include/data.h"


//ANSI color codes for terminal output (found off google)
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

//Clear input buffer
void clear_input_buffer(void){
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}

//seperator line
void print_seperator(void){
    printf("-----------------------------------------------------------\n");
}

//pause and wait for the user
void pause_for_user(void){
    printf("\nPress ENTER to continue...");
    getchar();
}

//get integer input WITHIN RANGE
int get_int_input(const char* prompt, int min, int max){
    int value;
    int valid=1;

     while (!valid){
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clear_input_buffer();
            if (value >= min && value <= max) {
                valid =0;
            } else {
                printf("Input is invalid. Please enter a value between %d and %d.\n", min, max);
            }
        } else {
            clear_input_buffer();
            printf("Input is invalid. Please enter a number.\n");
        }
    }
    return value;
}

//basic string input
void get_string_input(const char* prompt, char* buffer, int max_length){
    printf("%s",prompt);
    if (fgets(buffer,max_length,stdin) != NULL){
        buffer[strcspn(buffer,"\n")]='\0';
    }
}

//display menu
void display_menu(void){
    print_separator();
    printf("%s%s===ELECTIBLE: McMaster First-Year Elective Finder ===%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    print_separator();
    printf("\n");
    printf("1.Browse All Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("2.Filter Courses (COMING SOON)\n", COLOR_GREEN, COLOR_RESET);
    printf("3.Sort Courses (COMING SOON)\n",COLOR_GREEN, COLOR_RESET);
    printf("4.Add New Course (COMING SOON)\n",COLOR_GREEN, COLOR_RESET);
    printf("5.View Recommendations (COMING SOON)\n", COLOR_GREEN, COLOR_RESET);
    printf("6.Help\n",COLOR_GREEN, COLOR_RESET);
    printf("7.Exit\n", COLOR_GREEN, COLOR_RESET);
    printf("\n");
}

static void display_course_row(Course course, int index) {
    printf("%-4d %-10s %-40s %4d/5  %4d/5  %s     %s         %.1f/5\n",
           index +1,
           course.course_code,
           course.title,
           course.difficulty,
           course.workload,
           course.has_exam ? "Yes" : "No ",
           course.has_midterm ? "Yes" : "No ",
           course.rating);
}

//display list of courses
void display_courses(Course* courses,int count){
    if (courses==NULL ||count <= 0){
        printf("\n%sNo courses to display.%s\n");
        return;
    }
    printf("\n%s%sFound %d courses:%s\n\n", COLOR_BOLD, COLOR_BLUE, count, COLOR_RESET);
    printf("%-4s %-10s %-40s %-6s %-6s %-6s %-9s %-6s\n",
           "#", "Code","Title","Diff","Work","Exam","Midterm", "Rating");
    print_seperator();

    for (int i = 0; i < count; i++) {
        display_course_row(courses[i], i);
    }

    printf("\n");
}


//display info for a single course
void display_course_detail(Course course){
    print_separator();
    printf("%s%s%s%s\n",COLOR_BOLD,COLOR_CYAN,course.title,COLOR_RESET);
    printf("Course Code:     %s\n", course.course_code);
    printf("Subject Area:    %s\n",course.subject_area);
    printf("Difficulty:      %d/5\n",course.difficulty);
    printf("Workload:        %d/5\n", course.workload);
    printf("Has Exam:        %s\n",course.has_exam ? "Yes" : "No");
    printf("Has Midterm:     %s\n",course.has_midterm ? "Yes" : "No");
    printf("Rating:          %.1f/5\n", course.rating);
    printf("\nDescription:\n%s\n",course.description);
    print_separator();
}

//get filter preferences from user (stubfor now)
FilterCriteria get_filter_preferences(void){
    printf("\nFilter Courses: not implemented yet.\n");
    FilterCriteria criteria =create_default_filter_criteria();
    return criteria;
}


//get sort preferences from user (stub)
void get_sort_preferences(SortCriteria** criteria, int* num_criteria) {
    printf("\nSort Courses: not implemented yet.\n");
    *criteria =NULL;
    *num_criteria = 0;
}

//get new course input from user (stub)
Course get_new_course_input(void){
    Course c;
    strcpy(c.title, "Placeholder Course");
    strcpy(c.course_code, "XXXX 1XX3");
    strcpy(c.subject_area, "Placeholder");
    c.difficulty = 3;
    c.workload = 3;
    c.has_exam = 0;
    c.has_midterm = 0;
    c.rating = 3.0f;
    strcpy(c.description, "This is a placeholder course (adding courses is not implemented yet).");
    c.year_offered=2025;
    return c;
}

//display help info (so basic rn)
void display_help(void){
    print_separator();
    printf("%s%s----HELP----%s\n\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("%sWelcome to Electible!%s\n\n", COLOR_BOLD, COLOR_RESET);
    printf("This app will help Mcmaster first year eng students to find and explore elective based on their preferences.\n\n");
     printf("- Browse All Courses: %sImplemented%s\n", COLOR_GREEN, COLOR_RESET);
    printf("- Filter, Sort, Add, Recommendations: %sPlanned%s\n\n", COLOR_YELLOW, COLOR_RESET);
    print_seperator();
}

//display recommended courses (stub)
void display_recommendations(Course* courses, int count) {
    (void)courses;
    (void)count;
    printf("\nRecommendations are not implemented yet.\n");
}


//main UI handler
void handle_user_interaction(Course** courses, int* count, const char* filename) {
    (void)filename;

    int running =1;
    Course* working_set=*courses;
    int working_count= *count;

    while (running){
        display_menu();
        int choice=get_int_input("Enter choice (1-7): ", 1, 7);

        switch (choice){
            case MENU_BROWSE:{
                display_courses(working_set,working_count);
                pause_for_user();
                break;
            }

            case MENU_FILTER:{
                printf("\nFilter feature not implemented yet.\n");
                pause_for_user();
                break;
            }

            case MENU_SORT:{
                printf("\nSort feature not implemented yet.\n");
                pause_for_user();
                break;
            }

            case MENU_ADD:{
                printf("\nAdd New Course feature not implemented yet.\n");
                pause_for_user();
                break;
            }

            case MENU_RECOMMENDATIONS:{
                display_recommendations(*courses, *count);
                pause_for_user();
                break;
            }

            case MENU_HELP:{
                display_help();
                pause_for_user();
                break;
            }

            case MENU_EXIT:{
                printf("\nThank you for using Electible!\n");
                running = 0;
                break;
            }
        }
    }
}