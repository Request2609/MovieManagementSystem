/*
 * StudioPersist.h
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */

#ifndef STUDIO_PERSIST_H_
#define STUDIO_PERSIST_H_

#include "../Service/Studio.h"
#include"../Service/Seat.h"
//int Studio_Perst_ModifySeatCount(seat_node_t*s)

static const char STUDIO_DATA_FILE[] = "Studio.dat";
static const char STUDIO_DATA_TEMP_FILE[] = "StudioTmp.dat";

int Studio_Perst_Insert(studio_t *data);	////新方案将data前面的const去掉

int Studio_Perst_Update(const studio_t *data);

int Studio_Perst_DeleteByID(int ID);

int Studio_Perst_SelectByID(int ID, studio_t *buf);

int Studio_Perst_SelectAll(studio_list_t list);


#endif /* STUDIO_PERSIST_H_ */
