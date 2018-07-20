#include "../View/Studio_UI.h"
#include "../Common/List.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include"Seat_UI.h"
#include <stdio.h>
#include"Account_UI.h"
#include"../Persistence/EntityKey_Persist.h"
static const int STUDIO_PAGE_SIZE = 5;
static char *KeyName="Studio";
void Studio_UI_MgtEntry(account_node_t *temp) {//演出厅管理界面
	if(Account_Srv_UserLogIn(temp)==0){
			printf("\n\t\tLog failed!press [Enter] to return ......");
			while('\n'!=getchar());
			return ;
		}
	system("clear");

	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\t\t=================================================================================================\n");
		printf("\t\t***************************************Studio infomation*******************************************\n");
		printf("\t\t                                                                                              \n");
		printf("\t\t%-20s  %-20s  %-20s  %-20s  %-20s\n", "ID", "Name", "Rows","Column", "Seats_count                               ");
		printf("\t\t---------------------------------------------------------------------------------------------------- \n");

		Paging_ViewPage_ForEach(head, paging, studio_node_t, pos, i){
			printf("\n\t\t%-20d  %-20s  %-20d  %-20d  %-20d                                         \n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
		}

		printf("\n\t\t-----------All number:%2d -------------------------------------------- page %2d/%2d ----------------\n",
				paging.totalRecords, Paging_CurPage(paging),
				Paging_TotalPages(paging));
		
		printf("\t\t[P]Previous page|[N]Next page|[A]Add studio|[D]delete studio|[U]Modify studio|[S]Seats info|[E]Exit \n");
		printf("\t\t====================================================================================================\n");
		printf("\n\t\tInput you choice:");

		scanf("%c", &choice);
		while('\n'!=getchar());
		switch (choice) {
			case 'a':
			case 'A':
				if (Studio_UI_Add())
				{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
				}
			break;
			case 'd':
			case 'D':
				printf("\n\t\tInput studio ID:");
				scanf("%d", &id);
			if (Studio_UI_Delete(id)) {
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				}
				system("clear");
				break;
		case 'u':
		case 'U':
			printf("\t\tInput studio ID:");
			scanf("%d", &id);
			while('\n'!=getchar());
			if (Studio_UI_Modify(id)) {
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			system("clear");
			break;
		case 's':
		case 'S':
			Seat_UI_MgtEntry();
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (!Paging_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			system("clear");
			break;
		case 'n':
		case 'N':
			if (!Paging_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			system("clear");
			break;
		}
	} while (choice != 'e' && choice != 'E');

	}

int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;
	seat_node_t* h=NULL;
	List_Init(h,seat_node_t);
	int key;
	do {

		printf("\n\t\t===============================================================================\n");
		printf("\t\t***********************************  Studio Add *********************************\n");
		printf("\t\t=================================================================================\n");
		printf("\t\tInput studio name:");
		scanf("%s",rec.name);
		while('\n'!=getchar());
		key=EntKey_Perst_GetNewKeys(KeyName);
		if(key<0){
			printf("\n\t\tGetkey failed!\n");
			return 0;
		}
		rec.id=key;
		printf("\n\t\tInput studio rows number:");
		scanf("%d", &(rec.rowsCount));
		printf("\n\t\tInput studio column number:");
		scanf("%d", &(rec.colsCount));
		rec.seatsCount = 0;
		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\t\tAdd studio success!\n");
		} else
			printf("\t\tAdd studio failed!\n");
		printf("\n\t\t======================\n");
		printf("\t\t[A]Continue        [E]Exit\n");
		printf("\t\t=======================\n");
		printf("\n\t\tInout you choice:");
		while('\n'!=getchar());
		scanf("%c", &choice);
	} while ('e' != choice &&'E' != choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {//演出厅修改界面
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t\tStudio not exist!\n");
		return 0;
	}

	printf("\n\t\t===================================================================================\n");
	printf("\t\t************************************Modify Information*******************************\n");
	printf("\t\t=====================================================================================\n");
	printf("\t\tStudio_ID:%d\n", rec.id);
	printf("\t\tStudio_name[%s]:", rec.name);
	fflush(stdin);
	fgets(rec.name,40,stdin);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		do {
			printf("\t\tRows number >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("\t\tColumns number >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		} while (newrow < rec.rowsCount || newcolumn < rec.colsCount);
		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	} else {
		printf("\t\tSet rowsNumber:\n");
		scanf("%d", &rec.rowsCount);
		printf("\t\tSet columnsNumber:\n");
		scanf("%d", &rec.colsCount);
		rec.seatsCount = 0;
	}


	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf("\n\t\tModify success!\n");
	} else
		printf("\n\t\tModify failed!\n");
	printf("\n\t\tPress[Enter] key return.....\n");

	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {//演出厅删除界面

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		if (Seat_Srv_DeleteAllByRoomID(id))
			printf("\n\t\tDelete success!\n");
		rtn = 1;
	} else {
		printf("\n\t\tSeats not exist!\n");
	}
	getchar();
	return rtn;
}

