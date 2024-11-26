#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void compare_asc(const void *a, const void *b) {
    const Task *date1 = (const Task *)a;
    const Task *date2 = (const Task *)b;
    if (date1->due_date.year != date2->due_date.year) {
        return date1->due_date.year - date2->due_date.year;
    } else if (date1->due_date.month != date2->due_date.month) {
        return date1->due_date.month - date2->due_date.month;
    } else {
        return date1->due_date.day - date2->due_date.day;
    }
}

void compare_dec(const void *a, const void *b) {
    const Task *date1 = (const Task *)a;
    const Task *date2 = (const Task *)b;
    if (date1->due_date.year != date2->due_date.year) {
        return date2->due_date.year - date1->due_date.year;
    } else if (date1->due_date.month != date2->due_date.month) {
        return date2->due_date.month - date1->due_date.month;
    } else {
        return date2->due_date.day - date1->due_date.day;
    }
}

void order_task(Task tasks[], int count) {

    int option;
    if(!count){ 
        printf("*** No tasks, try to add one first ***");
        return;
    }
   do
   {
    printf("Sort (0 ascending, 1 descending): ");
    scanf("%d", &option);
   } while (option && option != 1);
   
   qsort(tasks, count, sizeof(tasks[0].due_date), option ? compare_asc : compare_dec);
   for (int i = 0; i < count; i++)
   {
    printf("%d- %s (%d/%d/%d) \n", i+ 1, tasks[i].title, tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year);
   }
   
}

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

void add_date(Task* task){
    int day, month, year;
    printf("=> Date \n");
    do
    {
        printf("==> Month: ");
        scanf("%d", &month);
        if(month > 12 || month < 1)printf("*** Invalid input ***\n");
    } while (month > 12 || month < 1 );
    task->due_date.month = month;
    do
    {
        printf("==> Day: ");
        scanf("%d", &day);
        if(day < 1 || (month == 2 && day > 28) || (month != 2 && day > 31)) printf("*** Invalid input ***\n");
    } while (day < 1 || (month == 2 && day > 28) || (month != 2 && day > 31));
    task->due_date.day = day;
    do
    {
        printf("==> Year(>2010): ");
        scanf("%d", &year);
        if(year < 2010) printf("*** Invalid input ***\n");
    } while (year < 2010);
    task->due_date.year = year;
    
}

void add_task(Task tasks[], int *count) {
    Task new_task;
    printf("*** Please add details ***\n");
    getchar();
    add_title(&new_task);
    add_desc(&new_task);
    add_status(&new_task);
    add_priority(&new_task);
    add_date(&new_task);
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
        printf("==>  Please select the task you want to see from above:  \n");
        scanf("%d", &task);
        if (task > count || task <= 0){
             printf("*** Invalid choice ***\n");
        } else{
            printf("==> title: %s\n", DB[count-1].title);
            printf("==> Description: %s\n", DB[count-1].desc);
            printf("==> Status: %s\n", DB[count-1].status ? "COMPLETED" : "INCOMPLETED");
            printf("==> Priority: %s\n", DB[count-1].priority ? "HIGH" : "LOW");
            printf("==> Date: %d/%d/%d",  DB[count-1].due_date.day,  DB[count-1].due_date.month,  DB[count-1].due_date.year);
        }
    } while (task > count || task <= 0);
}

