#ifndef COMMON_H_
#define COMMON_H_
//¿¿¿¿¿¿¿¿¿
typedef struct {
	int year;
	int month;
	int day;
}user_date_t;

typedef struct {
	int hour;
	int minute;
	int second;
}user_time_t;

int ScanKeyboard();


char *Str2Upper(char *str);

char *Str2Lower(char *str);

int DateCmp(user_date_t dt1, user_date_t dt2);

user_date_t DateNow();

user_time_t TimeNow();

#endif 
