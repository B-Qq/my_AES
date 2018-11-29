#ifndef AECIMP_H

#define AECIMP_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"

#define CBC 1
#define CTR 1
#define ECB 1

class AecImp
{
public:
    AecImp();
    virtual ~AecImp();
    std::string phex(uint8_t* str);
    //加密
    std::string encrypt_ecb(std::string _clearValue);
    //解密
    std::string decrypt_ecb(std::string _secretValue);
    //设置密码
    int set_key(std::string &_key);
    //获取密码
    std::string get_key(void);
    int IntStrToBcd(const std::string _str);
    std::string HexStrToHex(const std::string _str, const unsigned int _size);
private:
    std::string m_key;
};


#endif /* end of include guard: AECIMP_H */
