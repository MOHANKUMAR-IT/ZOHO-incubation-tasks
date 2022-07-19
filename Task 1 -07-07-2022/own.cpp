#include <iostream>
#include <string.h>
using namespace std;

void str_cat(char des[],char src[]){
    int i = 0, j = 0;
    while (des[i] != '\0')
        i += 1;
    while (src[j] != '\0') {
        des[i + j] = src[j];
        j += 1;
    }
    des[i + j] = '\0';

    printf("%s\n", des);
}
void str_cpy(char des[],char src[]){
    int i=0;
    while(src[i] != '\0'){
        des[i] = src[i];i++;
    }
    des[i] = '\0';
    printf("%s\n",des);
}
void str_ncat(char des[],char src[],int n)
{
    int i = 0, j = 0;
    while (des[i] != '\0')
        i ++;
    while (src[j] != '\0' && j<n) {
        des[i + j] = src[j];
        j ++;
    }
    des[i + j] = '\0';

    printf("%s\n", des);
}

char* str_tok(char* s, char d)
{
    static char* input = NULL;
    if (s != NULL)
        input = s;
    if (input == NULL)
        return NULL;
    char* result = new char[strlen(input) + 1];
    int i = 0;
    for (; input[i] != '\0'; i++) {
        if (input[i] != d)
            result[i] = input[i];
        else {
            result[i] = '\0';
            input = input + i + 1;
            return result;
        }
    }
    result[i] = '\0';
    input = NULL;
    return result;
}


int compare(const char *X, const char *Y)
{
    while (*X!='\0' && *Y!='\0')
    {
        if (*X != *Y) {
            return 0;
        }
        X++;
        Y++;
    }
    return 1;
}

bool str_str(const char* X, const char* Y)
{
    while (*X != '\0')
    {
        if ((*X == *Y) && compare(X, Y)) {
            return true;
        }
        X++;
    }
    return false;
}bool str_cmp(const char *a,const char *b){
    if(*a=='\0' && *b=='\0')return true;
    else if(*a==*b){
        return str_cmp(a+1,b+1);
    }
    return false;

}
int main() {

    char des[1000]="Hello,", src[100]="Zoho";
    cout<<"concatination\n";
    str_cat(des,src);
    char copy[20] = "Hello world!";
    cout<<"\ncopy\n";
    str_cpy(des,copy);
    cout<<"\nstring n cat\n";
    str_ncat(des,src,2);
    cout<<"\nString Tokens\n";
    char forTokens[50] = "Hi Im Mohan Kumar from TCE";
    char* ptr = str_tok(forTokens, ' ');
    cout << ptr << endl;
    while (ptr != NULL) {
        ptr = str_tok(NULL, ' ');
        cout << ptr << endl;
    }


    printf("\nstrstr\n");
    char *a = "hello zoho world",*b = "zoho";
    printf("\n%d\n", str_str(a, b));
    printf("\nstcmp\n");
    char *c = "zoho",*d = "zoho";
    printf("\n%d\n", str_cmp(c, d));
    return 0;
}
