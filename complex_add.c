#include <stdio.h>
#include <string.h>
#include <math.h>

int combine_two_terms(char* a, char* b, char* result)
{
    

     strcpy(result, "An error in combine_two_terms_occurred");

    if ((a[0] != '\0') && (a[0] != '-') && (b[0] != '\0') && (b[0] !='-')) {                    // a + b  (a > 0, b > 0)
        snprintf(result, 1024, "%s + %s", a, b);
        return 0;}

    if ((a[0] != '-') && (a[0] != '\0') && (b[0] != '\0') && (b[0] == '-')){                    // a - b ( a > 0, b < 0)     
        snprintf(result, 1024, "%s - %s", a, &(b[1]));
        return 0;}

    if ((a[0] == '\0')  && (b[0] == '-')){                                              // -b (a == 0, b < 0)
        snprintf(result, 1024, "%s", b);
        return 0;}
    
    if ((a[0] == '-')  && (b[0] == '-')){                                               // -a -b (a < 0, b < 0)
        snprintf(result, 1024, "%s - %s", a, &(b[1]));
        return 0;}
    
    if ((a[0] == '\0') && (b[0] != '-')){                                               // b (a == 0, b > 0)                 
        snprintf(result, 1024, "%s", b);
        return 0;}

    if ((a[0] != '\0') && (a[0] != '-') && (b[0] == '\0')){                             // a (a > 0, b == 0)
        snprintf(result, 1024, "%s", a);
        return 0;}
    
    if ((a[0] != '\0') && (a[0] == '-') && (b[0] == '\0')){                             // -a ( a < 0, b == 0)
        snprintf(result, 1024, "%s", a);
        return 0;}
 
    if ((a[0] == '-') && (b[0] != '-') && (b[0] != '\0')){                                 // -a + b (a < 0, b > 0)
        snprintf(result, 1024, "%s + %s", a, b);
        return 0;}

    return -1;                                                                          // a > 0, b > 0, c < 0
}





typedef struct _IN
{
    float a;
    float b; // i-part
} complex_number;

complex_number create_complex_number(float a, float b)
{   
    complex_number i;
    i.a = a;
    i.b = b;
    return i;
}


complex_number complex_add(complex_number x, complex_number y) {
    complex_number r;
    r.a = x.a + y.a;
    r.b = x.b + y.b;
    return r;
}

complex_number complex_divide(complex_number x, complex_number y) {
    complex_number r;
    r.a = ((x.a * y.a) + (x.b * y.b)) / ((pow(y.a, 2) + pow(y.b, 2)));
    r.b = ((x.b * y.a) - (x.a * y.b)) / ((pow(y.a, 2) + pow(y.b, 2)));

    return r;
}



complex_number complex_multiply(complex_number x, complex_number y) {
    complex_number r;
    r.a = (x.a * y.a) - (x.b * y.b);
    r.b = (x.a * y.b) + (x.b * y.a);

    return r;
}



char* get_string_cn(char* Result, complex_number x)
{
    char a_str[1024];
    char b_str[1024];

    if (x.a != 0)
        snprintf(a_str, 1024, "%f", x.a);
    if (x.b != 0)
        snprintf(b_str, 1024, "%fi", x.b);

    combine_two_terms(a_str, b_str, Result);

return Result;
}


int main(void)
{
    char cn_str[1024];
    complex_number r;

    complex_number a = create_complex_number(5, 2);
    complex_number b = create_complex_number(7, 12);

    printf("a is %s\n", get_string_cn(cn_str, a));
    printf("b is %s\n", get_string_cn(cn_str, b));


    r = complex_add(a, b);
    printf("The sum is %s\n", get_string_cn(cn_str, r));

    r = complex_multiply(a, b);
    printf("The product is %s\n", get_string_cn(cn_str, r));

    r = complex_divide(a, b);
    printf("The fraction is %s\n", get_string_cn(cn_str, r));

    return 0;
}