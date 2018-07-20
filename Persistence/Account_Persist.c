#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"../Common/List.h"
#include"../Persistence/EntityKey_Persist.h"
#include"Account_Persist.h"
#include"../Common/passwd.h"

static char*accountfile="Account.dat";
static char*accountfile_temp="Account_temp.dat";
int Account_Perst_Insert(account_node_t*h){//添加用户信息
	FILE*fp;
	account_node_t *temp=NULL;
	temp=(account_node_t*)malloc(sizeof(account_node_t));
	temp=h->next; 
	if(access(accountfile,0)){
		fp=fopen(accountfile,"wb+");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
		}

		fwrite(temp,sizeof(account_node_t),1,fp);
		
	}

	else{
		fp=fopen(accountfile,"ab");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
		}
		while(temp!=h){
			fwrite(temp,sizeof(account_node_t),1,fp);
			temp=temp->next;
		}
	}
	fclose(fp);
	free(temp);

	return 1;
}
int Account_Perst_JudgeInfo(account_node_t *p){//验证用户信息

	if(access(accountfile,0))return 0;
	FILE*fp=fopen(accountfile,"rb");
	if(fp==NULL){
		printf("Error!\n");
		return 0;
	}	
	account_node_t*temp;
	temp=NULL;
	temp=(account_node_t*)malloc(sizeof(account_node_t));

	while(1){
		if(fread(temp,sizeof(account_node_t),1,fp)<1)break;
		if((0==(strcmp(temp->data.username,p->data.username)))&&(0==(strcmp(temp->data.password,p->data.password)))){
				free(temp);
				free(p);
				fclose(fp);
				return 1;
			}
	}
	free(temp);
	free(p);
	fclose(fp);
	return 0;
}
int Account_Perst_SearchInfo(account_node_t*p){//查找用户信息
	if(access("Account.dat",0)){

		return 0;
	}
	FILE*fp;
	fp=fopen("Account.dat","rb");
	if(fp==NULL){
		return 0;
	}

	account_node_t*temp=NULL;
	temp=(account_node_t*)malloc(sizeof(account_node_t));
	while(1){
		if(fread(temp,sizeof(account_node_t),1,fp)<1){
			break;
		}

		if((strcmp(p->data.username,temp->data.username)==0)&&(strcmp(p->data.phoneNum,temp->data.phoneNum)==0)&&p->data.type==temp->data.type){

			p->data.id=temp->data.id;
			fclose(fp);
			free(temp);
			return 1;
		}
	}
	fclose(fp);
	free(temp);
	return 0;
}
int Account_Perst_SaleLogIn(account_node_t* h){//售票员登陆（在项目中未起作用）
	if(access(accountfile,0)){
		return 0;
	}
	printf("\n\t\t===========================================================================\n");
	printf("\t\t*******************************Salesman login*******************************\n");
	FILE*fp=fopen(accountfile,"rb");
	if(fp==NULL){
		printf("\t\tError!\n");
		return 0;
	}
	account_node_t*q=NULL;
	q=(account_node_t*)malloc(sizeof(account_node_t));

	printf("\n\n\t\tInput user name:");
	scanf("%[^\n]",h->data.username);
	while('\n'!=getchar());

	while(1){
		char* ps;
		set_disp_mode(STDIN_FILENO,0);
		getpasswd(h->data.password, sizeof(h->data.password));
		ps=h->data.password;
   	while(*ps!='\n')
   			ps++;
  		*ps='\0';
		set_disp_mode(STDIN_FILENO,1);
		if(strlen(h->data.password)<6){
		printf("\n\t\tPassword is too short!\n");
		}
		else{
			break;
			}		
		}

	while(1){
		if(fread(q,sizeof(account_node_t),1,fp)<1){
			break;
		}
		if(strcmp(q->data.username,h->data.username)==0&&strcmp(q->data.password,h->data.password)==0&&q->data.type==h->data.type){
			h->data.id=q->data.id;
			strcpy(h->data.phoneNum,q->data.phoneNum);
			strcpy(h->data.username,q->data.username);
			strcpy(h->data.password,q->data.password);
			free(q);
			fclose(fp);
			return 1;
		}
	}	
	free(q);
	fclose(fp);
	printf("\n\t\tNo salesman account at present,press [Enter] to return and add......");
	while('\n'!=getchar());
	system("clear");
	return 0;
}
int Account_Perst_Add(account_node_t*h){//添加新用户
	FILE*fp;
	account_node_t* temp;
	temp=(account_node_t*)malloc(sizeof(account_node_t));
	temp=h->next;
	if(access(accountfile,0)){
		fp=fopen(accountfile,"wb+");
		if(fp==NULL){
			return 0;
		}
		while(1){
			fwrite(temp,sizeof(account_node_t),1,fp);
			temp=temp->next;
			if(temp==h)break;
		}
	}else{
		fp=fopen(accountfile,"ab");
		if(fp==NULL){
			return 0;
		}
		while(1){
			fwrite(temp,sizeof(account_node_t),1,fp);
			temp=temp->next;
			if(temp==h)break;
		}
	}
	fclose(fp);
	free(temp);

	return 1;
}
int Account_Perst_FetchAll(account_node_t* h){//将所有用户传入链表中
	account_node_t* temp;
	int count=0;
	FILE*fp;
	if(access(accountfile,0)){
		printf("\n\t\tNo user!\n"); 
		return 0;
	}
	fp=fopen(accountfile,"rb");
	while(1){


		temp=(account_node_t*)malloc(sizeof(account_node_t));
		if(fread(temp,sizeof(account_node_t),1,fp)<1)break;

		count++;
		List_AddTail(h,temp);
	}

	return count;
}
int Account_Perst_FetchAdmin(account_node_t*h){//将所有管理员传到链表上在此工程中并没有起作用
	account_node_t*temp;
	FILE*fp;

	if(access(accountfile,0))return 0;
	fp=fopen(accountfile,"rb");
	while(1){
		temp=(account_node_t*)malloc(sizeof(account_node_t));
		if(fread(temp,sizeof(account_node_t),1,fp)<1)break;
		if(temp->data.type==9){

			List_AddTail(h,temp);
		}
	}
	if(h->next==h)return 0;
	return 1;
} 
int Account_Perst_Delete(){//删除用户
	int id;
	int found=0;
	FILE *fp,*fp1;
	account_node_t *temp;

	temp=(account_node_t*)malloc(sizeof(account_node_t));
	printf("\n\t\tInput delete ID:");
	scanf("%d",&id);
	while('\n'!=getchar());
	if(access(accountfile,0)){

		return 0;
	}
	fp=fopen(accountfile,"rb");
	if(fp==NULL){
		printf("\n\t\tError!\n");
		return 0;
	}
	fp1=fopen(accountfile_temp,"wb");
	if(fp==NULL){
		return 0;
	}
	while(1){
		if(fread(temp,sizeof(account_node_t),1,fp)<1)break;
		if(temp->data.id==id){
			found++;
		}
		else{
			fwrite(temp,sizeof(account_node_t),1,fp1);
		}
	}
	
	fclose(fp);
	fclose(fp1);
	remove(accountfile);
	free(temp);
	if(found==0){
		return 0;
	}
	if(rename(accountfile_temp,accountfile)!=0){
		printf("%d\n",rename(accountfile_temp,accountfile));
		return 0;
	}
	return 1;
}

int Account_Perst_Modify(account_node_t  *temp){//修改用户信息
	int found=0;
	if(access(accountfile,0)){
		return found;
	}
	FILE*fp=fopen(accountfile,"rb+");
	if(fp==NULL){
		return found;
	}
	account_node_t *p;
	p=(account_node_t*)malloc(sizeof(account_node_t));
	while(1){
		if(fread(p,sizeof(account_node_t),1,fp)<1)  break;
		if(strcmp(p->data.username,temp->data.username)==0&&strcmp(temp->data.phoneNum,p->data.phoneNum)==0&&p->data.type==temp->data.type){
			temp->data.id=p->data.id;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,-(int)(sizeof(account_node_t)),SEEK_CUR);	
			fwrite(temp,sizeof(account_node_t),1,fp);
			fsetpos(fp,&pos);
			found=1;
			break;
		}
	}
	free(temp);
	free(p);
	fclose(fp);
	return found;

}


