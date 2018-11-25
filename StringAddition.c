#include <stdio.h>

int lenid(char *str)
{
    int l = 0;
    for(l = 0; str[l] != '\0'; l++);
    return (l);
}


int main(void)
{
    char str1[101];
    char str2[101];
    char strT[201];
    int i1, i2, iT, l1, l2;

    printf("Please choose the first string:\n");
    scanf("%100s", str1); 
    l1 = lenid(str1);

    printf("Please choose the second string:\n");
    scanf("%100s", str2);
    l2 = lenid(str2);

    for(i1 = 0; i1 <= l1; i1++) 
    {
        strT[i1] = str1[i1];
    }
    for(i2 = 0; i2 <= l2; i2++)
    {
        strT[l1 + i2] = str2[i2]; 
    }

    strT[l1 + l2] = '\0';
    

    printf("Your strings combined became: %s, \n", strT);
return 0;

}
