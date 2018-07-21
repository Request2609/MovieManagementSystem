#include"Ticket_Perst.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../Common/List.h"
#include"../Service/Play.h"
#include"../Service/Seat.h"
#include"Seat_Persist.h"
static const char*TicketFile="Ticket.dat";
int Ticket_Perst_Insert(ticket_node_t*h){//添加演出票
	FILE*fp;
	ticket_node_t*temp;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	temp=h->next;
	if(access(TicketFile,0)){
		fp=fopen(TicketFile,"wb");
		if(fp==NULL){
			return 0;
		} 
		while(temp!=h){
			fwrite(temp,sizeof(ticket_node_t),1,fp);
			temp=temp->next;
		}
	}else{
		fp=fopen(TicketFile,"ab");
		if(fp==NULL){
			return 0;
		} 
		while(temp!=h){
			
			fwrite(temp,sizeof(ticket_node_t),1,fp);
			temp=temp->next;		
			}
	}
	fclose(fp);
	return 1;
}
int Ticket_Perst_FetchAll(int id,ticket_node_t*h){//将所有演出票数据存到链表
	if(access(TicketFile,0)){
		printf("\n\t\tNo tickets!");
		return 0; 
	}
	FILE*fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	} 
	int count=0;
	ticket_node_t*temp;
	while(1){
		temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1)break;
		if(temp->data.schedule_id==id){
			count++;
			List_AddTail(h,temp);
		}
	}
	free(temp);
	fclose(fp); 
	return count;
}
int Ticket_Perst_FetchByID(schedule_node_t* h,ticket_node_t* p){//根据票Id查找票
	if(access(TicketFile,0)){
		return 0; 
	}
	FILE*fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		return 0;
	}
	ticket_node_t*temp=NULL;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	while(1){
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1)break;
		if(temp->data.schedule_id==h->data.id&&temp->data.status==TICKET_AVL){
			p->data.id=temp->data.id;
			p->data.price=temp->data.price;
			p->data.seat_id=temp->data.seat_id;
			p->data.status=temp->data.status;
			free(temp);
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	free(temp);
	return 0;
}
int Ticket_Perst_SearchByTId(ticket_node_t* p){
	if(access(TicketFile,0)){
		printf("\n\t\tNo tickets!\n");
		return 0;
	}
	FILE*fp;
	fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	}
	ticket_node_t* temp=NULL;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	while(1){
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1){
			break;
		}
		if(temp->data.id==p->data.id){
			p->data.schedule_id=temp->data.schedule_id;
			p->data.seat_id=temp->data.seat_id;
			p->data.price=temp->data.price;
			temp->data.status=1;
			if(Ticket_Perst_ModifyStatus(temp)==0){
				printf("\n\t\tError!\n");
				return 0;
			}
			free(temp);
			fclose(fp);
			return 1;
		}
	}
	free(temp);
	fclose(fp);
	return 0;
}
int Ticket_Perst_ModifyStatus(ticket_node_t*p){//修改票状态
	if(access(TicketFile,0)){

		return 0;
	}
	FILE*fp;
	fp=fopen(TicketFile,"rb+");
	if(fp==NULL){

		return 0;
	}


	ticket_node_t*temp=NULL;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	while(1){
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1){
			break;
		}
		if(temp->data.id==p->data.id){
			p->data.price=temp->data.price;
			p->data.seat_id=temp->data.seat_id;
			p->data.schedule_id=temp->data.schedule_id;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*((int)sizeof(ticket_node_t)),SEEK_CUR);
			fwrite(p,sizeof(ticket_node_t),1,fp);
			fsetpos(fp,&pos);
			fclose(fp);
			free(temp);
			return 1;
		}
	}
	free(temp);
	fclose(fp);
	return 0;
}
int Ticket_Perst_ReturnModify(sale_node_t* p){//退票
	if(access(TicketFile,0)){
		return 0;
	}
	FILE*fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	}
	seat_node_t*s=NULL;
	s=(seat_node_t*)malloc(sizeof(seat_node_t));
	ticket_node_t* q=NULL;
	q=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	while(1){
		if(fread(q,sizeof(ticket_node_t),1,fp)<1){
			break;
		}

		if(q->data.id==p->data.ticket_id){
			s->data.id=q->data.seat_id;
			s->data.status=1;
			if(Seat_Perst_Modify(s)==0)return 0;
			p->data.value=q->data.price;
			printf("\n***\n");
			q->data.status=0;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*((int)sizeof(ticket_node_t)),SEEK_CUR);
			fwrite(q,sizeof(ticket_node_t),1,fp);
			fsetpos(fp,&pos);
			fclose(fp);
			free(q);
			return 1; 
		}
	}
	fclose(fp);
	free(q);
	return 0;
} 
