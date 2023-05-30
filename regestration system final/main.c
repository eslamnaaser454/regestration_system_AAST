#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#define ll long long
#define db long double
#include <stdlib.h>
typedef struct data_student
{
    char fname_student[50];
    char sname_student[50];
    char tname_student[50];
    char lname_student[50];
    int day;
    int year;
    int month;
    float sec_grade;
} br;
typedef struct student
{
    int reg;
    int reg2;
    char sub[7][50];
    char grade[7][3];
    float gpa;
    int credit;
    char reg_number[9];
    int feb_number;
    int type;
    int solom;
    int mood;
} st;
typedef struct course
{
    int sub_num;
    int counter;
    char sub_code[40];
    char sub_name[54];
    int sub_hour;
    char prequisites[38];

} cr;
st stt;
cr crr;
br brr;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mood()
{
    int selectt;
    printf("Academic advisor (1)\n");
    printf("student (2)\n");
    printf("Manager (3)\n");
    printf("Exit (4)\n");
    scanf("%d", &selectt);
    if (selectt == 2)
    {
        stt.mood = 2;
        new_line();
        printing_subjects();
    }
    else if (selectt == 1)
    {
        stt.mood = 1;
        new_line();
        academic_advisor();
    }
    else if (selectt == 3)
    {
        stt.mood = 3;
        new_line();
        manager();
    }

    else if (selectt == 4)
    {
        new_line();
        printf("\n                                                            SEE YOU SOON ^^!\n");
        new_line();
        return;
    }

    else
    {
        SetColor(196); // red
        printf("\nInvalid Input!\nPlease try again");
        SetColor(0); // black
        new_line();
        mood();
    }
}
void SetColor(int ForgC)
{
    WORD wColor;
    // This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // csbi is used for wAttributes word

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void new_line()
{
    printf("\n");
    printf("============================================================================================================================================\n");
}

void printing_subjects()
{
    printf("Enter registration number: \n");
    scanf("%s", &stt.reg_number);
    for (int i = 0; i < 7; i++)
    {
        if (isalpha(stt.reg_number[i]))
        {
            printing_subjects();
            break;
        }
    }
    int regnum = atoi(stt.reg_number);
    FILE *fp = fopen("grades.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    int found = 0;
    while (!feof(fp))
    {

        fscanf(fp, "%d \n", &stt.reg);
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%s", stt.grade[i]);
        }
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%s", stt.sub[i]);
        }

        fscanf(fp, "%f %d", &stt.gpa, &stt.credit);

        if (stt.reg == regnum)
        {
            printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-35s%-38s\n", "Subject", "Grade");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");

            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 44; j++)
                {
                    if (stt.sub[i][j] == '_')
                    {
                        printf(" ");
                        continue;
                    }
                    else if (stt.sub[i][j] == 'X')
                        printf(" ");
                    else
                        printf("%c", stt.sub[i][j]);
                }
                printf("%s\n\n", stt.grade[i]);
            }
            printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-35s%-44.2f\n", "Total GPA", stt.gpa);
            printf("%-35s%-44d\n", "Total Credit", stt.credit);
            printf("-------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            found = 1;

            if (stt.credit == 0)
            {
                main_choose2();
            }
            else
                new_reg();
        }
    }

    if (!found)
    {
        SetColor(196); // red
        printf("Student not found!\nPlease try again\n");
        SetColor(0); // black
        new_line();
        printing_subjects();
    }
    fclose(fp);
}
void new_reg()
{

    int select;
    printf("New Registration (1)\n");
    printf("Exit (2)\n");
    scanf("%d", &select);
    if (select == 1)
    {
        new_line();
        regestrtion();
    }
    else if (select == 2)
    {
        return;
    }
    else
    {
        SetColor(196); // red
        printf("Invalid Input!\nPlease try again");
        SetColor(0); // black
        new_line();
        new_reg();
    }
}
void regestrtion()
{
    FILE *fp = fopen("regestrationdata.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s%-35s %-10s %45s %30s\n", "NO.", "Course Code", "Course Name", "Course Hours", "Prequisites");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 16; i++)
    {
        fscanf(fp, "%d %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

        if (crr.sub_num <= 9)
        {
            printf("0");
        }
        printf("%d ", crr.sub_num);

        for (int j = 0; j < 40; j++)
        {
            if (crr.sub_code[j] == '_' || crr.sub_code[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_code[j]);
        }

        for (int j = 0; j < 54; j++)
        {
            if (crr.sub_name[j] == '_' || crr.sub_name[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_name[j]);
        }

        printf("%d", crr.sub_hour);

        for (int j = 0; j < 38; j++)
        {
            if (crr.prequisites[j] == '_' || crr.prequisites[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.prequisites[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);

    final_reg();
    return;
}
void final_reg()
{
    int max_laod;
    int reg_load = 0;
    crr.counter = 0;

    if (stt.gpa < 2.0)
    {
        max_laod = 12;
    }

    if (stt.gpa >= 2.0)
    {
        max_laod = 18;
    }

    FILE *fp1 = fopen("regestrationdata.txt", "r");
    if (fp1 == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    FILE *fp2 = fopen("stdselection.txt", "w");
    if (fp2 == NULL)
    {
        printf("Error: could not open file.\n");
        fclose(fp1);
        return;
    }

    FILE *fp63 = fopen("allow.txt", "a");
    if (fp63 == NULL)
    {
        printf("Error: could not open file.\n");
        fclose(fp1);
        return;
    }

    FILE *fp83 = fopen("allow.txt", "r");
    if (fp83 == NULL)
    {
        printf("Error: could not open file.\n");
        fclose(fp1);
        return;
    }

    if (stt.mood == 2)
    {
        printf("NOTE\n-In Maths courses you can select one of the following {5, 15, 8}\n-In Physics courses you can select one of the following {10, 2}\n");
        printf("-In English courses you can select both of {7, 3}, only {16}, or only {11}\n-In you can select both of {4, 1} or only {9}\n");
        printf("-If you have any conflict, please contact your academic advisor\n\n");
    }

    printf("Enter the subject NO. you want to register \nIf you are done, type (0)\n");

    int subnumm;
    int entered_values[50] = {0};
    int entered_count = 0;

    do
    {
        scanf("%d", &subnumm);

        int is_duplicate = 0;
        for (int i = 0; i < entered_count; i++)
        {
            if (subnumm == entered_values[i])
            {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate)
        {
            SetColor(196); // red
            printf("%d is used before!\n", subnumm);
            SetColor(0); // black
            continue;
        }

        entered_values[entered_count] = subnumm;
        entered_count++;

        int num;
        int c = 0;
        int found = 0;
        while (!feof(fp1))
        {
            fscanf(fp1, "%d\n %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

            if (subnumm == 0)
            {
                found = 1;
                fclose(fp2);
                new_line();
                Display_registration();
                return;
            }
            else if (subnumm == crr.sub_num)
            {
                if (subnumm == 1 && !strcmp(stt.grade[1], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 2 && !strcmp(stt.grade[5], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 3 && !strcmp(stt.grade[2], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 4 && !strcmp(stt.grade[1], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 5 && !strcmp(stt.grade[6], "F") && !strcmp(stt.sub[6], "Precalculus"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 7 && !strcmp(stt.grade[2], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 11 && !strcmp(stt.grade[2], "F") && !strcmp(stt.sub[6], "Academic_English0"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == 15 && !strcmp(stt.grade[6], "F"))
                {
                    SetColor(196); // red
                    printf("Subject has a prerequisite!\n");
                    SetColor(0); // black
                }
                else if (subnumm == crr.sub_num)
                {
                    c++;

                    if (reg_load <= max_laod && reg_load + crr.sub_hour <= max_laod)
                    {
                        if (subnumm == 8)
                        {
                            reg_load = reg_load + 3;
                        }

                        if (subnumm == 16)
                        {
                            reg_load = reg_load + 2;
                        }

                        for (int i = 0; i < c; i++)
                        {
                            fscanf(fp83, "%d", &num);

                            if (subnumm == 5 && num == 15)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 5 && num == 8)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 15 && num == 8)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 15 && num == 5)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 8 && num == 5)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 8 && num == 15)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 16 && num == 7)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 16 && num == 3)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 16 && num == 11)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 7 && num == 11)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 7 && num == 16)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 3 && num == 16)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 3 && num == 11)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 11 && num == 3)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 11 && num == 7)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 11 && num == 16)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 10 && num == 2)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 2 && num == 10)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 4 && num == 9)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 1 && num == 9)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 9 && num == 1)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else if (subnumm == 9 && num == 4)
                            {
                                SetColor(196); // red
                                printf("Not allowed!\n");
                                SetColor(0); // blackSetColor(0); //black
                            }

                            else
                            {
                                fprintf(fp2, "%d %s %s %d %s\n", crr.sub_num, crr.sub_code, crr.sub_name, crr.sub_hour, crr.prequisites);
                                reg_load += crr.sub_hour;
                                crr.counter++;
                                fprintf(fp63, "%d\n", subnumm);
                                fflush(fp63);
                            }
                        }
                    }

                    else
                    {
                        SetColor(196); // red
                        printf("Sorry! you have exceeded the available credit.\n");
                        SetColor(0); // black
                        fclose(fp2);
                        new_line();
                        Display_registration();
                        return;
                    }
                }

                found = 1;
            }
        }

        if (!found)
        {
            SetColor(196); // red
            printf("%d is not found!\n", subnumm);
            SetColor(0); // black
        }

        rewind(fp1);

    } while (subnumm != 0);

    fclose(fp1);
}
void Display_registration()
{

    FILE *fp10 = fopen("stdselection.txt", "r");
    fprintf(fp10, "sagy");
    fprintf(fp10, "done");
    if (fp10 == NULL)
    {

        printf("Error: could not open file.\n");
        return;
    }

    SetColor(82); // green
    printf("\n                                            Your registration is done successfully!!^^\n");
    SetColor(0); // black

    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s%-35s %-10s %45s %30s\n", "NO.", "Course Code", "Course Name", "Course Hours", "Prequisites");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < crr.counter; i++)
    {
        fscanf(fp10, "%d %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

        if (crr.sub_num <= 9)
        {
            printf("0");
        }
        printf("%d ", crr.sub_num);

        for (int j = 0; j < 40; j++)
        {
            if (crr.sub_code[j] == '_' || crr.sub_code[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_code[j]);
        }

        for (int j = 0; j < 54; j++)
        {
            if (crr.sub_name[j] == '_' || crr.sub_name[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_name[j]);
        }

        printf("%d", crr.sub_hour);

        for (int j = 0; j < 38; j++)
        {
            if (crr.prequisites[j] == '_' || crr.prequisites[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.prequisites[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp10);

    if (stt.mood == 2)
        main_choose();
    else if (stt.mood == 1)
        main_choose3();
}
void Display_registration_advisor()
{

    FILE *fp10 = fopen("stdselection.txt", "r");
    fprintf(fp10, "sagy");
    fprintf(fp10, "done");
    if (fp10 == NULL)
    {

        printf("Error: could not open file.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s%-35s %-10s %45s %30s\n", "NO.", "Course Code", "Course Name", "Course Hours", "Prequisites");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < crr.counter; i++)
    {
        fscanf(fp10, "%d %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

        if (crr.sub_num <= 9)
        {
            printf("0");
        }
        printf("%d ", crr.sub_num);

        for (int j = 0; j < 40; j++)
        {
            if (crr.sub_code[j] == '_' || crr.sub_code[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_code[j]);
        }

        for (int j = 0; j < 54; j++)
        {
            if (crr.sub_name[j] == '_' || crr.sub_name[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_name[j]);
        }

        printf("%d", crr.sub_hour);

        for (int j = 0; j < 38; j++)
        {
            if (crr.prequisites[j] == '_' || crr.prequisites[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.prequisites[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp10);
}
void Display_edited()
{

    FILE *fp10 = fopen("endselectioN.txt", "r");
    fprintf(fp10, "sagy");
    fprintf(fp10, "done");
    if (fp10 == NULL)
    {

        printf("Error: could not open file.\n");
        return;
    }

    SetColor(82); // green
    printf("\n                                            Your registration is done successfully!!^^\n");
    SetColor(0); // black

    printf("\n-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s%-35s %-10s %45s %30s\n", "NO.", "Course Code", "Course Name", "Course Hours", "Prequisites");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < crr.counter - 1; i++)
    {
        fscanf(fp10, "%d %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

        if (crr.sub_num <= 9)
        {
            printf("0");
        }
        printf("%d ", crr.sub_num);

        for (int j = 0; j < 40; j++)
        {
            if (crr.sub_code[j] == '_' || crr.sub_code[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_code[j]);
        }

        for (int j = 0; j < 54; j++)
        {
            if (crr.sub_name[j] == '_' || crr.sub_name[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_name[j]);
        }

        printf("%d", crr.sub_hour);

        for (int j = 0; j < 38; j++)
        {
            if (crr.prequisites[j] == '_' || crr.prequisites[j] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.prequisites[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp10);

    main_choose2();
}
void main_choose()
{
    int select;
    printf("GPA calculator (1)\n");
    printf("Student schedule (2)\n");
    printf("Home page (3)\n");
    printf("Exit (4)\n");
    scanf("%d", &select);

    if (select == 2)
    {
        new_line();
        samaa();
    }
    else if (select == 1)
    {
        new_line();
        read();
    }
    else if (select == 3)
    {
        new_line();
        mood();
    }
    else if (select == 4)
    {
        return;
    }
    else
    {
        SetColor(196); // red
        printf("Invalid input!\nPlease try again");
        SetColor(0); // black
        new_line();
        main_choose();
    }
}
void samaa()
{
    printf("Enter the schedule name (A)(B)(C)(D)(E)(F):\n");
    char c[20];
    scanf("%s", c);

    if (strcmp(c, "A") == 0)
    {
        new_line();
        Scientific_mathematics();
        main_choose2();
    }

    else if (strcmp(c, "B") == 0)
    {
        new_line();
        schedule_Precalculus();
        main_choose2();
    }

    else if (strcmp(c, "C") == 0)
    {
        new_line();
        schedule_Scientific_science();
        main_choose2();
    }

    else if (strcmp(c, "D") == 0)
    {
        new_line();
        schedule_Physic();
        main_choose2();
    }

    else if (strcmp(c, "E") == 0)
    {
        new_line();
        schedule_Introduction_to_Computing();
        main_choose2();
    }

    else if (strcmp(c, "F") == 0)
    {
        new_line();
        Academic_English();
        main_choose2();
    }
    else
    {
        SetColor(196); // red
        printf("Invalid input!\nPlease try again");
        SetColor(0); // black
        new_line();
        samaa();
    }
}
void main_choose2()
{
    int select;
    printf("Home page (1)\n");
    printf("Exit (2)\n");
    scanf("%d", &select);
    if (select == 2)
    {
        return;
    }

    else if (select == 1)
    {
        new_line();
        mood();
    }

    else
    {
        SetColor(196); // red
        printf("Invalid input!\nPlease try again");
        SetColor(0); // black
        new_line();
        main_choose2();
    }
}
void read()
{
    float totpoints = 0.0;
    float totcred = 0.0;

    FILE *fp2 = fopen("stdselection.txt", "r");
    if (fp2 == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    while (!feof(fp2))
    {
        int gradefinal;
        fscanf(fp2, "%d %s %s %d %s\n", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);

        printf("\nEnter your grade in ");
        for (int i = 0; i < 53; i++)
        {
            if (crr.sub_name[i] == '_')
            {
                continue;
            }
            else if (crr.sub_name[i] == 'X')
            {
                printf(" ");
                continue;
            }
            printf("%c", crr.sub_name[i]);
        }
        printf(" ");
        totcred += crr.sub_hour;
        scanf("%d", &gradefinal);

        if (crr.sub_hour == 2)
        {

            if (gradefinal >= 96 && gradefinal <= 100)
            {
                totpoints += 8.0;

                printf("your grade is A+\n");
            }
            else if (gradefinal <= 95 && gradefinal >= 92)
            {
                totpoints += 7.4;
                printf("\nyour grade is A\n");
            }
            else if (gradefinal <= 91 && gradefinal >= 88)
            {
                totpoints += 6.8;
                printf("your grade is A-\n");
            }
            else if (gradefinal <= 87 && gradefinal >= 84)
            {
                totpoints += 6.4;
                printf("your grade is B+\n");
            }
            else if (gradefinal <= 83 && gradefinal >= 80)
            {
                totpoints += 6.0;
                printf("your grade is B\n");
            }
            else if (gradefinal <= 79 && gradefinal >= 76)
            {
                totpoints += 5.6;
                printf("your grade is B-\n");
            }
            else if (gradefinal <= 75 && gradefinal >= 72)
            {
                totpoints += 5.2;
                printf("your grade is C+\n");
            }
            else if (gradefinal <= 71 && gradefinal >= 68)
            {
                totpoints += 4.8;
                printf("your grade in is C\n");
            }
            else if (gradefinal <= 67 && gradefinal >= 64)
            {
                totpoints += 4.4;
                printf("your grade is C-\n");
            }
            else if (gradefinal <= 63 && gradefinal >= 60)
            {
                totpoints += 4.0;
                printf("your grade is D+\n");
            }
            else if (gradefinal <= 59 && gradefinal >= 55)
            {
                totpoints += 3.0;
                printf("your grade is D\n");
            }
            else if (gradefinal <= 54 && gradefinal >= 50)
            {
                totpoints += 2.0;
                printf("your grade is D-\n");
            }
            else if (gradefinal < 50)
            {
                printf("your grade is F\n");
            }
            else
            {
                SetColor(196); // red
                printf("Invalid input");
                SetColor(0); // black
            }
        }
        if (crr.sub_hour == 3)
        {
            if (gradefinal >= 96 && gradefinal <= 100)
            {
                totpoints += 12.0;
                printf("your grade is A+\n");
            }
            else if (gradefinal <= 95 && gradefinal >= 92)
            {
                totpoints += 11.1;
                printf("\nyour grade is A");
            }
            else if (gradefinal <= 91 && gradefinal >= 88)
            {
                totpoints += 10.2;
                printf("your grade is A-\n");
            }
            else if (gradefinal <= 87 && gradefinal >= 84)
            {
                totpoints += 9.6;
                printf("your grade is B+\n");
            }
            else if (gradefinal <= 83 && gradefinal >= 80)
            {
                totpoints += 9.0;
                printf("your grade is B\n");
            }
            else if (gradefinal <= 79 && gradefinal >= 76)
            {
                totpoints += 8.4;
                printf("your grade is B-\n");
            }
            else if (gradefinal <= 75 && gradefinal >= 72)
            {
                totpoints += 7.8;
                printf("your grade is C+ \n");
            }
            else if (gradefinal <= 71 && gradefinal >= 68)
            {
                totpoints += 7.2;
                printf("your grade is C\n");
            }
            else if (gradefinal <= 67 && gradefinal >= 64)
            {
                totpoints += 6.6;
                printf("your grade is C-\n");
            }
            else if (gradefinal <= 63 && gradefinal >= 60)
            {
                totpoints += 6.0;
                printf("your grade is D+\n");
            }
            else if (gradefinal <= 59 && gradefinal >= 55)
            {
                totpoints += 4.5;
                printf("your grade is D\n");
            }
            else if (gradefinal <= 54 && gradefinal >= 50)
            {
                totpoints += 3.0;
                printf("your grade is D-\n");
            }
            else if (gradefinal < 50)
            {
                printf("your grade is F\n");
            }
            else
            {
                SetColor(196); // red
                printf("Invalid input");
                SetColor(0); // black
            }
        }
        if (crr.sub_hour == 0)
        {
            if (gradefinal >= 50)
            {
                printf("your grade is P\n");
            }
            else if (gradefinal < 50)
            {
                printf("your grade is F\n");
            }
            else
            {
                SetColor(196); // red
                printf("Invalid input");
                SetColor(0); // black
            }
        }
    }

    float gpa = totpoints / totcred;
    int total = totcred;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nYour total credits hours is: %d", total);
    printf("\nYour GPA is: %.2f\n", gpa);
    new_line;
    main_choose2();
}
void academic_advisor()
{
    int selectt;
    printf("Febuary student registration (1)\n");
    printf("Sebtember student registration (2)\n");
    printf("Edit recent registration (3)\n");
    printf("Home Page (4)\n");
    printf("Exit (5)\n");
    scanf("%d", &selectt);
    if (selectt == 1)
    {
        new_line();
        feb_student();
    }
    else if (selectt == 2)
    {
        new_line();
        sep_student();
    }
    else if (selectt == 4)
    {
        new_line();
        mood();
    }
    else if (selectt == 3)
    {
        new_line();
        edit_reg();
    }
    else if (selectt == 5)
    {
        new_line();
        printf("\n                                                            SEE YOU SOON ^^!\n");
        new_line();
        return;
    }
    else
    {
        SetColor(196); // red
        printf("Invalid Input!\nplease try again");
        SetColor(0); // black
        new_line();
        academic_advisor();
    }
}
void sign()
{
    int degree;

    FILE *fp77 = fopen("grades.txt", "a");
    if (fp77 == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    if (stt.solom == 7)
    {
        int num = 22100;
        if (brr.month > 9 && brr.day > 9)
        {
            fprintf(fp77, "\n\n%d%d%d", num, brr.month, brr.day);
            fflush(fp77);
        }
        else if (brr.month <= 9 && brr.day <= 9)
        {
            fprintf(fp77, "\n\n%d0%d0%d", num, brr.month, brr.day);
            fflush(fp77);
        }
        else if (brr.month <= 9 && brr.day > 9)
        {
            fprintf(fp77, "\n\n%d0%d%d", num, brr.month, brr.day);
            fflush(fp77);
        }
        else if (brr.month > 9 && brr.day <= 9)
        {
            fprintf(fp77, "\n\n%d0%d%d", num, brr.month, brr.day);
            fflush(fp77);
        }
    }

    printf("Enter student registration number: \n");
    char regnum[20];
    scanf("%s", regnum);

    FILE *fp20 = fopen("grades.txt", "r");
    if (fp20 == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    int found = 0;
    while (!feof(fp20))
    {

        char line[256];
        fgets(line, sizeof(line), fp20);
        char *token = strtok(line, " ");
        char *id = token;

        if (strcmp(id, regnum) == 0)
        {
            printf("Please enter student degree in English placement test: ");
            scanf("%d", &degree);

            if (degree < 19 && stt.type == 1)
            {
                printf("\ncongratulations!\nNew student has been added successfully\n");
                fprintf(fp77, " U U U U U U U Information_System Introduction_to_computing Remedial_English Business Creativity Physics Precalculus 0.0 0");
                fflush(fp77);
                new_line();
                Semester_1_schedule_Scientific_science_Remedial_English();
                main_choose2();
            }
            else if (degree >= 19 && stt.type == 1)
            {
                printf("\ncongratulations!\nNew student has been added successfully\n");
                fprintf(fp77, " U U U U U U U Information_System Introduction_to_computing Academic_English Business Creativity Physics Precalculus 0.0 0");
                fflush(fp77);
                new_line();
                Semester_1_schedule_Scientific_science();
                main_choose2();
            }
            else if (degree < 19 && stt.type == 2)
            {
                printf("\ncongratulations!\nNew student has been added successfully\n");
                fprintf(fp77, " U U U U U U U Information_System Introduction_to_computing Remedial_English Business Creativity Physics Precalculus 0.0 0");
                fflush(fp77);
                new_line();
                Semester_1_schedule_Scientific_mathematics_Remedial_English();
                main_choose2();
            }
            else if (degree >= 19 && stt.type == 2)
            {
                printf("\ncongratulations!\nNew student has been added successfully\n");
                fprintf(fp77, " U U U U U U U Information_System Introduction_to_computing Academic_English Business Creativity Physics Precalculus 0.0 0");
                fflush(fp77);
                new_line();
                Semester_1_schedule_Scientific_mathematics();
                main_choose2();
            }

            else
                found = 1;
        }
    }

    if (!found)
    {
        SetColor(196); // red
        printf("Student not found!\nPlease try again\n");
        SetColor(0); // black
        new_line();
        sign();
    }
    fclose(fp20);
}
void feb_student()
{
    sign();
}
void edit_reg()
{
    FILE *fp1 = fopen("stdselection.txt", "r");
    FILE *fp3 = fopen("endselectioN.txt", "w");
    int subnum;

    Display_registration_advisor();

    printf("Enter the number of the subject which you want to delete\n");
    scanf("%d", &subnum);
    while (!feof(fp1))
    {

        fscanf(fp1, "%d %s %s %d %s", &crr.sub_num, crr.sub_code, crr.sub_name, &crr.sub_hour, crr.prequisites);
        if (subnum == crr.sub_num)
        {
            continue;
        }
        else
        {

            fprintf(fp3, "%d %s %s %d %s\n", crr.sub_num, crr.sub_code, crr.sub_name, crr.sub_hour, crr.prequisites);
        }
    }
    fclose(fp1);
    fclose(fp3);

    printf("The process is done\n");
    new_line();
    Display_edited();
}
void manager()
{
    FILE *fp = fopen("grades.txt", "a");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    int section;
    struct data_student sec_student;
    printf("Enter Your first, second, third, and last name:\n");
    scanf("%s %s %s %s", brr.fname_student, brr.sname_student, brr.tname_student, brr.lname_student);

    printf("\nEnter your total high school score out of 410:\n");
    scanf("%f", &brr.sec_grade);
    while (1)
    {
        if (brr.sec_grade < 0 || brr.sec_grade > 410)
        {
            SetColor(196); // red
            printf("Invalid input!\nPlease try again\n");
            SetColor(0); // black
            scanf("%d", &brr.sec_grade);
        }
        else
            break;
    }

    printf("\nEnter the day of birth:\n");
    scanf("%d", &brr.day);
    while (1)
    {
        if (brr.day < 1 || brr.day > 31)
        {
            SetColor(196); // red
            printf("Invalid input!\nPlease try again\n");
            SetColor(0); // black
            scanf("%d", &brr.day);
        }
        else
            break;
    }

    printf("\nEnter the month of birth:\n");
    scanf("%d", &brr.month);
    while (1)
    {
        if (brr.month < 1 || brr.month > 12)
        {
            SetColor(196); // red
            printf("Invalid input!\nPlease try again\n");
            SetColor(0); // black
            scanf("%d", &brr.month);
        }
        else
            break;
    }

    printf("\nEnter the year of birth:\n");
    scanf("%d", &brr.year);

    while (1)
    {
        if (brr.year <= 1970 || brr.year > 2005)
        {
            SetColor(196); // red
            printf("Invalid input!\nPlease try again\n");
            SetColor(0); // black
            scanf("%d", &brr.year);
        }
        else
            break;
    }

    if (brr.sec_grade < 246)
    {
        new_line();
        SetColor(196); // red
        printf("\nRejected!\n");
        SetColor(0); // black
        new_line();
        main_choose2();
        return;
    }

    printf("\nScientific science (1)\nScientific mathematics (2)\nliterary (3)\n");
    scanf("%d", &section);

    if (section == 3)
    {
        new_line();
        SetColor(196); // red
        printf("\nRejected!\n");
        SetColor(0); // black
        new_line();
        main_choose2();
        return;
    }
    else if (section == 1)
    {
        stt.solom = 7;

        new_line();
        SetColor(82); // green
        printf("\nAccepted!\n\n");
        SetColor(0); // black
        printf("Expenses will be paid under the category: ");
        if (brr.sec_grade >= 287)
            printf("A\n");
        else if (brr.sec_grade < 287 && brr.sec_grade >= 266.5)
            printf("B\n");
        else if (brr.sec_grade < 266.5 && brr.sec_grade > 246)
            printf("C\n");
        int num = 22100;
        if (brr.month > 9 && brr.day > 9)
        {
            printf("Your registration number is %d%d%d", num, brr.month, brr.day);
            stt.type = 1;
            new_line();
            main_choose2();
        }
        else if (brr.month <= 9 && brr.day <= 9)
        {
            printf("Your registration number is %d0%d0%d", num, brr.month, brr.day);
            stt.type = 1;
            new_line();
            main_choose2();
        }
        else if (brr.month <= 9 && brr.day > 9)
        {
            printf("Your registration number is %d0%d%d", num, brr.month, brr.day);
            stt.type = 1;
            new_line();
            main_choose2();
        }
        else if (brr.month > 9 && brr.day <= 9)
        {
            printf("Your registration number is %d%d0%d", num, brr.month, brr.day);
            stt.type = 1;
            new_line();
            main_choose2();
        }
    }

    else if (section == 2)
    {
        stt.solom = 7;
        new_line();
        SetColor(82); // green
        printf("\nAccepted!\n\n");
        SetColor(0); // black
        printf("Expenses will be paid under the category: ");
        if (brr.sec_grade >= 287)
            printf("A\n");
        else if (brr.sec_grade < 287 && brr.sec_grade >= 266.5)
            printf("B\n");
        else if (brr.sec_grade < 266.5 && brr.sec_grade > 246)
            printf("C\n");
        int num = 22100;
        if (brr.month > 9 && brr.day > 9)
        {
            printf("Your registration number is %d%d%d", num, brr.month, brr.day);
            stt.type = 2;
            new_line();
            main_choose2();
        }
        else if (brr.month <= 9 && brr.day <= 9)
        {
            printf("Your registration number is %d0%d0%d", num, brr.month, brr.day);
            stt.type = 2;
            new_line();
            main_choose2();
        }
        else if (brr.month <= 9 && brr.day > 9)
        {
            printf("Your registration number is %d0%d%d", num, brr.month, brr.day);
            stt.type = 2;
            new_line();
            main_choose2();
        }
        else if (brr.month > 9 && brr.day <= 9)
        {
            printf("Your registration number is %d%d0%d", num, brr.month, brr.day);
            stt.type = 2;
            new_line();
            main_choose2();
        }
    }

    else
    {
        SetColor(196); // red
        printf("invalid number");
        SetColor(0); // black
    }

    return;
}
void sep_student()
{
    printf("Enter student registration number: \n");
    scanf("%s", &stt.reg_number);

    for (int i = 0; i < 7; i++)
    {
        if (isalpha(stt.reg_number[i]))
        {
            printing_subjects();
            break;
        }
    }

    int regnum = atoi(stt.reg_number);

    FILE *fp = fopen("grades.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    int found = 0;
    while (!feof(fp))
    {

        fscanf(fp, "%d \n", &stt.reg);
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%s", stt.grade[i]);
        }
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%s", stt.sub[i]);
        }

        fscanf(fp, "%f %d", &stt.gpa, &stt.credit);

        if (stt.reg == regnum)
        {
            new_line();
            new_reg();
        }
    }

    if (!found)
    {
        SetColor(196); // red
        printf("Student not found!\nPlease try again\n");
        SetColor(0); // black
        new_line();
        sep_student();
    }
    fclose(fp);
}
main_choose3()
{
    int select;
    printf("Edit this registration (1)\n");
    printf("Student schedule (2)\n");
    printf("Home page (3)\n");
    printf("Exit (4)\n");
    scanf("%d", &select);

    if (select == 2)
    {
        new_line();
        samaa();
    }
    else if (select == 1)
    {
        new_line();
        edit_reg();
    }
    else if (select == 3)
    {
        new_line();
        mood();
    }
    else if (select == 4)
    {
        return;
    }
    else
    {
        SetColor(196); // red
        printf("Invalid input!\nPlease try again");
        SetColor(0); // black
        new_line();
        main_choose();
    }
}
void Scientific_mathematics()
{
    FILE *fp = fopen("schedule Scientific mathematics.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject1[10], code_Subject2[10], code_Subject3[10], code_Subject4[10], code_Subject5[10], code_Subject6[10], code_Subject7[10], code_Subject8[10], code_Subject9[10], code_Subject10[10], code_Subject11[10], code_Subject12[10], code_Subject13[10], code_Subject14[10];
    char Subject1[50], Subject2[50], Subject3[50], Subject4[50], Subject5[50], Subject6[50], Subject7[50], Subject8[50], Subject9[50], Subject10[50], Subject11[50], Subject12[50], Subject13[50], Subject14[50];
    char room1[15], room2[15], room3[15], room4[15], room5[15], room6[15], room7[15], room8[15], room9[15], room10[15], room11[15], room12[15], room13[15], room14[15];
    char day1[15], day2[15], day3[15], day4[15], day5[15], day6[15], day7[15], day8[15], day9[15], day10[15], day11[15], day12[15], day13[15], day14[15];
    char time1[15], time2[15], time3[15], time4[15], time5[15], time6[15], time7[15], time8[15], time9[15], time10[15], time11[15], time12[15], time13[15], time14[15];
    char lecturer1[50], lecturer2[50], lecturer3[50], lecturer4[50], lecturer5[50], lecturer6[50], lecturer7[50], lecturer8[50], lecturer9[50], lecturer10[50], lecturer11[50], lecturer12[50], lecturer13[50], lecturer14[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject1, Subject1, room1, day1, time1, lecturer1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject2, Subject2, room2, day2, time2, lecturer2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject3, Subject3, room3, day3, time3, lecturer3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject4, Subject4, room4, day4, time4, lecturer4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject5, Subject5, room5, day5, time5, lecturer5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject6, Subject6, room6, day6, time6, lecturer6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject7, Subject7, room7, day7, time7, lecturer7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject8, Subject8, room8, day8, time8, lecturer8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject9, Subject9, room9, day9, time9, lecturer9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject10, Subject10, room10, day10, time10, lecturer10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject11, Subject11, room11, day11, time11, lecturer11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject12, Subject12, room12, day12, time12, lecturer12);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject13, Subject13, room13, day13, time13, lecturer13);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group A");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%22s %32s %22s %20s %27s\n", code_Subject1, Subject1, room1, day1, time1, lecturer1);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject2, Subject2, room2, day2, time2, lecturer2);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject3, Subject3, room3, day3, time3, lecturer3);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject4, Subject4, room4, day4, time4, lecturer4);
    printf("%s%30s %24s %22s %20s %27s\n", code_Subject5, Subject5, room5, day5, time5, lecturer5);
    printf("%s%48s %6s %22s %20s %27s\n", code_Subject6, Subject6, room6, day6, time6, lecturer6);
    printf("%s%34s %20s %22s %20s %27s\n", code_Subject7, Subject7, room7, day7, time7, lecturer7);
    printf("%s%22s %32s %22s %20s %27s\n", code_Subject8, Subject8, room8, day8, time8, lecturer8);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject9, Subject9, room9, day9, time9, lecturer9);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject10, Subject10, room10, day10, time10, lecturer10);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    printf("%s%30s %24s %22s %20s %27s\n", code_Subject12, Subject12, room12, day12, time12, lecturer12);
    printf("%s%48s %6s %22s %20s %27s\n", code_Subject13, Subject13, room13, day13, time13, lecturer13);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void schedule_Scientific_science()
{
    FILE *fp = fopen("schedule Scientific science .txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject_Scientific_science1[10], code_Subject_Scientific_science2[10], code_Subject_Scientific_science3[10], code_Subject_Scientific_science4[10], code_Subject_Scientific_science5[10], code_Subject_Scientific_science6[10], code_Subject_Scientific_science7[10], code_Subject_Scientific_science8[10], code_Subject_Scientific_science9[10], code_Subject_Scientific_science10[10], code_Subject_Scientific_science11[10], code_Subject_Scientific_science12[10], code_Subject_Scientific_science13[10], code_Subject_Scientific_science14[10];
    char Subject_Scientific_science1[50], Subject_Scientific_science2[50], Subject_Scientific_science3[50], Subject_Scientific_science4[50], Subject_Scientific_science5[50], Subject_Scientific_science6[50], Subject_Scientific_science7[50], Subject_Scientific_science8[50], Subject_Scientific_science9[50], Subject_Scientific_science10[50], Subject_Scientific_science11[50], Subject_Scientific_science12[50], Subject_Scientific_science13[50], Subject_Scientific_science14[50];
    char room_Scientific_science1[15], room_Scientific_science2[15], room_Scientific_science3[15], room_Scientific_science4[15], room_Scientific_science5[15], room_Scientific_science6[15], room_Scientific_science7[15], room_Scientific_science8[15], room_Scientific_science9[15], room_Scientific_science10[15], room_Scientific_science11[15], room_Scientific_science12[15], room_Scientific_science13[15], room_Scientific_science14[15];
    char day_Scientific_science1[15], day_Scientific_science2[15], day_Scientific_science3[15], day_Scientific_science4[15], day_Scientific_science5[15], day_Scientific_science6[15], day_Scientific_science7[15], day_Scientific_science8[15], day_Scientific_science9[15], day_Scientific_science10[15], day_Scientific_science11[15], day_Scientific_science12[15], day_Scientific_science13[15], day_Scientific_science14[15];
    char time_Scientific_science1[15], time_Scientific_science2[15], time_Scientific_science3[15], time_Scientific_science4[15], time_Scientific_science5[15], time_Scientific_science6[15], time_Scientific_science7[15], time_Scientific_science8[15], time_Scientific_science9[15], time_Scientific_science10[15], time_Scientific_science11[15], time_Scientific_science12[15], time_Scientific_science13[15], time_Scientific_science14[15];
    char lecturer_Scientific_science1[50], lecturer_Scientific_science2[50], lecturer_Scientific_science3[50], lecturer_Scientific_science4[50], lecturer_Scientific_science5[50], lecturer_Scientific_science6[50], lecturer_Scientific_science7[50], lecturer_Scientific_science8[50], lecturer_Scientific_science9[50], lecturer_Scientific_science10[50], lecturer_Scientific_science11[50], lecturer_Scientific_science12[50], lecturer_Scientific_science13[50], lecturer_Scientific_science14[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science13, Subject_Scientific_science13, room_Scientific_science13, day_Scientific_science13, time_Scientific_science13, lecturer_Scientific_science13);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science14, Subject_Scientific_science14, room_Scientific_science14, day_Scientific_science14, time_Scientific_science14, lecturer_Scientific_science14);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group C");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
    printf("%s%31s %23s %22s %20s %27s\n", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
    printf("%s%18s %36s %22s %20s %27s\n", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject_Scientific_science13, Subject_Scientific_science13, room_Scientific_science13, day_Scientific_science13, time_Scientific_science13, lecturer_Scientific_science13);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject_Scientific_science14, Subject_Scientific_science14, room_Scientific_science14, day_Scientific_science14, time_Scientific_science14, lecturer_Scientific_science14);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void schedule_Physic()
{
    FILE *fp = fopen("schedule Physic .txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject1[10], code_Subject2[10], code_Subject3[10], code_Subject4[10], code_Subject5[10], code_Subject6[10], code_Subject7[10], code_Subject8[10], code_Subject9[10], code_Subject10[10], code_Subject11[10], code_Subject12[10], code_Subject13[10], code_Subject14[10];
    char Subject1[50], Subject2[50], Subject3[50], Subject4[50], Subject5[50], Subject6[50], Subject7[50], Subject8[50], Subject9[50], Subject10[50], Subject11[50], Subject12[50], Subject13[50], Subject14[50];
    char room1[15], room2[15], room3[15], room4[15], room5[15], room6[15], room7[15], room8[15], room9[15], room10[15], room11[15], room12[15], room13[15], room14[15];
    char day1[15], day2[15], day3[15], day4[15], day5[15], day6[15], day7[15], day8[15], day9[15], day10[15], day11[15], day12[15], day13[15], day14[15];
    char time1[15], time2[15], time3[15], time4[15], time5[15], time6[15], time7[15], time8[15], time9[15], time10[15], time11[15], time12[15], time13[15], time14[15];
    char lecturer1[50], lecturer2[50], lecturer3[50], lecturer4[50], lecturer5[50], lecturer6[50], lecturer7[50], lecturer8[50], lecturer9[50], lecturer10[50], lecturer11[50], lecturer12[50], lecturer13[50], lecturer14[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject1, Subject1, room1, day1, time1, lecturer1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject2, Subject2, room2, day2, time2, lecturer2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject3, Subject3, room3, day3, time3, lecturer3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject4, Subject4, room4, day4, time4, lecturer4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject5, Subject5, room5, day5, time5, lecturer5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject6, Subject6, room6, day6, time6, lecturer6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject7, Subject7, room7, day7, time7, lecturer7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject8, Subject8, room8, day8, time8, lecturer8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject9, Subject9, room9, day9, time9, lecturer9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject10, Subject10, room10, day10, time10, lecturer10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject11, Subject11, room11, day11, time11, lecturer11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject12, Subject12, room12, day12, time12, lecturer12);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject13, Subject13, room13, day13, time13, lecturer13);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group D");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject1, Subject1, room1, day1, time1, lecturer1); //
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject2, Subject2, room2, day2, time2, lecturer2);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject3, Subject3, room3, day3, time3, lecturer3);
    printf("%s%15s %39s %22s %20s %27s\n", code_Subject4, Subject4, room4, day4, time4, lecturer4);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject5, Subject5, room5, day5, time5, lecturer5);
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject6, Subject6, room6, day6, time6, lecturer6);
    printf("%s%31s %23s %22s %20s %27s\n", code_Subject7, Subject7, room7, day7, time7, lecturer7);
    printf("%s%18s %36s %22s %20s %27s\n", code_Subject8, Subject8, room8, day8, time8, lecturer8);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject9, Subject9, room9, day9, time9, lecturer9);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject10, Subject10, room10, day10, time10, lecturer10);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    printf("%s%15s %39s %22s %20s %27s\n", code_Subject12, Subject12, room12, day12, time12, lecturer12);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject13, Subject13, room13, day13, time13, lecturer13);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void schedule_Precalculus()
{
    FILE *fp = fopen("schedule Precalculus.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject1[10], code_Subject2[10], code_Subject3[10], code_Subject4[10], code_Subject5[10], code_Subject6[10], code_Subject7[10], code_Subject8[10], code_Subject9[10], code_Subject10[10], code_Subject11[10], code_Subject12[10], code_Subject13[10], code_Subject14[10];
    char Subject1[50], Subject2[50], Subject3[50], Subject4[50], Subject5[50], Subject6[50], Subject7[50], Subject8[50], Subject9[50], Subject10[50], Subject11[50], Subject12[50], Subject13[50], Subject14[50];
    char room1[15], room2[15], room3[15], room4[15], room5[15], room6[15], room7[15], room8[15], room9[15], room10[15], room11[15], room12[15], room13[15], room14[15];
    char day1[15], day2[15], day3[15], day4[15], day5[15], day6[15], day7[15], day8[15], day9[15], day10[15], day11[15], day12[15], day13[15], day14[15];
    char time1[15], time2[15], time3[15], time4[15], time5[15], time6[15], time7[15], time8[15], time9[15], time10[15], time11[15], time12[15], time13[15], time14[15];
    char lecturer1[50], lecturer2[50], lecturer3[50], lecturer4[50], lecturer5[50], lecturer6[50], lecturer7[50], lecturer8[50], lecturer9[50], lecturer10[50], lecturer11[50], lecturer12[50], lecturer13[50], lecturer14[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject1, Subject1, room1, day1, time1, lecturer1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject2, Subject2, room2, day2, time2, lecturer2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject3, Subject3, room3, day3, time3, lecturer3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject4, Subject4, room4, day4, time4, lecturer4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject5, Subject5, room5, day5, time5, lecturer5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject6, Subject6, room6, day6, time6, lecturer6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject7, Subject7, room7, day7, time7, lecturer7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject8, Subject8, room8, day8, time8, lecturer8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject9, Subject9, room9, day9, time9, lecturer9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject10, Subject10, room10, day10, time10, lecturer10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject11, Subject11, room11, day11, time11, lecturer11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject12, Subject12, room12, day12, time12, lecturer12);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject13, Subject13, room13, day13, time13, lecturer13);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group B");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%22s %32s %22s %20s %27s\n", code_Subject1, Subject1, room1, day1, time1, lecturer1);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject2, Subject2, room2, day2, time2, lecturer2);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject3, Subject3, room3, day3, time3, lecturer3);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject4, Subject4, room4, day4, time4, lecturer4);
    printf("%s%30s %24s %22s %20s %27s\n", code_Subject5, Subject5, room5, day5, time5, lecturer5);
    printf("%s%48s %6s %22s %20s %27s\n", code_Subject6, Subject6, room6, day6, time6, lecturer6);
    printf("%s%34s %20s %22s %20s %27s\n", code_Subject7, Subject7, room7, day7, time7, lecturer7);
    printf("%s%22s %32s %22s %20s %27s\n", code_Subject8, Subject8, room8, day8, time8, lecturer8);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject9, Subject9, room9, day9, time9, lecturer9);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject10, Subject10, room10, day10, time10, lecturer10);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    printf("%s%30s %24s %22s %20s %27s\n", code_Subject12, Subject12, room12, day12, time12, lecturer12);
    printf("%s%48s %6s %22s %20s %27s\n", code_Subject13, Subject13, room13, day13, time13, lecturer13);
    printf("%s%42s %12s %22s %20s %27s\n", code_Subject14, Subject14, room14, day14, time14, lecturer14);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void schedule_Introduction_to_Computing()
{
    FILE *fp = fopen("schedule_Introduction_to_Computing.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject1[10], code_Subject2[10], code_Subject3[10], code_Subject4[10], code_Subject5[10], code_Subject6[10], code_Subject7[10], code_Subject8[10], code_Subject9[10], code_Subject10[10], code_Subject11[10], code_Subject12[10];
    char Subject1[50], Subject2[50], Subject3[50], Subject4[50], Subject5[50], Subject6[50], Subject7[50], Subject8[50], Subject9[50], Subject10[50], Subject11[50];
    char room1[15], room2[15], room3[15], room4[15], room5[15], room6[15], room7[15], room8[15], room9[15], room10[15], room11[15];
    char day1[15], day2[15], day3[15], day4[15], day5[15], day6[15], day7[15], day8[15], day9[15], day10[15], day11[15];
    char time1[15], time2[15], time3[15], time4[15], time5[15], time6[15], time7[15], time8[15], time9[15], time10[15], time11[15];
    char lecturer1[50], lecturer2[50], lecturer3[50], lecturer4[50], lecturer5[50], lecturer6[50], lecturer7[50], lecturer8[50], lecturer9[50], lecturer10[50], lecturer11[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject1, Subject1, room1, day1, time1, lecturer1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject2, Subject2, room2, day2, time2, lecturer2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject3, Subject3, room3, day3, time3, lecturer3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject4, Subject4, room4, day4, time4, lecturer4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject5, Subject5, room5, day5, time5, lecturer5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject6, Subject6, room6, day6, time6, lecturer6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject7, Subject7, room7, day7, time7, lecturer7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject8, Subject8, room8, day8, time8, lecturer8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject9, Subject9, room9, day9, time9, lecturer9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject10, Subject10, room10, day10, time10, lecturer10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group E");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%18s %36s %22s %20s %27s\n", code_Subject1, Subject1, room1, day1, time1, lecturer1);
    printf("%s%33s %21s %22s %20s %27s\n", code_Subject2, Subject2, room2, day2, time2, lecturer2);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject3, Subject3, room3, day3, time3, lecturer3);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject4, Subject4, room4, day4, time4, lecturer4);
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject5, Subject5, room5, day5, time5, lecturer5);
    printf("%s%31s %23s %22s %20s %27s\n", code_Subject6, Subject6, room6, day6, time6, lecturer6);
    printf("%s%18s %36s %22s %20s %27s\n", code_Subject7, Subject7, room7, day7, time7, lecturer7);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject8, Subject8, room8, day8, time8, lecturer8);
    printf("%s%33s %21s %22s %20s %27s\n", code_Subject9, Subject9, room9, day9, time9, lecturer9);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject10, Subject10, room10, day10, time10, lecturer10);
    printf("%s%45s %9s %22s %20s %27s\n", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void Academic_English()
{
    FILE *fp = fopen("Academic English.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject1[10], code_Subject2[10], code_Subject3[10], code_Subject4[10], code_Subject5[10], code_Subject6[10], code_Subject7[10], code_Subject8[10], code_Subject9[10], code_Subject10[10], code_Subject11[10], code_Subject12[10];
    char Subject1[50], Subject2[50], Subject3[50], Subject4[50], Subject5[50], Subject6[50], Subject7[50], Subject8[50], Subject9[50], Subject10[50], Subject11[50];
    char room1[15], room2[15], room3[15], room4[15], room5[15], room6[15], room7[15], room8[15], room9[15], room10[15], room11[15];
    char day1[15], day2[15], day3[15], day4[15], day5[15], day6[15], day7[15], day8[15], day9[15], day10[15], day11[15];
    char time1[15], time2[15], time3[15], time4[15], time5[15], time6[15], time7[15], time8[15], time9[15], time10[15], time11[15];
    char lecturer1[50], lecturer2[50], lecturer3[50], lecturer4[50], lecturer5[50], lecturer6[50], lecturer7[50], lecturer8[50], lecturer9[50], lecturer10[50], lecturer11[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject1, Subject1, room1, day1, time1, lecturer1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject2, Subject2, room2, day2, time2, lecturer2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject3, Subject3, room3, day3, time3, lecturer3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject4, Subject4, room4, day4, time4, lecturer4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject5, Subject5, room5, day5, time5, lecturer5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject6, Subject6, room6, day6, time6, lecturer6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject7, Subject7, room7, day7, time7, lecturer7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject8, Subject8, room8, day8, time8, lecturer8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject9, Subject9, room9, day9, time9, lecturer9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject10, Subject10, room10, day10, time10, lecturer10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group F");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject1, Subject1, room1, day1, time1, lecturer1);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject2, Subject2, room2, day2, time2, lecturer2);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject3, Subject3, room3, day3, time3, lecturer3);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject4, Subject4, room4, day4, time4, lecturer4);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject5, Subject5, room5, day5, time5, lecturer5);
    printf("%s%31s %23s %22s %20s %27s\n", code_Subject6, Subject6, room6, day6, time6, lecturer6);
    printf("%s%18s %36s %22s %20s %27s\n", code_Subject7, Subject7, room7, day7, time7, lecturer7);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject8, Subject8, room8, day8, time8, lecturer8);
    printf("%s%39s %15s %22s %20s %27s\n", code_Subject9, Subject9, room9, day9, time9, lecturer9);
    printf("%s%27s %27s %22s %20s %27s\n", code_Subject10, Subject10, room10, day10, time10, lecturer10);
    printf("%s%24s %30s %22s %20s %27s\n", code_Subject11, Subject11, room11, day11, time11, lecturer11);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void Semester_1_schedule_Scientific_mathematics()
{
    FILE *fp = fopen("Semester#1,schedule Scientific mathematics.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject_Scientific_science1[10], code_Subject_Scientific_science2[10], code_Subject_Scientific_science3[10], code_Subject_Scientific_science4[10], code_Subject_Scientific_science5[10], code_Subject_Scientific_science6[10], code_Subject_Scientific_science7[10], code_Subject_Scientific_science8[10], code_Subject_Scientific_science9[10], code_Subject_Scientific_science10[10], code_Subject_Scientific_science11[10], code_Subject_Scientific_science12[10];
    char Subject_Scientific_science1[50], Subject_Scientific_science2[50], Subject_Scientific_science3[50], Subject_Scientific_science4[50], Subject_Scientific_science5[50], Subject_Scientific_science6[50], Subject_Scientific_science7[50], Subject_Scientific_science8[50], Subject_Scientific_science9[50], Subject_Scientific_science10[50], Subject_Scientific_science11[50], Subject_Scientific_science12[50];
    char room_Scientific_science1[15], room_Scientific_science2[15], room_Scientific_science3[15], room_Scientific_science4[15], room_Scientific_science5[15], room_Scientific_science6[15], room_Scientific_science7[15], room_Scientific_science8[15], room_Scientific_science9[15], room_Scientific_science10[15], room_Scientific_science11[15], room_Scientific_science12[15];
    char day_Scientific_science1[15], day_Scientific_science2[15], day_Scientific_science3[15], day_Scientific_science4[15], day_Scientific_science5[15], day_Scientific_science6[15], day_Scientific_science7[15], day_Scientific_science8[15], day_Scientific_science9[15], day_Scientific_science10[15], day_Scientific_science11[15], day_Scientific_science12[15];
    char time_Scientific_science1[15], time_Scientific_science2[15], time_Scientific_science3[15], time_Scientific_science4[15], time_Scientific_science5[15], time_Scientific_science6[15], time_Scientific_science7[15], time_Scientific_science8[15], time_Scientific_science9[15], time_Scientific_science10[15], time_Scientific_science11[15], time_Scientific_science12[15];
    char lecturer_Scientific_science1[50], lecturer_Scientific_science2[50], lecturer_Scientific_science3[50], lecturer_Scientific_science4[50], lecturer_Scientific_science5[50], lecturer_Scientific_science6[50], lecturer_Scientific_science7[50], lecturer_Scientific_science8[50], lecturer_Scientific_science9[50], lecturer_Scientific_science10[50], lecturer_Scientific_science11[50], lecturer_Scientific_science12[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group A");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%18s %35s %22s %20s %27s\n", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
    printf("%s%32s %21s %22s %20s %27s\n", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
    printf("%s%18s %35s %22s %20s %27s\n", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void Semester_1_schedule_Scientific_science()
{
    FILE *fp = fopen("Semester#1,schedule Scientific science .txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject_Scientific_science1[10], code_Subject_Scientific_science2[10], code_Subject_Scientific_science3[10], code_Subject_Scientific_science4[10], code_Subject_Scientific_science5[10], code_Subject_Scientific_science6[10], code_Subject_Scientific_science7[10], code_Subject_Scientific_science8[10], code_Subject_Scientific_science9[10], code_Subject_Scientific_science10[10], code_Subject_Scientific_science11[10], code_Subject_Scientific_science12[10];
    char Subject_Scientific_science1[50], Subject_Scientific_science2[50], Subject_Scientific_science3[50], Subject_Scientific_science4[50], Subject_Scientific_science5[50], Subject_Scientific_science6[50], Subject_Scientific_science7[50], Subject_Scientific_science8[50], Subject_Scientific_science9[50], Subject_Scientific_science10[50], Subject_Scientific_science11[50], Subject_Scientific_science12[50];
    char room_Scientific_science1[15], room_Scientific_science2[15], room_Scientific_science3[15], room_Scientific_science4[15], room_Scientific_science5[15], room_Scientific_science6[15], room_Scientific_science7[15], room_Scientific_science8[15], room_Scientific_science9[15], room_Scientific_science10[15], room_Scientific_science11[15], room_Scientific_science12[15];
    char day_Scientific_science1[15], day_Scientific_science2[15], day_Scientific_science3[15], day_Scientific_science4[15], day_Scientific_science5[15], day_Scientific_science6[15], day_Scientific_science7[15], day_Scientific_science8[15], day_Scientific_science9[15], day_Scientific_science10[15], day_Scientific_science11[15], day_Scientific_science12[15];
    char time_Scientific_science1[15], time_Scientific_science2[15], time_Scientific_science3[15], time_Scientific_science4[15], time_Scientific_science5[15], time_Scientific_science6[15], time_Scientific_science7[15], time_Scientific_science8[15], time_Scientific_science9[15], time_Scientific_science10[15], time_Scientific_science11[15], time_Scientific_science12[15];
    char lecturer_Scientific_science1[50], lecturer_Scientific_science2[50], lecturer_Scientific_science3[50], lecturer_Scientific_science4[50], lecturer_Scientific_science5[50], lecturer_Scientific_science6[50], lecturer_Scientific_science7[50], lecturer_Scientific_science8[50], lecturer_Scientific_science9[50], lecturer_Scientific_science10[50], lecturer_Scientific_science11[50], lecturer_Scientific_science12[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group C");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%19s %34s %22s %20s %27s\n", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
    printf("%s%32s %21s %22s %20s %27s\n", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
    printf("%s%19s %34s %22s %20s %27s\n", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void Semester_1_schedule_Scientific_science_Remedial_English()
{
    FILE *fp = fopen("Semester_1_schedule_Scientific_science_Remedial English.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject_Scientific_science1[10], code_Subject_Scientific_science2[10], code_Subject_Scientific_science3[10], code_Subject_Scientific_science4[10], code_Subject_Scientific_science5[10], code_Subject_Scientific_science6[10], code_Subject_Scientific_science7[10], code_Subject_Scientific_science8[10], code_Subject_Scientific_science9[10], code_Subject_Scientific_science10[10], code_Subject_Scientific_science11[10], code_Subject_Scientific_science12[10];
    char Subject_Scientific_science1[50], Subject_Scientific_science2[50], Subject_Scientific_science3[50], Subject_Scientific_science4[50], Subject_Scientific_science5[50], Subject_Scientific_science6[50], Subject_Scientific_science7[50], Subject_Scientific_science8[50], Subject_Scientific_science9[50], Subject_Scientific_science10[50], Subject_Scientific_science11[50], Subject_Scientific_science12[50];
    char room_Scientific_science1[15], room_Scientific_science2[15], room_Scientific_science3[15], room_Scientific_science4[15], room_Scientific_science5[15], room_Scientific_science6[15], room_Scientific_science7[15], room_Scientific_science8[15], room_Scientific_science9[15], room_Scientific_science10[15], room_Scientific_science11[15], room_Scientific_science12[15];
    char day_Scientific_science1[15], day_Scientific_science2[15], day_Scientific_science3[15], day_Scientific_science4[15], day_Scientific_science5[15], day_Scientific_science6[15], day_Scientific_science7[15], day_Scientific_science8[15], day_Scientific_science9[15], day_Scientific_science10[15], day_Scientific_science11[15], day_Scientific_science12[15];
    char time_Scientific_science1[15], time_Scientific_science2[15], time_Scientific_science3[15], time_Scientific_science4[15], time_Scientific_science5[15], time_Scientific_science6[15], time_Scientific_science7[15], time_Scientific_science8[15], time_Scientific_science9[15], time_Scientific_science10[15], time_Scientific_science11[15], time_Scientific_science12[15];
    char lecturer_Scientific_science1[50], lecturer_Scientific_science2[50], lecturer_Scientific_science3[50], lecturer_Scientific_science4[50], lecturer_Scientific_science5[50], lecturer_Scientific_science6[50], lecturer_Scientific_science7[50], lecturer_Scientific_science8[50], lecturer_Scientific_science9[50], lecturer_Scientific_science10[50], lecturer_Scientific_science11[50], lecturer_Scientific_science12[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group D");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%19s %34s %22s %20s %27s\n", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
    printf("%s%32s %21s %22s %20s %27s\n", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
    printf("%s%19s %34s %22s %20s %27s\n", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
void Semester_1_schedule_Scientific_mathematics_Remedial_English()
{

    FILE *fp = fopen("Semester#1,schedule Scientific mathematics_Remedial_English.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    //////////////////////////////////////declare varibales/////////////////////////////////////////////////////////
    char code_Subject_Scientific_science1[10], code_Subject_Scientific_science2[10], code_Subject_Scientific_science3[10], code_Subject_Scientific_science4[10], code_Subject_Scientific_science5[10], code_Subject_Scientific_science6[10], code_Subject_Scientific_science7[10], code_Subject_Scientific_science8[10], code_Subject_Scientific_science9[10], code_Subject_Scientific_science10[10], code_Subject_Scientific_science11[10], code_Subject_Scientific_science12[10];
    char Subject_Scientific_science1[50], Subject_Scientific_science2[50], Subject_Scientific_science3[50], Subject_Scientific_science4[50], Subject_Scientific_science5[50], Subject_Scientific_science6[50], Subject_Scientific_science7[50], Subject_Scientific_science8[50], Subject_Scientific_science9[50], Subject_Scientific_science10[50], Subject_Scientific_science11[50], Subject_Scientific_science12[50];
    char room_Scientific_science1[15], room_Scientific_science2[15], room_Scientific_science3[15], room_Scientific_science4[15], room_Scientific_science5[15], room_Scientific_science6[15], room_Scientific_science7[15], room_Scientific_science8[15], room_Scientific_science9[15], room_Scientific_science10[15], room_Scientific_science11[15], room_Scientific_science12[15];
    char day_Scientific_science1[15], day_Scientific_science2[15], day_Scientific_science3[15], day_Scientific_science4[15], day_Scientific_science5[15], day_Scientific_science6[15], day_Scientific_science7[15], day_Scientific_science8[15], day_Scientific_science9[15], day_Scientific_science10[15], day_Scientific_science11[15], day_Scientific_science12[15];
    char time_Scientific_science1[15], time_Scientific_science2[15], time_Scientific_science3[15], time_Scientific_science4[15], time_Scientific_science5[15], time_Scientific_science6[15], time_Scientific_science7[15], time_Scientific_science8[15], time_Scientific_science9[15], time_Scientific_science10[15], time_Scientific_science11[15], time_Scientific_science12[15];
    char lecturer_Scientific_science1[50], lecturer_Scientific_science2[50], lecturer_Scientific_science3[50], lecturer_Scientific_science4[50], lecturer_Scientific_science5[50], lecturer_Scientific_science6[50], lecturer_Scientific_science7[50], lecturer_Scientific_science8[50], lecturer_Scientific_science9[50], lecturer_Scientific_science10[50], lecturer_Scientific_science11[50], lecturer_Scientific_science12[50];
    /////////////////////////////////////////scan from file /////////////////////////////////////////////////////
    while (!feof(fp))
    {
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
        fscanf(fp, "%s %s %s %s %s %s", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    }

    ///////////////////////////////////////////print /////////////////////////////////////////
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%70s\n", "Group B");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-30s %-25s %-22s %-21s %-22s %s\n", "Code", "Subject", "Room", "Day", "Time", "Lecturer");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s%18s %35s %22s %20s %27s\n", code_Subject_Scientific_science1, Subject_Scientific_science1, room_Scientific_science1, day_Scientific_science1, time_Scientific_science1, lecturer_Scientific_science1);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science2, Subject_Scientific_science2, room_Scientific_science2, day_Scientific_science2, time_Scientific_science2, lecturer_Scientific_science2);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science3, Subject_Scientific_science3, room_Scientific_science3, day_Scientific_science3, time_Scientific_science3, lecturer_Scientific_science3);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science4, Subject_Scientific_science4, room_Scientific_science4, day_Scientific_science4, time_Scientific_science4, lecturer_Scientific_science4);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science5, Subject_Scientific_science5, room_Scientific_science5, day_Scientific_science5, time_Scientific_science5, lecturer_Scientific_science5);
    printf("%s%32s %21s %22s %20s %27s\n", code_Subject_Scientific_science6, Subject_Scientific_science6, room_Scientific_science6, day_Scientific_science6, time_Scientific_science6, lecturer_Scientific_science6);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science7, Subject_Scientific_science7, room_Scientific_science7, day_Scientific_science7, time_Scientific_science7, lecturer_Scientific_science7);
    printf("%s%18s %35s %22s %20s %27s\n", code_Subject_Scientific_science8, Subject_Scientific_science8, room_Scientific_science8, day_Scientific_science8, time_Scientific_science8, lecturer_Scientific_science8);
    printf("%s%24s %29s %22s %20s %27s\n", code_Subject_Scientific_science9, Subject_Scientific_science9, room_Scientific_science9, day_Scientific_science9, time_Scientific_science9, lecturer_Scientific_science9);
    printf("%s%33s %20s %22s %20s %27s\n", code_Subject_Scientific_science10, Subject_Scientific_science10, room_Scientific_science10, day_Scientific_science10, time_Scientific_science10, lecturer_Scientific_science10);
    printf("%s%43s %10s %22s %20s %27s\n", code_Subject_Scientific_science11, Subject_Scientific_science11, room_Scientific_science11, day_Scientific_science11, time_Scientific_science11, lecturer_Scientific_science11);
    printf("%s%15s %38s %22s %20s %27s\n", code_Subject_Scientific_science12, Subject_Scientific_science12, room_Scientific_science12, day_Scientific_science12, time_Scientific_science12, lecturer_Scientific_science12);
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    fclose(fp);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

    system("color B0");
    printf("============================================================================================================================================\n");
    printf("                                            Arab Academy for Science, Technology & Maritime Transport                                             \n");
    printf("                                                college of computing and information technology                                             \n");
    printf("============================================================================================================================================\n");
    mood();
    return 0;
}
