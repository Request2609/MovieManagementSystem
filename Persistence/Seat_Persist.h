#ifndef SEAT_PERST_H_
#define SEAT_PERST_H_
#include"../Service/Seat.h"
int Seat_Perst_FetchByID(seat_node_t*h,int schedule_id);
int Seat_Perst_Insert(seat_node_t* h);
int Seat_Perst_FetchAll(int id,seat_node_t* h);
int Seat_Perst_SameStudioSeat(int id,seat_node_t*h);
int Seat_Perst_Add(seat_node_t* head);
int Seat_Perst_Delete(seat_node_t* p);
int Seat_Perst_CountStudioSeat(seat_node_t*s,int seatNum,int studio_id);
int Seat_Perst_SelectTByID(seat_node_t*temp,int id);
int Seat_Perst_Modify(seat_node_t*p);
int Seat_Perst_ModifyInfo(seat_node_t*p);
#endif
