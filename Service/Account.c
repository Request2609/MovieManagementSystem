#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"Account.h"
#include"../Common/List.h"
#include"../Persistence/EntityKey_Persist.h"
#include"../Persistence/Account_Persist.h"
#include"../Common/passwd.h"
static const char*accountfile="Account.dat";
static const char *keyname="Account";
void Account_Srv_FirstLogIn(){
	if(access(accountfile,0)){
		printf("\n\t\t======================================================================================");
		printf("\n\t\t*****************************Welcome to use the system********************************");
		printf("\n\n\n\t\tYou are the first time to come in this system!Please apply a account number!\n");
		account_node_t*p,*h;
		List_Init(h,account_node_t);
		p=NULL; 

		p=(account_node_t*)malloc(sizeof(account_node_t));
		p->data.type=9;
		p->data.id=EntKey_Perst_GetNewKeys(keyname);
		while(1){
			printf("\n\n\t\tPlease input you phone number:");

			scanf("%[^\n]",p->data.phoneNum);
			if(strlen(p->data.phoneNum)==11){
				break;
			}

			printf("\n\t\tPlease input correct phone number!\n");
		}
		while('\n'!=getchar());

		printf("\n\t\tPlease input user name:");


		scanf("%[^\n]",p->data.username);
		while(strlen(p->data.username)<2){
			while('\n'!=getchar());
			printf("\n\t\tUser name is too short!");
			printf("\n");
			printf("\t\tPlease Input again:");

			scanf("%[^\n]",p->data.username);
		}
		while('\n'!=getchar());
		char* ps;
		set_disp_mode(STDIN_FILENO,0); 
		getpasswd(p->data.password, sizeof(p->data.password));
		ps=p->data.password;
       	while(*ps!='\n')
         		ps++;
      	*ps='\0';
		set_disp_mode(STDIN_FILENO,1); 
//		printf("\n%s\n",p->data.password);
		List_AddTail(h,p);
		if(Account_Perst_Insert(h)==0){
			printf("\n\t\tAdd administritor failed!\n");
			remove("account.dat");
			return;
		}
		printf("\n\t\tCongratulation!You are the first [adminastrater] in this system!\n");
		return ;
		}else{
			return;
		}
}
int Account_Srv_SearchPass(account_node_t*p){
	if(Account_Perst_SearchInfo(p)==0){

		return 0;
	}
	printf("\n\t\tVirified succeed!\n");
	printf("\n\t\tPress [Enter] to return.....");
	while('\n'!=getchar());
	printf("\n\t\tPlease input new password:");
	char* ps;
	set_disp_mode(STDIN_FILENO,0);
	getpasswd(p->data.password, sizeof(p->data.password));
	ps=p->data.password;
   	while(*ps!='\n')
     		ps++;
  	*ps='\0';
	set_disp_mode(STDIN_FILENO,1);
	if(Account_Perst_Modify(p)==0){
		return 0;
	} 
	return 1;
}
int  Account_Srv_LogIn(){

		account_node_t *p=NULL;
		p=(account_node_t*)malloc(sizeof(account_node_t)); 
		printf("\n\t\t=====================================================================================");
		printf("\n\n\t\tInput user number:");

		scanf("%[^\n]",p->data.username);
		while('\n'!=getchar());
		while(1){
				char* ps;
				set_disp_mode(STDIN_FILENO,0);
				getpasswd(p->data.password, sizeof(p->data.password));
				ps=p->data.password;
	       	while(*ps!='\n')
	         		ps++;
	      	*ps='\0';
				set_disp_mode(STDIN_FILENO,1);
			if(strlen(p->data.password)<6){
				printf("\n\t\tThe password is too short!\n");
				}
		else{
			break;
		}		
		}

		if(Account_Perst_JudgeInfo(p)==0){
			printf("\n\t\tLog Fail!\n"); 
			return 0;
		}
		return 1;
}
int Account_Srv_Add(){
	account_node_t *h,*p,*testHead,*temp;
	char choice;
//	char choices;
	List_Init(testHead,account_node_t);
	List_Init(h,account_node_t);
	p=(account_node_t*)malloc(sizeof(account_node_t));
	while(1){
//		printf("\n\t\t");
		printf("\n\t\tInput user username:");
		scanf("%[^\n]",p->data.username);
		while('\n'!=getchar());
		while(strlen(p->data.username)<2){
			printf("\n\t\tUser name is too short,try again!");
			printf("\n");
			printf("\n\t\tInput user name:\n");
			scanf("%[^\n]",p->data.username);
			while('\n'!=getchar());
		}
		if(Account_Perst_FetchAll(testHead)){

			temp=testHead->next;
			while(temp!=testHead){
				if(strcmp(temp->data.username,p->data.username)==0){
					printf("\n\n\t\tThis user has exist!");
					printf("\n\n\t\tPress [Enter] to return.....");
					while('\n'!=getchar());
					return 0;
				}
				temp=temp->next;
			}
		}
		printf("\n\n\t\t   User_Type:[M]Manager        [A]Administrater        [S]Salesman        [O]Other user\n");
		printf("\n\n\t\tInput user type:");
		choice=getchar();
		while('\n'!=getchar());
		if(choice=='o'||choice=='O')p->data.type=USR_ANOMY;
		else if(choice=='M'||choice=='m')p->data.type=USR_MANG;
		else if(choice=='s'||choice=='S')p->data.type=USR_CLERK;
		else if(choice=='A'||choice=='a')p->data.type=USR_ADMIN;
		else {
			printf("\n\t\tChoice is not exsist!");
			return 0;
		} 
		p->data.id=EntKey_Perst_GetNewKeys(keyname); 
		while(1){
			printf("\n\t\tPlease input user phone number:");

			scanf("%[^\n]",p->data.phoneNum);
			while('\n'!=getchar());
			if(strlen(p->data.phoneNum)==11){
			break;
			}

			printf("\n\t\tPlease input correct number!\n");
		}

		while(1){

			char* ps;
			set_disp_mode(STDIN_FILENO,0);
			getpasswd(p->data.password, sizeof(p->data.password));
			ps=p->data.password;
	       	while(*ps!='\n')
	         		ps++;
	      	*ps='\0';
			set_disp_mode(STDIN_FILENO,1);
			if(strlen(p->data.password)<6){
				printf("\n\t\tThe password is too short!\n");
				}
			else{
				break;
			}
				}		
		List_AddTail(h,p); 
		printf("\n\t\t[E]Exit       [C]Continue\n");
		printf("\n\n\t\tInput you choice:");
		choice=getchar();
		while('\n'!=getchar());
		if(choice=='e'||choice=='E')break;
	}
	if(Account_Perst_Add(h)==0){
		return 0;
	} 
	printf("\n\t\tAdd  user successfully!Press [Enter] to return......");
	while('\n'!=getchar());

	return 1;
}
int Account_Srv_Delete(){
	if(Account_Perst_Delete()==0){
		return 0;
	}
	return 1;
}
int Account_Srv_UserLogIn1(account_node_t* temp){

	printf("\n\t\t============================================================================================");
	printf("\n\t\t**************************************User log in*******************************************");
	printf("\n\t\t============================================================================================");

	account_node_t* h;
	List_Init(h,account_node_t);
	if(Account_Perst_FetchAll(h)==0){
		printf("\n\t\tNo user,press [Enter] to return.....");
		while('\n'!=getchar());
		return 0;
	}
	int ch;
	printf("\n\t\t============================================================================================");
	printf("\n\t\t\t0.Others       1.Salesman       2.Manager      9.Administrater");
	printf("\n\t\t============================================================================================");
	printf("\n\n\t\tChoose user type:");
	scanf("%d",&ch);
	while('\n'!=getchar());
	temp->data.type=ch;
	printf("\n\t\tInput user number:");
	scanf("%[^\n]",temp->data.username);
	while('\n'!=getchar());
	while(1){

		char* ps;
		set_disp_mode(STDIN_FILENO,0);
		getpasswd(temp->data.password, sizeof(temp->data.password));
		ps=temp->data.password;
       while(*ps!='\n')
         	ps++;
      *ps='\0';
		set_disp_mode(STDIN_FILENO,1);
		if(strlen(temp->data.password)<6){
			printf("\n\t\tThe password is too short!\n");
		}
		else{
			break;
			}
		}
	account_node_t* p;
		p=h->next;

		while(p!=h){
			if(strcmp(p->data.username,temp->data.username)==0&&strcmp(p->data.password,temp->data.password)==0&&(temp->data.type==p->data.type)){
				temp->data.id=p->data.id;
				strcpy(temp->data.phoneNum,p->data.phoneNum);
				return 1;
			}
			p=p->next;
		}
		free(temp);
		printf("\n\t\tLog fail!");
		while('\n'!=getchar());
		system("clear");
		return 0;
	}
