#include"Schedule_Persist.h"
#include"../Service/Schedule.h"
#include"../Common/List.h"
#include<unistd.h>
#include"EntityKey_Persist.h"
static char*planfiles="Schedule.dat";
static char*planfiles_temp="Schedule_temp.dat"; 
static const char*KeyName="Schedule";
int Schedule_Perst_SelectByPlayName(char*name,schedule_node_t*h){//根据剧目名称查询演出计划
	char names[NAMELONG];
	int play_id=0;
	int playnum=0;
	FILE*fp=fopen("Play.dat","rb+");
	if(fp==NULL){
		printf("\t\tNo schedule plan!\n");
		return 0;
	}

	printf("\n\t\tInput movie name:");
	scanf("%[^\n]",names);
	while('\n'!=getchar());
	strcpy(name,names); 
	play_node_t*temp;
	temp=(play_node_t*)malloc(sizeof(play_node_t)); 
	while(1){
		if(fread(temp,sizeof(play_node_t),1,fp)<1)break;
		if(strcmp(names,temp->data.name)==0){
			play_id=temp->data.id;

			break;
		} 
	}
	if(play_id==0){
		printf("\n\t\tHave no the movie!\n");
		return 0;
	} 
	free(temp);
	fclose(fp);
	if(access("Play.dat",0)){
		printf("\n\t\tHave no the schedule plan!\n");
		return 0;
	}
	fp=fopen(planfiles,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	} 
	schedule_node_t*p;
	while(1){
		p=(schedule_node_t*)malloc(sizeof(schedule_node_t));
		if(fread(p,sizeof(schedule_node_t),1,fp)<1)break;
		playnum++;
		if(p->data.play_id==play_id){
			List_AddTail(h,p);
		}
		else{
			free(p);
		}
	}
	fclose(fp);
	return playnum ;
} 
void Schedule_Perst_Insert(schedule_node_t*h){//添加演出计划
	FILE*fp;
	schedule_node_t*temp;
	temp=(schedule_node_t*)malloc(sizeof(schedule_node_t)); 
	if(access(planfiles,0)){
		fp=fopen(planfiles,"wb+");
		if(fp==NULL){
			printf("\t\tError!\n");
			return ;
		}
		temp=h->next;
		while(1){
			fwrite(temp,sizeof(schedule_node_t),1,fp);
			temp=temp->next;	
			if(temp==h){
				break;
			}
		}
	}
	else{	
		temp=h->next;
		fp=fopen(planfiles,"ab");
		if(fp==NULL){
			printf("\t\tError!\n");
			return ; 
				}
	while(1){
		fwrite(temp,sizeof(schedule_node_t),1,fp);
		temp=temp->next;
		if(temp==h)break;
		}
	}
	free(temp);
	fclose(fp);
	printf("\n\t\tAdd success!\n");
	printf("\n\t\tPress [Enter]key to return...... ");
	getchar();
} 
int Schedule_Perst_Modify(int plan_id){//修改演出计划
	FILE*fp;
	if(access(planfiles,0)){
		printf("\n\t\tNo schedule plan!\n");
		return 0;
	}
	fp=fopen(planfiles,"rb+");
	if(fp==NULL){
		return 0;
	}
	
	schedule_node_t*p;
	p=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	while(1){
		if(fread(p,sizeof(schedule_node_t),1,fp)<1)break;
		if(p->data.id==plan_id){
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,-(int)sizeof(schedule_node_t),SEEK_CUR);
			p->data.id=EntKey_Perst_GetNewKeys(KeyName);
			printf("\n\t\tInput movie ID:");
			scanf("%d",&p->data.play_id);
			printf("\n\t\tInput schedule plan id:");
			scanf("%d",&p->data.studio_id);//�˴�Ӧ���жϸ��ݳ����Ƿ���� 
			printf("\n\t\tInput start_date:");
			scanf("%d%d%d",&p->data.date.year,&p->data.date.month,&p->data.date.day);
			printf("\n\t\tInput start_time:");
			scanf("%d%d%d",&p->data.time.hour,&p->data.time.minute,&p->data.time.second);
			printf("\n\t\tInput seats_count:");
			scanf("%d",&p->data.seat_count);
			fwrite(p,sizeof(schedule_node_t),1,fp);
			fsetpos(fp,&pos);
			break; 
		}
	}
	free(p); 
	fclose(fp);
	return 1;
}
int Schedule_Perst_FetchAll(schedule_node_t*h){//将所有演出计划用链表存储 
	FILE*fp=fopen(planfiles,"rb");
	if(fp==NULL){
		printf("\n\t\tThere's no movie!\n");
		return 0;
	}
	int count=0;
	schedule_node_t*temp;
	while(1){
		temp=(schedule_node_t*)malloc(sizeof(schedule_node_t));
		if(fread(temp,sizeof(schedule_node_t),1,fp)<1)break;
		count++;
		List_AddTail(h,temp); 
	}
	free(temp);
	fclose(fp);
	return count;
} 
int Schedule_Perst_RemByID(int plan_id){//取消演出计划
	FILE*fp,*fp1;
	if(rename(planfiles,planfiles_temp)<0){
		return 0;
	}
	int flag=0;
	schedule_node_t*temp;
	fp=fopen(planfiles_temp,"rb");
	if(fp==NULL){
		return 0;
	} 
	fp1=fopen(planfiles,"wb");
	if(fp1==NULL){
		return 0;
	}
	temp=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	while(1){
		if(fread(temp,sizeof(schedule_node_t),1,fp)<1)break; 
		if(temp->data.id==plan_id){
			flag=1;
			continue;
		}
		fwrite(temp,sizeof(schedule_node_t),1,fp1);
	}
	free(temp);
	fclose(fp);
	fclose(fp1); 
	remove(planfiles_temp); 
	if(flag==0){
		printf("\n\t\tThere's no schedule plan!\n");
		return 0;
	}
	return 1;
}
int Schedule_Perst_FetchByID(schedule_node_t*h,int id){//根据ID删除演出计划
	if(access(planfiles,0)){
		return 0;
	} 
	FILE*fp=fopen(planfiles,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	}
	schedule_node_t*temp;
	while(1){
		temp=(schedule_node_t*)malloc(sizeof(schedule_node_t));
		if(fread(temp,sizeof(schedule_node_t),1,fp)<1)break;
		if(temp->data.id==id){
			List_AddTail(h,temp); 
			break;
		} 
	} 
	if(h->next==h){
		return 0;
	}
	fclose(fp);
	return 1;
}
