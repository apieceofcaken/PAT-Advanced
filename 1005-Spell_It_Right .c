/*
感谢：https://github.com/OliverLew/PAT/blob/master/PATAdvanced/1005.c

Given a non-negative integer N, your task is to compute the sum of all the digits of N, and output every digit of the sum in English.

Input Specification:
Each input file contains one test case. Each case occupies one line which contains an N (≤10^100 ).

Output Specification:
For each test case, output in one line the digits of the sum in English words. There must be one space between two consecutive words, but no extra space at the end of a line.

Sample Input:
12345
Sample Output:
one five
*/

//计算各位数的和sum，并用英语单词输出sum的各位数。
//输出用一个字符串数组，计算部分要注意能计算大数，低空间复杂度
//将输入看作字符串，使用getchar()，计算过程中转换计算

#include<stdio.h>


int main()
{
    char a;
    char eng_number[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    /*对比学习一下，大括号数组赋值可以换行
    char c, *digits[] = {
        "zero", "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"
    };
    */
    int sum = 0, digits[100], i = 0;
	int flag = 0;

    digits[0] = 0;

    for(a = getchar(); a != '\n' && a != EOF; a = getchar()) //对比：while((c = getchar()) != '\n')
    {
        sum = sum + (int)a - '0';//(int)a 转换后为ASCII码，比真实值大'0'(48)

    }

    
    while(sum > 0)
    {
        digits[i++] = sum % 10;
        sum = sum / 10;
        flag = 1;
    }

    
    if(flag == 0) printf("%s", eng_number[0]); //注意输入为0的边界条件，学习更好的处理方法
    for(i--; i >= 0; i--)
    {
        printf("%s", eng_number[digits[i]]);
		if(i > 0) printf(" "); 
    }
    /*对比：
    if(sum >= 100)
        printf("%s ", digits[sum / 100]);
    if(sum >= 10)
        printf("%s ", digits[sum % 100 / 10]);
    printf("%s", digits[sum % 10]);
    */

    return 0;
    
}
