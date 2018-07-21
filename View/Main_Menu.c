#include "../View/Main_Menu.h"
#include <stdio.h>
#include<stdlib.h>
#include "../View/Studio_UI.h"
#include "../Common/List.h"
#include"../View/Schedule_UI.h"
#include"../Service/Schedule.h"
#include"../Persistence/Schedule_Persist.h"
#include"../Service/Account.h"
#include"../View/Account_UI.h"
#include"Sale_UI.h"
#include"Play_UI.h"
#include "Salesanalysis_UI.h"
#include"Ticket_UI.h"

void Main_Menu(){//影院主界面
	Account_Srv_FirstLogIn();
	account_node_t* temp;
	temp=(account_node_t*)malloc(sizeof(account_node_t));
	temp->data.type=9;
	system("clear");
	char choice;
	do {
		system("clear");
		printf("\n\t\t====================================================================================================");
		printf("\n\t\t****************************Welcome to You_Le Theatre Management System*****************************");
		printf("\t\t                                                                      					                       \n");
		printf("\t\t                                                                                   			              \n");
		printf("\t\t                 [S].Studio_Management                       [P].Movie Management                      \n");
		printf("\t\t                                                                                                        \n");
		printf("\t\t	   	 [T].Sale_Management                         [R].Return_T_Management                  \n");
		printf("\t\t                                                                                                        \n");
		printf("\t\t	   	 [Q].Get_Movie_Infomation                    [N].Money_Count                          \n");
		printf("\t\t                                                                                                        \n");
		printf("\t\t          	 [F].Find password                           [A].Salesman_Management                                            ");
		printf("\n");
		printf("\n\t\t 	   	 [E].Exit                                 \n");
		printf("\t\t                                                                                                        \n");
		printf("\t\t*****************************************************************************************************");
		printf("\n\t\t=====================================================================================================");
		printf("\n\n\t\tInput you choice:"); 
		choice=getchar();
		while('\n'!=getchar());
			switch (choice) {
					case 'S':
					case 's':
							system("clear");
							temp->data.type=1;
							Studio_UI_MgtEntry(temp);
							system("clear");
							break;
					case 'P':
					case 'p':
							system("clear");
							Play_UI_MgtEntry();
							break;
					case 'Q':
					case 'q':
						system("clear");
						Queries_Menu();
						break;
					case 'T':
					case 't':
						system("clear");
						temp->data.type=1;
						Sale_UI_MgtEntry(temp);
						break;
					case 'R':
					case 'r':
						system("clear");
						temp->data.type=1;
						Sale_UI_ReturnTicket(temp);
						break;
					case 'N':
					case 'n':
						system("clear");
						SalesAanalysis_UI_MgtEntry(temp);
						break;
					case 'A':
					case 'a':
						system("clear");
						Account_UI_MgtEntry(temp);
						system("clear");
						break;
					case 'F':
					case 'f':
						Account_UI_SearchPass();
						break;
		}
	} while ('E' != choice && 'e' != choice);
}

void Queries_Menu(){//查询票务信息界面
	char name[50];
	int i,schedule_id;
	char choice;
	schedule_node_t*h=NULL,*temp=NULL;
	Pagination_t paging;
	List_Init(h,schedule_node_t);
	paging.totalRecords=Schedule_Srv_FetchByPlayName(name,h);
	if(paging.totalRecords==0){
		return;
	}
	temp=h->next;
	schedule_id=temp->data.id;
	paging.pageSize=pagesize;
	Paging_Locate_FirstPage(h,paging);
	do{
		printf("\n\t\t==========================================================================================================");
		printf("\n\t\t|***********************************************Schedule_Plan*********************************************|\n");
		printf("\t\t==========================================================================================================\n");
		printf("\n\t\t%-15s%-20s%-20s%-20s%-20s%-20s\n","Plan_ID","Play_name","Studio_ID","Start_date","Start_time","Seats_count");
		Paging_ViewPage_ForEach(h, paging, schedule_node_t,temp, i){
		printf("\n\t\t%-15d%-20s%-20d  %d-%d-%d           %d:%d:%d%15d\n",temp->data.id,name,
		temp->data.studio_id,temp->data.date.year,temp->data.date.month,
		temp->data.date.day,temp->data.time.hour,temp->data.time.minute,
		temp->data.time.second,temp->data.seat_count);
		}
		printf("\t\t|------All plan %2d--------------------------------------------------------------page %2d  All page%2d------|\n",paging.totalRecords,Paging_CurPage(paging),Paging_TotalPages(paging));
		printf("\t\t   (P)previous page              (N)next page                   (T)All tickets                (E)Exit\n");
		printf("\t\t|********************************************************************************************************|");
		printf("\n\t\t=========================================================================================================\n");

		printf("\n\t\tInput choice:");

		scanf("%c",&choice); 
		while('\n'!=getchar());
		switch(choice){
			case 'p':
			case 'P':
				if(!Paging_IsFirstPage(paging))
				Paging_Locate_OffsetPage(h, paging, -1, schedule_node_t);
				break;
			case 'N':
			case 'n':
				if(!Paging_IsLastPage(paging))
				Paging_Locate_OffsetPage(h, paging, -1, schedule_node_t);
				break;
			case 'T':
			case 't':
				Ticket_UI_SearchInfo(schedule_id);;
				break; 
			} 
	
	} while(choice!='e'&&choice!='E');
}
