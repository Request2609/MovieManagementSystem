#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include"../Service/Play.h" 
#define NAMELONG 30
//#include"../Persistence/Play_Persist.h"
typedef struct{//�����ݳ�ʱ�νṹ�� 
	int hour;
	int minute;
	int second;
}ttms_time_t;
typedef struct{//�����ݳ���Ŀ�ṹ�� 
	int id;//�ݳ��ƻ�ID 
	int play_id;//���ݾ�ĿID 
	int studio_id;//�ݳ���ID 
	ttms_date_t date;//��ӳ���� 
	ttms_time_t time;//��ӳʱ�� 
	int seat_count;//��λ�� 
}schedule_t;
typedef struct schedule_node { 
	schedule_t data;//���ݽڵ� 
	struct schedule_node *next;
	struct schedule_node *prev;
}schedule_node_t,*schedule_list_t;
int Schedule_Srv_FetchByPlayName(char*name,schedule_node_t*h);//���ݾ�Ŀ���ƻ�ȡ�ݳ��ƻ� 
void Schedule_Srv_Add();//����ݳ��ƻ� 
void Schedule_Srv_DeleteByID();//�޸��ݳ��ƻ� 
void Schedule_Srv_Modify();//ɾ���ݳ��ƻ� 4
int Schedule_Srv_JudgeIsExsist(int play_id);
//int Schedule_Srv_FetchByPlay(schedule_node_t*h,char playname[],int play_id);
#endif 
