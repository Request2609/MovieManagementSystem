#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_
#include"Play.h"
#include"Schedule.h"
#include"Sale.h"
typedef struct{
	int play_id;//剧目编号 
	char name[30];//剧目名称 
	char area[9];//区域名称
	int duration;
	int totaltickets;//剧目上座数量 
	int sales;//剧目销售额 
//	int sales;//剧目销售额
	int price;//剧目票价 
	ttms_date_t start_date;
	ttms_date_t end_date; 
}salesanalysis_t;
typedef struct salesanalysis_node{
	salesanalysis_t data;
	struct salesanalysis_node*next;
	struct salesanalysis_node*prev;
}salesanalysis_node_t;
int Salesanalysis_Srv_AddAllMoney(salesanalysis_node_t*h);
#endif 