int Account_Srv_UserLogIn(account_node_t* temp){

	printf("\n\t\t============================================================================================");
	printf("\n\t\t**************************************User log in*******************************************");
	printf("\n\t\t============================================================================================");

	account_node_t* h;
	List_Init(h,account_node_t);
	if(Account_Perst_FetchAll(h)==0){
		printf("\n\t\tNo user,press [Enter] to return.....");
		while('\n'!=getchar());
		return 0;
	}
//	int ch;
//	printf("\n\t\t===============================================================================");
//	printf("\n\t\t\t0.Others       1.Salesman       2.Manager      9.Administrater");
//	printf("\n\t\t===============================================================================");
//	printf("\n\n\t\tChoose user type:")
//	scanf("%d",&ch);
//	while('\n'!=getchar());
//	temp->data.type=ch;
	printf("\n\t\tInput user number:");
	scanf("%[^\n]",temp->data.username);
	while('\n'!=getchar());
	while(1){

		char* ps;
		set_disp_mode(STDIN_FILENO,0);
		getpasswd(temp->data.password, sizeof(temp->data.password));
		ps=temp->data.password;
       while(*ps!='\n')
         	ps++;
      *ps='\0';
		set_disp_mode(STDIN_FILENO,1);
		if(strlen(temp->data.password)<6){
			printf("\n\t\tThe password is too short!\n");
		}
		else{
			break;
			}		
		}
/*	USR_ANOMY= 0,
	USR_CLERK=1,
	USR_MANG=2,
	USR_ADMIN=9
 * */
//	printf("*%s*",temp->data.password);
	account_node_t* p;
	p=h->next;

	while(p!=h){
		if(strcmp(p->data.username,temp->data.username)==0&&strcmp(p->data.password,temp->data.password)==0&&(temp->data.type==p->data.type)){
			temp->data.id=p->data.id;
			strcpy(temp->data.phoneNum,p->data.phoneNum);
			return 1;
		} 
		p=p->next; 
	}
	free(temp);
	printf("\n\t\tLog fail!");
	while('\n'!=getchar());
	system("clear");
	return 0;
}
int Account_Srv_Modify(){
	account_node_t *p,*h,*temp;
	int s,found=0;
	List_Init(h,account_node_t); 
	temp=(account_node_t*)malloc(sizeof(account_node_t));

	printf("\t\tInput user number:");
	scanf("%[^\n]",temp->data.username);
	while('\n'!=getchar());
	if(Account_Perst_FetchAll(h)==0){
		return 0;
	}
	p=h->next;
	while(p!=h){
		if(strcmp(p->data.username,temp->data.username)==0){
			found=1;
			break;
		}
		p=p->next;
	}
	if(!found){
		printf("\n\t\tUser is not exist!\n");
		return 0;
	}

	printf("\n\t\tInput phone number:");
	scanf("%[^\n]",p->data.phoneNum);
	while('\n'!=getchar());

	while(1){
		char* ps;
		set_disp_mode(STDIN_FILENO,0);
		getpasswd(p->data.password, sizeof(p->data.password));
		ps=p->data.password;
   	while(*ps!='\n')
     		ps++;
  		*ps='\0';
  		set_disp_mode(STDIN_FILENO,1);
		if(strlen(temp->data.password)<6){
			printf("\n\t\tThe password is too short!\n");
		}
		else{
			break;
			}		
		}
	printf("\n\t\t 1.Adminastrater   2.Salesman   3.Manager   4.Others\n");
	printf("\n\t\tChoose the new type:");
	scanf("%d",&s);
	while('\n'!=getchar());
	if(s==1)temp->data.type=USR_ADMIN;
	else if(s==2)temp->data.type=USR_CLERK;
	else if(s==3)temp->data.type=USR_MANG;
	else temp->data.type=USR_ANOMY;
	if(Account_Perst_Modify(temp)==0){
		return 0;
	}
	return 1;	
}
