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

/*disable colors on windows by default(if the colours dont work I'll uncomment)*/
/*#define COLOR_RESET ""
#define COLOR_BOLD ""
#define COLOR_CYAN ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_BLUE ""*/

//Clear input buffer
void clear_input_buffer(void){
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}

//seperator line
void print_seperator(void){
    printf("-----------------------------------------------------------\n");
}

//pause and wait for user
void pause_for_user(void){
    printf("\nPress ENTER to continue...");
    getchar();
}

//get integer input WITHIN RANGE
int get_int_input(const char* prompt, int min, int max){
    int value;
    int valid=0;

     while (!valid){
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clear_input_buffer();
            if (value >= min && value <= max) {
                valid =1;
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

//get float input within the range
float get_float_input (const char* prompt, float min, float max){
    float value;
    int valid =0;

    while (!valid){
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            clear_input_buffer();
            if (value >= min && value <= max) {
                valid =1;
            } else {
                printf("Input is invalid. Please enter a value between %.1f and %.1f.\n", min, max);
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
        //removing newline
        buffer[strcspn(buffer,"\n")]='\0';
    }
}

//display main menu
void display_menu(void){
    print_separator();
    printf("%s%s---ELECTIBLE: McMaster First-Year Elective Finder ---%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    print_separator();
    printf("\n");
    printf("%s1.%s Browse All Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s2.%s Filter Courses (COMING SOON)\n", COLOR_GREEN, COLOR_RESET);
    printf("%s3.%s Sort Courses (COMING SOON)\n",COLOR_GREEN, COLOR_RESET);
    printf("%s4.%s Add New Course (COMING SOON)\n",COLOR_GREEN, COLOR_RESET);
    printf("%s5.%s View Recommendations (COMING SOON)\n", COLOR_GREEN, COLOR_RESET);
    printf("%s6.%s Help\n",COLOR_GREEN, COLOR_RESET);
    printf("%s7.%s Exit\n", COLOR_GREEN, COLOR_RESET);
    printf("\n");
}

//display course in tablen r0w format
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

//display list of courses in table
void display_courses(Course* courses,int count){
    if (courses==NULL ||count <= 0){
        printf("\n%sNo courses to display.%s\n", COLOR_YELLOW, COLOR_RESET);
        return;
    }
    printf("\n%s%sFound %d courses:%s\n\n", COLOR_BOLD, COLOR_BLUE, count, COLOR_RESET);
    //Table  header
    printf("%-4s %-10s %-40s %-6s %-6s %-6s %-9s %-6s\n",
           "#", "Code","Title","Diff","Work","Exam","Midterm", "Rating");
    print_seperator();

//display each course
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
    FilterCriteria critera=create_default_filter_criteria();

    printf("\n%s%S------Filter Courses------%s\n", COLOR_BOLD, COLOR_CYAN,COLOR_RESET);
    printf("LEave filters blank or enter -1 to skip.\n\n");

    //subject area filter
    printf("FIlter by subject area?(e.g., Math, Business,etc.)\n");
    get_string_input("Subject area (ENTER to skip): ", criteria.subject_area, sizeof(criteria.subject_area));

    //dificulty
    printf("\nFilter by difficulty?(1-5)\n");
    char response[10];
    get_string_input("Minimum difficulty (ENTER to skip): ", response, sizeof(response));
    if (strlen(response)>0){
        criteria.min_difficulty=atoi(response);
        if (criteria.min_difficulty<1 ||criteria.min_difficulty > 5) {
            criteria.min_difficulty = -1;
        }
    }
    get_string_input("Maximum difficulty (ENTER to skip): ", response, sizeof(response));
    if (strlen(response)>0){
        criteria.min_difficulty=atoi(response);
        if (criteria.min_difficulty<1||criteria.min_difficulty > 5) {
            criteria.min_difficulty = -1;
        }
    }

    //workload filter//
    printf("\nFilter by workload?(1-5)\n");
    char response[10];
    get_string_input("Minimum workloda (ENTER to skip): ", response, sizeof(response));
    if (strlen(response)>0){
        criteria.min_workload=atoi(response);
        if (criteria.min_workload<1 ||criteria.min_workload > 5) {
            criteria.min_workload = -1;
        }
    }
    get_string_input("Maximum workload (ENTER to skip): ", response, sizeof(response));
    if (strlen(response)>0){
        criteria.max_workload=atoi(response);
        if (criteria.max_workload<1 ||criteria.max_workload >5) {
            criteria.max_workload = -1;
        }
    }

//exam filter
printf("\nFilter by exam presence?\n");
printf("1. Courses with exams\n");
printf("2. Courses without exams\n");
printf("3. No preference\n");
int exam_choice =get_int_input("Choice: ",1,3);
if (exam_choice ==1){
    criteria.has.exam=1;
} else if (exam_choice =2){
    criteria.has_exam=0;
}

//midterm filter
printf("\nFilter by midterm presence?\n");
printf("1. Courses with midterms\n");
printf("2. Courses without midterms\n");
printf("3. No preference\n");
int midterm_choice = get_int_input("Choice: ",1,3);
if (midterm_chpice =-1){
    criter.has_midterm=1;
}else if (midterm_choice==2){
    criter.has_midterm=0;
}

//ratinf filter
printf("\nFilter by minimum rating? (0.0-5.0)\n");
    get_string_input("Minimum rating (ENTER to skip):", response, sizeof(response));
    if (strlen(response) >0){
        criteria.min_rating = (float)atof(response);
        if (criteria.min_rating <0.0f || criteria.min_rating > 5.0f) {
            criteria.min_rating =-1.0f;
        }
    }
    return criteria;
}

//get sort preferences from user (stub)
void get_sort_preferences(SortCriteria** criteria, int* num_criteria) {
    printf("\n%s%s---Sort Courses---%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("Select sort field:\n");
    printf("1.Difficulty\n");
    printf("2.Workload\n");
    printf("3.Rating\n");
    printf("4.Course Code\n");
    printf("5.Title\n");

    int field_choice -git_int_input("Sort byL ",1,5);

    printf("\nSort order:\n");
    printf("1.Ascending\n");
    printf("2.Descending\n");
    int order_choice=get_int_input("Order: ", 1, 2);

    *criteria =(SortCriteria*)malloc(sizeof(SortCriteria));
    if (*criteria == NULL){
        *num_criteria = 0;
        return;
    }

    (*criteria)[0].field=(SortField)(field_choice - 1);
    (*criteria)[0].order=(order_choice ==1) ? ASCENDING:DESCENDING;
    *num_criteria=1
}

//get new course input from user (stub) MAKE SURE YOU ADD THE LOGUC LATER
Course get_new_course_input(void){
    Course course;
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
    printf("1. Browse All Courses: View complete list of available elctives\n");
    printf("2. Filter Courses: Narrow down courses by subject, difficulty, workload, etc.\n");
    printf("3. Sort Courses: Orgamize courses by a selected field and order\n");
    printf("4. Add New Courses: coming soon\n");
    printf("5. Recommendations: coming soon\n");
    print_seperator();
}

//display recommended courses (stub) MAKE SURE TO COME BACK AND AD DLOGIC 
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
    int is_filtered =0;

    while (running){
        display_menu();
        int choice=get_int_input("Enter choice (1-7): ", 1, 7);

        switch (choice){
            case MENU_BROWSE:{
                if (is_filterd && working_set != *courses){
                    free(working_set);
                    working_set= *courses;
                    working_count = *count;
                    is_filtered =0;
                }
                display_courses(working_set,working_count);
                pause_for_user();
                break;
            }

            case MENU_FILTER:{
                FilterCriteria criteria =get_filter_preferences();
                if (is_filtered && working_set != *courses){
                    free(working_set);
                }
                int filtered_count=0;
                Course* filtered = apply_multiple_filters(*courses, *count, criter, &filtered_count);

                if (filtered != NULL && filtered_count>0){
                    working_set=filtered;
                    working_count= filtered_count;
                    is_filtered =1;

                    printf("\nFiltering complete%s\n", COLOR_GREEN, COLOR_RESET);
                    display_courses(working_set, working_count);
                }else{
                    printf("\n%sNo courses match your filters.%s\n", COLOR_YELLOW, COLOR_RESET);
                    working_set=*courses;
                    working_count=*count;
                    is_filtered=0;
                }

                pause_for_user();
                break;
            }

            case MENU_SORT:{
                SortCriteria* sort_criteria=NULL;
                int num_criteria=0;
                get_sort_preferences(&sort_criteria, &num_criteria);

                if (sort_criteria != NULL && num_criteria > 0) {
                    sort_multi_criteria(working_set,working_count,sort_criteria,num_criteria);
                    printf("\n%sSorting complete!%s\n", COLOR_GREEN, COLOR_RESET);
                    display_courses(working_set, working_count);
                    free(sort_criteria);
                } else {
                    printf("\n%sSorting failed.%s\n", COLOR_YELLOW, COLOR_RESET);
                }

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