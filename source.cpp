#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>

#include "Console.h"

std::vector<std::string> split(std::string str, std::string sep) {
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current = strtok(cstr, sep.c_str());
    while (current != NULL) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}
int hex2size(std::string hex)
{
    int holder;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> holder;

    return static_cast<int>(holder);
}

std::string ConvFHex(std::string HexInput) {
    int len = HexInput.length();
    std::string newString;
    for (int i = 0; i < len; i += 2)
    {
        std::string byte = HexInput.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        newString.push_back(chr);
    }
    return newString;
}

int main() {
    std::string ConstantSize;
    std::string Bytecode = "01 02 05 70 72 69 6E 74 04 77 61 72 6E 01 05 00 00 01 0F A3 00 00 00 8C 02 01 00 8C 00 0A 00 8C 01 01 00 A8 00 09 00 A4 03 01 00 00 00 00 40 52 04 02 00 9F 03 02 01 A4 03 03 00 00 00 20 40 52 04 02 00 9F 03 02 01 8B 00 F7 FF 82 00 01 00 04 03 01 04 00 00 00 40 03 02 04 00 00 20 40 00 00 01 18 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 01 00 00 00 00 00";
    std::vector<std::string> Hex;
    Hex = split(Bytecode, " ");
    ConstantSize = (Hex[1]);

    std::string constr = "";

    int lk_r = 0;
    int init = 0;
    int clsr = 0;
    console::log("Constants", "");
    /* Because I failed to convert it into a string! */
    std::cout << hex2size(ConstantSize) << std::endl;
    if (Hex[0] != "01") {
        console::log("Error", "The bytecode given was not compiled successfully.");
        exit(0);
    }
    int topselctr       = 2;
    int b_s             = hex2size(Hex[topselctr]);
    int psr             = 1;
    bool brkr           = false;
    int conv            = 0;
    std::string temp_constr = "";

    for (int i = 0; i < hex2size(ConstantSize); i++)
    {
        for (int cur = topselctr + psr; cur < topselctr + b_s + 1; cur++)
        {
            temp_constr += ConvFHex(Hex[cur]);
            conv = cur;
        }
        if (!brkr)
        {
            psr++;
            brkr = true;
        }
        b_s = hex2size(Hex[conv + 1]) + 1;
        console::log("c" + std::to_string(i + 1), temp_constr + "\n");
        topselctr = conv++;
        temp_constr = "";
    }
    /* Gives the user time to analyze the results. */
    Sleep(INT_MAX);
}
