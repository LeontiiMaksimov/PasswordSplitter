#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <random>
#include <map>
#include <functional>
#include "bigint.h" // <3

#ifdef __unix__
#define conClear "clear"
#endif

#ifdef _WIN32
#define conClear "cls"
#endif

std::vector<bool> bigToBin(bigint m)
{
    std::vector <bool> vec;
    bigint two = 2, zero = 0;
    while (m > zero)
    {
        if (m % two == zero)
        {
            vec.push_back(0);
        }
        else
        {
            vec.push_back(1);
        }
        m /= 2;
    }
    std::reverse(vec.begin(), vec.end());
    return vec;
}

// base 95 to decimal
bigint from95ToDec(std::string num)
{
    bigint power = 1, out = 0;
    for (long long i = num.size() - 1; i >= 0; --i)
    {
        out += (num[i] - 32) * power;
        power *= 95;
    }
    return out;
}

//bigint to char
char bigToChar(bigint num)
{
    char out = 0;
    bigint zero = 0;
    while (num > zero)
    {
        out++;
        num -= 1;
    }
    return out;
}


//binary to decimal
bigint toDec(std::vector<bool> num)
{
    bigint current = 1, out = 0;
    for (long long i = num.size() - 1; i >= 0; --i)
    {
        if (num[i] == 1)
        {
            out += current;
        }
        current *= 2;
    }
    return out;
}

//decimal to base 95
std::string to95(bigint num)
{
    std::string out;
    char remainder;
    bigint zero = 0;
    bigint base = 95;
    while (num > zero)
    {
        if (num < base)
        {
            remainder = bigToChar(num);
            out.push_back(remainder + 32);
            num = 0;
        }
        else
        {
            remainder = bigToChar(num % base);
            num /= base;
            out.push_back(remainder + 32);
        }
    }
    std::reverse(out.begin(), out.end());
    return out;
}



// print a vector (bool)
void printVec(const std::vector<bool>& vec)
{
    for (bool elem : vec)
    {
        std::cout << elem;
    }
    std::cout << std::endl << std::endl << std::endl;
}

// find a complementary vector to XOR to the resultant
std::vector<bool> compVec(const std::vector<bool>& finalVec, const std::vector<bool>& parentVec)
{
    std::vector<bool> out(parentVec.size());
    for (long long i = 0; i < out.size(); ++i)
    {
        if (parentVec[i] ^ 0 == finalVec[i])
        {
            out[i] = 0;
        }
        else
        {
            out[i] = 1;
        }
    }
    return out;
}

// XOR vector operation
std::vector<bool> xorVec(const std::vector<bool>& vec1, const std::vector<bool>& vec2)
{
    std::vector<bool> vecOut(vec1.size());
    for (long long i = 0; i < vecOut.size(); ++i)
    {
        vecOut[i] = (vec1[i] ^ vec2[i]);
    }
    return vecOut;
}


// bolean vector -> char
char toChar(const std::vector<bool>& vec)
{
    short int i = 128;
    char out = 0;
    for (char elem : vec)
    {
        if (elem == 1)
        {
            out += i;
        }
        i /= 2;
    }
    return out;
}

// vector of vectors of binary values -> string
std::string toStr(const std::vector<bool>& vec)
{
    std::string out;
    std::vector<bool> temp(8);
    out.resize(vec.size() / 8);
    for (long long i = 0; i < vec.size() / 8; ++i)
    {
        for (long long j = 0; j < 8; ++j)
        {
            if (vec[i * 8 + j] == 1)
            {
                temp[j] = 1;
            }
            else
            {
                temp[j] = 0;
            }
        }
        out += toChar(temp);
    }
    return out;
}

// check if the char is valid
bool validVec(const std::vector<bool>& vec)
{
    char letter;
    letter = toChar(vec);
    if (letter < 127 && letter > 31)
    {
        return true;
    }
    return false;
}

// random boolean value generator
bool randomBool()
{
    static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
    return gen();
}

// random value generator (no filter)
std::vector<bool> genVec(long long len)
{
    std::vector<bool> vector;
    vector.resize(len);
    for (long long i = 0; i < len; ++i)
    {
        vector[i] = randomBool();
    }
    return vector;
}

// random value generator filtered **make more efficient**
std::vector<bool> genVecFiltered(long long len)
{
    long long batch = len / 8;
    std::vector<bool> batchVec(8, 0);
    std::vector<bool> vector;
    vector.resize(len);
    for (long long i = 0; i < len / 8; ++i)
    {
        while (!validVec(batchVec))
        {
            for (long long j = 1; j < 8; ++j)
            {
                batchVec[j] = randomBool();
            }
        }
        for (bool elem : batchVec)
        {
            vector.push_back(elem);
        }
        std::fill(batchVec.begin(), batchVec.end(), 0);
    }
    return vector;
}

