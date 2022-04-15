#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <random>
#include <map>
#include <functional>

// bolean vector -> char
char toChar(std::vector<bool> vec)
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
std::string toStr(std::vector<bool> vec)
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
    if (toChar(vec)) < 127 && toChar(vec)) > 31)
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
    for (int i = 0; i < len; ++i)
    {
        vector[i] = randomBool();
    }
    return vector;
}

// random value generator filtered
std::vector<bool> genVecFiltered(long long len)
{
    long long batch = len / 8;
    std::vector<bool> batchVec(8, 0);
    std::vector<bool> vector;
    vector.resize(len);
    for (int i = 0; i < len / 8; ++i)
    {
        while (!validVec(batchVec))
        {
            for (int j = 1; j < 8; ++j)
            {
                batchVec[j] = randomBool();
            }
        }
        for (bool elem : batchVec)
        {
            vector.push_back(
    }
    return vector;
}

// char -> boolean vector
std::vector<bool> toBinary(char m)
{
    short int n = static_cast <short int>(m);
    std::vector <bool> vec;
    short int i = 128;
    while (n != 0)
    {
        if (n - i >= 0)
        {
            vec.push_back(1);
            n -= i;
        }
        else
        {
            vec.push_back(0);
        }
        i /= 2;
    }
    while (vec.size() < 8)
    {
        vec.push_back(0);
    }
    return vec;
}


// string -> vector of vector of binary values
std::vector<bool> to_vec(std::string str)
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



int main()
{
    std::string str;
    while (true)
    {
        std::cin >> str;
        str = toStr(genVec(184));
        for (char elem : str)
        {
            std::cout << elem;
        }
        std::cout << " ";
    }
}
