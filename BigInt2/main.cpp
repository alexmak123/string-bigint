#include <iostream>
#include "BigInt2.h"
#include "string.h"
using namespace std;
int main() {
    BigInt s1("459872345983248947928340457");
    BigInt s2("879813414181263471023234213");
    cout << s1 - s2;
    return 0;
}
