#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include"../View/Play_UI.h"
typedef enum{
	USR_ANOMY= 0,
	USR_CLERK=1,
	USR_MANG=2,
	USR_ADMIN=9
}account_type_t;
typedef struct{
	int id;
	char phoneNum[35]; 
	account_type_t type;
	char username[30];
	char password[30];
}account_t;
typedef struct account_node{
	account_t data;
	struct account_node *next;
	struct account_node *prev;
}account_node_t,*account_list_t;
int Account_Srv_Add();
int Account_Srv_LogIn();
void Account_Srv_FirstLogIn();
int Account_Srv_UserLogIn1(account_node_t* temp);
int Account_Srv_Delete();
int Account_Srv_UserLogIn(account_node_t* temp);
int Account_Srv_Modify();
int Account_Srv_SearchPass(account_node_t*p);
//void Account_Srv_Delete(); 
#endif

