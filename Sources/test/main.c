#include <stdio.h>
#include <string.h>

int main()
{
    char s1[30]="HelloWorld is good";
    char s2[10]="new";

    printf("%d",strstr(s1,s2));
}