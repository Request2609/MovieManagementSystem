/*
 * Seat.h
 *
 * Created on: 2015��4��27��
 * Updated on: 2015��5��23��
 * Author: lc
 */
#ifndef SEAT_H_
#define SEAT_H_
#include"../Service/Studio.h"
typedef enum{
	SEAT_NONE=0,			//��λ
	SEAT_GOOD=1,			//����λ
	SEAT_BROKEN=9,			//�𻵵���λ
	SEAT_FULL=2//��ռ 
}seat_status_t;

typedef struct {
	int id;					//��λid
	int roomID;				//�����ݳ���id
	int row;           		//��λ�к�
    int column;        		//��λ�к�
    seat_status_t status;	//��λ�ڸ��е�״̬��0��ʾû����λ��1��ʾ����λ����չ2�ɱ�ʾ��λ����
} seat_t;


//˫������
typedef struct seat_node {
	seat_t data;
	struct seat_node *next, *prev;
} seat_node_t, *seat_list_t;
int Seat_Srv_Delete(seat_node_t* p);
int Seat_Srv_PrintAllSeat(seat_node_t*h);
//�����С�������ʼ���ݳ���
int Seat_Srv_Add(seat_node_t*h,int num);
int Seat_Srv_FetchByRoomID(seat_node_t* h,int id);
//int Seat_Srv_FetchByRoomID(seat_node_t*h,int id);//
int Seat_Srv_DeleteAllByRoomID(int id);
int Seat_Srv_Modify(seat_node_t*p);
int Seat_Srv_ModifyInfo(seat_node_t*p);//�޸���λ�кţ��кã�״̬�� 

#endif //SEAT_H_





