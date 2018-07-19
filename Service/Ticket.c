#include"Ticket.h"
#include"../Common/List.h"
#include"../Persistence/Schedule_Persist.h"
#include"../Service/Schedule.h"
#include"../Persistence/EntityKey_Persist.h"
#include"Seat.h"
#include"../Persistence/Play_Persist.h" 
#include"../Persistence/Seat_Persist.h"
#include"../Persistence/Ticket_Perst.h"
#include"../Persistence/Studio_Persist.h"
static char* KeyName="Ticket"; 
/*
typedef enum{
	TICKET_AVL=0;//���� 
	TICKET_SOLD=1;//���� 
	TICKET_RESV=9;//Ԥ�� 
	
}ticket_status_t;
typedef struct{
	int id;//Ʊid 
	int schedule_id;//�ݳ��ƻ�Id 
	int seat_id;//��λid 
	int price;//Ʊ�� 
	ticket_status status;//Ʊ״̬ 
}ticket_t;
*/ 
void Ticket_Srv_GenBatch(){//��������Ʊ 

	 schedule_node_t*head=NULL,*temp=NULL;
	 
//	 temp=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	head=(schedule_node_t*)malloc(sizeof(schedule_node_t));
	List_Init(head,schedule_node_t);
	
	ticket_node_t*h=NULL,*t=NULL;
	
	h=(ticket_node_t*)malloc(sizeof(ticket_node_t));
	List_Init(h,ticket_node_t);
	
	int ticketNum;
	printf("\n\t\tInput schedule ID:");
	fflush(stdin);
	scanf("%d",&head->data.id);
//	play_node_t*play=NULL;
//	play=(play_node_t*)malloc(sizeof(play_node_t));
	if(Schedule_Perst_FetchByID(head,head->data.id)==0){
		printf("\n\t\tThe schedule is not exist!\n");
		return ;
	}
	studio_t*ptr=NULL;
	ptr=(studio_t*)malloc(sizeof(studio_t));
//	printf("_%d_\n",head->data.studio_id);
	if(Studio_Perst_SelectByID((head->next)->data.studio_id,ptr)==0){
//		printf("\n******\n");
		printf("\n\t\tNo this studio!\n");
		return ;
	}
	seat_node_t*s=NULL,*q=NULL;
	List_Init(s,seat_node_t);
	int i,seatNum=0;
	temp=head->next;
	seatNum=Seat_Perst_CountStudioSeat(s,seatNum,temp->data.studio_id);//������λͷ��㣬��λ���������ݳ���ID����ͬ���ݳ�������λ���������ϣ���������λ���� 
	if(seatNum==0){
		printf("\n\t\tNot set seat in studio!\n");
		return ;
	}
	while(1){
		printf("\n\t\tInput ticket number:");
//		fflush(stdin);
		scanf("%d",&ticketNum);
		if(seatNum<ticketNum){
			printf("\n\t\tThere is %d seat in No.%d studio in schedule!\n",temp->data.studio_id,seatNum);
		}
		else{
			break;
		}
	}
		q=s->next;
		int price;
		printf("\n\t\t%d\n",(head->next)->data.play_id);
		price=Play_Perst_FetchPriceByID((head->next)->data.play_id);
		if(price==0){
//			printf("\n\t\t***************\n");
//			printf("��ĿƱ��") 
			return ;
		}
		
//		printf("\n\t\t������Ʊ��:");
//		fflush(stdin);
//		scanf("%d",&price);
//	printf("\n=%d=\n",seatNum);
//	system("pause");
		for(i=0;i<ticketNum;i++){
			t=(ticket_node_t*)malloc(sizeof(ticket_node_t));
			t->data.id=EntKey_Perst_GetNewKeys(KeyName);
			t->data.schedule_id= temp->data.id;
			t->data.seat_id=q->data.id;
			t->data.price=price;
			t->data.status=TICKET_AVL;
			List_AddTail(h,t);//������洢Ʊ����Ϣ
			q=q->next;//��λID�����ı�
	}
//	printf("\n\t\t===========\n");
	if(Ticket_Perst_Insert(h)==0){
		printf("\n\t\tError!\n");
//		printf("")/
		return ; 
	} 
	printf("\n\t\tStorage ticket success! \n");
	printf("\n\t\tPress [Enter] to return......");
	while('\n'!=getchar());
}
