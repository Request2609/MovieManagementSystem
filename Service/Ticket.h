#ifndef TICKET_H_
#define TICKET_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum{
	TICKET_AVL=0,//���� 
	TICKET_SOLD=1,//���� 
	TICKET_RESV=9//Ԥ�� 
	
}ticket_status_t;
typedef struct{
	int id;//Ʊid 
	int schedule_id;//�ݳ��ƻ�Id 
	int seat_id;//��λid 
	int price;//Ʊ�� 
	ticket_status_t status;//Ʊ״̬ 
}ticket_t;
typedef struct ticket_node{
	ticket_t data;
	struct ticket_node*next,*prev; 
}ticket_node_t,*ticket_list_t;
void Schedule_Srv_FetchByID(); 
void Ticket_Srv_GenBatch();
#endif
