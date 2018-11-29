#include <iostream>
#include "AecImp.h"

int main(void)
{
    int exit = 0;
    std::string _key = "1234567890123456";
    std::string _value_temp;
    std::string plain_text= "{\"KEY_VER\":\"0102030405060708\",\"KEY_NUM\":\"3\",\"TKEY_NUM\":\"2\",\"SKEY_NUM\":\"3\",\"KEYS\":[{\"KEY\":\"0102030405\"},{\"KEY\":\"06070809\"}]}"; 
    std::string  _value = "8cdf9d7e4201fbb3926d07db7ebcf2ccc40740dda2bb88088b6a5d1f530ab251ae2cffd862e50609563c70ea4873c4d71c97bb5fcf9ce8106a47ded045b57879e70d9311a86a5a8139ccec7c78260a1efaa219adc0c2ade98c41cd4dc22a2764ffa468519222b85b297d05eb1a3c3d845e65e3ff88b3c6e0477be57a08c7e87f";
    AecImp *aes = new AecImp;
    _value_temp = aes->HexStrToHex(_value,_value.size()/2);
    aes->set_key(_key);
    std::cout << "encrypt_ecb:" << aes->encrypt_ecb(plain_text) << std::endl;
    std::cout << aes->decrypt_ecb(_value_temp) << std::endl;

    return exit;
}
