#include"Salesanalysis_UI.h"
#include<stdio.h>
#include"../Common/List.h"
#include<stdlib.h>
#include"../Service/Sale.h"
#include"Account_UI.h"
#include"../Service/Account.h"
#include"../Persistence/Account_Persist.h"
#include"../Service/Salesanalysis.h"
#include"../Persistence/Salesanalysis_Persist.h"
static const int pagesize=5; 
void SalesAanalysis_UI_MgtEntry(account_node_t*p){//订单信息界面
	char ch;
	p->data.type=2;
	while(Account_Srv_UserLogIn(p)==0){
		printf("\n\t\tLog failed!Press [Enter] to return ......");
		while('\n'!=getchar());
		return ;
	}
	int i;
	sale_node_t*temp=NULL,*h=NULL;
	List_Init(h,sale_node_t);
	Pagination_t paging;
	paging.totalRecords=Salesanalysis_Perst_SelectAllSale(h);
	if(paging.totalRecords==0){
		printf("\n\t\tCount statistics data!\n");
		return ;
	}
	printf("%d\n",paging.totalRecords);
	paging.pageSize=pagesize;
	paging.offset=0;
	Paging_Locate_FirstPage(h,paging);
	do{
		system("clear");
		printf("\n\n\t\t=========================================================================================================");
		printf("\n\t\t%-15s%-15s%-15s%-15s%-15s%-15s%-15s","Sale_ID","Salesman_ID","Ticket_ID","Process_date",
"Process_time","Tocket_price","Process_type");
		printf("\n\t\t|--------------------------------------------------------------------------------------------------------|\n");
		Paging_ViewPage_ForEach(h,paging,sale_node_t,temp,i){
			printf("\n\t\t%-15d%-15d%-15d %d-%d-%d       %d:%d:%d      %-15d",temp->data.id,temp->data.user_id,
			temp->data.ticket_id,temp->data.date.year,temp->data.date.month,temp->data.date.day,
			temp->data.time.hour,temp->data.time.minute,temp->data.time.second,temp->data.value);
			if(temp->data.type==1){
				printf("%-15s\n","SEll"); 
			} 
			else{
				printf("%-15s\n","RETURN");
			}

		}
		printf("\t\t--------All statists:%2d-------------------------------------------------------Page %2d/%2d-------- -------\n",paging.totalRecords,Paging_CurPage(paging),Paging_TotalPages(paging));
		printf("\n\t\t=========================================================================================================");
		printf("\n\t\t-------------------------------------------------Statist_data--------------------------------------------\n");
		printf("\t\t                                             			                         	  \n");
		printf("\t\t	[P]Previous page  	    						[N]Next page	                     \n");
		printf("                                                                       				  \n");
		printf("\t\t					[C]Statistics all sale money                       		  \n");
		printf("	         	                                                           				  \n");
		printf("\t\t					[G].Get all kinds movie money info                        \n");
		printf("		                                                                  					  \n");
		printf("\t\t					[S].Sort all money depend movie                      	  \n");
		printf("                                                                       				  \n");
		printf("\t\t					[E].Exit                                                  \n");
		printf("                                                                        				  \n");
		printf("\t\t*************************************************************************************************\n");
		printf("\n\t\tInput you choice:");
		scanf("%c",&ch);
		while('\n'!=getchar());
		switch(ch){
			case'P':
			case'p': 
				if(!Paging_IsFirstPage(paging))
				Paging_Locate_OffsetPage(h, paging, -1, sale_node_t);
				break;
			case'N':
			case'n':
				if(!Paging_IsLastPage(paging))
				Paging_Locate_OffsetPage(h, paging, 1, sale_node_t);
				break; 
			case 'c':
			case 'C':
				Salesanalysis_UI_AddAllMoney();
				break;
			case 'd':
			case 'D':
				break;
			case 'G':
			case 'g':
				break;
			case 's':
			case 'S':
				break;
		}
	}while(ch!='e'&&ch!='E');

}
void Salesanalysis_UI_AddAllMoney(){//根据时间段计算总销售额
	printf("\n\t\t======================================================================================================");
	printf("\n\t\t|********************************************Enquire sale data***************************************|\n");
	printf("\t\t========================================================================================================");
	salesanalysis_node_t*h=NULL;
	h=(salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
	printf("\n\n\t\tInput start_date:");

	scanf("%d%d%d",&h->data.start_date.year,&h->data.start_date.month,&h->data.start_date.day);
	while('\n'!=getchar());
	printf("\n\t\tInput end_date:");
	scanf("%d%d%d",&h->data.end_date.year,&h->data.end_date.month,&h->data.end_date.day);
	while('\n'!=getchar());
	int money;
	money=Salesanalysis_Srv_AddAllMoney(h);
	if(money==0){
		return ;

	}
	printf("\n\t\t=================================================================================================");
	printf("\n\n\t\tStart_date:%d--%d--%d\n",h->data.start_date.year,h->data.start_date.month,h->data.start_date.day);
	printf("\n\t\tEnd_date:%d--%d--%d\n",h->data.end_date.year,h->data.end_date.month,h->data.end_date.day);
	printf("\n\t\tAll_sale_money:%d\n",money);
	printf("\n\t\t================================================================================================\n");
	printf("\n\t\tPress [Enter] to return.....");
	while('\n'!=getchar());
	system("clear");
}
