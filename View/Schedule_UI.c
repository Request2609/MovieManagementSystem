#include"Schedule_UI.h"
#include"../Common/List.h"
#include"../Service/Play.h"
#include"Ticket_UI.h"
#include"Play_UI.h"
#include"../Persistence/Schedule_Persist.h"
static const int pageSize=5;
void Schedule_UI_MgtEntry(){//演出计划管理界面
	char choice;
	int i;
	schedule_node_t*h;
	List_Init(h,schedule_node_t);
	Pagination_t paging;
	paging.offset=0;
	paging.totalRecords=Schedule_Perst_FetchAll(h);
	paging.pageSize=pageSize;
	schedule_node_t*temp=NULL;
	Paging_Locate_FirstPage(h,paging);
	do{
		system("clear");
		printf("\n\t\t====================================================================================================================\n");
		printf("\n\t\t---------------------------------------------------Schedule_plan----------------------------------------------------\n");
		printf("\t\t                                                                                                      \n");
		printf("\t\t%-15s%-20s%-20s%-18s%-20s%-15s\n","Schedule_id","Movie_name","Studio_id","Start_date","Start_time","Seats_Count");
		Paging_ViewPage_ForEach(h, paging, schedule_node_t,temp, i){
		printf("\n\t\t%-15d%-20d%-20d %d-%d-%d         %d:%d:%d   %15d                   \n",temp->data.id,temp->data.play_id,
		temp->data.studio_id,temp->data.date.year,temp->data.date.month,
		temp->data.date.day,temp->data.time.hour,temp->data.time.minute,
		temp->data.time.second,temp->data.seat_count);
		}
		printf("\t\t----All schedule %2d--------------------------------------------------------------No.%2d page  All page%2d------------\n",paging.totalRecords,Paging_CurPage(paging),Paging_TotalPages(paging));
		printf("\n\t\t====================================================================================================================\n");
		printf("\t\t|***********************************************Schedule_plan management**********************************************|\n");
		printf("\n");
		printf("\t\t                          [P]Next page                                         [P]Previous page");
		printf("\n");
		printf("\n\t\t                          [T]Add ticket                                        [A]Add schedule plan");
		printf("\n");
		printf("\n\t\t                          [M]Modify schedule                                   [D]Delete schedule ");
		printf("\n");
		printf("\n\t\t                          [E]Exit");
		printf("\n\t\t");
		printf("\n\t\t====================================================================================================================");
		while('\n'!=getchar());
		printf("\n\t\tInput you choice:");
		scanf("%c",&choice);
		switch(choice){
			case 'p':
			case 'P':
				if(!Paging_IsFirstPage(paging))
				Paging_Locate_OffsetPage(h, paging, -1, schedule_node_t);
				break;
			case 'N':
			case 'n':
				if(!Paging_IsLastPage(paging))
				Paging_Locate_OffsetPage(h, paging, 1, schedule_node_t);
				break;
			case 'T':
			case 't':
				Ticket_UI_MgtEntry();
				break;
			case 'A':
			case 'a':
				Schedule_Srv_Add(); 
				break;
			case 'D':
			case 'd':
				Schedule_UI_Delete();
				break;
			case 'M':
			case 'm':
				Schedule_UI_Modify();
				break; 
			default:
				break; 
		}
	}while(choice!='e'&&choice!='E');
	
}
void Schedule_UI_Add(){//演出计划添加界面
	Schedule_Srv_Add();
}
void Schedule_UI_Delete(){//演出计划删除界面
	Schedule_Srv_DeleteByID();
}
void Schedule_UI_Modify(){//演出计划修改界面
	Schedule_Srv_Modify();
}
int Schedule_UI_SelectByPlayName(schedule_node_t*h){//根据剧目名称查询演出计划界面
	char name[50]; 
	if(Schedule_Srv_FetchByPlayName(name,h)==0)return 0;
	return Schedule_Perst_SelectByPlayName(name,h);
}
