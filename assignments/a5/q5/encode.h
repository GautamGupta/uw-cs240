#include <iostream>
#include <string>

using namespace std;

class Encode {
public:
    Encode() {};
    ~Encode() {};

    unsigned int Compress(const string &, unsigned char *&);
    string Decompress(unsigned char *, unsigned int);

private:
    void SetBit(unsigned int, unsigned char *);
};
