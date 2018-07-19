#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"Schedule_Persist.h"
#include"../Common/List.h"
#include"../Service/Sale.h" 
static const char* SaleFile ="Sale.dat";
int Sale_Perst_FetchAll(sale_node_t*h){//查找所有订单信息
	if(access("Sale.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("Sale.dat","rb");
	if(fp==NULL){
//		printf(":"
		return 0;
	}
	int count=0;
	sale_node_t*temp=NULL;
	while(1){
		temp=(sale_node_t*)malloc(sizeof(sale_node_t));
		if(fread(temp,sizeof(sale_node_t),1,fp)<1){
			free(temp);
			break;
		}
		count++;
		List_AddTail(h,temp);
	}
	fclose(fp);
	return count;
}
int Sale_Perst_FetchByID(play_node_t* h,schedule_node_t*p){//通过订单ID查找订单数据
	if(access("Schedule.dat",0)){
		return 0;
	}
	FILE*fp=fopen("Schedule.dat","rb");
	if(fp==NULL){
		return 0;
	}
	schedule_node_t* temp;
	temp=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	while(1){
		if(fread(temp,sizeof(schedule_node_t),1,fp)<1)break;
		if(temp->data.play_id==h->data.id){
			p->data.id=temp->data.id ;
			p->data.play_id=temp->data.play_id;
			p->data.studio_id=temp->data.studio_id;
			p->data.seat_count=temp->data.seat_count;
			p->data.date.year=temp->data.date.year; 
			p->data.date.month=temp->data.date.month;
			p->data.date.day=temp->data.date.day;
			p->data.time.hour=temp->data.time.hour;
			p->data.time.minute=temp->data.time.minute;
			p->data.time.second=temp->data.time.second;
			free(temp);
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	free(temp); 
	return 0;
}
int Sale_Perst_SearchByTID(sale_node_t*p){//根据票的ID查找订单信息
	if(access("Sale.dat",0))return 0;
	FILE*fp;
	fp=fopen("Sale.dat","rb");
	if(fp==NULL){
		return 0;
	}
	sale_node_t*h=NULL;
	h=(sale_node_t*)malloc(sizeof(sale_node_t));
	while(1){
		if(fread(h,sizeof(sale_node_t),1,fp)<1){
			break;
		}
		if(h->data.id==p->data.id&&h->data.type==-1){
			p->data.ticket_id=h->data.ticket_id;
			free(h);
			fclose(fp);
			return 1;
		}
	}
	free(h);
	fclose(fp);
	return 0;
}
int Sale_Perst_Modify(sale_node_t*h){//订单数据修改
	if(access("sale.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("sale.dat","rb+");
	if(fp==NULL){
		return 0;
	} 
	sale_node_t*p=NULL;
	int flag=0;
	p=(sale_node_t*)malloc(sizeof(sale_node_t));
	while(1){
		if(fread(p,sizeof(sale_node_t),1,fp)<1){
			break;;
		}
		if(p->data.ticket_id==h->data.ticket_id){
			flag=1;
			p->data.type=SALE_SELL;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*(int)sizeof(sale_node_t),SEEK_CUR);
			fwrite(p,sizeof(sale_node_t),1,fp);
			fsetpos(fp,&pos);
			break; 
		}
	}
	fclose(fp);
	free(p);
	if(flag==0){
		return 0;
	}
	return 1;
}
int Sale_Perst_Add(sale_node_t*h){//添加订单数据
	FILE*fp;
	if(access(SaleFile,0),0){
		fp=fopen(SaleFile,"wb");
		if(fp==NULL){
			return 0;
		}
		fwrite(h,sizeof(sale_node_t),1,fp);
		fclose(fp);
	}
	else{
		fp=fopen(SaleFile,"ab");
		if(fp==NULL){
			return 0;
		}
		fwrite(h,sizeof(sale_node_t),1,fp);
		fclose(fp);
	}
	return 1;
}
