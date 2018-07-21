#include <stdio.h>
#include"../Persistence/Ticket_Perst.h"
#include"Ticket_UI.h"
#include"../Service/Ticket.h"
#include "../View/Studio_UI.h"
#include "../Common/List.h"
#include"../View/Schedule_UI.h"
#include"../Service/Schedule.h"
#include"../Persistence/Schedule_Persist.h"

static const int pagesize=5;
void Ticket_UI_MgtEntry(){//票据生成界面
	char choice;
	do{
		printf("\n\t\t======================================================================\n");
		printf("\t\t                                                                      \n");
		printf("\t\t                           Ticket management                           \n");
		printf("\t\t                                                                      \n");
		printf("\t\t      [A]. Start make                                [E].Exit    \n");
		printf("\t\t                                                                      \n");
		printf("\t\t                                              \n");
		printf("\t\t======================================================================\n"); 
		printf("\n\t\tInput your choice:");
		scanf("%c",&choice);
		while('\n'!=getchar());
		switch(choice){
			case 'A':
			case 'a':
				Ticket_Srv_GenBatch();
				break;
		}
	}while(choice!='e'&&choice!='E');
}
void Ticket_UI_SearchInfo(int schedule_id){//搜索票据界面
	int i;
	char choice;
	Pagination_t paging;
	ticket_node_t*h=NULL,*temp=NULL;
	List_Init(h,ticket_node_t); 
	paging.totalRecords=Ticket_Perst_FetchAll(schedule_id,h);
	if(!paging.totalRecords){
		printf("\n\t\tNo tickets!\n");
		return;
	}
	paging.pageSize=pagesize;
	paging.offset=0;
	Paging_Locate_FirstPage(h,paging);
	do{
		system("clear");
		printf("\n\t\t===========================================================================================\n");
		printf("\t\t******************************************Ticket list**************************************\n");
		printf("\t\t===========================================================================================\n");
		printf("\t\t%-17s%-20s%-20s%-20s%-20s\n","Ticket_ID","Schedule_ID","Seat_ID","Ticket_price","Status");
		Paging_ViewPage_ForEach(h, paging, ticket_node_t, temp,i){
		printf("\n\t\t%-17d%-20d%-20d%-20d",temp->data.id,temp->data.schedule_id,temp->data.seat_id,temp->data.price);
		if(temp->data.status==0){
			printf("%-20s\n","WILL_SELL"); 
			}
		else if(temp->data.status==1){
			printf("%-20s\n","HAVE_SOLD");
			}
		else{
				printf("%-20s\n","STOR_TICK"); 
			}
			
		}
		printf("\n\t\t--------All number:%2d----------------------------------------No.%2d page All page:%2d-------\n",
		paging.totalRecords,
		Paging_CurPage(paging),Paging_TotalPages(paging));
		printf("\n\t\t=============================================================================================");
		printf("\n\t\t     [P].Previous page                    [N].Next page                        [E] Exit   ");
		printf("\n\t\t=============================================================================================\n");
		printf("\n\t\tInput you choice:");

		choice=getchar();
		while('\n'!=getchar());
		switch(choice){
			case 'p':
			case 'P':
				if(!Paging_IsFirstPage(paging))
				Paging_Locate_OffsetPage(h, paging,-1, ticket_node_t); 

				break;
			case 'N':
			case 'n':
				if(!Paging_IsLastPage(paging))
				Paging_Locate_OffsetPage(h, paging, 1, ticket_node_t)
				break;
				}
		}while(choice!='e'&&choice!='E');
		system("clear");
} 

