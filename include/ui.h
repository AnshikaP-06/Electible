// SFWRENG 2XC3: Electible
// Module D:User Interface
// Yasmine Abdelmalek

#ifndef UI_H
#define UI_H

#include "filter.h"
#include "sort.h"

//Menu options
typedef enum{
    MENU_BROWSE=1,
    MENU_FILTER=2,
    MENU_SORT=3,
    MENU_ADD=4,
    MENU_RECOMMENDATIONS=5,
    MENU_HELP=6,
    MENU_EXIT=7
} MenuOption;

//Show  main menu
void display_menu(void);

//Show a list of courses in a tavle
void display_courses(Course* courses,int count);

//show all details for that one course
void display_course_detail(Course course);

//ask user for filters they wanr
FilterCriteria get_filter_preferences(void);

//ask user how they want to sort
void get_sort_preferences(SortCriteria** criteria,int* num_criteria);

//get info on new course from user
Course get_new_course_input(void);

//main loop
void handle_user_interaction(Course** courses,int* count, const char* filename);

//help info 
void display_help(void);

//recommended courses display
void display_recommendations(Course* courses,int count);

//clear leftover stuff
void clear_input_buffer(void);

//get integer choice from user
int get_int_input(const char* prompt, int min,int max);

//makes sure floats allowed to
float get_float_input(const char* prompt,float min,float max);

//strings also allowed
void get_string_input(const char* prompt,char* buffer, int max_length);

//line seperator just for clarity
void print_separator(void);

//wait for user to keep going
void pause_for_user(void);

#endif