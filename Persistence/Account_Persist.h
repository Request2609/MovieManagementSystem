#ifndef ACCOUNT_PERSIST_H_
#define ACCOUNT_PERSIST_H_
#include"../Service/Account.h"
int Account_Perst_Insert(account_node_t*h);
int Account_Perst_JudgeInfo(account_node_t *p);
int Account_Perst_Add(account_node_t*h);////����û� 
int Account_Perst_FetchAll(account_node_t *h);//���û���Ϣ�������� 
int Account_Perst_Delete();//ɾ���ǹ���Ա�û�
int Account_Perst_FetchAdmin(account_node_t*h);//���ڴ�������Ա���� 
int Account_Perst_Modify(account_node_t*temp);
int Account_Perst_SaleLogIn(account_node_t* h);//�û���¼�����û���Ϣ��¼���ṹ��ָ��ڵ��� 
int Account_Perst_SearchInfo(account_node_t*p);//�����û���Ϣ 
#endif