// char -> boolean vector
std::vector<bool> toBinary(char m)
{
    std::vector <bool> vec;
    while (m > 0)
    {
        if (m % 2 == 0)
        {
            vec.push_back(0);
        }
        else
        {
            vec.push_back(1);
        }
        m /= 2;
    }
    while (vec.size() != 8)
    {
        vec.push_back(0);
    }
    std::reverse(vec.begin(), vec.end());
    return vec;

}

// string -> vector of vector of binary values
std::vector<bool> toVec(const std::string& str)
{
    std::vector<bool> out;
    out.resize(str.size() * 8);
    std::vector<bool> temp;
    for (long long i = 0; i < str.size(); ++i)
    {
        temp = toBinary(str[i]);
        for (short int j = 0; j < 8; ++j)
        {
            out[8 * i + j] = temp[j];
        }
    }
    return out;
}

// generate keys (not filtered) **optimize + dont save**
void genUnfiltered()
{
    long long n;
    std::string password;
    std::vector<std::vector<bool>> keys;
    std::cout << "Enter how many sub-passwords you want [min = 2]" << std::endl;
    std::cin >> n;
    keys.resize(n);
    std::system(conClear);
    std::cout << "Enter the password" << std::endl;
    std::cin >> password;
    std::system(conClear);
    std::vector<bool> parentVec(password.size() * 8);
    for (int i = 1; i < n; ++i)
    {
        keys[i] = genVec(password.size() * 8);
        if (i == 1)
        {
            parentVec = keys[1];
        }
        else
        {
            parentVec = xorVec(parentVec, keys[i]);
        }
    }
    keys[0] = compVec(toVec(password), parentVec);
    for (std::vector<bool> elem : keys)
    {
        printVec(elem);
    }
}

// decrypt **optimize + dont save**
void decrypt()
{
    long long n, maxSize = 0;
    std::string password, subPas;
    std::vector<std::vector<bool>> keys;
    std::vector<bool> out;
    std::vector<bool> tempVal;
    std::cout << "Enter how many sub-passwords you have [min = 2]" << std::endl;
    std::cin >> n;
    keys.resize(n);
    std::system(conClear);
    std::cout << "Enter all keys seperated by a space or enter" << std::endl;
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> subPas;
        tempVal = bigToBin(from95ToDec(subPas));
        keys[i] = tempVal;
    }
    for (std::vector<bool> elem : keys)
    {
        if (elem.size() > maxSize)
        {
            maxSize = elem.size();
        }
    }
    for (std::vector<bool>& elem : keys)
    {
        while (elem.size() < maxSize)
        {
            elem.push_back(0);
        }
    }
    out = keys[0];
    for (int i = 1; i < n; ++i)
    {
        out = xorVec(out, keys[i]);
    }
    std::cout << toStr(out) << std::endl;
    //std::cout << toStr(out) << std::endl;
}

// decrypt {input - decimal number} finish 
void decryptDec()
{
    long long n;
    std::string password;
    std::vector<std::vector<bool>> keys;
    std::vector<bool> out;
    std::string tempVal;
    std::cout << "Enter how many sub-passwords you have [min = 2]" << std::endl;
    std::cin >> n;
    keys.resize(n);
    std::system(conClear);
    std::cout << "Enter all keys seperated by a space or enter" << std::endl;
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> tempVal;
        for (char elem : tempVal)
        {
            if (elem == '0')
            {
                keys[i].push_back(0);
            }
            else
            {
                keys[i].push_back(1);
            }
        }
    }
    out = keys[0];
    for (int i = 1; i < n; ++i)
    {
        out = xorVec(out, keys[i]);
    }
    std::cout << toStr(out) << std::endl;
}

// generate keys (not filtered) **optimize + dont save**
void encrypt()
{
    long long n;
    std::string password;
    std::vector<std::vector<bool>> keys;
    std::cout << "Enter how many sub-passwords you want [min = 2]" << std::endl;
    std::cin >> n;
    keys.resize(n);
    std::system(conClear);
    std::cout << "Enter the password" << std::endl;
    std::cin >> password;
    std::system(conClear);
    std::vector<bool> parentVec(password.size() * 8);
    for (int i = 1; i < n; ++i)
    {
        keys[i] = genVec(password.size() * 8);
        if (i == 1)
        {
            parentVec = keys[1];
        }
        else
        {
            parentVec = xorVec(parentVec, keys[i]);
        }
    }
    keys[0] = xorVec(toVec(password), parentVec);
    for (std::vector<bool> elem : keys)
    {
        std::cout << to95(toDec(elem)) << std::endl;
        std::cout << std::endl;
    }

}

int main()
{
    std::string str;
    std::cout << "Enter 0 to make decrypt password and 1 to encrypt it" << std::endl;
    bool value;
    std::cin >> value;
    std::system(conClear);
    if (value)
    {
        encrypt();
    }
    else
    {
        decrypt();
    }
}
