#include"Salesanalysis.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"../Persistence/Sale_Perst.h"
int Salesanalysis_Srv_AddAllMoney(salesanalysis_node_t*h){
	if(access("Sale.dat",0)){
		return 0;
	}		
	FILE*fp;
	fp=fopen("Sale.dat","rb");
	if(fp==NULL){
		return 0;
	}
	sale_node_t*temp=NULL;
	int money=0;
	temp=(sale_node_t*)malloc(sizeof(sale_node_t));
	while(1){
		if(fread(temp,sizeof(sale_node_t),1,fp)<1){
			break;
		}
		if(h->data.start_date.year==temp->data.date.year&&temp->data.date.year==h->data.end_date.year){
//			if(h->data.start_date.year<=temp->data.date.year&&temp->data.date.year<=h->data.end_date.year){
				if(h->data.start_date.month<=temp->data.date.month&&temp->data.date.month<=h->data.end_date.month){//������ȣ��Ƚ�����
					if(h->data.start_date.day<=temp->data.date.day&&temp->data.date.day<=h->data.end_date.day){
						temp->data.type=1?(money=money+temp->data.value):(money=money-temp->data.value);
						printf("\n\t\t*******\n");

				}
			}
		}
//		else{
//			if(h->data.start_date.year<=temp->data.date.year&&temp->data.date.year<=h->data.end_date.year){
//				for()
//			}
//		}

//		}
	}
	fclose(fp);
	free(temp);
	if(money==0){

		return 0;
	}
	return money;
}
