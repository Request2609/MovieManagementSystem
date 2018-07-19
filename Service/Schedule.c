#include<stdlib.h>
//#include"../Persistence/EntityKey_Persist.h"
#include<stdio.h>
#include"../Persistence/EntityKey_Persist.h"
#include"Schedule.h"
#include"../Common/List.h"
#include"Studio.h"
#include"../View/Seat_UI.h"
#include"Seat.h"
#include"Account.h"
#include"../Persistence/Schedule_Persist.h"
#include"../Persistence/Studio_Persist.h"
#include"../Persistence/Seat_Persist.h"
static const char*KeyName="Schedule_t";
int Schedule_Srv_FetchByPlayName(char*name,schedule_node_t*h){//���ݾ�Ŀ���Ʋ��Ҿ�Ŀ�ݳ��ƻ� 

	printf("\n\t\t==========================================================================================");
	printf("\n\t\t**************************************Search schedule*************************************");
	printf("\n\t\t==========================================================================================\n");
	int i;
	i=Schedule_Perst_SelectByPlayName(name,h);
	if(i==0){
		return 0;
	}
	return i; 
} 
void Schedule_Srv_Add(){
	studio_t *ptr=NULL;
	ptr=(studio_t*)malloc(sizeof(studio_t));
	char choice;
//	long key;
//	int count=1;
	
	printf("\n\t\t=========================================================================================");
	printf("\n\t\t****************************************Add schedule*************************************");
	printf("\n\t\t=========================================================================================");
	schedule_node_t *h;
	schedule_node_t *p;
	List_Init(h,schedule_node_t);
//	h=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	do{
			//key=EntKey_Perst_GetNewKeys(scheduleName,count);
			p=(schedule_node_t*)malloc(sizeof(schedule_node_t));
			p->data.id=EntKey_Perst_GetNewKeys(KeyName); 
			printf("\n\t\tInput movie ID:");
			scanf("%d",&p->data.play_id);//�˴�Ӧ���жϸþ�Ŀ�Ƿ���� 
			if(!Schedule_Srv_JudgeIsExsist(p->data.play_id)){
				printf("\n\t\tThere is no the movie!\n");
				printf("\n\t\tPress [Enter] to return......");
//				getchar();
				while('\n'!=getchar());
				getchar();
				return;
			}
//			printf("%d",p->data.id);
			printf("\n\t\tInput studio id:");
			scanf("%d",&p->data.studio_id);//�˴�Ӧ���жϸ��ݳ����Ƿ����
			if(Studio_Perst_SelectByID(p->data.studio_id,ptr)==0){
				printf("\n\t\tStudio not exist!");
				printf("\n\t\tPress [Enter] to return.....");
				while('\n'!=getchar());
				getchar();
				return ;
			} 
			printf("\n\t\tInput start date:");
			scanf("%d%d%d",&p->data.date.year,&p->data.date.month,&p->data.date.day);
			printf("\n\t\tInput start time:");
			scanf("%d%d%d",&p->data.time.hour,&p->data.time.minute,&p->data.time.second);
			printf("\n\t\tInput seatsCount:");
			scanf("%d",&p->data.seat_count);
			int seatNum=0;
			seat_node_t*s=NULL;
			List_Init(s,seat_node_t); 
			seatNum=Seat_Perst_CountStudioSeat(s,seatNum,p->data.studio_id);
			if(seatNum<p->data.seat_count){
				printf("\n\t\tThere is no so many seats in the studio!\n");
				return ;
			}
//			List_Destroy(s,seat_node_t);
//			Seat_UI_Add(p->data.studio_id,p->data.seat_count);
//			h->prev=p->prev;
//			h->prev->next= p;
//			p->next=h;
//			h->prev = p;
			List_AddTail(h,p); 
			printf("\n\t\t[E].Exit      [A].Continue");
			printf("\n\t\tInput you choice:"); 
			while('\n'!=getchar());
			choice=getchar();
	}while(choice!='e'&&choice!='E');
//	temp->next=h;
//	h->prev=temp;
	Schedule_Perst_Insert(h);
} 
void Schedule_Srv_Modify(){
	int plan_id;
	
	printf("\n\t\t=======================================================================================");
	printf("\n\t\t**************************************Modidy schedule**********************************");
	printf("\n\t\t=======================================================================================");
	printf("\n\t\tInput schedule_ID:");
	scanf("%d",&plan_id);
	if(Schedule_Perst_Modify(plan_id)==0){
		printf("\n\t\tModify failed!");
		return;
	}
	printf("\n\t\tModify success!\n");
}
void Schedule_Srv_DeleteByID(){
	
	printf("\n\t\t==========================================================================================");
	printf("\n\t\t**************************************Delete schedule*************************************\n");
	printf("\t\t===========================================================================================");
	int plan_id;
	printf("\n\t\tInput schedule_ID:");
	scanf("%d",&plan_id);
	if(Schedule_Perst_RemByID(plan_id)==0){
		printf("\n\t\tDelete failed!\n");
		return; 
	}
	printf("\n\t\tDelete success!\n");
	printf("\n\t\tPress [Enter] to return....");
	while('\n'!=getchar());
	getchar();
}
int Schedule_Srv_JudgeIsExsist(int play_id){
	FILE*fp=fopen("Play.dat","rb");
	if(fp==NULL){
		return 0;
	}
//	int flag=0;
	play_node_t*temp;
	temp=(play_node_t*)malloc(sizeof(play_node_t));
	while(1){
		if(fread(temp,sizeof(play_node_t),1,fp)<1)break;
		if(temp->data.id==play_id){
//			flag=1;
			printf("\n\t\tMovie name:%s",temp->data.name);
			printf("\n\t\tPress [Enter] to return......");
			while('\n'!=getchar());
			getchar();
//			system("pause");
			return 1;
		}
	}
	free(temp); 
	return 0;
}
