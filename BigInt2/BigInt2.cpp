#include "BigInt2.h"
#include <cassert>
#include "string.h"
const BigInt ONE(1), ZERO(0);

// Конструктор по умольчанию создает число 0.
BigInt :: BigInt(){
    // массив нулей.
    value = new int[max_size]();
    sign = true;
}

BigInt :: BigInt(const String & s){
    int p = s.size();
    if (p > max_size){
        std:: cout << "превышен лимит";
    }
    else{
        int i = 0;
        value = new int [max_size]();
        if (s[0] == '-'){
            sign = false;
            for (int j = 0; j < p; j++){
                if (p - i - 1 == 0){
                    break;
                }
                value[j] = s[p - i - 1] - '0';
                i++;
            }
        }
        else{
            sign = true;
            for (int j = 0; j < p; j++){
                value[j] = s[p - i - 1] - '0';
                i++;
            }
        }
    }
}

BigInt :: BigInt(int num) {
    sign = num >= 0;
    num = std::abs(num);
    value = new int[max_size]();
    int i = 0;
    while (num != 0) {
        value[i] = num % 10;
        num /= 10;
        i++;
    }
}

BigInt :: BigInt(const BigInt &other){
    value = new int[max_size]();
    sign = other.sign;
    for (int i = 0; i < max_size; i++) {
        value[i] = other.value[i];
    }
}

BigInt :: ~BigInt(){
    delete [] value;
}

BigInt& BigInt :: operator = (const BigInt& other){
    sign = other.sign;
    for (int i = 0; i < max_size; i++) {
        value[i] = other.value[i];
    }
    return *this;
}


// Вспомогательная функция, которая сравнивает абсолютные значения
// чисел не обращая внимания на знаки. Возвращает:
int compare_abs(const BigInt& left, const BigInt& right) {
    for (int i = BigInt::max_size - 1; i >= 0; i--) {
        if (left.value[i] > right.value[i]) {
            return 1;
        } else if (left.value[i] < right.value[i]) {
            return -1;
        }
    }
    return 0;
}

bool operator == (const BigInt& left, const BigInt& right) {
    int comp = compare_abs(left, right);

    return (left.sign == right.sign) && (comp == 0);
}

bool operator < (const BigInt& left, const BigInt& right) {
    if (left.sign && !right.sign) {
        return false;
    }
    if (!left.sign && right.sign) {
        return true;
    }

    int comp = compare_abs(left, right);

    if (left.sign) {
        return comp == -1;
    } else {
        return comp == 1;
    }
}

bool operator > (const BigInt& a, const BigInt& b) {
    if (a < b || a == b){
        return false;
    }
    else {
        return true;
    }
}

BigInt abs_plus(const BigInt& left, const BigInt& right) {
    BigInt res; // Инициализируем ноль.

    // Эта переменная есть десяток, который переносится со сложением.
    bool additional_one = false;
    for (int i = 0; i < BigInt::max_size; i++) {
        int digit = left.value[i] + right.value[i];
        if (additional_one) {
            // Перенос предыдущего десятка.
            digit++;
        }
        if (digit >= 10) {
            // Происходит переход десятка
            additional_one = true;
            digit -= 10;
        }
        else {
            additional_one = false;
        }
        res.value[i] = digit;
    }
    //проверка на оуверфлоу
    assert(!additional_one);
    return res;
}

// эта операция считает, что: |left| >= |right|.
BigInt abs_minus(const BigInt& left, const BigInt& right) {
    int comp = compare_abs(left, right);
    // Проверка |left| >= |right|.  я не использую оператор сравнения, так как
    // оператор сравнения учитывает знаки, а тут знаки мы игнорируем.
    assert(comp >= 0);
    BigInt res;
    bool minus_one = false;
    for (int i = 0; i < BigInt::max_size; i++) {
        int digit = left.value[i] - right.value[i];
        if (minus_one) {
            digit--;
        }
        if (digit < 0) {
            digit += 10;
            minus_one = true;
        } else {
            minus_one = false;
        }
        res.value[i] = digit;
    }
    return res;
}

BigInt operator + (const BigInt& left, const BigInt& right) {
    if (left.sign == right.sign) {
        // Одинаковые знаки - используем сложение модулей и потом просто приставим нужный знак.
        BigInt res = abs_plus(left, right);
        res.sign = left.sign;
        return res;
    }

    // Разные знаки.
    int comp = compare_abs(left, right);
    if (comp == 0) {
        return ZERO;
    }

    BigInt res;
    if (comp == 1) {
        // |left| > |right|
        res = abs_minus(left, right);
        res.sign = left.sign;
    } else {
        // |right| > |left|
        res = abs_minus(right, left);
        res.sign = right.sign;
    }

    return res;
}

BigInt operator - (const BigInt& left, const BigInt& right) {
    return left + (-right);
}

BigInt operator - (const BigInt& num) {
    BigInt num_copy = num;
    num_copy.sign = !num.sign;
    return num_copy;
}

BigInt& BigInt :: operator++() {
    *this = *this + ONE;
    return *this;
}

BigInt& BigInt :: operator--() {
    *this = *this - ONE;
    return *this;
}

int BigInt :: calculate_length() const {
    for (int i = max_size - 1; i >= 0; i--) {
        if (value[i] != 0) {
            return i + 1;
        }
    }
    return 0;
}

std::ostream & operator << (std::ostream &out, const BigInt& num){
    int length = num.calculate_length()

    if (length == 0) {
        std::cout << 0;
    }

    if (!num.sign){
        std::cout << '-';
    }

    for (int i = length - 1; i >= 0; i--){
        std::cout << num.value[i];
    }
    return out;
}
