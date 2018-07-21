#include<stdlib.h>
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
int Schedule_Srv_FetchByPlayName(char*name,schedule_node_t*h){//根据剧目目名称查询要演出计划

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
void Schedule_Srv_Add(){//演出计划添加
	studio_t *ptr=NULL;
	ptr=(studio_t*)malloc(sizeof(studio_t));
	char choice;
	system("clear");
	printf("\n\t\t=========================================================================================");
	printf("\n\t\t****************************************Add schedule*************************************");
	printf("\n\t\t=========================================================================================");
	schedule_node_t *h;
	schedule_node_t *p;
	List_Init(h,schedule_node_t);
	do{
			p=(schedule_node_t*)malloc(sizeof(schedule_node_t));
			p->data.id=EntKey_Perst_GetNewKeys(KeyName); 
			printf("\n\t\tInput movie ID:");
			scanf("%d",&p->data.play_id);
			if(!Schedule_Srv_JudgeIsExsist(p->data.play_id)){
				printf("\n\t\tThere is no the movie!\n");
				printf("\n\t\tPress [Enter] to return......");
				while('\n'!=getchar());

				return;
			}
			printf("\n\t\tInput studio id:");
			scanf("%d",&p->data.studio_id);
			if(Studio_Perst_SelectByID(p->data.studio_id,ptr)==0){
				printf("\n\t\tStudio not exist!");
				printf("\n\t\tPress [Enter] to return.....");
				while('\n'!=getchar());

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
			List_AddTail(h,p); 
			printf("\n\t\t[E].Exit      [A].Continue");
			printf("\n\t\tInput you choice:"); 
			choice=getchar();
			while('\n'!=getchar());
	}while(choice!='e'&&choice!='E');
	Schedule_Perst_Insert(h);
} 
void Schedule_Srv_Modify(){//修改演出计划
	int plan_id;
	
	printf("\n\t\t=======================================================================================");
	printf("\n\t\t**************************************Modidy schedule**********************************");
	printf("\n\t\t=======================================================================================");
	printf("\n\t\tInput schedule_ID:");
	scanf("%d",&plan_id);
	if(Schedule_Perst_Modify(plan_id)==0){
		printf("\n\t\tModify failed!Press [Enter] to return......");
		while('\n'!=getchar());
		return;
	}
	printf("\n\t\tModify success!Press [Enter] to return......");
	while('\n'!=getchar());
}
void Schedule_Srv_DeleteByID(){
	
	printf("\n\t\t==========================================================================================");
	printf("\n\t\t**************************************Delete schedule*************************************\n");
	printf("\t\t===========================================================================================");
	int plan_id;
	printf("\n\t\tInput schedule_ID:");
	scanf("%d",&plan_id);
	if(Schedule_Perst_RemByID(plan_id)==0){
		printf("\n\t\tDelete failed!Press [Enter] to return......\n");
		while('\n'!=getchar());
		return; 
	}
	printf("\n\t\tDelete success!\n");
	printf("\n\t\tPress [Enter] to return....");
	while('\n'!=getchar());

}
int Schedule_Srv_JudgeIsExsist(int play_id){//判断演出计划是否存在
	FILE*fp=fopen("Play.dat","rb");
	if(fp==NULL){
		return 0;
	}
	play_node_t*temp;
	temp=(play_node_t*)malloc(sizeof(play_node_t));
	while(1){
		if(fread(temp,sizeof(play_node_t),1,fp)<1)break;
		if(temp->data.id==play_id){
			printf("\n\t\tMovie name:%s",temp->data.name);
			printf("\n\t\tPress [Enter] to continue......");
			while('\n'!=getchar());
			return 1;
		}
	}
	free(temp); 
	return 0;
}
