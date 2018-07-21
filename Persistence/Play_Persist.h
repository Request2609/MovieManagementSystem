#ifndef PLAY_PERSIST_H_
#define PLAY_PERSIST_H_
#include "../Service/Play.h"
//#include"EntityKey_Persist.h"

void Play_Perst_RemByID();
void Play_Perst_SelectByID();
int Play_Perst_Insert(play_node_t*p);
void Play_Perst_Update();
int Play_Perst_SelectAll(play_node_t*h);
int Play_Perst_FetchByName(play_node_t* h);
int Play_Perst_FetchPriceByID(int id);//为生成演出票找剧目票价 
#endif
