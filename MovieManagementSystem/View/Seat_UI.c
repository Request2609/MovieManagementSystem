#include"Seat_UI.h" 
#include<stdlib.h>
#include<stdio.h>
#include"../Common/List.h" 
#include"../Service/Studio.h"
#include"../Service/Seat.h" 
#include"../Persistence/Studio_Persist.h"
#include"../Persistence/Seat_Persist.h"
static const int pagesize=5;
void Seat_UI_MgtEntry(){//座位管理界面
	
	char choice;

	int num;
	int studio_id;
	do{
		system("clear");
		printf("\n\t\t=======================================================================================================\n");
		printf("\t\t*******************************************Seat infomation**********************************************\n");
		printf("\t\t========================================================================================================\n");
		printf("\t\t[A].Add seats [D].Delete seats [P].Print all seats [M].Modify all seats [S].Search seats info [E].Exit\n ");
		printf("\t\t========================================================================================================\n");
		printf("\n\n\t\tInput you choice:");
		scanf("%c",&choice);
		while('\n'!=getchar());
		switch(choice){
			case 'a':
			case 'A':
				printf("\n\t\tInput studio_ID:");
				scanf("%d",&studio_id);
				printf("\n\t\tInput seats_count:");
				scanf("%d",&num);				
				Seat_UI_Add(studio_id,num);
				break;
			case 's':
			case 'S':
				printf("\n\t\tInput studio_ID:");
				scanf("%d",&studio_id);
				Seat_UI_Print(studio_id); 
				break;
			case 'M':
			case 'm':
				Seat_UI_Modify();
				system("clear");
				break;
			case 'D':
			case 'd':
				Seat_UI_Delete();
				system("clear");
				break;
			case 'p':
			case 'P':
				Seat_UI_PrintAllSeat();
				break;
		}
		}while(choice!='e'&&choice!='E');
}
void Seat_UI_Add(int studio_id,int num){//座位信息添加
	studio_t* p=NULL;

	p=(studio_t*)malloc(sizeof(studio_t));
	if(Studio_Perst_SelectByID(studio_id,p)==0){
		printf("\n\t\tNo the studio!\n");
		return ;
	}
	p->seatsCount=p->seatsCount+num;
	p->rowsCount=(p->seatsCount%p->colsCount==0)?(p->seatsCount/p->colsCount):(p->seatsCount/p->colsCount+1);
	if(Studio_Perst_Update(p)==0){
		printf("\n\t\tStorage data failed!\n");
		return;
		}

	seat_node_t *h=NULL;
	List_Init(h,seat_node_t);
	if(Seat_Perst_FetchAll(studio_id,h)==0){
		h->data.id=studio_id;
		h->data.row=0;
		h->data.column=(*p).colsCount;
		h->data.status=0;
		h->data.roomID=studio_id;	
	}
	if(h->next==h){
		h->data.id=studio_id;
		h->data.row=0;
		h->data.column=(*p).colsCount;
		h->data.status=0;
		h->data.roomID=studio_id;
	}

	if(Seat_Srv_Add(h,num)==0){
		printf("\n\t\tAdd seats failed!\n"); 
		return ; 
	} 
	printf("\n\t\tAdd seats success!\n");
	
	return ;
}

