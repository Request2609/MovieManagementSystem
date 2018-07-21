/*
 * Common_Persist.c
 *
 *  Created on: 2015��5��4��
 *      Author: Administrator
 */
#include "../Persistence/EntityKey_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

//����洢����ʵ���������ļ���ΪEntityKey.dat
static const char ENTITY_KEY_FILE[] = "EntityKey.dat";

typedef struct {
	char entyName[41];
	int key;
} entity_key_t;


/*���ݴ����ʵ����entName��ʵ�����count��Ϊ���count����ʵ�����һ������Ϊcount������ֵ���䣬
 * ʹ��ÿ����ʵ���ڸ������ڶ����Է��䵽 Ψһ�� ����������ֵΪ�������������Сֵ*/
int EntKey_Perst_GetNewKeys(const char entName[]){
	entity_key_t ent,temp;
	FILE*fp;
	int key=1;
	strcpy(temp.entyName,entName);
	if(access(ENTITY_KEY_FILE,0)){ 
		fp=fopen(ENTITY_KEY_FILE,"wb");
		if(fp==NULL){
			return 0;
		}
		strcpy(ent.entyName,entName);
//		printf("\n=%d=\n",key);
		ent.key=key;
//		printf("\n=%d=\n",key);
		fwrite(&ent,sizeof(entity_key_t),1,fp);
		fclose(fp);
		return key;
	}
	else{
		fp=fopen(ENTITY_KEY_FILE,"rb+");
		if(fp==NULL){
			printf("\n\t\tϵͳ����\n"); 
			return 0;
		}
		while(1){
			if(fread(&ent,sizeof(entity_key_t),1,fp)<1)break;
//			printf("%s\n",ent.entyName);	
			if(strcmp(ent.entyName,entName)==0){
				fseek(fp,-((int)sizeof(entity_key_t)),SEEK_CUR);
				ent.key++;
//				printf("\n*%d*\n",ent.key); 
			//	system("pause"); 
				key=ent.key;		
				fwrite(&ent,sizeof(entity_key_t),1,fp);
				fclose(fp);
				return key;
			} 
		}
	}
	if(key==1){
//		printf("\n*****\n");
		temp.key=key;
		fwrite(&temp,sizeof(entity_key_t),1,fp);
	}	
	
	fclose(fp);
	return key;
}
