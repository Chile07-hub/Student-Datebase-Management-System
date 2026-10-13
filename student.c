#include <stdio.h>
#include <string.h>
struct Student
{
    int id;
    char name[20];
    char mob[15];
    char add[30];
};

void Print_all_User_info(struct Student arr[], int size)
{
    if (size == 0)
    {
        printf("\nNo Student Records Available!\n");
        return;
    }

    printf("\n");
    printf("==========================================================================\n");
    printf("                         STUDENT DATABASE MANAGEMENT SYSTEM                        \n");
    printf("                                ALL STUDENT RECORDS                             \n");
    printf("==========================================================================\n");

    printf("+----------+----------------------+------------------------------+---------------+\n");
    printf("| ID       | Name                 | Address                      | Mobile        |\n");
    printf("+----------+----------------------+------------------------------+---------------+\n");

    for (int i = 0; i < size; i++)
    {
        printf("| %-8d | %-20s | %-28s | %-13s |\n",
               arr[i].id,
               arr[i].name,
               arr[i].add,
               arr[i].mob);
    }

    printf("+----------+----------------------+------------------------------+---------------+\n");
    printf("Total Students: %d\n", size);
    printf("==========================================================================\n");
}

int id_Validation(struct Student arr[], int size, int id)
{
    for(int i=0; i < size;i++)
    {
        if(id == arr[i].id)
        {
            return 0;
        }
    }
    return 1;
}

