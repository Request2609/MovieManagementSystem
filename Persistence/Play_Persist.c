#include "../Service/Play.h"
#include"Play_Persist.h"
#include"../Common/List.h" 
#include"EntityKey_Persist.h"
#include<unistd.h>
//static const char playname[]="Movie";
static char*filename_temp="Play_temp.dat";
static char*filename="Play.dat";
//static const char *KeyName="Play";
void Play_Perst_RemByID(){//根据影片ID删除影片
	int flag=0;
	printf("\n\t\t====================================================================================\n");
	printf("\n\t\t**************************************Delete movie**********************************\n");
	printf("\n\t\t====================================================================================\n");
	FILE*fp=fopen(filename,"rb");
	if(fp==NULL){
		printf("\n\t\tFile not exist!\n");
		return ;
	}	
	FILE*fp_temp=fopen(filename_temp,"wb");
	if(fp_temp==NULL){
		printf("\n\t\tBuild file failed!\n");
		return;
	}
	int id;
	printf("\n\t\tInput play_ID:");
	scanf("%d",&id);
 	play_node_t*temp;
 	temp=(play_node_t*)malloc(sizeof(play_node_t));
 	while(1){
 		if(fread(temp,sizeof(play_node_t),1,fp)<1)break; 
 		if(temp->data.id==id){
 			flag=1;
			 }
		if(temp->data.id!=id){
 			fwrite(temp,sizeof(play_node_t),1,fp_temp);
 		}
	 }
 	
 	free(temp);
 	fclose(fp);
 	fclose(fp_temp);
 	remove(filename);
 	rename(filename_temp,filename);
 	if(flag==0){
 		printf("\n\t\tNo the movie!\n");
 		return;
 	}
 	printf("\n\t\tDelete success!\n");
// 	system("p");
}
void Play_Perst_SelectByID(){//根据ID搜索剧目
	printf("\n\t\t==================================================================================\n");
	printf("\t\t**************************************Index movie**********************************\n");
	printf("\t\t===================================================================================\n");
	int id;
	FILE*fp=fopen(filename,"rb");
	if(fp==NULL){
		printf("Error!\n");
		system("pause");
		return;
	} 
	
	printf("Input play_ID:");
	scanf("%d",&id);
	play_node_t*temp;
	int flag=0;
	temp=(play_node_t*)malloc(sizeof(play_node_t));
	while(1){
		if(fread(temp,sizeof(play_node_t),1,fp)<1)break;
		if(temp->data.id==id){
			printf("\n\n%-5s%-20s%-15s%-10s%-30s%-10s\n","ID","Movie_name","Movie_area","Movie_time"
			,"Start_date->End_date","Ticket_price");
			printf("\n%-5d%-20s%-15s%-10d%d.%d.%d->%d.%d.%d%15d\n",temp->data.id,
			temp->data.name,temp->data.area,temp->data.duration,temp->data.start_date.year,
			temp->data.start_date.month,temp->data.start_date.day,temp->data.end_date.year,
			temp->data.end_date.month,temp->data.end_date.day,temp->data.price);		
			flag=1;
			break;
		}
	} 
	free(temp);
	fclose(fp);
	if(flag==0){
		printf("\n\t\tCan't find infomation!\n");
		return;
	}
	
}
int Play_Perst_Insert(play_node_t*h){//添加影片信息
	FILE*fp;
	play_node_t*temp=NULL;
	temp=(play_node_t*)malloc(sizeof(play_node_t)); 
	if(access(filename,0)){
		fp=fopen(filename,"wb+");
		if(fp==NULL){
			return 0;
		}
		temp=h->next;
		while(1){
			fwrite(temp,sizeof(play_node_t),1,fp);
			temp=temp->next;
			if(temp==h)break;
		}
		}
	else{
		fp=fopen(filename,"ab");
		if(fp==NULL){
			return 0;
		}
	temp=h->next;
	while(1){
		fwrite(temp,sizeof(play_node_t),1,fp);
		temp=temp->next;
		if(temp==h)break;
	}
	}
	fclose(fp);
	free(temp); 
	return 1;
}
void Play_Perst_Update(){//修改影片信息
	int id;
	printf("\n\t\t=========================================================================================\n");
	printf("\t\t**************************************Modify Movie_info**********************************\n");
	printf("\t\t=========================================================================================\n");
	printf("\n\t\tInput play_ID:");
	scanf("%d",&id);
	FILE*fp=fopen(filename,"rb+");
	if(fp==NULL){
		return ;
	}
	play_node_t*p;
	int flag=0,type;
	p=(play_node_t*)malloc(sizeof(play_node_t));
	while(1){
		if(fread(p,sizeof(play_node_t),1,fp)<1)break;
		if(p->data.id==id){
			flag=1;
			fpos_t pos;
			fgetpos(fp,&pos);
			fseek(fp,(-1)*((int)sizeof(play_node_t)),SEEK_CUR);
				p->data.id=id;
            printf("\n\n\t\tInput movie_name:");
            fflush(stdin);
            scanf("%s",p->data.name);
            printf("\n\n\t\t1.PLAY_TYPE_FILE  2.PLAY_TYPE_OPEAR  3.PLAY_TYPE_CONCERT\n");
            printf("\n\t\tChoose the movie type:");
            fflush(stdin);
            scanf("%d",&type);
           	switch(type){
           		case 1:
           			p->data.type=PLAY_TYPE_FILE;
           			break;
          		case 2:
 					p->data.type=PLAY_TYPE_OPEAR;
					break;
				case 3:
					p->data.type=PLAY_TYPE_CONCERT;
					break;
				default:
					printf("\n\t\tInput error!\n");
					return;          			
           	}
            printf("\n\n\t\tInput movie area:");
            scanf("%s",p->data.area);
            printf("\n\n\t\t1.PLAY_RATE_CHILD  2.PLAY_TYPE_TEENAGE  3.PLAY_RATE_ADULT\n");
		printf("\n\n\t\tChoose movie rank:");
            scanf("%d",&type);
            switch(type){
            	case 1:
            		p->data.rating=PLAY_RATE_CHILD;
            		break;
            	case 2:
					p->data.rating=PLAY_RATE_TEENAGE;
					break;
				case 3:
					p->data.rating=PLAY_RATE_ADULT;
					break;
				default:
					printf("\n\t\tYou can't input error info!\n");
					return; 
            }
            printf("\n\n\t\tInput movie time:");
            scanf("%d",&p->data.duration);
            printf("\n\n\t\tInput start date:");
            scanf("%d %d %d",&p->data.start_date.year,&p->data.start_date.month,&p->data.start_date.day);
            printf("\n\t\tInput end date:");
			scanf("%d %d %d",&p->data.end_date.year,&p->data.end_date.month,&p->data.end_date.day);
			printf("\n\t\tInput ticket price:");
			scanf("%d",&p->data.price);
			fwrite(p,sizeof(play_node_t),1,fp);
			fsetpos(fp,&pos);
			return ;
		} 
	}
	fclose(fp);
	if(flag==0){
		printf("\n\t\tThe movie not exist!");
		return;
	}
}
int Play_Perst_FetchPriceByID(int id){
	if(access("Play.dat",0)){
		return 0;
	} 
	FILE*fp;
	fp=fopen("Play.dat","rb");
	if(fp==NULL){
		return 0;
	}
	play_node_t*temp=NULL;
	temp=(play_node_t*)malloc(sizeof(play_node_t));
	int price;
	while(1){
		if(fread(temp,sizeof(play_node_t),1,fp)<1){
			free(temp);
			break;
		}
		if(temp->data.id==id){
			price=temp->data.price;
			free(temp);
			fclose(fp);
			return price;
		}
	}
	fclose(fp);
	return 0;
}
int Play_Perst_SelectAll(play_node_t*h){//将所有影片数据传入到链表中
	FILE*fp=fopen(filename,"rb");
	if(fp==NULL){
		printf("\n\t\tNo movie at present!\n\n");
		return 0; 
	}
	play_node_t*temp=NULL,*q=NULL;
	int count=0;
	temp=h;
	while(1){
		q=(play_node_t*)malloc(sizeof(play_node_t));
		if(fread(q,sizeof(play_node_t),1,fp)<1)break;
		count++;
		q->next=temp->next;
		q->prev=temp;
		temp->next=q;
		temp=q;
	}
	temp->next=h;
	h->prev=temp;
	fclose(fp);
	return count; 
}
int Play_Perst_FetchByName(play_node_t* h){//根据影片名称查找信息
		if(access(filename,0)){
			return 0;
		}
		FILE*fp=fopen(filename,"rb");
		if(fp==NULL){
			printf("\n\t\tError!\n");
			return 0;
		}
		play_node_t* temp;
		temp=(play_node_t*)malloc(sizeof(play_node_t));
		while(1){
			if(fread(temp,sizeof(play_node_t),1,fp)<1)break;
			if(strcmp(temp->data.name,h->data.name)==0){
				h->data.id=temp->data.id;
				free(temp);
				fclose(fp);
				return 1;
			}
			printf("%s\n",h->data.name);
			printf("%s\n",temp->data.name);
		}
		free(temp);
		fclose(fp);
		return 0;
} 

