#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include"../Service/Play.h" 
#define NAMELONG 30
//#include"../Persistence/Play_Persist.h"
typedef struct{//定义演出时段结构体 
	int hour;
	int minute;
	int second;
}ttms_time_t;
typedef struct{//安排演出剧目结构体 
	int id;//演出计划ID 
	int play_id;//上演剧目ID 
	int studio_id;//演出厅ID 
	ttms_date_t date;//放映日期 
	ttms_time_t time;//放映时间 
	int seat_count;//座位数 
}schedule_t;
typedef struct schedule_node { 
	schedule_t data;//数据节点 
	struct schedule_node *next;
	struct schedule_node *prev;
}schedule_node_t,*schedule_list_t;
int Schedule_Srv_FetchByPlayName(char*name,schedule_node_t*h);//根据剧目名称获取演出计划 
void Schedule_Srv_Add();//添加演出计划 
void Schedule_Srv_DeleteByID();//修改演出计划 
void Schedule_Srv_Modify();//删除演出计划 4
int Schedule_Srv_JudgeIsExsist(int play_id);
//int Schedule_Srv_FetchByPlay(schedule_node_t*h,char playname[],int play_id);
#endif 
