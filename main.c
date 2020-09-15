#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void admin_registration();
void student_registration();
void login_fnc();
void admin_login();
int search_student(char *ID, char *pass);
void student_login();


int main()
{
    int a, b, c, i, c_hr;
    char str[10];

    printf("1. Signup\n2. Login\nEnter Your Option..");
    scanf("%d", &a);
    system("cls");
    if(a==1){ ///admin - student (registration)
        printf("\t\tEnter Account Type\n\n1. Admin\n2. Student\nEnter Your Option..");
        scanf("%d", &b);
        system("cls");
        if(b==1){  ///admin
            admin_registration();
        }
        else if(b==2){  /// student
            student_registration();
        }
    }
    else if(a==2){
        system("cls");
        login_fnc();  /// admin - student (login)

    }




    return 0;
}

void admin_registration() ///
{
    FILE *fp_co_inf;
    char *str[10];
    int t_sub, a, i, check=0;
    float *c_hr;

    while(1){
        printf("\t\tEnter Admin key ..");   /// 123456
        scanf("%d", &a);
        system("cls");
        if(a==123456){
            while(1){
                printf("Enter This Semister Total Subject : ");
                scanf("%d", &t_sub);
                system("cls");
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
                    printf("Enter Course Title : ");
                    scanf("%s", str[i]);
                    printf("Enter  Credit Hours : ");
                    scanf("%f", &c_hr[i]);
                }
                printf("\n\nIf You want to Save It Then Press 1. Otherwise Press 2.");
                scanf("%d", &a);
                system("cls");
                if(a==1){
                    fp_co_inf = fopen("Course_info.txt", "w");
                    if(!fp_co_inf){
                        printf("Course_info file Opening Failed");
                        return ;
                    }
                    for(i=0; i<t_sub; i++){
                        fprintf(fp_co_inf, "%s %.3f\n", str[i], c_hr[i]);
                    }
                    fclose(fp_co_inf);
                    check++;
                    break;
                }
                else if(a==2){
                    system("cls");

                }
            }
            if(check){
                printf("\n\nSave Successful\n");
                break;
            }
        }
        else{
            printf("\t\tDon't match your key . Please Try Again : \n");
        }
    }

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
        printf("\t\tN.B. Use '_' instead of space enxmple Jack_Pritom_Soren\n\n");
        printf("Enter User Name : ");
        scanf("%s", name);
        printf("Enter Student ID : ");
        scanf("%s", ID);
        printf("Enter Password N.B.(Maximum 8 character) : ");
        scanf("%s", pass);
        printf("\n\t\tEnter 1 To create Account, & if you want to change information Enter 2 : ");
        scanf("%d", &n);
        system("cls");
        if(n==1){
            st_info = fopen("Stu_login_info.txt", "a");
            fprintf(st_info, "%s %s %s\n", ID, pass, name);
            check++;
            fclose(st_info);
            break;
        }
        else if(n==2){
            printf("Account Creation Unsuccessful!\nEnter Your Information Again\n");
        }
    }
    if(check){
        printf("Account Creation Successful\n\n");
    }

    free(ID);
    free(pass);
}

void login_fnc()
{
    char ID[12], pass[9];
    char old_ID[] = "admin", old_pass[] = "123456";

    while(1){
        printf("Enter Your ID : ");
        scanf("%s", ID);
        printf("Enter Your Password: ");
        scanf("%s", pass);

        if((strcmp(ID, old_ID)==0) && (strcmp(pass, old_pass)==0)){
            system("cls");
            admin_login();
            break;
        }
        else if(search_student(ID, pass)){
            printf("Student\n");
            system("cls");
            student_login();
            break;
        }
        else{
            system("cls");
            printf("Wrong ID or Password\nPlease Try Again\n\n");
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
    printf("Admin\n\n");

}
void student_login()
{
    printf("Student\n\n");
}
