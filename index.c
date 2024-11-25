#include <stdio.h>
#include <string.h>

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


void add_title(Task* task) {
    char title[50];
    printf("=> Title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    //reassign a new value
    strcpy(task->title, title);
}

void add_desc(Task* task) {
    char desc[100];
    printf("=> Description: ");
    fgets(desc, sizeof(desc), stdin);
    desc[strcspn(desc, "\n")] = '\0';
    //reassign a new value
    strcpy(task->desc, desc);
}

void add_status(Task* task) {
    int input;
    do
    {  
       printf("=> Status (0 => INCOMPLETE, 1 => COMPLETE): ");
       scanf("%d", &input);
       if(input > 1) printf("*** Invalid Choice ***\n");
       else task->status = input;
    } while (input && input != 1);
    
}

void add_priority(Task* task) {
    int input;
    do
    {  
       printf("=> Priority (0 => LOW, 1 => HIGH): ");
       scanf("%d", &input);
       if(input > 1) printf("*** Invalid Choice ***\n");
       else task->priority = input;
       
    } while (input && input != 1);
    
}

void add_task(Task tasks[], int *count) {
    Task new_task;
    printf("*** Please add details ***\n");
    getchar();
    add_title(&new_task);
    add_desc(&new_task);
    add_status(&new_task);
    add_priority(&new_task);
    tasks[*count] = new_task;
    *count += 1;
    printf("\n***** Your task is added successfully!! *****\n");
}

void list_all(Task DB[], int count) {
    //if no task
    if(!count) printf("*** No tasks, try to add one first ***");
    if (count) {
        for (int i = 0; i < count; i++)
        {
            printf("==> %d - %s (%s)\n", i + 1, DB[i].title, DB[i].status ? "COMPLETED" : "INCOMPLETED");
        }
    }
}

void list_task(Task DB[], int count) {
    int task;
    if(!count) {
        printf("*** No tasks, try to add one first ***");
        return;
    }
    printf("**** All tasks ****\n");
    list_all(DB, count);
    do
    {
        printf("==> Enter a task number:  \n");
        scanf("%d", &task);
        if (task > count || task <= 0){
             printf("*** Invalid choice ***\n");
        } else{
            printf("==> title: %s\n", DB[count-1].title);
            printf("==> Description: %s\n", DB[count-1].desc);
            printf("==> Status: %s\n", DB[count-1].status ? "COMPLETED" : "INCOMPLETED");
            printf("==> Priority: %s\n", DB[count-1].priority ? "HIGH" : "LOW");
        }
    } while (task > count || task <= 0);
}

void update_task(Task DB[], int count) {
    int task;
    int update_title, update_desc, update_priority, update_status;
    if(!count) {
        printf("*** No tasks to edit ***"); 
        return;
    }
    printf("Please select the task you want to update\n");
    //list all tasks
    list_all(DB, count);
    //which task to edit
    scanf("%d", &task);

    //ask for title
    printf("Title: %s => update ? (Yes: 0, No: 1)\n", DB[task-1].title);
    scanf("%d", &update_title);
    if(!update_title){
        getchar();
        add_title(&DB[task-1]);
    }
    //ask for desc
    printf("Description: %s => update ? (Yes: 0, No: 1) ",  DB[task-1].desc);
    scanf("%d", &update_desc);
    if(!update_desc){
        getchar();
        add_desc(&DB[task-1]);
    }
    //ask for priority
    printf("Priority: %s => update ? (Yes: 0, No: 1) ",  DB[task-1].priority ? "HIGH" : "LOW");
    scanf("%d", &update_priority);
    if(!update_priority){
        add_priority(&DB[task-1]);
    }
    //ask for status
    printf("Status: %s => update ? (Yes: 0, No: 1) ", DB[count-1].status ? "COMPLETED" : "INCOMPLETED");
    scanf("%d", &update_status);
    if(!update_status) {
        add_status(&DB[task-1]);
    }

    printf("*** Task updated successfully *** \n");
}

void delete_task(Task DB[], int *count) {
    int task;
    if(!count) printf("*** No tasks to delete ***");
    if(count) {
         printf("**** All tasks ****\n");
         list_all(DB, *count);
        do{
            printf("==> Enter a task number:  \n");
            scanf("%d", &task);
            if (task > *count || task <= 0){
                printf("*** Invalid choice ***\n");
            } else{
                for (int i = task - 1; i < *count; i++){
                    DB[i] = DB[i+1];
                }
            
            }
        } while (task > *count || task <= 0);
        printf("Your task is deleted successfully\n");
        *count -=1;
    }
}



int main() {
    Task DB[50];
    int tasks = 0, action; // tasks to track the number of tasks; action for user action
    

    do
    {
        printf("\n*** Choose an action ***\n");
        printf("1 - ADD / 2 - LIST / 3 - DETAILS / 4 - UPDATE / 5 - DELETE / 0 - QUIT\n");
        scanf("%d", &action);
       //Action 1 for adding, 2 for listing, 3 for updating, 4 for deleting, 0 to quit
       switch (action)
       {
       case 1:
        add_task(DB, &tasks);
        break;
       case 2:
        list_all(DB, tasks);
        break;
       case 3:
        list_task(DB, tasks);
        break;
       case 4:
        update_task(DB, tasks); 
        break;
       case 5:
        delete_task(DB, &tasks);
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