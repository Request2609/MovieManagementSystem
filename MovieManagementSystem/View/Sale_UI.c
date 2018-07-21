#include"Sale_UI.h"
#include<stdio.h>
#include"../Common/List.h"
#include"../Service/Play.h"
#include"../Service/Account.h"
#include"../Persistence/Play_Persist.h"
#include"../Persistence/Account_Persist.h"
#include"../Service/Sale.h"
#include"Play_UI.h"
#include"Account_UI.h"
static const int pagesize=5; 
void Sale_UI_MgtEntry(account_node_t*p){//订单信息管理界面

	if(Account_Perst_SaleLogIn(p)==0){
		return ;
		}
 
	system("clear");
	int i;
   play_node_t *h;
   List_Init(h,play_node_t);
	Pagination_t paging;
	paging.offset=0;
	paging.pageSize=pagesize;
	paging.totalRecords=Play_Perst_SelectAll(h);
	play_node_t*temp;
	Paging_Locate_FirstPage(h,paging);	
	char choice;
	do{
		printf("\n\n\t\t=========================================================================================================");
		printf("\n\t\t**********************************************Movie management*******************************************\n");
		printf("\n\t\t%-10s%-15s%-20s%-20s%-30s%-20s\n","ID","Movie_name","Movie_area","Movie_time","Start_date->End_date","Ticket_price");
		Paging_ViewPage_ForEach(h,paging,play_node_t,temp,i){
			printf("\n\t\t%-10d%-15s%-20s%-20d%d.%d.%d->%d.%d.%d%20d\n",temp->data.id,
			temp->data.name,temp->data.area,temp->data.duration,temp->data.start_date.year,
			temp->data.start_date.month,temp->data.start_date.day,temp->data.end_date.year,
			temp->data.end_date.month,temp->data.end_date.day,temp->data.price);
				}
		printf("\t\t------All member:%2d---------------------------------------------------------------Page: %2d/%2d--------------\n",paging.totalRecords
,Paging_CurPage(paging),Paging_TotalPages(paging));		
		printf("\n\t\t===========================================================================================================");
		printf("\n\t\t                                                              					   \n");
		printf("\t\t   		  	>>>>[P]Previous page             	     >>>>[N]Next page           	   \n");
		printf("\t\t                                                       						   \n");
		printf("\t\t     			>>>>[F]Search movie ticket 		     >>>>[B]Sale ticket                 \n");
		printf("\t\t                                                                                                \n");
		printf("\t\t 		        >>>>[E]Exit                                        				   \n");
		printf("\t\t                                                              					   \n");
		printf("\t\t===========================================================================================================");
		printf("\n\n\t\tInput you choice:");
		scanf("%c",&choice);
		switch(choice){
				case 'N':
				case 'n':
					if(!Paging_IsLastPage(paging))
					Paging_Locate_OffsetPage(h, paging, 1, play_node_t);
					break;
				case 'p':
				case 'P':	
					if(!Paging_IsFirstPage(paging))
					Paging_Locate_OffsetPage(h, paging, -1, play_node_t);
					break;
				case 'F':
				case 'f':
					Sale_UI_FindByName();
					break;
				case 'B':
				case 'b':
					Sale_UI_SellTicket(p);
					break;					
		}	
	}while(choice!='e'&&choice!='E'); 
}
int  Sale_UI_FindByName(){//根据影片名称查询订单信息界面
	play_node_t* h=NULL;
	h=(play_node_t*)malloc(sizeof(play_node_t));
	while('\n'!=getchar());
	printf("\n\t\tInput movie name:");

	scanf("%[^\n]",h->data.name);
	while('\n'!=getchar());
	if(Sale_Srv_FetchByName(h)==0){
		printf("\n\t\tYou can't get movie infomation!Press [Enter] to return ......");
		while('\n'!=getchar());
		return 0 ;
	}
	return 1; 
}
void Sale_UI_SellTicket(account_node_t* accountInfo){//买票管理界面
	if(Sale_UI_FindByName()==0){
		return;
	}
	ticket_node_t* p=NULL;
	p=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	printf("\n\t\t===========================================================================================================\n");
	printf("\n\t\t**************************************************Sale ticket**********************************************\n");
	printf("\n\t\tInput movie ticket_ID:");
	scanf("%d",&p->data.id);
	while('\n'!=getchar());
	if(Sale_Srv_Add(accountInfo,p)==0){
		printf("\n\t\tGet ticket failed!\n");
		return;
	} 
	printf("\n\t\tHave fun!\n");
	printf("\n\t\tPress [Enter] to return......");
	while('\n'!=getchar());
} 
void Sale_UI_ReturnTicket(account_node_t*p){//退票界面


	if(Account_Perst_SaleLogIn(p)==0){
		printf("\n\n\t\tLog failed!Press [Enter] to return ......");
		while('\n'!=getchar());
		return ;

	}

	sale_node_t*s=NULL;
	s=(sale_node_t*)malloc(sizeof(sale_node_t));
	printf("\n\t\t=====================================================================================\n");
	printf("\n\t\t************************************Return ticket************************************\n");
	s->data.user_id=p->data.id;
	printf("\n\t\tInput sale_ID:");

	scanf("%d",&s->data.id);
	while('\n'!=getchar());
	if(Sale_Srv_ReturnTicket(s)==0){
		printf("\t\tReturn failed!\n");
		printf("\n\t\tPress [Enter] to return......");
		while('\n'!=getchar());
		return;
	}  
	printf("\n\t\tReturn success!Welcome next time!\n");
	printf("\n\t\tPress[Enter]to return......");
	while('\n'!=getchar());
}
