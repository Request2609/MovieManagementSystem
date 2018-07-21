#ifndef STUDIO_H_
#define STUDIO_H_

typedef struct {
	int id;			
	char name[30];	
	int rowsCount;	
	int colsCount;	
	int seatsCount;
} studio_t;

typedef struct studio_node {
	studio_t data;		
	struct studio_node *next;	
	struct studio_node *prev;	
} studio_node_t, *studio_list_t;

int Studio_Srv_Add(studio_t *data);

int Studio_Srv_Modify(const studio_t *data);

int Studio_Srv_DeleteByID(int ID);

int Studio_Srv_FetchByID(int ID, studio_t *buf);

int Studio_Srv_FetchAll(studio_list_t list);

studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID);

#endif 
