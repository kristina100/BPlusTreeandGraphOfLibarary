/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 15:56:56
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 17:06:34
 */
#include"Login.h"
#include"Utils.h"

char Data_Users[10] = "Users.dat";

/**
 * @brief 打印登录界面
 */
void Login_Options(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("学生选项");
        printf("__");
    }
    printf("\n\n");
    printf("1.学生登录\n");
    printf("2.管理员登录\n");
    printf("3,学生注册\n");
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
    //循环操作标志
    int flag = 1;
    //选择
    int choose;
    
    while (flag){
        Login_Options();
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
                if(Register_Stu() == SUCCESS){
                    printf("注册成功\n");
                }else{
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
    char ID[11];
    char password[6];
    Stu stu = NULL;
    Stu_Init(stu);

    //输入账号密码
    printf("请输入账号:");
    scanf("%s", ID);

    printf("请输入密码:");
    scanf("%s", password);

    //打开文件
    fp = fopen(Data_Users, "rb");
    
    //检查账号
    while(fread(stu, sizeof(student), 1, fp) != NULL){
        if(strcmp(ID, stu->ID) == 0){
            if(strcmp(password, stu->password) == 0){
                fclose(fp);
                return stu;
            }
        } 
    }
    fclose(fp);

    return NULL;
}

/**
 * @brief 注册
 */
Status Register_Stu(){

    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("注册");
        printf("__");
    }
    printf("\n");
    //初始化
    FILE *fp = NULL;
    Stu stu = NULL, temp = NULL;
    Stu_Init(stu);
    Stu_Init(temp);
    
    //创建账号
    printf("请输入学号:");
    scanf("%s", stu->ID);

    //打开文件
    fp = fopen(Data_Users, "rb");

    //检查账号是否存在
    while(fread(temp, sizeof(student), 1, fp) != NULL){

        if(strcmp(temp->ID, stu->ID) == 0){
            fclose(fp);
            return ERROR;
        }
    }
    
    fclose(fp);

    printf("请输入密码(6位):");
    scanf("%s", stu->password);

    printf("请输入姓名:");
    scanf("%s", stu->name);

    //写入文件
    fp = fopen(Data_Users, "ab+");
    fwrite(stu, sizeof(student), 1, fp);
    fclose(fp);
    return SUCCESS;
}