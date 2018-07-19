#include "../Common/common.h"
#include<stdio.h>
#include<fcntl.h>
#include <time.h>
//真真真真
char *Str2Upper(char *str) {
	if (NULL == str)
		return NULL;
	else {
		char *p = str;
		while ('\0' != *p) {
			if (*p >= 'a' && *p <= 'z')
				*p -= 32;
			p++;
		}
		return str;
	}
}
//真真真真真真
char *Str2Lower(char *str) {
	if (NULL == str)
		return NULL;
	else {
		char *p = str;
		while ('\0' != *p) {
			if (*p >= 'A' && *p <= 'Z')
				*p += 32;
			p++;
		}
		return str;
	}
}

//真真真
int DateCmp(user_date_t dt1, user_date_t dt2) {
	if (dt1.year < dt2.year)
		return -1;
	else if (dt1.year == dt2.year && dt1.month < dt2.month)
		return -1;
	else if (dt1.year == dt2.year && dt1.month == dt2.month && dt1.day < dt2.day)
		return -1;
	else if (dt1.year == dt2.year && dt1.month == dt2.month
			&& dt1.day == dt2.day)
		return 0;
	else
		return 1;
}
//真真真真
user_date_t DateNow() {
	user_date_t curDate;
	time_t now;         
	struct tm *timeNow;         
	time(&now);
	timeNow = localtime(&now);
	curDate.year=timeNow->tm_year+1900;
	curDate.month=timeNow->tm_mon+1;
	curDate.day=timeNow->tm_mday;

	return curDate;
}

//真真真真
user_time_t TimeNow(){
	user_time_t curTime;
	time_t now;         
	struct tm *timeNow;        
	time(&now);
	timeNow = localtime(&now);
	curTime.hour=timeNow->tm_hour;
	curTime.minute=timeNow->tm_min;
	curTime.second=timeNow->tm_sec;
	return curTime;
}


