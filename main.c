#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>


typedef struct
{
    int semester, marks;
    float c_hr;
    long long int ID;
    char name[25], password[10], course_name[8], SGPA[6], CGPA[6];

}login_student_info;

typedef struct
{
    int semes;
    float hr;
    char sub[8];

}info;

typedef struct
{
    char ID[12], name[25];
    char SGPA[8], CGPA[8];

}smester_copy;

void program_name();
void admin_registration();
void student_registration();
int semester_counter(FILE *fp_co_inf);
void login_fnc();
void admin_login();
int add_semester_marks();
void add_notice();
float sgpa_calculate(login_student_info *n_semester_course_info, int i);
float cgpa_calculate(float SGPA, int semester_counter, char *ID);
float grade_calculate(int marks);
char* get_semester_file_name(int *semester_counter);
void ID_sorting(int total_student);
int find_total_student();
int search_student(char *ID, char *pass);
void student_login(char *ID);
void summary(char *ID);
void print_summary(char *ID, login_student_info store_result);
void previous_course_result(char *ID);
char* get_space();
void check_notice();


int compare(const void *p, const void *q)
{
    const login_student_info *a = p;
    const login_student_info *b = q;

    return (a->ID - b->ID);
}

int main()
{
    int a, b, c, i, c_hr;
    char str[10];

    while(1){
        program_name();  // printing program name.
        printf("\n%s[1] Signup\n%s[2] Login\n%s[3] Exit\n\n%sEnter Your Option..", get_space(), get_space(), get_space(),get_space());
        scanf("%d", &a);
        system("cls");
        if(a==1){   /// admin & student (registration)
            printf("%sEnter Account Type\n\n%s[1] Admin\n%s[2] Student\n%s[3] Back To Main Menu\n\n%sEnter Your Option..", get_space(), get_space(), get_space(),get_space(), get_space());
            scanf("%d", &b);
          system("cls");
            if(b==1){
                admin_registration();  //Admin registration function.
            }
            else if(b==2){  // student registration function.
                student_registration();
            }
        }
        else if(a==2){
            system("cls");
            login_fnc();  /// admin - student (login)
        }
        else if(a==3){
            break;
        }
    }



    return 0;
}

void program_name()
{
    char program_name[] = "**Student Management System**";
    int i;

    printf("\t\t\t\t\t  ");

    for(i=0; program_name[i]!='\0'; i++){
        printf("%c", program_name[i]);
        Sleep(50);
    }
    printf("\n\n\n");
}

void admin_registration()
{
    FILE *fp_co_inf;
    char *str[10];
    int t_sub, a, i, check=0, x;
    float *c_hr;


    while(1){
        printf("%sEnter Admin key ..", get_space());   /// 123456
        scanf("%d", &a);
        system("cls");
        if(a==123456){
            while(1){
                printf("%sEnter This Semester Total Subject : ", get_space());
                scanf("%d", &t_sub);
                printf("\n");
                c_hr = (float*)malloc(sizeof(float)*(t_sub+1));
                if(!c_hr){
                    printf("Allocation Failed");
                    return;
                }
                for(i=0; i<t_sub; i++){
                    str[i] = (char*)malloc(sizeof(char)*10);
                    if(!str[i]){
                        printf("Allocation Failed");
                        return;
                    }
                    printf("%sEnter Course Title : ", get_space());
                    scanf("%s", str[i]);
                    printf("%sEnter  Credit Hours : ", get_space());
                    scanf("%f", &c_hr[i]);
                }
                printf("\n\n\t\t\t\t [#] If You want to Save It Then Press [1]. Otherwise Press [2]..");
                scanf("%d", &a);
                system("cls");
                if(a==1){
                    fp_co_inf = fopen("Course_info.txt", "a+");
                    if(!fp_co_inf){
                        printf("Course_info.txt File Opening Failed");
                        return ;
                    }
                    x = semester_counter(fp_co_inf);   // semester counter function
                    for(i=0; i<t_sub; i++){
                        fprintf(fp_co_inf, "%d %s %.3f\n", x, str[i], c_hr[i]);
                        free(str[i]);
                    }
                    fclose(fp_co_inf);
                    free(c_hr);
                    check++;
                    break;
                }
                else if(a==2){
                    system("cls");
                }
            }
            if(check){
                printf("\n\n\n\n\n%sSave Successful", get_space());
                Sleep(3000);
                system("cls");
                break;
            }
        }
        else{
            printf("%sWrong Password. Please Try Again.\n", get_space());
        }
    }

}

