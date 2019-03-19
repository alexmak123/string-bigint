#include "string.h"

String :: String() {
    data = NULL;
    length = 0;
    capasity = 0;
}

String :: String(const String & a) {
    length = a.length;
    capasity = a.capasity;
    data = new char [capasity];
    for (size_t i = 0; i < length; i++) {
        data[i] = a.data[i];
    }
}

String :: String(const char * a) {
    size_t strlen = 0;
    while (a[strlen] != '\0') {
        strlen++;
    }
    length = strlen;
    capasity = length;
    data = new char [capasity];
    for (size_t i = 0 ; i < length; i++) {
        data[i] = a[i];
    }
}

void String :: increase_capasity() {
    if (capasity == 0){
        capasity = 1;
        length = 0;
        data = new char [1];
    }
    int cap = capasity * 2;
    char* data2 = new char [cap];
    for (size_t i = 0; i < length; i++) {
        data2[i] = data[i];
    }
    delete [] data;
    data = data2;
    capasity = cap;
}

String :: ~String (){
    delete [] data;
    capasity = 0;
    length = 0;
}

int String :: size() const{
    return length;
}

String String::substr(size_t pos, size_t len) const {
    String b;
    b.capasity = len;
    b.length = len;
    b.data = new char [capasity];
    size_t j = 0;
    for (size_t i = pos; i < len + pos; i++){
        b.data[j] = data[i];
        j++;
    }
    return b;
}

char& String :: operator [] (size_t index){
    return data[index];
}

const char& String :: operator [] (size_t index) const{
    return data [index];
}

String& String :: operator = (const String& a){
    this->length = a.length;
    this->capasity = a.capasity;
    delete[] this->data;
    this->data = new char [capasity];
    for (size_t i = 0; i < a.length; i++){
        this->data[i] = a.data[i];
    }
    return *this;
}

String& String :: operator += (const String& a){
    increase_capasity();
    while (a.capasity >= capasity){
        increase_capasity();
    }
    for (size_t i = length; i < a.length + length; i++){
        this->data[i] = a.data[i - length];
    }
    this->length = this->length + a.length;
    return * this;
}

bool operator == (const String & a, const String & b){
    if (a.length == b.length){
        for (size_t i = 0; i < a.length; i++){
            if ( a.data[i] != b.data[i]){
                return false;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

String operator +(const String& a, const String& b){
    String s;
    s.capasity = a.capasity + b.capasity;
    s.length = a.length + b.length;
    s.data = new char [s.capasity];
    for (size_t i = 0; i < a.length; i++){
        s.data[i] = a.data[i];
    }
    for (size_t i = a.length; i < s.length; i++){
        s.data[i] = b.data[i - a.length];
    }
    return s;
}

std :: ostream & operator << (std::ostream &out, const String &obj){
    for (size_t i = 0; i < obj.length; i++){
        out << obj[i];
    }
    out << " ";
    return out;
}

std::istream & operator >> (std::istream &is, String &obj){
    for (size_t i = 0; i < obj.length; i++){
        is >> obj[i];
    }
    return is;
}

