#ifndef TICKET_H_
#define TICKET_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum{
	TICKET_AVL=0,//待售 
	TICKET_SOLD=1,//已售 
	TICKET_RESV=9//预留 
	
}ticket_status_t;
typedef struct{
	int id;//票id 
	int schedule_id;//演出计划Id 
	int seat_id;//座位id 
	int price;//票价 
	ticket_status_t status;//票状态 
}ticket_t;
typedef struct ticket_node{
	ticket_t data;
	struct ticket_node*next,*prev; 
}ticket_node_t,*ticket_list_t;
void Schedule_Srv_FetchByID(); 
void Ticket_Srv_GenBatch();
#endif