int semester_counter(FILE *fp_co_inf)
{
   int course_counter = 0;
   char line[30], sub[10];
   float c_hr;

    while(NULL!=(fgets(line, 28, fp_co_inf))){
        sscanf(line, "%d %s %f", &course_counter, sub, &c_hr);
    }

    fseek(fp_co_inf, SEEK_SET, 0);

    return ++course_counter;
}

void student_registration()
{
    FILE *st_info;
    char name[25], *ID, *pass;
    int i, j, n, check = 0;


    ID = (char*)malloc(sizeof(char)*12);
    pass = (char*)malloc(sizeof(char)*9);
    if(!ID || !pass){
        printf("Allocation Failed");
        return;
    }
    while(1){
        printf("\t\t\t\t[N.B] Use '_' instead of space enxmple Jack_Pritom_Soren\n\n");
        printf("%sEnter Student Name : ", get_space());
        scanf("%s", name);
        printf("%sEnter Student ID : ", get_space());
        scanf("%s", ID);
        printf("%sEnter Password [N.B] (Maximum 8 character) : ", get_space());
        scanf("%s", pass);
        printf("\n\n\t\t\t\t [#] If You want to Save It Then Press [1] Otherwise Press [2]..");
        scanf("%d", &n);
       // system("cls");
        if(n==1){
            st_info = fopen("Stu_login_info.txt", "a");
            fprintf(st_info, "%s %s %s\n", ID, pass, name);
            check++;
            fclose(st_info);
            break;
        }
        else if(n==2){
            system("cls");
            printf("\n\n\n\t\t\t\t          Account Creation Failed!\n\t\t\t\t          Enter Your Information Again\n");
            Sleep(3000);
            system("cls");
        }
    }
    if(check){
        system("cls");
        printf("\n\n\n%sAccount Creation Successful\n\n", get_space());
        Sleep(3000);
        system("cls");
    }

    free(ID);
    free(pass);
}

void login_fnc()
{
    char ID[12], pass[9];
    char old_ID[] = "123456", old_pass[] = "admin";

    while(1){
        printf("%sEnter Your ID : ", get_space());
        scanf("%s", ID);
        printf("%sEnter Your Password: ", get_space());
        scanf("%s", pass);
        system("cls");

        if((strcmp(ID, old_ID)==0) && (strcmp(pass, old_pass)==0)){
            admin_login();  // Admin Login
            break;
        }
        else if(search_student(ID, pass)){
            student_login(ID);
            break;
        }
        else{
            printf("%sWrong ID or Password. Please Try Again.", get_space());
            Sleep(3000);
            system("cls");
        }
    }


}

int search_student(char *ID, char *pass)
{
    FILE *fp_in_Stu_login;
    char str[50], old_std_ID[12], old_std_pass[9];



    fp_in_Stu_login = fopen("Stu_login_info.txt", "r");
    if(!fp_in_Stu_login){
        printf("Stu_login_info File Opening Failed");
        return 0;
    }

    while(NULL!=(fgets(str, 49, fp_in_Stu_login))){
        sscanf(str, "%s %s", old_std_ID, old_std_pass);
        if(((strcmp(ID, old_std_ID))==0) && ((strcmp(pass, old_std_pass)==0))){
                fclose(fp_in_Stu_login);
                return 1;
           }
    }

    fclose(fp_in_Stu_login);

    return 0;
}

void admin_login()
{
    int option;

    ID_sorting(find_total_student());

    while(1){
        printf("%s[1] Add Marks\n%s[2] Send Notice\n%s[3] Sign Out\n\n%sEnter Your Option... ", get_space(), get_space(), get_space(), get_space());
        scanf("%d", &option);

        if(option==1){
            system("cls");
            add_semester_marks();
        }
        else if(option==2){
            system("cls");
            add_notice();
        }
        else if(option==3){
            system("cls");
            break;
        }
        else{
            printf("%sThis Option Is Invalid.", get_space());
            Sleep(3000);
            system("cls");
        }
    }
}

