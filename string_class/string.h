#include <iostream>


class String{
    friend bool operator == (const String &, const String &);
    friend String operator + (const String &, const String &);
    friend std::ostream & operator << (std::ostream &, const String &);
    friend std::istream & operator >> (std::istream &, String &);

  private:
    char *data;
    size_t capasity; // сколько символов могу впихнуть (вместимость)
    size_t length;

  public:
    String();
    String(const String &);
    String(const char * const);
    void increase_capasity( );
    ~String();
    int size();
    String substr(size_t pos, size_t len) const;
    char& operator[](size_t index);
    const char& operator[] (size_t index) const;
    String& operator = (const String &);
    String& operator += (const String &);
};
