#include "Studio_Persist.h"
#include "../Service/Studio.h"
#include "../Persistence/EntityKey_Persist.h"		////�·����������
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include<string.h>
////��Ӷ���������ʶ����
////��Ӷ���������ʶ����
//static const char STUDIO_KEY_NAME[] = "Studio";
////��Ӷ���������ʶ����
////��Ӷ���������ʶ����

int Studio_Perst_Insert(studio_t *data) {	////�·�����dataǰ���constȥ����
	assert(NULL!=data);

	////����������Ʒ���������ӵĴ���
	////����������Ʒ���������ӵĴ���
	////����������Ʒ���������ӵĴ���
	////����������Ʒ���������ӵĴ���



	FILE *fp = fopen(STUDIO_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(studio_t), 1, fp);

	fclose(fp);
	return rtn;
}

int Studio_Perst_Update(const studio_t * data) {
	assert(NULL!=data);

	FILE *fp = fopen(STUDIO_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	studio_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(studio_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(studio_t)), SEEK_CUR);
				fwrite(data, sizeof(studio_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

int Studio_Perst_DeleteByID(int ID) {

	//��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵���

	//��ԭʼ�����ļ�������
	if(rename(STUDIO_DATA_FILE, STUDIO_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(STUDIO_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(STUDIO_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", STUDIO_DATA_TEMP_FILE);
		return 0;
	}


	studio_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(studio_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(studio_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(STUDIO_DATA_TEMP_FILE);
	return found;
}

int Studio_Perst_SelectByID(int ID, studio_t *buf) {
	assert(NULL!=buf);
	FILE *fp = fopen(STUDIO_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}
////	printf("\n***\n");
	studio_t data;
	int found = 0;
//	printf("\n**\n");
	while (1) {
		if (fread(&data, sizeof(studio_t), 1, fp)<1)break;
			if (ID == data.id) {
//				printf("\n-%d-\n",data.id);
				strcpy(buf->name,data.name);
				buf->colsCount=data.colsCount;
				buf->rowsCount=data.rowsCount;
				buf->seatsCount=data.seatsCount;
				buf->id=data.id; 
//				printf("\n*****\n");
//				printf("\n*%d*\n",(*buf).colsCount);
				found = 1;
				break;
			}
		
		}
	fclose(fp);
	return found;
}/* 
int Studio_Perst_ModifySeatCount(seat_node_t*s){//���ݴ���������λId�޸��ݳ�����λ���� 
	if(access(STUDIO_DATA_FILE,0))return 0;
	FILE*fp;
	fp=fopen(STUDIO_DATA_FILE,"rb");
	if(fp==NULL){
		return 0;
	} 
	studio_node_t*h=NULL;
	h=(seat_node_t*)malloc(sizeof(seat_noder_t));
	while(1){
		if(fread(h,sizeof(seat_node_t),1,fp)<1)break;
		if(h->data.seat_id==s->data.id){
			h->data.seatsCount++;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*(int)sizeof(studio_node_t),SEEK_CUR);
			fwrite(h,sizeof(studio_node_t),1,fp);
			fsetpos(fp,&pos);
			fclose(fp);
			free(h);
			return 1;
		}
	}
	fclose(fp);
	free(h);
	return 0;
}*/ 
int Studio_Perst_SelectAll(studio_list_t list) {
	studio_node_t *newNode;
	studio_t data;
	int recCount = 0;
	assert(NULL!=list);
	List_Free(list,studio_node_t);

	FILE *fp = fopen(STUDIO_DATA_FILE, "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(studio_t), 1, fp)) {
			newNode = (studio_node_t*) malloc(sizeof(studio_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}
