#ifndef SCHEDULE_PERSIST_H_
#define SCHEDULE_PERSIST_H_
#include"../Service/Schedule.h"
void Schedule_Perst_Insert();
//int Schedule_Srv_FetchAll(schedule_node_t*h);
int Schedule_Perst_RemByID(int play_id); 
int Schedule_Perst_Modify(int plan_id);
int Schedule_Perst_SelectByPlayName(char*name,schedule_node_t*h);
int Schedule_Perst_SelectByID(schedule_node_t*h,int id); 
int Schedule_Perst_FetchAll(schedule_node_t*h);
int Schedule_Perst_FetchByID(schedule_node_t*h,int id);
#endif 
