/*
 * @Descripttion: 
 * @Author: Hx
 * @Date: 2021-12-23 14:33:31
 * @LastEditors: Hx
 * @LastEditTime: 2021-12-23 20:14:49
 */
#include"Student.h"
#include"Utils.h"


/**
 * @brief ��ʼ��Stu
 */
Status Stu_Init(Stu &stu){

    stu = (Stu)malloc(sizeof(student));
    if(stu == NULL) return OVERFLOW;
    stu->book = NULL;
    stu->power = 0;

    return SUCCESS;
}

/**
 * @brief ��ӡѧ��ѡ��
 */
void Stu_Options(){

    Clean();
    for (int i = 0; i < 10; i++){
        if(i == 5)
            printf("ѧ��ѡ��");
        printf("__");
    }
    printf("\n\n");
    printf("1.��ѯ�鼮\n");
    printf("2.�����鼮\n");
    printf("3.�黹�鼮\n");
    printf("4.������Ϣ\n");
    printf("0.����\n\n");

    for (int i = 0; i < 15; i++){
        printf("__");
    }
    printf("\n");
    printf("��ѡ������: ");                      
}

/**
 * @brief ѧ������
 */
void Stu_Operation(Stu &stu){

    //ѭ��������־
    int flag = 1;
    //ѡ��
    int choose;
    
    while (flag){
        Stu_Options();
        scanf("%d", &choose);
     
        switch (choose){
            
            //������һ��
            case 0:{
                return;
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
 * @brief ����
 */
Status Stu_Borrow(){
    return SUCCESS;
}

/**
 * @brief ����
 */
Status Stu_return(){
    return SUCCESS;
}

/**
 * @brief �鿴��Ϣ
 */
void Stu_MyInfo(){

}

/**
 * @brief �һ�����
 */
Status Stu_FindPassword(){
    return SUCCESS;
}

/**
 * @brief ��������
 */
Status Stu_ChangePassword(){
    return SUCCESS;
}