void update_task(Task DB[], int count) {
    int task;
    int update_title, update_desc, update_priority, update_status, update_date;
    if(!count) {
        printf("*** No tasks to edit ***"); 
        return;
    }
   
    do
    {
         //list all tasks
        list_all(DB, count);
        printf("=> Please select the task you want to update from above: ");
        //which task to edit
        scanf("%d", &task);
    } while (!task || task < 0 || task > count);
    

    //ask for title
    do
    {
       printf("Title: %s => update ? (Yes: 0, No: 1)\n", DB[task-1].title);
       scanf("%d", &update_title);
       if(!update_title && update_title > 1) printf("*** Invalid option ***");
    } while (!update_title && update_title > 1);
    //if yes
    if(!update_title){
        getchar();
        add_title(&DB[task-1]);
    }
    //ask for desc
    do
    {
        printf("Description: %s => update ? (Yes: 0, No: 1) ",  DB[task-1].desc);
        scanf("%d", &update_desc);
       if(!update_desc && update_desc > 1) printf("*** Invalid option ***");
    } while (!update_desc && update_desc > 1);
    //if yes
    if(!update_desc){
        getchar();
        add_desc(&DB[task-1]);
    }
    //ask for property
    do
    {
        printf("Priority: %s => update ? (Yes: 0, No: 1) ",  DB[task-1].priority ? "HIGH" : "LOW");
        scanf("%d", &update_priority);
        if(!update_priority && update_priority > 1) printf("*** Invalid option ***");
    } while (!update_priority && update_priority > 1);
    //if yes
    if(!update_priority){
        add_priority(&DB[task-1]);
    }
    //ask for status
    do
    {
        printf("Status: %s => update ? (Yes: 0, No: 1) ", DB[count-1].status ? "COMPLETED" : "INCOMPLETED");
        scanf("%d", &update_status);
        if(!update_status && update_status);
    } while (!update_status && update_status);
    //if yes
    if(!update_status) {
        add_status(&DB[task-1]);
    }
    //ask for date
    do
    {
        printf("Date: %d/%d/%d => update ? (Yes: 0, No: 1)", DB[count-1].due_date.day, DB[count-1].due_date.month, DB[count-1].due_date.year);
        scanf("%d", &update_date);
        if(!update_date && update_date);
    } while (!update_date && update_date);
    //If yes
    if(!update_date) {
        add_date(&DB[task-1]);
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
            printf("==>  Please select the task you want to delete from above::  \n");
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

void filter_task(Task DB[], int count) {
    int by, which;
    
    do
    {
         printf("Filter by => (0 status, 1 priority): ");
        scanf("%d", &by);
        if(!by && by > 1) printf("*** Invalid option ***");
    } while (!by && by > 1);
    
    do
    {
        if(!by) printf("0 INCOMPLETE / 1 COMPLETE");
        else printf("0 LOW / 1 HIGH");
         scanf("%d", &which);
        if(!which && which > 1)  printf("*** Invalid option ***");
    } while (!which && which > 1);

    for (int i = 0; i < count; i++)
    {
        if (!by && DB[i].status == which) printf("==> %d - %s (%s)\n", i + 1, DB[i].title, DB[i].status ? "COMPLETED" : "INCOMPLETED");
        if(by && DB[i].priority == which) printf("==> %d - %s (%s)\n", i + 1, DB[i].title, DB[i].priority ? "HIGH" : "LOW");
        
    }
    
    
    
}

void save_task(Task DB[], int count) {
    if(!count) {
        printf("*** No tasks to save ***"); 
        return;
    }
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    for(int i = 0; i < count; i++){
        fprintf(file,"%d - %s(%d/%d/%d)=> %s - %s\n %s\n\n", i + 1, DB[i].title, DB[i].due_date.day, DB[i].due_date.month, DB[i].due_date.year, DB[i].status ? "COMPLETE" : "COMPLETED", DB[i].priority ? "High" : "LOW", DB[i].desc);
    }
    fclose(file);
    printf("*** Tasks Saved successfully ***");
}

int main() {
    Task DB[50];
    int tasks = 0, action; // tasks to track the number of tasks; action for user action
    

    do
    {
        printf("\n*** Choose an action ***\n");
        printf("******** MENU ********\n");
        printf("1 - ADD / 2 - LIST / 3 - FILTER / 4 - DETAILS / 5 - UPDATE / 6 - DELETE / 7 - SAVE / 0 - QUIT\n");
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
        filter_task(DB, tasks);
        break; 
        case 4:
        list_task(DB, tasks);
        break;
       case 5:
        update_task(DB, tasks); 
        break;
       case 6:
        delete_task(DB, &tasks);
        break;
       case 7:
        save_task(DB, tasks);
        break;
       case 8:
        order_task(DB, tasks);
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