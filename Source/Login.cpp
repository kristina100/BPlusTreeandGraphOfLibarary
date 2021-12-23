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
 * @brief ��ӡ��¼����
 */
void Login_Options(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("ѧ��ѡ��");
        printf("__");
    }
    printf("\n\n");
    printf("1.ѧ����¼\n");
    printf("2.����Ա��¼\n");
    printf("3,ѧ��ע��\n");
    printf("0.�˳�\n\n");

    for (int i = 0; i < 15; i++){
        printf("__");
    }
    printf("\n");
    printf("��ѡ�����: ");     
}

/**
 * @brief ��¼ѡ��
 */
void Login_Operation(){
    //ѭ��������־
    int flag = 1;
    //ѡ��
    int choose;
    
    while (flag){
        Login_Options();
        scanf("%d", &choose);
     
        switch (choose){
            
            //������һ��
            case 0:{
                return;
            }break;

            //ѧ����¼
            case 1:{
                Stu stu = NULL;
                stu = Login_Stu();
                if(stu == NULL){
                    printf("��¼ʧ�ܣ��˺Ż��������\n");
                }else{
                    printf("��¼�ɹ�\n");
                    Sleep(1);
                    Stu_Operation(stu);
                }
                Pause();
            }break;

            //����Ա��¼
            case 2:{
                
            }break;
            
            //ע��
            case 3:{
                if(Register_Stu() == SUCCESS){
                    printf("ע��ɹ�\n");
                }else{
                    printf("�˺��Ѵ���\n");
                }
                Pause();
            }break;
        
            default:{
                printf("\n����������\n");
                Pause();
            }break;
        }
    Clean();
    }
}

/**
 * @brief ѧ����¼
 */
Stu Login_Stu(){
    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("��¼");
        printf("__");
    }
    printf("\n");
    FILE *fp = NULL;
    char ID[11];
    char password[6];
    Stu stu = NULL;
    Stu_Init(stu);

    //�����˺�����
    printf("�������˺�:");
    scanf("%s", ID);

    printf("����������:");
    scanf("%s", password);

    //���ļ�
    fp = fopen(Data_Users, "rb");
    
    //����˺�
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
 * @brief ע��
 */
Status Register_Stu(){

    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("ע��");
        printf("__");
    }
    printf("\n");
    //��ʼ��
    FILE *fp = NULL;
    Stu stu = NULL, temp = NULL;
    Stu_Init(stu);
    Stu_Init(temp);
    
    //�����˺�
    printf("������ѧ��:");
    scanf("%s", stu->ID);

    //���ļ�
    fp = fopen(Data_Users, "rb");

    //����˺��Ƿ����
    while(fread(temp, sizeof(student), 1, fp) != NULL){

        if(strcmp(temp->ID, stu->ID) == 0){
            fclose(fp);
            return ERROR;
        }
    }
    
    fclose(fp);

    printf("����������(6λ):");
    scanf("%s", stu->password);

    printf("����������:");
    scanf("%s", stu->name);

    //д���ļ�
    fp = fopen(Data_Users, "ab+");
    fwrite(stu, sizeof(student), 1, fp);
    fclose(fp);
    return SUCCESS;
}