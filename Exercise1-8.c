# include <stdio.h>

#define oow 0
#define iw 1

int main(void)
{

    int c, nl, tb, nw, nc, state; 
    nl = tb = nw = nc = 0;

    state = oow;

    while((c = getchar()) != EOF)
    {
        nc++;

        if (c == '\n')
            nl++; 

        if (c == '\t')
            tb++;
    
        if (c == ' '|| (c == '\t') || (c == '\n'))
            state = oow;
    
        else if (state == oow)
        {
            state = iw;
            nw++;
        }
    }   
    printf("%d %d %d %d", nc, nw, nl, tb);
    return 0;
}