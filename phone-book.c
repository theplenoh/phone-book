#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECORD_SZ 30

void printMenu();
void strSplit2By(const char ch[], char str[], char* arr[]);
void printAllRecords(char* arr[][2], const int row);
void loadFromFile(const char path[], char* arr[][2], int *row);
void saveToFile(const char path[], char* arr[][2], int *row);
void insertEntry(char* arr[][2], int *row);
void deleteEntry(char* arr[][2]);
void searchForEntry(char* arr[][2], const int row);
void freeMyRows(char* arr[][2], const int row);

int main()
{
    char* records[RECORD_SZ][2]; // 레코드 저장
    int row=0; // 레코드 수
    char datafile[] = "./data.txt";
    int choice;

    printMenu();
    while (1)
    {
        printf(">> "); scanf("%d", &choice);
        switch(choice)
        {
            case 0:
                printMenu();
                break;
            case 1:
                loadFromFile(datafile, records, &row);
                break;
            case 2:
                saveToFile(datafile, records, &row);
                break;
            case 3:
                printAllRecords(records, row);
                break;
            case 4:
                insertEntry(records, &row);
                break;
            case 5:
                searchForEntry(records, row);
                break;
            case 6:
                deleteEntry(records);
                break;
            case 7:
                printf("Exiting the Program.\n");
                freeMyRows(records, row);
                return 0;
                break;
            default:
                printf("Error - an Exception!\n");
        }
    }

    freeMyRows(records, row);
    return 0;
}

void printMenu()
{
    printf("=== Menu ==============\n");
    printf("0. Print this menu\n");
    printf("1. Load from the File\n");
    printf("2. Save to the File\n");
    printf("3. Print All Records\n");
    printf("4. Insert an Entry\n");
    printf("5. Search for an Entry\n");
    printf("6. Delete an Entry by Record Idx\n");
    printf("7. Exit Program\n");
    printf("=======================\n");
}

void loadFromFile(const char path[], char* arr[][2], int *row)
{
    int i, cnt=0;
    char line[80];
    FILE* fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
    }
    else {
        while (fgets(line, sizeof(line), fp))
        {
            line[strlen(line)-1]='\0';
            strSplit2By("|", line, arr[cnt++]);
        }
        fclose(fp);
    }

    *row = cnt;
}

void strSplit2By(const char ch[], char str[], char* arr[])
{
    int i=0;
    char* p = strtok(str, ch);
    while (p != NULL)
    {
        arr[i] = (char*)malloc(sizeof(char)*40);
        strcpy(arr[i++], p);
        p = strtok(NULL, ch);
    }
}

void saveToFile(const char path[], char* arr[][2], int *row)
{
    FILE* fp = fopen(path, "w");
    int i;

    if (fp == NULL) {
        printf("Error opening file!\n");
    }
    else {
        for(i=0; i<*row; i++)
            fprintf(fp, "%s|%s\n", arr[i][0], arr[i][1]);
        fclose(fp);
    }
}

void insertEntry(char* arr[][2], int *row)
{
    arr[*row][0] = (char*)malloc(sizeof(char)*40);
    printf("Name: ");
    scanf("%s", arr[*row][0]);

    arr[*row][1] = (char*)malloc(sizeof(char)*40);
    printf("Phone #: ");
    scanf("%s", arr[*row][1]);

    (*row)++;
}

void deleteEntry(char* arr[][2])
{
    int recIdx;
    printf("Record Idx: ");
    scanf("%d", &recIdx);

    strcpy(arr[recIdx][0], "**DELETED**");
    strcpy(arr[recIdx][1], "**NULL**");
}

void searchForEntry(char* arr[][2], const int row)
{
    int i;
    char searchWord[15];
    printf("Search Word: "); scanf("%s", searchWord);

    printf("Result: %s\n", searchWord);
    printf("=== Search Result =========\n");
    for(i=0; i<row; i++)
    {
        if (!strcmp(arr[i][0], searchWord))
            printf("%2d. [%s] [%s]\n", i, arr[i][0], arr[i][1]);
    }
    printf("===========================\n");
}

void printAllRecords(char* arr[][2], const int row)
{
    int i;

    printf("=== Print All Records ===\n");
    for(i=0; i<row; i++)
        printf("%2d. [%s] [%s]\n", i, arr[i][0], arr[i][1]);
    printf("=========================\n");
}

void freeMyRows(char* arr[][2], const int row)
{
    int i;
    for(i=0; i<row; i++)
    {
        free(arr[i][0]);
        free(arr[i][1]);
    }
}