int add_semester_marks()
{
    FILE *this_semester, *fp_course_info_in, *fp_Stu_login_info_in;
    login_student_info *n_semester_course_info;  // structure
    int i, j, semester_counter, option;
    char *line, *name, *password, *ID;
    float SGPA, CGPA;


    char *semester_name = get_semester_file_name(&semester_counter);  // get_semester_file_name function

    fp_Stu_login_info_in = fopen("Stu_login_info.txt", "r");
    this_semester = fopen(semester_name, "w");

    if(!fp_Stu_login_info_in || !this_semester){
        printf("%s File Opening Failed", semester_name);
        return EXIT_FAILURE;
    }

    line = (char*)calloc(50, sizeof(char));
    ID = (char*)calloc(13, sizeof(char));
    password = (char*)calloc(10, sizeof(char));
    name = (char*)calloc(25, sizeof(char));


    if(NULL==ID || NULL==password || NULL==name){
        printf("Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }

    n_semester_course_info = (login_student_info*)calloc(7, sizeof(login_student_info));
    if(!n_semester_course_info){
        printf("'n_semester_course_info' Structure Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }

    fp_course_info_in = fopen("Course_info.txt", "r");
    if(!fp_course_info_in){
        printf("Course_info.txt File Opening Failed");
        return EXIT_FAILURE;
    }

    info course;  /// structure

    i = 0;
    while(NULL!=(fgets(line, 50, fp_course_info_in))){
        sscanf(line, "%d %s %f", &course.semes, course.sub, &course.hr);
        if(course.semes==semester_counter){
            n_semester_course_info[i].semester = course.semes;
            strcpy(n_semester_course_info[i].course_name, course.sub);
            n_semester_course_info[i].c_hr = course.hr;
            i++;
        }
        else if(course.semes==semester_counter+1)
            break;
    }


    while(NULL!=(fgets(line, 50, fp_Stu_login_info_in))){
        sscanf(line, "%s %s %s", ID, password, name);
        while(1){
            for(j=0; j<i; j++){
                printf("%sStudent Name : %s\n%sStudent ID : %s\n%sEnter %s Marks : ", get_space(), name, get_space(), ID, get_space(), n_semester_course_info[j].course_name);
                scanf("%d", &n_semester_course_info[j].marks);
                printf("\n");
            }
            printf("\t\t\tIf You Want to Save The Information then Press [1], Other wise Press [2]...");
            scanf("%d", &option);
            if(option==1){
                SGPA = sgpa_calculate(n_semester_course_info, i);  // sgpa_calculate function
                CGPA = cgpa_calculate(SGPA, semester_counter, ID);  // cgpa_calculate function

                for(j=0; j<i; j++)
                    fprintf(this_semester, "%s %s %s %d %.3f\n", ID, name, n_semester_course_info[j].course_name, n_semester_course_info[j].marks, n_semester_course_info[j].c_hr);

                fprintf(this_semester, "%s %s %.3f %.3f\n", ID, name, SGPA, CGPA);  ///ID name SGPA CGPA
                printf("\t\t\t\t            Information Saved Successfully.");
                Sleep(3000);
                system("cls");
                break;
            }
            else{
                printf("\t\t\t        Failed To Save Information.Please Try Again And Save Them.");
                Sleep(3000);
                system("cls");
            }
        }
    }


    free(line);
    free(ID);
    free(password);
    free(name);
    free(n_semester_course_info);

    fclose(fp_Stu_login_info_in);
    fclose(this_semester);
    fclose(fp_course_info_in);

    return 0;
}

void add_notice()
{
    FILE *fp_in_notice;
    char *str;

    printf("%s[N.B] Type 'STOP' To Exit\n\n", get_space());


    fp_in_notice = fopen("Notice.txt", "w");
    if(!fp_in_notice){
        printf("Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }
    str = (char*)malloc((sizeof(char)*100));

    gets(str);

    while(0!=strcmp(str, "STOP")){
        fprintf(fp_in_notice, "%s ", str);
        gets(str);
    }
    system("cls");

    free(str);
    fclose(fp_in_notice);
}

float sgpa_calculate(login_student_info *n_semester_course_info, int i)
{
    int total_course = i;
    float grade, total_c_hr=0, grade_c_hr = 0;

    for(i=0; i<total_course; i++){
        grade_c_hr += (n_semester_course_info[i].c_hr)*(grade_calculate(n_semester_course_info[i].marks));
        total_c_hr += n_semester_course_info[i].c_hr;
    }


    return (grade_c_hr/total_c_hr);
}

float cgpa_calculate(float SGPA, int semester_counter, char *ID)
{
    FILE *fp_in_previous_semester;
    smester_copy previous_semester_info;
    char previous_semester_name[12][20] = {"1st Semester.txt", "2nd Semester.txt", "3rd Semester.txt", "4th Semester.txt", "5th Semester.txt", "6th Semester.txt", "7th Semester.txt", "8th Semester.txt", "9th Semester.txt", "10th Semester.txt", "11th Semester.txt", "12th Semester.txt"};
    char *line, cgpa[8];
    float CGPA;
    int i;


    if(semester_counter==1)
        CGPA = SGPA;
    else{
        fp_in_previous_semester = fopen(previous_semester_name[semester_counter-2], "r");
        if(!fp_in_previous_semester){
            printf("%s File Opening Failed", previous_semester_name[semester_counter-1]);
            return EXIT_FAILURE;
        }
        line = (char*)calloc(72, sizeof(char));
        if(!line){
            printf("Dynamic Allocation Failed");
            return EXIT_FAILURE;
        }

        while(NULL!=(fgets(line, 70, fp_in_previous_semester))){
            sscanf(line , "%s %s %s %s", previous_semester_info.ID, previous_semester_info.name, previous_semester_info.SGPA, previous_semester_info.CGPA);
            if((strcmp(ID, previous_semester_info.ID))==-1)
                break;
            else if((strcmp(ID, previous_semester_info.ID))==0){
                strcpy(cgpa, previous_semester_info.CGPA);
            }
        }
        sscanf(cgpa, "%f", &CGPA);
      //  printf("Previous Semester CGPA = %.3f\n", CGPA);  ///================= test

        CGPA = (CGPA + SGPA)/2;

    //    printf("Current CGPA = %.3f\n", CGPA);   ///================= test


        fclose(fp_in_previous_semester);
        free(line);
    }


    return CGPA;
}

float grade_calculate(int marks)
{
    float grade;

    if(marks>=80)
        grade = 4.0;

    else if(marks>=75)
        grade = 3.75;

    else if(marks>=70)
        grade = 3.50;

    else if(marks>=65)
        grade = 3.25;

    else if(marks>=60)
        grade = 3.00;

    else if(marks>=55)
        grade = 2.75;

    else if(marks>=50)
        grade = 2.50;

    else if(marks>=45)
        grade = 2.25;

    else if(marks>=40)
        grade = 2.00;

    else
        grade = 0.00;

    return grade;
}

char* get_semester_file_name(int *semester_counter)
{
    static char semester_name[10];
    char this_semester_name[12][15] = {"1st Semester", "2nd Semester", "3rd Semester", "4th Semester", "5th Semester", "6th Semester", "7th Semester", "8th Semester", "9th Semester", "10th Semester", "11th Semester", "12th Semester"};
    int i, check=0;


    printf("\t\t\t\t     Enter Which Semester Marks you want to Submit ?\n\n");
    printf("%s[N.B] 1st Semester...", get_space());

    getchar();
    while(1){
        gets(semester_name);
        for(i=0; i<12; i++){
            if((strcmp(this_semester_name[i], semester_name))==0){
                strcat(semester_name, ".txt");
                *semester_counter = i+1;
                check++;
                break;
            }
        }
        if(check!=0){
            break;
        }
        else{
            printf("%sDidn't Match The N.B Format. Try Again..", get_space());
        }
    }

    return semester_name;
}

int find_total_student()
{
    FILE *fp_in;
    int count;
    char line[50];

    fp_in = fopen("Stu_login_info.txt", "r");
    if(!fp_in){
        printf("Stu_login_info.txt File Opening Failed");
        return EXIT_FAILURE;
    }

    for(count=0; NULL!=(fgets(line, 50, fp_in)); count++);

    fclose(fp_in);

    return count;
}

void ID_sorting(int total_student)
{
    FILE *fp_in;
    login_student_info *student; // Structure
    int i;
    long long int ID;
    char *name, *password;


    student = (login_student_info*)calloc(total_student, sizeof(login_student_info));
    name = (char*)calloc(25, sizeof(char));
    password = (char*)calloc(10, sizeof(char));
    if(!student || !name || !password){
        printf("Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }

    fp_in = fopen("Stu_login_info.txt", "r");
    if(!fp_in){
        printf("Stu_login_info.txt File Opening Failed");
        return EXIT_FAILURE;
    }

    for(i=0; i<total_student; i++){
        fscanf(fp_in, "%lld %s %s", &ID, password, name);
        student[i].ID = ID;
        strcpy(student[i].password, password);
        strcpy(student[i].name, name);
    }

    qsort(student, total_student, sizeof(login_student_info), compare);

    fclose(fp_in);

    fp_in = fopen("Stu_login_info.txt", "w");
    if(!fp_in){
        printf("Stu_login_info.txt File Opening Failed");
        return EXIT_FAILURE;
    }

    for(i=0; i<total_student; i++){
        fprintf(fp_in, "%lld %s %s\n", student[i].ID, student[i].password, student[i].name);
    }

    fclose(fp_in);
}

void student_login(char *ID)
{
    int n;


    while(1){
        printf("%s[1] Present Course\n%s[2] Previous Course\n%s[3] Notice Board\n%s[4] Sign Out\n\n%sEnter Your Option..", get_space(), get_space(), get_space(), get_space(), get_space());
        scanf("%d", &n);
        system("cls");
        if(n==1){
            summary(ID);
        }
        else if(n==2){
            previous_course_result(ID);
        }
        else if(n==3){
            check_notice();
        }
        else if(n==4)
            break;
        else
            printf("%sThis Option Is Invalid\n\n", get_space());
    }
}

void summary(char *ID)
{
    FILE *fp_in_summary;
    smester_copy summary;  // structure
    login_student_info store_result;
    int i, j, k, check = 0;
    char *line;
    char semester_result[12][20] = {"1st Semester.txt", "2nd Semester.txt", "3rd Semester.txt", "4th Semester.txt", "5th Semester.txt", "6th Semester.txt", "7th Semester.txt", "8th Semester.txt", "9th Semester.txt", "10th Semester.txt", "11th Semester.txt", "12th Semester.txt"};

    line = (char*)malloc(sizeof(char)*70);
    if(!line){
        printf("Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }

    for(i=11; i>=0; i--){
        fp_in_summary = fopen(semester_result[i], "r");
        while(NULL!=(fgets(line, 70, fp_in_summary))){
            sscanf(line, "%s %s %s %s", summary.ID, summary.name, summary.SGPA, summary.CGPA);
            if(0==(strcmp(ID, summary.ID))){
                strcpy(store_result.name, summary.name);
                strcpy(store_result.SGPA, summary.SGPA);
                strcpy(store_result.CGPA, summary.CGPA);
                check++;
            }
            else if(-1==(strcmp(ID, summary.ID))){
                break;
            }
        }
        fclose(fp_in_summary);
        if(check)
            break;
    }
    free(line);
    print_summary(ID, store_result);  // print_summary function
}

void print_summary(char *ID, login_student_info store_result)
{
    printf("%s        Summary\n\n", get_space());
    printf("%sName : %s\n", get_space(), store_result.name);
    printf("%sID : %s\n\n", get_space(), ID);
    printf("%sSGPA : %s\n", get_space(), store_result.SGPA);
    printf("%sCGPA : %s\n\n\n", get_space(), store_result.CGPA);
}

void previous_course_result(char *ID)
{
    FILE *fp_in_previous_result;
    smester_copy storing_result;
    char semester_result[12][20] = {"1st Semester", "2nd Semester", "3rd Semester", "4th Semester", "5th Semester", "6th Semester", "7th Semester", "8th Semester", "9th Semester", "10th Semester", "11th Semester", "12th Semester"};
    char *line, semester[20];
    int i, j, check;

    line = (char*)malloc(sizeof(char)*70);
    if(!line){
        printf("Dynamic Memory Allocation Failed");
        return EXIT_FAILURE;
    }

    for(i=0,j=0,check=0; i<12; i++){
        strcpy(semester, semester_result[i]);
        strcat(semester, ".txt");
        fp_in_previous_result = fopen(semester, "r");
        while(NULL!=(fgets(line, 70, fp_in_previous_result))){
            sscanf(line, "%s %s %s %s", storing_result.ID, storing_result.name, storing_result.SGPA, storing_result.CGPA);
            if(j==0){
                printf("\t\t\t\t\t%s Result\n\n", semester_result[i]);
                j++;
            }
            if(0==(strcmp(ID, storing_result.ID))){
                if(check==0){
                    printf("%sName : %s\n%sID : %s\n\n", get_space(), storing_result.name, get_space(), storing_result.ID);
                    check++;
                }
                printf("%s%s   %s\n", get_space(), storing_result.SGPA, storing_result.CGPA);
            }
        }
        if(j)
            printf("\n\n");
        j = 0;
        fclose(fp_in_previous_result);
    }

    free(line);
}

char* get_space()
{
    char *space;


    space = (char*)calloc(26, sizeof(char));
    strcpy(space, "\t\t\t\t\t\t");


    return space;
}

void check_notice()
{
    FILE *fp_in_notice;
    char *line;

    fp_in_notice = fopen("Notice.txt", "r");

    if(fp_in_notice!=NULL){
        line = (char*)(malloc((sizeof(char))*300));
        while(NULL!=fgets(line, 300, fp_in_notice)){
            printf("%s\n", line);
        }
        free(line);
    }
    else{
        printf("\n\n%sNo Notice!", get_space());
        Sleep(3000);
        system("cls");
    }

    printf("\n\n");
    fclose(fp_in_notice);
}
