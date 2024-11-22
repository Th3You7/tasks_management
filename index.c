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

void add_status(int status) {
    int input;
    do
    {  
        printf("=> Status (0 => INCOMPLETE, 1 => COMPLETE): ");
       scanf("%d", &input);
       if(input > 1) printf("*** Invalid Choice ***\n");
       else status = input;
    } while (input && input != 1);
    
}

void add_priority(int priority) {
    int input;
    do
    {  
       printf("=> Priority (0 => LOW, 1 => HIGH): ");
       scanf("%d", &input);
       if(input > 1) printf("*** Invalid Choice ***\n");
       else priority = input;
       
    } while (input && input != 1);
    
}

void add_task(Task DB, int count) {
    printf("*** Please add details ***\n");
    printf("=> title: ");
    getchar();
    fgets(DB.title, 50, stdin);
    printf("=> Description: ");
    fgets(DB.desc, 100, stdin);
    add_status(DB.status);
    add_priority(DB.priority);
    printf("\n***** Your task is added successfully!! *****\n");
}

void list_all() {}
void list_task() {}
void update_task() {}
void delete_task() {}


int main() {
    Task DB[50];
    int tasks = 0, action; // tasks to track the number of tasks; action for user action
    

    do
    {
        printf("\n*** Choose an action ***\n");
        printf("1 - ADD / 2 - LIST / 3 - UPDATE / 4 - DELETE / 0 - QUIT\n");
        scanf("%d", &action);
       //Action 1 for adding, 2 for listing, 3 for updating, 4 for deleting, 0 to quit
       switch (action)
       {
       case 1:
        add_task(DB[tasks], tasks);
        break;
       case 2:
        list_all(DB, tasks);
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
        printf("** Invalid Choice!! **\n");
       }
    } while (action);
    


    return 0;
}