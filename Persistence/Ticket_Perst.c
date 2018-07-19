#include"Ticket_Perst.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../Common/List.h"
#include"../Service/Play.h"
#include"../Service/Seat.h"
#include"Seat_Persist.h"
static const char*TicketFile="Ticket.dat";
//static const char*TicketFile_Temp="Ticket_Temp.dat";
int Ticket_Perst_Insert(ticket_node_t*h){
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
//int Ticket_Perst_DeleteByID(int id){
//	if(access(TicketFile,0)){
//		printf("\nû���ݳ�Ʊ��\n");
//		return 0;
//	}	
//	int flag=0;
//	FILE*fp=fopen(TicketFile,"rb");;
//	if(fp==NULL){
//		printf("\nϵͳ����\n");
//		return 0;
//	}
//	FILE*fp1=fopen(TicketFile_Temp,"wb");
//	if(fp1==NULL){
//		printf("\nϵͳ����\n");
//		return 0;
//	}
//	ticket_node_t*temp;
//	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t)); 
//	while(1){
//		temp=(ticket_node_t*)malloc(sizeof(ticket_node_t)); 
//		if(fread(temp,sizeof(ticket_node_t),1,fp)<1){
//			break;
//		}
//		if(temp->data.id==id){
//			free(temp);
//			flag=1;
//		}
//		if(temp->data.id!=id){
////			printf("\n*******\n");
//			fwrite(temp,sizeof(temp),1,fp1);
//		}
//	}
//	free(temp);
//	fclose(fp);
//	fclose(fp1);
//	remove(TicketFile);
//	
//	if(rename("Ticket_Temp.dat","Ticket.dat")<0){
//		printf("\n==%d==\n",rename(TicketFile_Temp,TicketFile));
//		return 0;
//	}
////	printf("%d\n",rename,)
//	return 1;
//}*/
/*
int Ticket_Perst_DeleteByID(int id){
	if(access(TicketFile,0)){
		return 0;
	}
	FILE*fp;
	fp=fopen(TicketFile,"rb");
	if(fp==NULL){
//		printf("")
		return 0;
	}
	FILE*fp1;
	fp1=fopen(TicketFile_Temp,"wb+");
	if(fp1==NULL){
		return 0;
	}
	ticket_node_t*temp=NULL;
	int flag=0;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	while(1){
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1){
			break;
			}
			if(temp->data.id==id){
				flag=1;	
			}
			if(temp->data.id!=id){
				fwrite(temp,sizeof(ticket_node_t),1,fp1);
			}
			
	}
	free(temp);
	fclose(fp);
	if(remove(TicketFile)==0){
		printf("\nɾ��ʧ�ܣ�\n");
		return 0;
	}
	fclose(fp1);
	if(rename(TicketFile_Temp,TicketFile)==0)return 0;
	if(flag==0){
		printf("\n******\n");
		return 0;
	}
	return 1;
}*/
int Ticket_Perst_FetchAll(int id,ticket_node_t*h){
	if(access(TicketFile,0)){
		printf("\n\t\tNo tickets!");
		return 0; 
	}
	FILE*fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		printf("\nError!\n");
		return 0;
	} 
	int count=0;
	ticket_node_t*temp;
	while(1){
		temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1)break;
//		printf("%d ",temp->data.schedule_id);
		if(temp->data.schedule_id==id){
//			printf("\n******\n");
			count++;
			List_AddTail(h,temp);
		}
	}
	free(temp);
//	if(count==0){
//		printf("\n��û������Ʊ��\n");
//		return 0;
//	}
	fclose(fp); 
	return count;
}
int Ticket_Perst_FetchByID(schedule_node_t* h,ticket_node_t* p){
	if(access(TicketFile,0)){
		return 0; 
	}
	FILE*fp=fopen(TicketFile,"rb");
	if(fp==NULL){
		return 0;
	}
	ticket_node_t*temp=NULL;
	temp=(ticket_node_t*)malloc(sizeof(ticket_node_t));
//	int schedule_id;
	while(1){
/*
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
}ticket_t;*/
		if(fread(temp,sizeof(ticket_node_t),1,fp)<1)break;
//		printf("*%d*",temp->data.id);
//		printf("%d")
		if(temp->data.schedule_id==h->data.id&&temp->data.status==TICKET_AVL){
			p->data.id=temp->data.id;
			p->data.price=temp->data.price;
			p->data.seat_id=temp->data.seat_id;
			p->data.status=temp->data.status;
			free(temp);
			fclose(fp);
//			printf("Ʊ�ۣ�",p->data.price);
//			free(temp);
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
//	printf("\n***\n");
	return 0;
}/*typedef enum{
	TICKET_AVL=0,//���� 
	TICKET_SOLD=1,//���� 
	TICKET_RESV=9//Ԥ�� 
	
}ticket_status_t;
typedef struct{
	int id;//Ʊid 
	int schedule_id;//�ݳ��ƻ�Id 
	int seat_id;//��λid 
	int price;//Ʊ�� 
	ticket_status_t status;//Ʊ״̬*/
int Ticket_Perst_ModifyStatus(ticket_node_t*p){
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
		if(fread(temp,sizeof(ticket_node_t),1,fp)<0){
			break;
		}
//		if(p->data.status==1){
//			printf("\n��������\n");
//		}
//		printf("%d  ",temp->data.id);
//		printf("*%d*",p->data.id);
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
int Ticket_Perst_ReturnModify(sale_node_t* p){//��Ʊʱ���޸�Ʊ��Ϣ 
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

//		printf("&%3d&",p->data.ticket_id);
		if(q->data.id==p->data.ticket_id){
//			printf("\n%%%%%%%\n");
			s->data.id=q->data.seat_id;
//			if(Schedule_Perst_FetchBySeatID(s)==0)return 0;
			s->data.status=1;
//			printf("\n+++++++\n");
			if(Seat_Perst_Modify(s)==0)return 0;
//			if(Schedule_Perst_ModifySeatCount(q->data.schedule_id)==0)return 0;;
			p->data.value=q->data.price;
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
