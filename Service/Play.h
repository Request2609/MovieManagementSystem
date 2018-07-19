#ifndef PLAY_H_
#define PLAY_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef enum{
    PLAY_TYPE_FILE=1,
    PLAY_TYPE_OPEAR=2,
    PLAY_TYPE_CONCERT=3
}play_type_t;
typedef enum{
    PLAY_RATE_CHILD=1, 
    PLAY_RATE_TEENAGE=2, 
    PLAY_RATE_ADULT=3
}play_rating_t;
typedef struct{
    int year;
    int month;
    int day;
}ttms_date_t;
typedef struct{
    int id;
    char name[30];
    play_type_t type;
    char area[9];
    play_rating_t rating;
    int duration;
    ttms_date_t start_date;
    ttms_date_t end_date;
    int price;
}play_t;
typedef struct play_node{
    play_t data;
    struct play_node*next;
    struct play_node*prev;
}play_node_t,*play_list_t;

void Play_Srv_DeleteByID(); 
//int Play_Srv_FetchAll(play_node_t*h);
void Play_Srv_Add();
void Play_Srv_Modify();
void Play_Srv_FetchByID();
//void ShowByPage(play_node_t*list,int pageSize);
#endif 


