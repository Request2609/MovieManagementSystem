#include"Salesanalysis_Persist.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../Common/List.h"
int Salesanalysis_Perst_SelectAllSale(sale_node_t*h){//将所有订单信息存到链表
	if(access("Sale.dat",0)){
		printf("\t\t Not sold ticket!");
		return 0;
	}
	FILE*fp;
	fp=fopen("Sale.dat","rb");
	if(fp==NULL){
		return 0;
	}
	int count=0;
	sale_node_t*temp=NULL;
	while(1){
		temp=(sale_node_t*)malloc(sizeof(sale_node_t));
		if(fread(temp,sizeof(sale_node_t),1,fp)<1){
			free(temp);
			break;
		} 
		count++;
		List_AddTail(h,temp);
	}
	fclose(fp);
	
	return count;
}
