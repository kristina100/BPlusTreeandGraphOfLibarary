/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 15:56:56
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 22:49:49
 */
#include"Login.h"
#include"Utils.h"

//存储学生数据的文件
char Data_Stu[] = "Students.dat";

//存储管理员数据的文件
char Data_Man[] = "Managers.dat";

/**
 * @brief 打印登录界面
 */
void Print_Login_Options(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("登录界面");
        printf("__");
    }
    printf("\n\n");
    printf("1.学生登录\n");
    printf("2,管理员登录\n");
    printf("3,注册\n");
    printf("0.退出\n\n");

    for (int i = 0; i < 15; i++){
        printf("__");
    }
    printf("\n");
    printf("请选择操作: ");     
}

/**
 * @brief 登录选项
 */
void Login_Operation(){
    
    //选择
    int choose;
    
    while (true){
        Print_Login_Options();
        scanf("%d", &choose);
        
        switch (choose){
            
            //返回上一级
            case 0:{
                return;
            }break;

            //学生登录
            case 1:{
                Stu stu = NULL;
                stu = Login_Stu();
                if(stu == NULL){
                    printf("登录失败，账号或密码错误\n");
                }else{
                    printf("登录成功\n");
                    Sleep(1);
                    Stu_Operation(stu);
                }
                Pause();
            }break;

            //管理员登录
            case 2:{

            }break;

            //注册
            case 3:{
                Status status = Register_Spilt();
                if(status == SUCCESS){
                    printf("注册成功\n");
                }else if(status == Exist){
                    printf("账号已存在\n");
                }
                Pause();
            }break;
        
            default:{
                printf("\n操作不存在\n");
                Pause();
            }break;
        }
    Clean();
    }
}

/**
 * @brief 学生登录
 */
Stu Login_Stu(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("登录");
        printf("__");
    }
    printf("\n");
    FILE *fp = NULL;
    char account[11];
    char password[6];
    Stu stu = NULL;
    //Stu_Init(stu);

    //输入账号密码
    printf("请输入账号:");
    scanf("%s", account);

    printf("请输入密码:");
    scanf("%s", password);

    //打开文件
    fp = fopen(Data_Stu, "rb");
    
    //在数据文件中查找账号
    while(fread(stu, sizeof(student), 1, fp) != NULL){
        
        if(strcmp(account, stu->account) == 0){
            //密码相同
            if(strcmp(password, stu->password) == 0){
                fclose(fp);
                return stu;
            }
            else
                break;
            
        }
    }
    fclose(fp);
    
    return NULL;
}

/**
 * @brief 打印注册选项
 * 
 */
void Print_Register_Option(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("登录界面");
        printf("__");
    }
    printf("\n\n");
    printf("1.学生注册\n");
    printf("2,管理员注册\n");
    printf("0.返回\n\n");

    for (int i = 0; i < 15; i++){
        printf("__");
    }
    printf("\n");
    printf("请选择操作: "); 
}

/**
 * @brief 分流学生和管理员
 * 
 */
Status Register_Spilt(){

    int choose;

    while (true){
        Print_Register_Option();
        scanf("%d", &choose);

        switch (choose){
            
            //返回
            case 0:{
                return Cancel;
            }break;

            //学生注册
            case 1:{
                Status status = Register_Operation(0);
                if(status == SUCCESS)
                    return SUCCESS;
                else
                    return Exist;
            }break;

            //管理员注册
            case 2:{
                Status status = Register_Operation(1);
                if(status == SUCCESS)
                    return SUCCESS;
                else if(status == ERROR){
                    printf("管理员注册权限无效\n");
                    return ERROR;
                }else   
                    return Exist;
                    
            }break;

            default:{
                printf("\n操作不存在\n");
                Pause();
            }break;
        }
    Clean();
    }
    
}

/**
 * @brief 注册
 */
Status Register_Operation(int mode){

    //初始化
    FILE *fp = NULL;

    switch (mode){

        //学生注册
        case 0:{     
            Stu stu = NULL, temp = NULL;
            Stu_Init(stu);
            Stu_Init(temp);

            printf("请输入账号:");
            scanf("%s", stu->account);

            //=================检查账号是否存在=================

            //打开文件
            fp = fopen(Data_Stu, "rb");

            while(fread(temp, sizeof(student), 1, fp) != NULL){

                if(strcmp(temp->account, stu->account) == 0){
                    fclose(fp);
                    return Exist;
                }
            }
            fclose(fp);
            
            printf("请输入学号:");
            scanf("%s", stu->ID);

            printf("请输入密码(6位):");
            scanf("%s", stu->password);

            printf("请输入姓名:");
            scanf("%s", stu->name);

            stu->power = 0;

            //写入文件
            fp = fopen(Data_Stu, "ab+");
            fwrite(stu, sizeof(student), 1, fp);
            
        }break;
        //管理员注册
        case 1:{
            Manager M = NULL, temp = NULL;
            Man_Init(M);
            Man_Init(temp);
            
            //检测管理员注册密钥
            int Mancode = 0;
            printf("请输入管理员注册密钥:");
            scanf("%d", &Mancode);
            //注册密钥错误
            if(Mancode != 1234) return FALSE;

            printf("请输入账号:");
            scanf("%s", M->account);
            
            
            //=================检查账号是否存在=================

            //打开文件
            fp = fopen(Data_Man, "rb");

            while(fread(temp, sizeof(student), 1, fp) != NULL){

                if(strcmp(temp->account, M->account) == 0){
                    fclose(fp);
                    return Exist;
                }
            }
            fclose(fp);
            
            printf("请输入密码(6位):");
            scanf("%s", M->password);

            printf("请输入姓名:");
            scanf("%s", M->name);

            M->power = 1;

            //写入文件
            fp = fopen(Data_Man, "ab+");
            fwrite(M, sizeof(student), 1, fp);
        }break;
    }
    fclose(fp);
    return SUCCESS;
}