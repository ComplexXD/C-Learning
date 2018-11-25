#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// f(x) = ax^2 + bx + c

typedef struct _QF
{
    float a;
    float b;
    float c;
} quadratic_function;

typedef struct _IN
{
    float a;
    float b; /* i-part */
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


complex_number complex_multiply(complex_number x, complex_number y) {
    complex_number r;
    r.a = (x.a * y.a) - (x.b * y.b);
    r.b = ((x.a * y.b) + (x.b * y.a));

    return r;
} 


complex_number complex_divide(complex_number x, complex_number y) {
    complex_number r;
    r.a = ((x.a * y.a) + (x.b * y.b)) / ((pow(y.a, 2) + pow(y.b, 2)));
    r.b = ((x.b * y.a) - (x.a * y.b)) / ((pow(y.a, 2) + pow(y.b, 2)));

    return r;
}


int get_numbers_of_roots(quadratic_function f)
{
    float r = sqrt((f.b * f.b) - (4 * f.a * f.c));
  
    if (r > 0)
        return 2;
    if (r == 0)
        return 1;
    else 
        return 0;
}

float qf_get_roots(quadratic_function f, int n)
{
    float r2 = sqrt((f.b * f.b) - (4 * f.a * f.c)) / (2 * f.a); 
    float r1 = (f.b * -1) / (2 * f.a);
    if (n == 0)
        return (r1 - r2);
    else
        return (r1 + r2);
}

quadratic_function create_quadratic_function(float a, float b, float c)
{
    quadratic_function f;
    f.a = a;
    f.b = b;
    f.c = c;
    return f;
}



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
float get_value_in_x(float x, quadratic_function f)
{
    float y = ((pow(x,2) * f.a) + (f.b * x) + f.c); 
    return y;
}


char* get_string_cn(char* Result, complex_number x)
{
    char a_str[1024];
    char b_str[1024];

    if (x.a != 0)
        snprintf(a_str, 1024, "f", x.a);
    if (x.b != 0)
        snprintf(b_str, 1024, "fi", x.b);

    combine_two_terms(a_str, b_str, Result);

return Result;

}

char* get_string_qf(char* result, quadratic_function f)
{
    char a_str[1024];
    char b_str[1024];
    char c_str[1024];
    char r_str[1024];

    a_str[0] = '\0';
    b_str[0] = '\0';
    c_str[0] = '\0';


    if (f.a != 0)
        snprintf(a_str, 1024, "%fx²", f.a);
    if (f.b != 0 )
        snprintf(b_str, 1024, "%fx", f.b);
    if (f.c != 0)
        snprintf(c_str, 1024, "%f", f.c);
    
    combine_two_terms(b_str, c_str, r_str);
    combine_two_terms(a_str, r_str, result);

return result;
}


quadratic_function dydx (quadratic_function f)
{
    return create_quadratic_function(0, 2*f.a, f.b);
}

int main(float argc, char* argv[])
{
    char f_str[1024], f_prime_str[1024];
    float a;
    float b;
    float c;
    float x;

    char a1[1024];
    char b1[1024];
    char c1[1024];
    char result[1024];


    printf("All values most corrolate with the function type f(x) = ax² + bx + c\n");
    printf("Enter A:\n");
    scanf("%f", &a);

    printf("Enter B:\n");
    scanf("%f", &b);

    printf("Enter C:\n");
    scanf("%f", &c);

    printf("Enter a value of X you want calculated:\n");
    scanf("%f", &x);

    
    

    quadratic_function f = create_quadratic_function(a,b,c);
    quadratic_function f_prime;

      if ((a == 0) && (b == 0) && (c == 0)){
        printf("\nAll values can not be zero!\n");
        return 0; }

    printf("\nThe function is %s\n", get_string_qf(result, f));
    printf("In which point you entered X: y = %f\n\n", get_value_in_x(x, f));

    f_prime = dydx(f);
    
    result[0] = '\0';

    printf("The prime function is = %s\n", get_string_qf(result, f_prime));
    printf("In which point your entered the dy/dx = %f\n\n", get_value_in_x(x, f_prime));


    int n = get_numbers_of_roots(f);
    printf("Number of roots = %d\n", n);

    if (n == 0)
    {
        printf("No roots to calculate\n");
        return 0;
    }
    if (n == 1)
    {
        printf("%f\n", qf_get_roots(f, 0));
        return 0;
    }
    else
    {
        printf("First root = %f\n", qf_get_roots(f, 0));
        printf("Second root = %f\n\n", qf_get_roots(f, 1));
        return 0;
    }
    
       
return 0;
}