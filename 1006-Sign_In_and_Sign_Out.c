/*
将时间化为秒，写一个Time_to_Seconds的转换函数
找 最小登入时间 和 最大登出时间 对应的 用户名即可
*/

#include<stdio.h>


#define HOUR_SECONDS 3600

int Time_to_Seconds(char* time)
{
    int i = 0, j = 0, h, k;
    int time_pieces[3][2];
    int seconds = 0;
    
    h = HOUR_SECONDS;

    for(i = 0, j = 0, k = 0; j < 9; j++)
    {
        if(time[j] != ':' && time[j] != '\0')
        {
            time_pieces[i][k] = (int)time[j] - '0';
			//printf("%d\n", time_pieces[i][k]);
			k = (k + 1) % 2;
			
        }
        else if(time[j] == ':')
        {
            i++;
        }
		
		
    }
	
    for(i = 0; i < 3; i++)
    {
        seconds += h * (time_pieces[i][0] * 10 + time_pieces[i][1]); 
		//printf("%d\n", seconds);
        h /= 60;
    }
	
    
    return seconds;

}

int main()
{
    char t[9];
    char earliest_in[], earliest_out[];
    char current[];
    int m;
    
    scanf
}
