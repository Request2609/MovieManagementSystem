#ifndef TICKET_PERST_H_
#define TICKET_PERST_H_
#include"../Service/Ticket.h"
#include"../Service/Play.h"
#include"../Service/Schedule.h"
#include"../Service/Sale.h"
//int Ticket_Perst_DeleteByID(int id);
int Ticket_Perst_FetchAll(int id,ticket_node_t*h);
int Ticket_Perst_Insert(ticket_node_t*h);
//int Ticket_Perst_FetchByID(play_node_t* h);
int Ticket_Perst_FetchByID(schedule_node_t* h,ticket_node_t*p);
int Ticket_Perst_SearchByTId(ticket_node_t* p);
int Ticket_Perst_ModifyStatus(ticket_node_t*p);
int Ticket_Perst_ReturnModify(sale_node_t* p);
//int Ticket_Perst_ReturnModify(sale_node_t* p);
#endif
