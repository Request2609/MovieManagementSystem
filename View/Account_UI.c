#include<stdlib.h>
#include<string.h> 
#include"Account_UI.h"
#include"../Common/List.h"
#include"../Service/Account.h"
#include"../Persistence/Account_Persist.h"
static const int pagesize=5;
void Account_UI_MgtEntry(account_node_t* p){//用户管理界面
	p->data.type=9;
	if(Account_Srv_UserLogIn(p)==0){
		printf("\n\t\tLog failed!\n");
		return ;
	}
	char choice;
	int i;
	account_node_t* temp, *h;
	Pagination_t paging;
	paging.offset=0;
	paging.pageSize=pagesize;
	List_Init(h,account_node_t);
	paging.totalRecords=Account_Perst_FetchAll(h);
	Paging_Locate_FirstPage(h, paging); 
	do{
		system("clear");
		printf("\n\t\t====================================================================================================");
		printf("\n\t\t|***************************************User management********************************************|\n");
		printf("\n\t\t====================================================================================================");
		printf("\n\n\t\t     %-25s%-25s%-25s%-25s\n","User_ID","User_Name","User_phone_number","User_type");
		Paging_ViewPage_ForEach(h, paging, account_node_t, temp, i){
			printf("\n\t\t      %-25d%-25s%-25s",temp->data.id,temp->data.username,temp->data.phoneNum);
			if(temp->data.type==0)printf("%-25s\n","Other_user");
			else if(temp->data.type==1)printf("%-25s\n","Salesman");
			else if(temp->data.type==2)printf("%-25s\n","Management");
			else printf("%-25s\n","Adminastrater");
		}
		printf("\n\t\t|-----All member:%2d--------------------------------------------No.%2d  All page:%2d------------------|\n",paging.totalRecords,
					Paging_CurPage(paging),Paging_TotalPages(paging));		
		

		printf("\n\t\t=====================================================================================================");
		printf("\n\n\t\t	      	        [A]Add user                     [D]Delete user       		        \n");
		printf("\t\t                                                          					   		  \n");
		printf("\t\t 			[F]Modify infomation       	[S]Find Password         	   		  \n");
		printf("\t\t                                                                               		   		  \n");
		printf("\t\t 			[P]Previous page           	[N]Next page          	   		  \n");
		printf("\t\t                                                          	                  	   		  \n");
		printf("\t\t 			[E]Exit                                                    		  \n");
		printf("\t\t                                                          					   		  \n");
		printf("\t\t|*****************************************************************************************************|");
		printf("\n\t\tInput you choice:");
		choice=getchar();
		while('\n'!=getchar());
		switch(choice){
			case 'p':
			case 'P':
				if(!(Paging_IsFirstPage(paging)))
				Paging_Locate_OffsetPage(h, paging, -1, account_node_t);
				break;
			case 'n':
			case 'N':
				if(!(Paging_IsLastPage(paging)))
				Paging_Locate_OffsetPage(h,paging,1,account_node_t); 
				break;
			case 'd':
			case 'D':
				system("clear");
				Account_UI_Delete();
				break;
			case 'a':
			case 'A':
				system("clear");
				Account_UI_Add();
				break;
			case 'F':
			case 'f':
				system("clear");
				Account_UI_Modify(); 
				break;
			case 'S':
			case 's':
				system("clear");
				Account_UI_SearchPass();
				break;
		}	
	} while(choice!='E'&&choice!='e');
	
}
int Account_UI_LogIn(){ //用户登录界面
	if(Account_Srv_LogIn()==0){

		return 0;
	}		
	printf("\n\t\tLog succeed!\n");
	printf("\n\t\tPress [Enter] key to return......");
	while('\n'!=getchar());
	return 1;
} 
void Account_UI_Add(){
	printf("\n\t\t===================================================================================================");
	printf("\n\t\t|******************************************Add user***********************************************|");
	printf("\n\t\t===================================================================================================");
	if(Account_Srv_Add()==0){
		printf("\n\t\tAdd failed\n");
		return;
	}

}
void Account_UI_Delete(){
	printf("\n\t\t======================================================================================================");
	printf("\n\t\t|******************************************Delete user***********************************************|");
	printf("\n\t\t======================================================================================================");
	if(Account_Srv_Delete()==0){
		printf("\n\t\tDelete failed!\n");
		printf("\n\t\tPress [Enter] to return ......");
		while('\n'!=getchar());
		return ;
	}
	printf("\n\t\tDelete success!\n");
	printf("\n\t\tPress [Enter] to return ......");
	while('\n'!=getchar());
	return ;
}
void Account_UI_Modify(){
	printf("\n\t\t============================================================================================================");
	printf("\n\t\t|******************************************Modify infomation***********************************************|");
	printf("\n\t\t============================================================================================================");
	if(Account_Srv_Modify()==0){
		printf("\n\t\tModify failed!\n");
		return ;
	}	
	printf("\n\t\tModify success!\n");
	return ;
}
void Account_UI_SearchPass(){//验证信息界面
	account_node_t*p=NULL;
	p=(account_node_t*)malloc(sizeof(account_node_t));
	printf("\t\tInput user name:");
	scanf("%[^\n]",p->data.username);
	while('\n'!=getchar());
	printf("\n\t\tInput phone number:");
	scanf("%[^\n]",p->data.phoneNum);
	while('\n'!=getchar());
	int ch;
	printf("\n\t\t0.others    1.Salesman     2.Manager   9.Administrater\n");
	printf("\n\t\tPlease input user type:");
	scanf("%d",&ch);
	while('\n'!=getchar());
	p->data.type=ch;
	if(Account_Srv_SearchPass(p)==0){
		printf("\n\t\tNo the user!\n");
		return ;
	} 
	printf("\n\t\tModify success!");
	printf("\n\n\t\tPress [Enter] to return......");
	getchar();
}
