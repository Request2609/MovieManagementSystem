#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"Seat_Persist.h"
#include"../Service/Seat.h"
#include"../Common/List.h"
static const char *seatfile="Seat.dat";
//static const char *seatfile_temp="seat_temp.dat";
int Seat_Perst_Delete(seat_node_t* p){
	seat_node_t* temp=NULL;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	if(access(seatfile,0)){
		return 0;
	}
	FILE*fp=fopen(seatfile,"rb+");
	if(fp==NULL){
		return 0;
	}	
//	FILE*fp1=fopen(seatfile,"wb");
//	if(fp==NULL){
//		return 0;
//	}
	p->data.status=SEAT_NONE;
//	if(p->data.status=SEAT_NONE)printf("\n*****\n");
	int flag=0;
	while(1){
		if(fread(temp,sizeof(seat_node_t),1,fp)<1)break;
//		printf("%d  %d  %d\n",temp->data.roomID,temp->data.row,temp->data.column);
		if((temp->data.roomID==p->data.roomID)&&(temp->data.row==p->data.row)&&(temp->data.column==p->data.column)){
			fpos_t pos;
			fgetpos(fp,&pos);
//			if(p->data.status==SEAT_NONE)printf("��λ��\n");
			fseek(fp,(-1)*(int)(sizeof(seat_node_t)),SEEK_CUR);
			flag=1;
			p->data.id=temp->data.id;
			fwrite(p,sizeof(seat_node_t),1,fp);
			fsetpos(fp,&pos);
			break;
		}
		
	}
	fclose(fp);
	free(temp);
	free(p);
	if(flag==0){
		printf("\nSeat not exist!\n"); 
		return 0;
	}
	else{
		return 1;
	}
}
int Seat_Perst_FetchAll(int id,seat_node_t* h){
	FILE*fp;
	seat_node_t* temp=NULL;
	if(access(seatfile,0)){
		return 0;
	}
	else{
		fp=fopen(seatfile,"rb");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
		}
		while(1){
			temp=(seat_node_t*)malloc(sizeof(seat_node_t));
			if(fread(temp,sizeof(seat_node_t),1,fp)<1){
				break;
			}
			if(temp->data.roomID==id){
				List_AddTail(h,temp);
				
			}else{
				free(temp);
			}
		}
	}
	fclose(fp);
	return 1;
}
int Seat_Perst_Insert(seat_node_t *h){
	FILE*fp;
	seat_node_t*p;
	p=(seat_node_t*)malloc(sizeof(seat_node_t));
	p=h->next;
	if(access(seatfile,0)){
		fp=fopen(seatfile,"wb+");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
	}
		while(1){
			fwrite(p,sizeof(seat_node_t),1,fp);
			p=p->next;
			if(p==h)break;
		}
//		printf("**\n");
	}
	else{
		fp=fopen(seatfile,"ab+");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
		} 
		while(p!=h){
			fwrite(p,sizeof(p),1,fp);
			p=p->next;
		} 
	} 
	free(p);
	fclose(fp);
	return 1; 
}

int Seat_Perst_SameStudioSeat(int id,seat_node_t*h){//����ͬ�ݳ�������λ���ݵ��뵽������ 
//	int i=0;
	if(access(seatfile,0)){
//		printf("") 
		return 0;
	}
//	printf("\n****\n");
	FILE*fp=fopen(seatfile,"rb");
	if(fp==NULL){
		return 0;
	}
	seat_node_t*temp=NULL;
	while(1){
		temp=(seat_node_t*)malloc(sizeof(seat_node_t));
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
//	printf("%d   ",temp->data.roomID);		
		if(temp->data.roomID==id){//					printf("*%d    %d*    ",temp->data.row,temp->data.column);
//					i++;

					List_AddTail(h,temp); 
		}
		else{
			free(temp);
		}
	}
//	printf("\n%d",i);
	fclose(fp);
	return 1;
}
int Seat_Perst_ModifyInfo(seat_node_t*p){
	if(access("Seat.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("Seat.dat","rb+");
	seat_node_t*temp=NULL;
//	if(p->data.status==0)printf("\n&&&&&&\n");
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	while(1){
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			free(temp);
			break;
		}
		if(temp->data.roomID==p->data.roomID&&temp->data.row==p->data.row&&temp->data.column==p->data.column){
//			printf("\n&&&&&\n");
			p->data.id=temp->data.id;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*(int)sizeof(seat_node_t),SEEK_CUR);
			fwrite(p,sizeof(seat_node_t),1,fp);
			fsetpos(fp,&pos);
			free(temp);
			fclose(fp);
			return 1;
		}
	}
//	printf("\n)))))\n");
	fclose(fp);
	return 0;
}

