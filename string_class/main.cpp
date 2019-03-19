#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    const char *a = "hello world ";
    const char *b = "my first project";
    String s1(a);
    String s2(b);
    s1 += s2;
    s1 += s2;
    cout << s1;
    return 0;
}
