#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include "../Common/List.h"
#include "Seat.h"
#include"../Service/Studio.h"
#include"../Persistence/EntityKey_Persist.h"
#include"../Persistence/Seat_Persist.h"
#include"../Persistence/Studio_Persist.h"
//static char*SeatFile="Seat.dat";
static const char*KeyName="Seat";
int Seat_Srv_PrintAllSeat(seat_node_t*h){//���ļ���ȡ��λ����ͷ�ڵ㣬�ٰ���\�н��д�ӡ 
	studio_t *p=NULL;
	int row,col,sRow; 
	p=(studio_t*)malloc(sizeof(studio_t));
	seat_node_t*temp=NULL,*q=NULL;
	q=h->next;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	temp=h->prev;//��temp��¼���һ����λ����Ϣ 
	if(Studio_Perst_SelectByID(temp->data.roomID,p)==0){//pΪҪ�������ݳ���id�ҵ��ݳ����󣬼�¼�������� 
		return 0;
	}
//	printf("*%d*\n",temp->data.row);
	sRow=temp->data.row;
	if(temp->data.column%p->colsCount==0){
		row=temp->data.row;
	}else{
		row=temp->data.row-1;//��������ݳ������һ����λ�ڵ��ܱ��ݳ�����׼����������ֱ�Ӱ���׼�б�׼�д�ӡ 
	}//����Ļ����Ƚ����һ����λ�����м�һȻ�󰲱�׼�б�׼�д�ӡ������ӡ���һ�� 
	col=p->colsCount;//�ݳ�����λ���� 
	int i,j;
//	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	
	printf("\n\t\t=====================================================================================");
	printf("\n\t\t******************************Seat model locate place********************************\n\n"); 
	for(i=0;i<row;i++){
		printf("\n\n");
		printf("\t\t             ");
		for(j=0;j<col;j++){
			if(q->data.status==0){
				printf("   ");//��λ
			}
			else if(q->data.status==1){
				printf("1  ");//��Ч��λ 
			}
			else if(q->data.status==2){
				printf("0  ");
			}
			else{
				printf("*  ");//�𻵵���λ 
			}
		q=q->next;
		if(q==h)break; 
		}
//		printf("%d ",q->data.id);
	}
//	printf("%d    %d\n",p->rowsCount,row);
	printf("\n\n");
	if(row<(sRow)){
		printf("\t\t             ");
		for(i=0;i<temp->data.column;i++){
				if(q->data.status==0){
				printf("    ");//��λ 
			}
			else if(q->data.status==1){
				printf("1  ");//��Ч��λ 
			}
			else if(q->data.status==2){
				printf("0  ");
			}
			else{
				printf("*  ");//�𻵵���λ 
			}
			q=q->next;
			if(q==h)break;
		}
	}
	
	printf("\n");
	return 1;
}
int Seat_Srv_Add(seat_node_t*h,int num){//�����λ��Ϣ h���Խ����һ����λ�����괫���� 
		studio_t*ptr=NULL;//�趨�ݳ����ṹ��ָ�룬��¼�ݳ������� 
		int i;
//		printf("%d\n",h->data.roomID);
		ptr=(studio_t*)malloc(sizeof(studio_t));
		seat_node_t* temp=NULL;
		temp=(seat_node_t*)malloc(sizeof(seat_node_t));
		temp=h->prev;
//		printf("\n=%d=\n",h->data.column); 
//		printf("\n+%d+\n",temp->data.roomID); 
		if(Studio_Perst_SelectByID(temp->data.roomID,ptr)==0){//pΪҪ�������ݳ���id�ҵ��ݳ����󣬼�¼�������� 
//			printf("\n*****\n");
			return 0;
		}
		seat_node_t* head=NULL,*q=NULL;;
		head=(seat_node_t*)malloc(sizeof(seat_node_t));
		List_Init(head,seat_node_t);
//		q=(seat_node_t*)malloc(sizeof(seat_node_t));
		for(i=0;i<num;i++){
			q=(seat_node_t*)malloc(sizeof(seat_node_t));
			q->data.id=EntKey_Perst_GetNewKeys(KeyName);
			if(temp->data.column==ptr->colsCount){
				q->data.row=temp->data.row+1;
				q->data.column=1;
			}
			else{
				q->data.row=temp->data.row;
				q->data.column=temp->data.column+1;
				}
			q->data.roomID=temp->data.roomID;
			q->data.status=SEAT_GOOD;
			List_AddTail(head,q);
			temp=q;//ÿ�ν��µĽڵ��������󣬼�¼�½ڵ����Ϣ 
		}	

		if(Seat_Perst_Add(head)==0){
			printf("\n\t\tAdd failed,try again!\n");
			return 0;
		}
		return 1;
}
int Seat_Srv_Delete(seat_node_t* p){
	p->data.status=SEAT_NONE;
	if(Seat_Perst_Delete(p)==0){
		return 0;
	}
	return 1;
} 
int Seat_Srv_FetchByRoomID(seat_node_t*h,int id){
	if(access("seat.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("seat.dat","rb");
	if(fp==NULL){
		return 0;
	}
	int count=0;
	seat_node_t*temp=NULL;
	while(1){
		temp=(seat_node_t*)malloc(sizeof(seat_node_t));
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
		if(temp->data.roomID==id){
			count++;
			List_AddTail(h,temp);
		}
		else{
			free(temp);
		}
	}
	free(temp);
	fclose(fp);
	return count;
}
int Seat_Srv_ModifyInfo(seat_node_t*p){
	if(Seat_Perst_ModifyInfo(p)==0){
		return 0;
	}
	else{
		return 1;
	}
}
int Seat_Srv_DeleteAllByRoomID(int id){
	if(access("seat.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("seat.dat","rb+");
	if(fp==NULL){
		return 0;
	}
	FILE*fp1;
	fp1=fopen("seat_temp.dat","wb");
	if(fp1==NULL){
		return 0;
	}
	seat_node_t*temp=NULL;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	while(1){
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
		if(temp->data.roomID==id){
			fwrite(temp,sizeof(seat_node_t),1,fp1);
		}
	}
	free(temp);
	fclose(fp);
	fclose(fp1);
	remove("seat.dat");
	rename("seat_temp","seat.dat");
	return 1; 
} 
