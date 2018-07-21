#ifndef SALE_H_ 
#define SALE_H_
#include "Play.h"
#include"Schedule.h"
#include"../Service/Ticket.h"
#include"../Service/Account.h"
#include"../Service/Play.h"
typedef enum{
	SALE_SELL=1,
	SALE_REFOUND=-1
}sale_type_t;
typedef struct{
	int id;
	int user_id;
	int ticket_id;
	ttms_date_t date;
	ttms_time_t time;
	int value;
	sale_type_t type;
}sale_t;
typedef struct sale_node{
	sale_t data;
	struct sale_node* next;
	struct sale_node* prev;
}sale_node_t,sale_list_t;
int Sale_Srv_Add(account_node_t* accountInfo,ticket_node_t* p);
int Sale_Srv_FetchByName(play_node_t* h);
int Sale_Srv_ReturnTicket(sale_node_t* p);
#endif
