#ifndef SALE_PERST_H_
#define SALE_PERST_H_
#include"../Service/Play.h"
#include"../Service/Sale.h"
#include"../Service/Schedule.h"
#include"../Common/List.h"
int Sale_Perst_FetchByID(play_node_t* h,schedule_node_t*p);
int Sale_Perst_Add(sale_node_t*h);
int Sale_Perst_Modify(sale_node_t*h);
int Sale_Perst_FetchAll(sale_node_t*h);
int Sale_Perst_SearchByTID(sale_node_t*p);

#endif
