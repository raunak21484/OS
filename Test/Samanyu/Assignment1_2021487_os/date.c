#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

char* get_month(int month)
{
	if(month==0)
		return "Jan";
	else if(month==1)
		return "Feb";
	else if(month==2)
		return "Mar";
	else if(month==3)
		return "Apr";
	else if(month==4)
		return "May";
	else if(month==5)
		return "Jun";
	else if(month==6)
		return "Jul";
	else if(month==7)
		return "Aug";
	else if(month==8)
		return "Sep";
	else if(month==9)
		return "Oct";
	else if(month==10)
		return "Nov";
	else if(month==11)
		return "Dec";
}

char* get_week_day(int day)
{
	if(day==0)
		return "Sun";
	else if(day==1)
		return "Mon";
	else if(day==2)
		return "Tue";
	else if(day==3)
		return "Wed";
	else if(day==4)
		return "Thr";
	else if(day==5)
		return "Fri";
	else if(day==6)
		return "Sat";
}
int main(int argc,char* argv[]) {
 
   time_t rawtime;
   struct tm *info; 
   time(&rawtime);
   info = gmtime(&rawtime);
   int gmt_hr=info->tm_hour;
   int gmt_min=info->tm_min;
   char* day=get_week_day(info->tm_wday);
   char* month=get_month(info->tm_mon);
   int printed=1;
   if(strcmp(argv[1],"-u")==0)
   {
   	printed=0;
   printf("%s %s %02d %02d:%02d:%02d UTC %d\n",day,month,info->tm_mday,info->tm_hour,info->tm_min,info->tm_sec,info->tm_year+1900);
   }
   else if(strcmp(argv[1],"-Ru")==0 || strcmp(argv[1],"-uR")==0)
   {
   	printed=0;
   	printf("%s, %02d %s %d %02d:%02d:%02d +%02d%02d\n",day,info->tm_mday,month,info->tm_year+1900,info->tm_hour,info->tm_min,info->tm_sec,0,0);
   }

   //el	se if(argv[1]=="-R")
   	time_t t;
    struct tm *now;
    time(&t);
    now  = localtime(&t);
   
    char* my_day=get_week_day(now->tm_wday);
    char* my_month=get_month(now->tm_mon);
   	int diff_hr=0;
   	int diff_min=0;
   	diff_min=now->tm_min-gmt_min;
   	diff_hr=now->tm_hour-gmt_hr;
   	char plus_minus[2];
   	if(diff_hr<0)
   	{
   		plus_minus[0]='-';
   		if(diff_min>0)
   		{
   			diff_hr=diff_hr+1;
   			diff_min=60-diff_min;
   		}
   	}
   	else
   	{
   		plus_minus[0]='+';
   		if(diff_min<0)
   		{
   			diff_hr=diff_hr-1;
   			diff_min=60+diff_min;
   		}
   	}
   	if(strcmp(argv[1],"-R")==0)
   		printf("%s, %02d %s %d %02d:%02d:%02d %s%02d%02d\n",my_day,now->tm_mday,my_month,now->tm_year+1900,now->tm_hour,now->tm_min,now->tm_sec,plus_minus,diff_hr,diff_min);
   	else
   	{
   		if(printed==1)
 			printf("%s %s %02d %02d:%02d:%02d IST %d\n",day,month,info->tm_mday,info->tm_hour,info->tm_min,info->tm_sec,info->tm_year+1900);
 		}
   return 0;
}