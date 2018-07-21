#ifndef SALE_UI_H_
#define SALE_UI_H_
#include"../Service/Account.h"
#include"../Persistence/Account_Persist.h"
#include"../Service/Ticket.h"
void Sale_UI_SellTicket(account_node_t* accountInfo); 
void Sale_UI_MgtEntry();
int Sale_UI_FindByName();
void Sale_UI_ReturnTicket(account_node_t* p);
#endif
