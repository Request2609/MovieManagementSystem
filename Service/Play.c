#include "Play.h"
#include"../Common/List.h"
#include"../Persistence/EntityKey_Persist.h"
#include"Account.h"
#include"../Persistence/Play_Persist.h"
static char*KeyName="Movie";
void Play_Srv_Add(){//影片的添加
	int type;
	char choice;
	play_node_t*h,*p;
	List_Init(h,play_node_t);
		printf("\n\t\t=========================================================================================");
	printf("\n\t\t*****************************************Add new movie************************************\n");
	printf("\t\t=========================================================================================");
	do{
			p=(play_node_t*)malloc(sizeof(play_node_t));
            p->data.id=EntKey_Perst_GetNewKeys(KeyName); 
            while('\n'!=getchar());
            printf("\n\t\tInput new movie name:");
            scanf("%[^\n]",p->data.name);
            printf("\n\t\t1.PLAY_TYPE_FILE  2.PLAY_TYPE_OPEAR  3.PLAY_TYPE_CONCERT\n");
            printf("\n\t\tInput new movie type:");
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
						printf("\t\tError infomation!\n");
						system("clear");
						return;
           	}
           	while('\n'!=getchar());
            printf("\n\t\tInput the product area:");
            scanf("%[^\n]",p->data.area);

            printf("\n\t\t1.PLAY_RATE_CHILD  2.PLAY_TYPE_TEENAGE  3.PLAY_RATE_ADULT\n");
            printf("\n\t\tInput its rank:");

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
						printf("\t\tError infomation!\n");

					return; 
            }
            printf("\n\t\tInput its time cost:");
            while('\n'!=getchar());
            	scanf("%d",&p->data.duration);
            	printf("\n\t\tInput its start on sale time:");
            	scanf("%d %d %d",&p->data.start_date.year,&p->data.start_date.month,&p->data.start_date.day);
            	printf("\n\t\tInput its end sale time:");
            	scanf("%d %d %d",&p->data.end_date.year,&p->data.end_date.month,&p->data.end_date.day);
					printf("\n\t\tInput its ticket price:");
					scanf("%d",&p->data.price);
					List_AddTail(h,p);
					printf("\n\t\t|*|(E)Exit                    |*|(C)Continue \n");

					while('\n'!=getchar());
					printf("\n\t\tInput you choice:");


					choice=getchar();
	}while(choice!='e'&&choice!='E');
	if(Play_Perst_Insert(h)==0){
		printf("\n\t\tAdd failed!\n");
	}
	else{

		printf("\n\t\tAdd success!\n");
	}
}
void Play_Srv_Modify(){//影片的修改
	Play_Perst_Update();
}

void Play_Srv_DeleteByID(){//影片的删除
	Play_Perst_RemByID();
}
void Play_Srv_FetchByID(){//根据id查询影片信息
	system("clear");
	Play_Perst_SelectByID();
}
