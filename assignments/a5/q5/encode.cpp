#include "encode.h"
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAX_DICT_SIZE = 256;

/**
 * This can be much better:
 *  - store 2 12 bit dictionary keys in 3 unsigned chars
 *  - BWT
 *  - Use 0-31 in nextCode
 */

/**
 * Compress the source text into result.

 * This function is responsible for allocating result.
 * The caller is responsible for freeing result.
 * Compress returns the length of the result.
 */
unsigned int Encode::Compress(const string &source, unsigned char *&result) {
    vector<int> codes;
    string w;
    unsigned int nextCode;

    // Intial dictionary for range given
    unordered_map<string, int> dict(MAX_DICT_SIZE);
    for (nextCode = 32; nextCode < 126; nextCode++) {
        dict[string(1, nextCode)] = nextCode;
    }

    for (string::const_iterator it = source.begin(); it != source.end(); ++it) {
        char K = *it;
        string wK = w + K;

        // Not found in dictionary
        if (dict.find(wK) == dict.end()) {
            codes.push_back(dict[w]);

            if (nextCode < MAX_DICT_SIZE) {
                dict.insert(make_pair(wK, nextCode++));
            }
            w = K;

        // Found
        } else {
            w = wK;
        }
    }

    if (!w.empty()) {
        codes.push_back(dict[w]);
    }

    result = (unsigned char *) malloc(source.length());
    unsigned char *it = result;
    for (int i = 0; i < codes.size(); i++) {
        *it++ = (unsigned char) codes.at(i);
    }

    return codes.size();
}

/**
 * Decompress codedText with the given length into a string.
 *
 * Returns the decoded text as a string.
 * Assumes codedText is not null, length > 0.
 */
string Encode::Decompress(unsigned char *codedText, unsigned int length) {
    unsigned int nextCode;

    // Intial dictionary for range given
    unordered_map<int, string> dict(MAX_DICT_SIZE);
    for (nextCode = 32; nextCode < 126; nextCode++) {
        dict[nextCode] = string(1, nextCode);
    }

    string s(1, *codedText);
    string result = s;
    for (int i = 1; i < length; i++) {
        unsigned char code = *(codedText + i);
        string s_prev = s;
        if (code == nextCode) {
            s = s_prev + s_prev[0];
        } else {
            s = dict[(int) code];
        }

        result += s;

        if (nextCode < MAX_DICT_SIZE) {
            dict.insert(make_pair(nextCode++, s_prev + s[0]));
        }
    }

    return result;
}

/**
 * Set the k-th bit of the unsigned char (data) to 1.
 * Assumes data is initially 0.
 *
 * Examples:
 *  - SetBit(0, data) --> data = 0000 0001
 *  - SetBit(1, data) --> data = 0000 0010
 *  - SetBit(2, data) --> data = 0000 0100
 */
void Encode::SetBit(unsigned int k, unsigned char *data) {
    *data |= (1 << k);
}
/*
int main() {
    Encode encode;
    string source = "betty bought a bit of better butter";
    unsigned char *codedText;
    string decodedText;

    int length = encode.Compress(source, codedText);
    for (int i = 0; i < length; i++) {
        cout << ((int) *(codedText + i)) << " ";
    }
    cout << endl;

    decodedText = encode.Decompress(codedText, length);
    for (int i = 0; i < decodedText.length(); i++) {
        cout << decodedText[i];
    }
    cout << endl;

    delete codedText;

    return 0;
}
*/
