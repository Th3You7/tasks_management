#include <stdio.h>


typedef struct 
{
    int day;
    int month;
    int year;
} Date;

typedef struct 
{
    char title[50];
    char desc[100];
    int status;
    int priority;
    Date due_date;
    Date start_date;
} Task;

void add_task() {}
void list_all() {}
void list_task() {}
void update_task() {}
void delete_task() {}


int main() {
    Task DB[50];
    int tasks = 0, action; // tasks to track the number of tasks; action for user action
    

    do
    {
        printf("*** Choose an action ***\n");
        printf("1 - ADD / 2 - LIST / 3 - UPDATE / 4 - DELETE / 0 - QUIT\n");
        scanf("%d", &action);
       //Action 1 for adding, 2 for listing, 3 for updating, 4 for deleting, 0 to quit
       switch (action)
       {
       case 1:
        add_task();
        break;
       case 2:
        list_all();
        break;
       case 3:
        update_task();
        break;
       case 4:
        delete_task();
        break;  
       case 0: 
        printf("**GOODBYE!!**");
        break; 
       default:
        printf("** Invalid Choice!!**\n");
       }
    } while (action);
    


    return 0;
}