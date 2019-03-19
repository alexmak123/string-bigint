#include <iostream>
#include <string.h>
class BigInt{
    static const int max_size = 1000;
    friend BigInt operator + (const BigInt&, const BigInt&);
    friend BigInt operator - (const BigInt&, const BigInt&);
    friend BigInt operator - (const BigInt&); // Унарный минус.
    friend bool operator == (const BigInt& , const BigInt&);
    friend bool operator < (const BigInt&, const BigInt&);
    friend bool operator > (const BigInt&, const BigInt&);
    friend std::ostream & operator << (std :: ostream &, const BigInt&);
    friend int compare_abs(const BigInt& left, const BigInt& right);
    friend BigInt abs_plus(const BigInt&, const BigInt&);
    friend BigInt abs_minus(const BigInt&, const BigInt&);
private:
    int* value;
    bool sign;
    int calculate_length() const;
public:
    BigInt();
    BigInt(int );
    BigInt(const BigInt& );
    BigInt (const String& );
    BigInt& operator = (const BigInt&);
    BigInt& operator ++();
    BigInt& operator --();
    ~BigInt();
};
