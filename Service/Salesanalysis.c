#include"Salesanalysis.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"../Common/common.h"
#include"../Persistence/Sale_Perst.h"
int Salesanalysis_Srv_AddAllMoney(salesanalysis_node_t*h){
	if(access("Sale.dat",0)){
		return 0;
	}
	user_date_t t1,t2,t3;
	FILE*fp;
	fp=fopen("Sale.dat","rb");
	if(fp==NULL){
		return 0;
	}
	t1.year=h->data.start_date.year;
	t1.month=h->data.start_date.month;
	t1.day=h->data.start_date.day;
	t3.year=h->data.end_date.year;
	t3.month=h->data.end_date.month;
	t3.day=h->data.end_date.day;
	sale_node_t*temp=NULL;
	int money=0;
	temp=(sale_node_t*)malloc(sizeof(sale_node_t));
	while(1){
		if(fread(temp,sizeof(sale_node_t),1,fp)<1){
			break;
		}
		t2.year=temp->data.date.year;
		t2.month=temp->data.date.month;
		t2.day=temp->data.date.day;
		if(DateCmp(t1,t2)<=0&&DateCmp(t2,t3)<=0){
			if(temp->data.type==-1)(money=money+temp->data.value);
			else(money=money-temp->data.value);
		}
	}
	fclose(fp);
	free(temp);
	if(money==0){
		printf("\n\t\tNo sale money ,the trade is cool between this time,press [Enter] to return......");
		while('\n'!=getchar());
		return 0;
	}
	return money;
}
