#include <iostream>

int main() {

    short int si;
    unsigned short int usi;
    unsigned int ui;
    int i;
    long int li;
    signed char sc;
    unsigned char uc;
    float f;
    double d;
    long double ld;


    printf("Size of int: %ld bytes\n",sizeof(i));
    printf("Size of float: %ld bytes\n",sizeof(f));
    printf("Size of double: %ld bytes\n",sizeof(d));
    printf("Size of signed char: %ld byte\n",sizeof(sc));
    printf("Size of unsigned char: %ld byte\n",sizeof(uc));
    printf("Size of short int: %ld byte\n",sizeof(si));
    printf("Size of unsigned short int: %ld byte\n",sizeof(usi));
    printf("Size of unsigned int: %ld byte\n",sizeof(ui));
    printf("Size of long int: %ld byte\n",sizeof(li));
    printf("Size of long double: %ld byte\n",sizeof(ld));
    return 0;
}
