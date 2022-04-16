#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
#include <random>
#include <map>
#include <functional>

#ifdef __unix__
    #define conClear "clear"
#endif

#ifdef _WIN32
    #define conClear "cls"
#endif


char randomChar() 
{
    static auto gen = std::bind(std::uniform_int_distribution<>(32, 126), std::default_random_engine());
    return gen();
}

std::string genStr(long long n)
{
    std::string str = "";
    for (long long i = 0; i < n; ++i)
    {
        str.push_back(randomChar());
    }
    return str;
}

void xorStr(std::string& str1, const std::string& str2)
{
    for (long long i = 0; i < str1.size(); ++i)
    {
        str1[i] = str1[i] ^ str2[i];
    }
}

void encrypt()
{
    long long n;
    std::string password, parentStr;
    std::vector<std::string> keys;
    std::cout << "Enter how many sub-passwords you want [min = 2]" << std::endl;
    std::cin >> n;
    keys.resize(n);
    std::system(conClear);
    std::cout << "Enter the password" << std::endl;
    std::cin >> password;
    std::system(conClear);
    for (int i = 1; i < n; ++i)
    {
        keys[i] = genStr(password.size());
        if (i == 1)
        {
            parentStr = keys[1];
        }
        else
        {
            parentStr = xorStr(parentStr, keys[i]);
        }
    }
    keys[0] = xorStr(password, parentStr);
    for (std::string elem : keys)
    {
        std::cout << elem << std::endl;
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
        // decrypt();
    }
}
