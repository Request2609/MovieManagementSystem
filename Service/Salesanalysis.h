#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_
#include"Play.h"
#include"Schedule.h"
#include"Sale.h"
typedef struct{
	int play_id;//��Ŀ��� 
	char name[30];//��Ŀ���� 
	char area[9];//��������
	int duration;
	int totaltickets;//��Ŀ�������� 
	int sales;//��Ŀ���۶� 
//	int sales;//��Ŀ���۶�
	int price;//��ĿƱ�� 
	ttms_date_t start_date;
	ttms_date_t end_date; 
}salesanalysis_t;
typedef struct salesanalysis_node{
	salesanalysis_t data;
	struct salesanalysis_node*next;
	struct salesanalysis_node*prev;
}salesanalysis_node_t;
int Salesanalysis_Srv_AddAllMoney(salesanalysis_node_t*h);
#endif 
