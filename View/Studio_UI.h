
#ifndef STUDIO_UI_H_
#define STUDIO_UI_H_
#include"../Service/Account.h"
int Studio_UI_Add(void);

int Studio_UI_Modify(int id);

int Studio_UI_Delete(int id);


void Studio_UI_MgtEntry(account_node_t* temp);

#endif /* STUDIO_UI_H_ */
