#include"Play_UI.h"
#include"../Service/Play.h" 
#include"../Common/List.h"
#include"../View/Schedule_UI.h"
#include"../Persistence/Play_Persist.h"
#include"Account_UI.h"
static const int pagesize=5;
void Play_UI_Add(){
	Play_Srv_Add();
}
void Play_UI_MgtEntry(){
	char ch;
	account_node_t* p;
	p=(account_node_t*)malloc(sizeof(account_node_t));
	p->data.type=9;
	while(1){
		if(Account_Srv_UserLogIn(p)==0){
			printf("\n\t\t  [c]Continue      [F]Forgot password     [E]Exit\n");


			printf("\n\t\tInput choice:");

			ch=getchar();
			while('\n'!=getchar());



			if(ch=='e'||ch=='E'){

				return;
			}
			else if(ch=='F'||ch=='f'){
				Account_UI_SearchPass();
			}
			else{
				continue;
			}
			}
			else{
				break;
			}
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
	do{	
		//printf("%d\n",paging.totalRecords);
		printf("\n\t\t==========================================================================================================");

		printf("\n\t\t***********************************************Movie_list*************************************************\n");

		printf("\t\t|*%-5s%-18s     %-13s   %-10s      %-30s%-10s  \n","ID","Movie_name","Movie_area","Movie_time","Start_date->End date","Ticket_price");

		Paging_ViewPage_ForEach(h,paging,play_node_t,temp,i){
			printf("\n\n\t\t%-5d%-18s       %-13s   %-10d        %d.%d.%d->%d.%d.%d   %15d\n",temp->data.id,
			temp->data.name,temp->data.area,temp->data.duration,temp->data.start_date.year,
			temp->data.start_date.month,temp->data.start_date.day,temp->data.end_date.year,
			temp->data.end_date.month,temp->data.end_date.day,temp->data.price);
			}

		printf("\t\t--------All movie:%2d--------------------------------------------------------Page %2d/%2d-------- ---\n",paging.totalRecords,Paging_CurPage(paging),Paging_TotalPages(paging));
		printf("\n\t\t|(N)Next page|(P)Previous page|(A)Add movie|(M)Modify movie|(D)Delete Movie|(S)Set schedule_plan|(E)Exit|\n");

		printf("\n\t\t********************************************************************************************************");
		printf("\n\t\t========================================================================================================");
		printf("\n\t\tInput choice:");
			ch=getchar();

			switch(ch){
				case 'N':
				case 'n':
					system("clear");
					if(!Paging_IsLastPage(paging))
					Paging_Locate_OffsetPage(h, paging, 1, play_node_t);
					break;
				case 'p':
				case 'P':	
					system("clear");
					if(!Paging_IsFirstPage(paging))
					Paging_Locate_OffsetPage(h, paging, -1, play_node_t);
					break;
				case 'A':
				case 'a':
					system("clear");
					Play_UI_Add();
					system("clear");
//					printf("\n\t\t");
//					system("clean");
//					system("pause");
					break;
				case 'M':
				case 'm':
					system("clear");
					Play_Srv_Modify();
//					printf("\n\t\t");
					system("clear");
					break;
				case 'D':
				case 'd':
					system("clear");
					Play_Srv_DeleteByID();
//					printf("\n\t\t");
//					system("clean");
					break;
				case 'S':
				case 's':

					system("clear");
					Schedule_UI_MgtEntry();
					break;
				default:
					system("clear");
					break; 
				}
			
		}while(ch!='e'&&ch!='E');

	}
 