int Seat_Perst_Add(seat_node_t* head){
//	printf("***\n"); 
	FILE*fp;
//	int i=0;
	seat_node_t*temp=NULL;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	temp=head->next; 
	if(access(seatfile,0)){
		fp=fopen(seatfile,"wb+");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
			}
//		}printf("\n******\n");
		while(temp!=head){
			fwrite(temp,sizeof(seat_node_t),1,fp);
			temp=temp->next;
		}
	}else{
		fp=fopen(seatfile,"ab");
		if(fp==NULL){
			printf("Error!\n");
			return 0;
		}
		while(temp!=head){
//			printf("%d    %d\n",temp->data.column,temp->data.row);
//			printf("\n*****************\n");
			fwrite(temp,sizeof(seat_node_t),1,fp);
			temp=temp->next;
		}
	}
	fclose(fp);
	free(temp);
	return 1;
} 
int Seat_Perst_CountStudioSeat(seat_node_t*s,int seatNum,int studio_id){
	if(access(seatfile,0)){
		return 0;
	}
	FILE*fp;
	fp=fopen(seatfile,"rb");
	if(fp==NULL){
		return 0; 
	}
	
	seat_node_t*temp=NULL;
	while(1){
		temp=(seat_node_t*)malloc(sizeof(seat_node_t));
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
		if(temp->data.roomID==studio_id){
			List_AddTail(s,temp);
			seatNum++;
		}
		else{
			free(temp);
			continue;
		}
	}
	fclose(fp);
	free(temp);
	return seatNum;
}
int Seat_Perst_FetchByID(seat_node_t*h,int schedule_id){//�����ݳ���ID����λ����������ͬ�ݳ�������λ���������� 
	if(access(seatfile,0)){
		return 0;
	}
	FILE*fp;
	fp=fopen(seatfile,"rb");
	if(fp==NULL){
		return 0;
	}
	seat_node_t*temp=NULL;
	int flag=0;
	while(1){
		temp=(seat_node_t*)malloc(sizeof(seat_node_t));
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
		if(temp->data.roomID==schedule_id){
			flag++;
			List_AddTail(h,temp);
		}
		else{
			free(temp);
		}
	}
	free(temp);
	fclose(fp);
	if(flag==0){
		return 0;
	}
	return flag; 
}
int Seat_Perst_SelectTByID(seat_node_t*temp,int id){
	if(access("seat.dat",0)){
		return 0;
	}
	FILE*fp;
	fp=fopen("seat.dat","rb");
	if(fp==NULL){
		return 0;
	}
	seat_node_t*q=NULL;
	int flag=0;
	q=(seat_node_t*)malloc(sizeof(seat_node_t)); 
	while(1){
	 	if(fread(q,sizeof(seat_node_t),1,fp)<1){
	 		break;
	 	}
	 	if(q->data.id==id){
	 		temp->data.id=q->data.id;
	 		temp->data.roomID=q->data.roomID;
	 		temp->data.row=q->data.row;
	 		temp->data.column=q->data.column;
	 		temp->data.status=SEAT_FULL;
	 		flag=1;
			break;;
	 	}
	}
	free(q);
	fclose(fp);
	if(flag==0){
		return 0;
	}
	return 1;
}
int Seat_Perst_Modify(seat_node_t*p){
	if(access(seatfile,0)){
		printf("\n=====\n");
		return 0;
	}
	FILE*fp;
	seat_node_t*temp=NULL;
	int flag=0;
	temp=(seat_node_t*)malloc(sizeof(seat_node_t));
	fp=fopen(seatfile,"rb+");
	if(fp==NULL){
		return 0;
	}
//	if(p->data.status==1)printf("\n%%%%%%\n");
	while(1){
		if(fread(temp,sizeof(seat_node_t),1,fp)<1){
			break;
		}
		if(temp->data.id==p->data.id){
//			printf("\n%%%%%%\n");
			temp->data.status=p->data.status;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*(int)(sizeof(seat_node_t)),SEEK_CUR);
			fwrite(temp,sizeof(seat_node_t),1,fp);
			fsetpos(fp,&pos);
			flag=1;
			break;
		}
	}
	free(temp);
	fclose(fp);
	if(flag==0){
		return 0;
	}
	return 1;
}
//int Seat_Perst_Add(seat_node_t* head){
//	
//}
/*typedef enum{
	SEAT_NONE=0,			//��λ
	SEAT_GOOD=1,			//����λ
	SEAT_BROKEN=9			//�𻵵���λ
}seat_status_t;

typedef struct {
	int id;					//��λid
	int roomID;				//�����ݳ���id
	int row;           		//��λ�к�
    int column;        		//��λ�к�
    seat_status_t status;	//��λ�ڸ��е�״̬��0��ʾû����λ��1��ʾ����λ����չ2�ɱ�ʾ��λ����
} seat_t;
*/
