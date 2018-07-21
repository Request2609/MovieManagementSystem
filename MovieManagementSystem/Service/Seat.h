
#ifndef SEAT_H_
#define SEAT_H_
#include"../Service/Studio.h"
typedef enum{
	SEAT_NONE=0,			
	SEAT_GOOD=1,			
	SEAT_BROKEN=9,	
	SEAT_FULL=2 
}seat_status_t;

typedef struct {
	int id;					
	int roomID;			
	int row;          
    int column;        
    seat_status_t status;
} seat_t;


typedef struct seat_node {
	seat_t data;
	struct seat_node *next, *prev;
} seat_node_t, *seat_list_t;
int Seat_Srv_Delete(seat_node_t* p);
int Seat_Srv_PrintAllSeat(seat_node_t*h);
int Seat_Srv_Add(seat_node_t*h,int num);
int Seat_Srv_FetchByRoomID(seat_node_t* h,int id);
int Seat_Srv_DeleteAllByRoomID(int id);
int Seat_Srv_Modify(seat_node_t*p);
int Seat_Srv_ModifyInfo(seat_node_t*p);

#endif 





