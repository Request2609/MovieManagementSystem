#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include"../Service/Play.h" 
#define NAMELONG 30
typedef struct{
	int hour;
	int minute;
	int second;
}ttms_time_t;
typedef struct{
	int id;
	int play_id;
	int studio_id;
	ttms_date_t date;
	ttms_time_t time; 
	int seat_count;
}schedule_t;
typedef struct schedule_node { 
	schedule_t data;
	struct schedule_node *next;
	struct schedule_node *prev;
}schedule_node_t,*schedule_list_t;
int Schedule_Srv_FetchByPlayName(char*name,schedule_node_t*h);
void Schedule_Srv_Add();
void Schedule_Srv_DeleteByID();
void Schedule_Srv_Modify();
int Schedule_Srv_JudgeIsExsist(int play_id);
#endif 