void Seat_UI_PrintAllSeat(){//显示所有座位信息
	studio_t *temp;
	temp=(studio_t*)malloc(sizeof(studio_t));
	int studio_id;
	seat_node_t*h=NULL;

	List_Init(h,seat_node_t);
	printf("\t\tInput studio_ID:");

	scanf("%d",&studio_id);
	while('\n'!=getchar());
	if(Studio_Perst_SelectByID(studio_id,temp)==0){
		printf("\n\t\tNo this studio,press [Enter] to return......");
		while('\n'!=getchar());
		return ;
	}
	if(Seat_Perst_SameStudioSeat(studio_id,h)==0){
		printf("\n\t\tNo.%d studio no seats!Press [Enter] to return.....\n",studio_id);
		while('\n'!=getchar());
		return   ;
		}
		h->data.id=studio_id;
//		printf("\n******\n");
	if(Seat_Srv_PrintAllSeat(h)==0){
			printf("\n\t\tError!\n");
			return ;
		}	
}
void Seat_UI_Delete(){//座位删除界面
	int studio_id;
	seat_node_t* p=NULL;
	p=(seat_node_t*)malloc(sizeof(seat_node_t));
	printf("\n\t\t==================================================================================\n");
	printf("\t\t*************************************Delete seats*********************************\n");
	printf("\t\t==================================================================================\n");
	printf("\n\t\tInput studio_ID:");
	fflush(stdin);
	studio_t *ptr=NULL;
	ptr=(studio_t*)malloc(sizeof(studio_t));
	scanf("%d",&studio_id);
	if(Studio_Perst_SelectByID(studio_id,ptr)==0){
		printf("\n\t\tStudio not exist!\n");
		return ;
	}
	p->data.roomID=studio_id;
	printf("\n\t\tInput seat row number and column number:");
	scanf("%d %d",&p->data.row,&p->data.column);
	if(Seat_Srv_Delete(p)==0){
		printf("\n\t\tDelete failed!\n");
		return ;
	} 
	printf("\n\t\tHave done!\n");
}
void Seat_UI_Print(int schedule_id){//座位分布图界面
	seat_node_t *q=NULL,*h=NULL;
	List_Init(h,seat_node_t);
	int i;
	char choice;
	Pagination_t paging;
	paging.totalRecords=Seat_Perst_FetchByID(h,schedule_id);
	if(paging.totalRecords==0){
		printf("\n\t\tNo seats in the studio!\n");
		return ;
	}
	paging.pageSize=pagesize;
	paging.offset=0;
	Paging_Locate_FirstPage(h,paging);
	do{
		system("clear");
		printf("\n\t\t============================================================================================\n");
		printf("\t\t***************************************Seats  infomation************************************\n");
		printf("\t\t============================================================================================\n");
		printf("\t\t%-20s%-20s%-20s%-20s%-20s\n","Seat_ID","Schedule_ID","Row_number","Column_number","Status");
		Paging_ViewPage_ForEach(h, paging, seat_node_t,q, i){
	
			printf("\t\t%-20d%-20d%-20d%-20d",q->data.id,q->data.roomID,q->data.row,q->data.column);
			if(q->data.status==0){
				printf("%-20s\n","SEAT_NONE");
			} 
			else if(q->data.status==1){
				printf("%-20s\n","SEAT_GOOD");
			}
			else if(q->data.status==2) {
				printf("%-20s\n","SEAT_FULL"); 
			}
			else{
				printf("%-20s\n","SEAT_BROKEN"); 
			} 
		} 
		printf("\n\t\t-----------All number:%2d -------------------------------------- page %2d/%2d -----------\n",
							paging.totalRecords, Paging_CurPage(paging),
							Paging_TotalPages(paging));
		printf("\n\t\t===========================================================================================\n");
		printf("\t\t[P]Previous page                      [N]Next page                          [E]Exit\n");
		printf("\t\t===========================================================================================\n");
		printf("\n\t\tInput you choice:");
		while('\n'!=getchar());
		choice=getchar();
		switch(choice){
			case'p':
			case'P':
				if(!Paging_IsFirstPage(paging))
				Paging_Locate_OffsetPage(h, paging, -1, seat_node_t);
				break;	
			case'N':
			case'n':
				if(!Paging_IsLastPage(paging))
				Paging_Locate_OffsetPage(h, paging, 1, seat_node_t);
				break;	
				}
	}while(choice!='E'&&choice!='e'); 
	
}
void Seat_UI_Modify(){//座位修改界面
		printf("\n\t\t========================================================================================\n");
		printf("\t\t*************************************Change seats info**********************************\n");
		printf("\t\t========================================================================================\n");
		seat_node_t*p=NULL;
		p=(seat_node_t*)malloc(sizeof(seat_node_t));
		printf("\n\t\tInput studio_id:");
		fflush(stdin);
		scanf("%d",&p->data.roomID);
		printf("\n\t\tInput seat row number:");

		scanf("%d",&p->data.row);
		printf("\n\t\tInput seat column number:");

		scanf("%d",&p->data.column);
		int status;
		printf("\n\t\t0.SEAT_NONE       1.SEAT_GOOD       2.SEAT_FULL       9.SEAT_BROKEN\n");
		printf("\n\t\tChoose a status:");
		scanf("%d",&status);
		p->data.status=status;
		if(Seat_Srv_ModifyInfo(p)==0){

			return ;
		}
		printf("\n\t\tModify success!\n"); 
		return ;
}
