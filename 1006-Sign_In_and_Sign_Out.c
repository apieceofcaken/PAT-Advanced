/*
At the beginning of every day, the first person who signs in the computer room will unlock the door, and the last one who signs out will lock the door. Given the records of signing in's and out's, you are supposed to find the ones who have unlocked and locked the door on that day.

Input Specification:
Each input file contains one test case. Each case contains the records for one day. The case starts with a positive integer M, which is the total number of records, followed by M lines, each in the format:

ID_number Sign_in_time Sign_out_time
where times are given in the format HH:MM:SS, and ID_number is a string with no more than 15 characters.

Output Specification:
For each test case, output in one line the ID numbers of the persons who have unlocked and locked the door on that day. The two ID numbers must be separated by one space.

Note: It is guaranteed that the records are consistent. That is, the sign in time must be earlier than the sign out time for each person, and there are no two persons sign in or out at the same moment.

Sample Input:
3
CS301111 15:30:28 17:00:10
SC3021234 08:00:00 11:25:25
CS301133 21:45:00 21:58:40
Sample Output:
SC3021234 CS301133
*/

/*
将时间化为秒，写一个Time_to_Seconds的转换函数
找 最小登入时间 和 最大登出时间 对应的 用户名即可
*/

#include<stdio.h>
#include<string.h>


#define HOUR_SECONDS 3600
#define MAX 99999

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
    char current_name[20], in_name[20], out_name[20];
    char current_in_time[10], current_out_time[10];
    int earlist_in_time = MAX, latest_out_time = 0;
    int temp_in_time, temp_out_time;  //存放转换后的时间
    int m, i = 0;

    scanf("%d", &m);
    for(i = 0; i < m; i++)
    {
        scanf("%s %s %s", current_name, current_in_time, current_out_time);
	    
        temp_in_time = Time_to_Seconds(current_in_time);
        temp_out_time = Time_to_Seconds(current_out_time);
	    
	/*
	对比一下简洁做法：使用scanf()将不需要的":"去掉，然后直接计算
        scanf("%s %d:%d:%d", name, &HH, &MM, &SS);
        time = (HH * 60 + MM) * 60 + SS;
	*/
	 
        if(earlist_in_time > temp_in_time)
        {
            earlist_in_time = temp_in_time;        
			strcpy(in_name, current_name); //重点！字符串的复制需要使用strcpy(目标，源)函数
        }
        if(latest_out_time < temp_out_time)
        {
            latest_out_time = temp_out_time;
            strcpy(out_name, current_name);
        }
    }
    printf("%s %s", in_name, out_name);

    return 0;

}
