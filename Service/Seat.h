/*
 * Seat.h
 *
 * Created on: 2015年4月27日
 * Updated on: 2015年5月23日
 * Author: lc
 */
#ifndef SEAT_H_
#define SEAT_H_
#include"../Service/Studio.h"
typedef enum{
	SEAT_NONE=0,			//空位
	SEAT_GOOD=1,			//有座位
	SEAT_BROKEN=9,			//损坏的座位
	SEAT_FULL=2//已占 
}seat_status_t;

typedef struct {
	int id;					//座位id
	int roomID;				//所在演出厅id
	int row;           		//座位行号
    int column;        		//座位列号
    seat_status_t status;	//座位在该行的状态，0表示没有座位，1表示有座位。扩展2可表示座位坏了
} seat_t;


//双向链表
typedef struct seat_node {
	seat_t data;
	struct seat_node *next, *prev;
} seat_node_t, *seat_list_t;
int Seat_Srv_Delete(seat_node_t* p);
int Seat_Srv_PrintAllSeat(seat_node_t*h);
//根据行、列数初始化演出厅
int Seat_Srv_Add(seat_node_t*h,int num);
int Seat_Srv_FetchByRoomID(seat_node_t* h,int id);
//int Seat_Srv_FetchByRoomID(seat_node_t*h,int id);//
int Seat_Srv_DeleteAllByRoomID(int id);
int Seat_Srv_Modify(seat_node_t*p);
int Seat_Srv_ModifyInfo(seat_node_t*p);//修改座位行号，列好，状态等 

#endif //SEAT_H_





