#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../Common/List.h"
#include"Sale.h"
#include"Ticket.h"
#include"../Persistence/EntityKey_Persist.h"
#include"../Common/common.h"
#include"../Persistence/Seat_Persist.h"
#include"Seat.h"
#include"../Persistence/Sale_Perst.h"
//#include"../Persistence/Sale_Perst.h"
#include"../Persistence/Play_Persist.h"
//#include"../Persistence/Sale_Perst.h"
#include"../Persistence/Ticket_Perst.h"
static const char * SaleName="Sale"; 
int Sale_Srv_FetchByName(play_node_t* h){
//	printf("\n****\n");
	if(Play_Perst_FetchByName(h)==0){//���ݾ�Ŀ���ƻ�ȡ��Ŀid,��h��¼
//		printf("****\n");
		printf("\n\t\tCan't find the Movie!\n");
		return 0;
	}
//	printf("%d\n",h->data.id); 
	ticket_node_t* temp=NULL;
	schedule_node_t* p=NULL;//��¼��Ӧ��ĿiD�µ��ݳ��ƻ���Ϣ 
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	p=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	if(Sale_Perst_FetchByID(h,p)==0){//���ݳ���Ŀid,���ݳ��ƻ���Ϣ����p��¼ 
		printf("\n\t\tCan't find the movie schedule plan!\n");
		return 0;
	} 
//	printf("\n*%d*\n",p->data.id);
//	printf("")
	if(Ticket_Perst_FetchByID(p,temp)==0){//���ݳ��ƻ�id��Ʊ����Ϣ����temp��¼ 
		printf("\n\t\tCan't find tickets!\n");
		return 0;
	}
//	printf("\n***%d***\n",p->data.year);
	printf("\n\t\tTicket_Info is here:\n");
	printf("\n\t\t===========================================================================================================\n");
	printf("\n\t\t%-15s%-15s%-20s%-20s%-15s%-15s%-15s\n","Ticket_ID","Movie_name","Start_date","Start_time","Studio_ID","Seat_ID","Ticket_price");
	printf("\n\t\t%-15d%-15s%d-%d-%d          %d:%d:%d            %-15d%-15d%-15d\n",temp->data.id,h->data.name,
	p->data.date.year,p->data.date.month,p->data.date.day,p->data.time.hour,
	p->data.time.minute,p->data.time.second,p->data.studio_id,temp->data.seat_id,temp->data.price);
	printf("\n\t\t===========================================================================================================\n");
	return 1;
}
int Sale_Srv_Add(account_node_t* accountInfo,ticket_node_t* p){
	if(Ticket_Perst_SearchByTId(p)==0){
		
		return 0;
	}
	if(access("Seat.dat",0)){
		return 0;
	}
	ticket_node_t*t=NULL;
	t=(ticket_node_t*)malloc(sizeof(ticket_node_t));
////	FILE*fp;
	seat_node_t*temp=NULL;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
//	if(Seat_Perst_SelectByID(p->data.seat_id,temp)==0){
//		return 0;
//	}
	temp->data.status=2; 
	temp->data.id=p->data.seat_id;
	if(Seat_Perst_Modify(temp)==0){
		
//		printf("\n*%d*\n",p->data.id);
//		printf("")
		return 0;
	}
//	fp=fopen("seat.dat","rb")
	user_date_t date;
	user_time_t time;
	date=DateNow();
	time=TimeNow(); 
	sale_node_t*h=NULL;
	h=(sale_node_t*)malloc(sizeof(sale_node_t));
	h->data.id=EntKey_Perst_GetNewKeys(SaleName);
	h->data.user_id=accountInfo->data.id;
	h->data.ticket_id=p->data.id; 
	h->data.date.year=date.year;
	h->data.date.month=date.month;
	h->data.date.day=date.day;
	h->data.time.hour=time.hour;
	h->data.time.minute=time.minute;
	h->data.time.second=time.second;
	h->data.value=p->data.price;
	h->data.type=1;
	t->data.id=h->data.ticket_id;
	t->data.status=1;
//	h->data.value=p->data.price;
	
	if(Ticket_Perst_ModifyStatus(t)==0){
//		printf("\n*****\n");
		return 0;
	}
//	h->data.type=SALE_SELL;
//	printf("\n***%d***\n",p->data.id);
	if(Sale_Perst_Add(h)==0){
//		printf()
//		printf("\n\t\t\n");
		return 0;
	}
	printf("\n\t\tSale information is here:\n");
	printf("\t\t=======================================================================================================\n");
	printf("\t\t%-20s%-20s%-20s%-20s%-20s%-20s\n","Sale_ID","Salesman_ID","Ticket_ID","Start_date","Start_time","Ticket_price");
	printf("\n\t\t%-20d%-20d%-20d    %d-%d-%d         %d:%d:%d             %-20d\n",h->data.id,
	accountInfo->data.id,p->data.id,date.year,date.month,date.day,time.hour,time.minute,time.second,p->data.price); 
	printf("\n\t\t======================================================================================================\n");
	return 1;
}
int Sale_Srv_ReturnTicket(sale_node_t* p){
	if(Sale_Perst_SearchByTID(p)==0)return 0; 
	if(Ticket_Perst_ReturnModify(p)==0){
		printf("\n\t\tReturn ticket failed!\n");
		return 0;
	}
	user_date_t date;
	user_time_t time;
	date=DateNow();
	time=TimeNow(); 
	p->data.type=-1;
//	printf("\n\t\t+++++%d++++\n");
	p->data.id=EntKey_Perst_GetNewKeys(SaleName);
	p->data.date.year=date.year;
//	p->data.value=
	p->data.date.month=date.month;
	p->data.date.day=date.day;
	p->data.time.hour=time.hour;
	p->data.time.minute=time.minute;
	p->data.time.second=time.second;
	if(Sale_Perst_Add(p)==0){
		return 0;
	}
	free(p);
	return 1;
}