int is_valid_mobile(struct Student arr[], int size, char mob[])
{
    for(int i = 0; mob[i] != '\0'; i++)
    {
        if(mob[i] < '0' || mob[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}

int mobile_validation(struct Student arr[], int size, char mob[])
{
    for(int i = 0; i < size; i++)
    {
        if(strcmp(arr[i].mob, mob) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void Add_student(struct Student arr[], int* size)
{
    if(*size >= 100)
    {
        printf("student database is full!\n");
        return;
    }

    int id_flag = 1;

    //validate ID
    do
    {
        printf("Enter Your ID: ");

        if(scanf("%d", &arr[*size].id) != 1)
        {
            printf("Invalid input! Enter positive Integer\n");
            while(getchar() != '\n');
            continue;
        }

        if(arr[*size].id <= 0)
             printf("ID must be positive and greater than zero\n");
        

        else if(id_Validation(arr,*size,arr[*size].id))
            id_flag = 0;
        
        else
            printf("ID already exists! Please Select Unique ID\n");
        
    } while(id_flag);
   

    printf("Enter Your Name: ");
    scanf(" %[^\n]", arr[*size].name);

    //validate Mobile Number
    int mob_flag = 1;

    do
    {
        printf("Enter Your 10-digit Mobile Number: ");
        scanf(" %[^\n]", arr[*size].mob);

        if(strlen(arr[*size].mob) != 10)
            printf("Mobile Number must contain exactly 10 digits\n");
        
        else if(!is_valid_mobile(arr, *size, arr[*size].mob))
            printf("Mobile Number must contain digits only\n");
        
        else if(!mobile_validation(arr, *size, arr[*size].mob))
            printf("Mobile nmber already exists! enter another number\n");
        
        else
            mob_flag = 0;
        
        
    } while (mob_flag);
    
    printf("Enter Your Address: ");
    scanf(" %[^\n]", arr[*size].add);

    (*size)++;

    printf("Student added Successfully!\n");
}

int Search_id(struct Student arr[], int size, int id)
{
   for(int i = 0; i < size; i++)
   {
    if(arr[i].id == id)
    {
        return i;
    }
   }
   return -1;
}

void Search_Student(struct Student arr[], int size)
{
    int id,i,index;
    printf("Enter Your id to search: ");
    scanf("%d", &id);

    index = Search_id(arr,size,id);

    if(index != -1)
    {
        printf("Student Data Found\n");
        printf("Id: %d\n", arr[index].id);
        printf("Name: %s\n", arr[index].name);
        printf("Address: %s\n", arr[index].add);
        printf("Mobile: %s\n", arr[index].mob);
    }
    else
    {
        printf("Student Not Found\n");
    }
}

void Delete_Student(struct Student arr[],int* size)
{
    int id,i;
    printf("Enter Your id to delete: ");
    scanf("%d", &id);

    int new_size = 0;

    for(i = 0; i < *size; i++)
    {
        if(id != arr[i].id)
        {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    if(*size == new_size)
    {
        printf("Student Not Found\n");
    }
    else
    {
        *size = new_size;
        printf("Student Deleted Successfully!\n");
    }
   
}

void Sort_Student(struct Student arr[], int size)
{
    //bubble sorting
    int i, j;
    struct Student temp;

    for(i = 0; i < size - 1; i++)
    {
        for(j = 0; j < size - 1 - i; j++)
        {
            if(arr[j].id > arr[j + 1].id)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    //Display sorted student record
    if(size == 0)
    {
        printf("No Stident records available!\n");
        return;
    }
    printf("\nStudent Records Sorted Successfully!\n");
    printf("-----------------------------------------\n");

    for(i = 0; i < size; i++)
    {
        printf("ID      :%d\n", arr[i].id);
        printf("Name    :%s\n", arr[i].name);
        printf("Mobile  :%s\n", arr[i].mob);
        printf("Address :%s\n", arr[i].add);
        printf("---------------------------------------\n");
    }
}

void Update_Student(struct Student arr[], int size)
{
    int id, index, opt;

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    index = Search_id(arr, size, id);

    if(index == -1)
    {
        printf("Student data Not Found!\n");
        return;
    }

    printf("What do you want to update?\n");
    printf("1. Name\n2. Address\n3. Mobile\n");
    printf("Enter Your choice: ");
    scanf("%d", &opt);

    switch(opt)
    {
        case 1:
                printf("Enter name: ");
                scanf(" %[^\n]", arr[index].name);
                printf("Name Updated Successfully!\n");
                break;
        case 2:
                printf("Enter Address: ");
                scanf(" %[^\n]", arr[index].add);
                printf("Address Updated Successfully!\n");
                break;
        case 3:
                printf("Enter Mobile Number: ");
                scanf(" %[^\n]", arr[index].mob);

                if(strlen(arr[index].mob) == 10 && 
                    is_valid_mobile(arr, size, arr[index].mob))
                {
                    printf("Mobile Number Updated Successfully!\n");

                }                    
               else
               {
                    printf("Invalid mobile Number!\n");
               }
               break;
    
        default:
                printf("Invalid Operation\n");
                break;
        
    }
   
}

int main()
{
    struct Student arr[100];
    int i = 1;
    int size = 0;
    int opt;

    while (i)
    {
        printf("\n");
        printf("====================================================\n");
        printf("           STUDENT DATABASE MANAGEMENT SYSTEM       \n");
        printf("====================================================\n");
        printf("                     MAIN MENU                      \n");
        printf("----------------------------------------------------\n");
        printf("     1. Add Student                                 \n");
        printf("     2. Search Student                              \n");
        printf("     3. Print Student Information                   \n");
        printf("     4. Delete Student Information                  \n");
        printf("     5. Sort Student Records                        \n");
        printf("     6. Update Student Information                  \n");
        printf("     7. Exit                                        \n");
        printf("====================================================\n");

        printf("Select one option from the above menu: ");
        scanf("%d", &opt);

        switch (opt)
        {
            case 1:
                Add_student(arr, &size);
                break;

            case 2:
                Search_Student(arr, size);
                break;

            case 3:
                Print_all_User_info(arr, size);
                break;

            case 4:
                Delete_Student(arr, &size);
                break;

            case 5:
                Sort_Student(arr, size);
                break;

            case 6:
                Update_Student(arr, size);
                break;

            case 7:
                printf("\nThank you for using Student Database Management System!\n");
                return 0;

            default:
                printf("\nInvalid option! Please select between 1 and 7.\n");
                break;
        }

        printf("\nDo you want to continue (1 - Yes / 0 - No): ");
        scanf("%d", &i);
    }

    printf("\nThank you for using Student Database Management System!\n");

    return 0;
}

