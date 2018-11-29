#include "AecImp.h"

AecImp::AecImp()
{
#if defined(AES256)
    printf("Deciphering AES256\n");
#elif defined(AES192)
    printf("Deciphering AES192\n");
#elif defined(AES128)
    printf("Deciphering AES128\n");
#else
    printf("You need to specify a symbol between AES128, AES192 or AES256. Exiting");
    return 0;
#endif
    m_key = "1234567890123456";
};

AecImp::~AecImp()
{
};

// prints string as hex
std::string AecImp::phex(uint8_t* str)
{
    char _tempbuf[200];
#if defined(AES256)
    uint8_t len = 32;
#elif defined(AES192)
    uint8_t len = 24;
#elif defined(AES128)
    uint8_t len = 16;
#endif

    unsigned char i;
    for (i = 0; i < len; ++i)
    {
        printf("%.2x", str[i]);
        sprintf(&_tempbuf[i*2],"%02x",str[i]);
    }
    printf("\n");
    return _tempbuf;
}

int AecImp::set_key(std::string &_key)
{
    if (_key.size() == 16)
    {
        m_key = _key;
    }
};

std::string AecImp::get_key(void)
{
    return  m_key;
};


std::string AecImp::encrypt_ecb(std::string _clearValue)
{
    std::string _result;
    uint8_t i;
    struct AES_ctx ctx;
    //AES_init_ctx(&ctx, key);
    AES_init_ctx(&ctx, (uint8_t *)m_key.c_str());
    
    int _size = _clearValue.size();

    for (i = 0; i < _size/16 + 1; ++i)
    {
      AES_ECB_encrypt(&ctx, (uint8_t *)_clearValue.c_str() + (i * 16));
      _result = _result + phex((uint8_t *)_clearValue.c_str() + (i * 16));
    }
    return _result;
};

//解密
std::string AecImp::decrypt_ecb(std::string _secretValue)
{
    int i = 0;
    int _size = 0;
    uint8_t *_value = (uint8_t *)_secretValue.c_str();
    //uint8_t key[16] = "1234567890123456";
    //uint8_t in[] = {0x6c,0xa6,0x50,0x72,0x26,0xfb,0x0c,0xa5,0x78,0x80,0x39,0x6e,0x05,0x8e,0xad,0x8b,0xd2,0x38,0x3c,0xb6,0xcc,0x41,0x43,0xd9,0xad,0x40,0xb8,0x50,0x96,0x3c,0x95,0x14,0x24,0xbe,0xb3,0x0f,0xde,0x54,0x8c,0xa7,0x27,0x75,0x93,0x66,0x83,0x81,0x30,0x33,0x96,0x74,0x56,0xdf,0x4a,0xf1,0x95,0xd9,0x5e,0xe5,0xa2,0x88,0xda,0x13,0x63,0x5f};
    struct AES_ctx ctx;
    //AES_init_ctx(&ctx, key);
    AES_init_ctx(&ctx, (uint8_t *)m_key.c_str());
    _size = _secretValue.size();
    for (i = 0; i < _size/16 ;i++)
    {
        AES_ECB_decrypt(&ctx, &(_value[16*i]));
    }
    return (const char *)_value;
};

//十六进制字符串传十六进制数
std::string AecImp::HexStrToHex(const std::string _str, const unsigned int _size)
{
    std::string _vstr;
	_vstr = _str;
    std::string _rstr;
    unsigned char _ch;
	while (_vstr.size() < _size*2)
	{
		_vstr = _vstr + '0';
	}
	for (unsigned int _i = 0; _i < _size; _i++)
	{
        _ch  = IntStrToBcd(_vstr.substr(_i*2, 2));
		_rstr.append(1,_ch);

	}

	return _rstr;
};

int AecImp::IntStrToBcd(const std::string _str)
{
	int _i = 0;
	int _len = 0;
	int _num = 0;
	int _val = 0;
	
	_len = _str.size();
	if (_len <= 0)
	{
		return 0;
	}
	_i = 0;
	if (_str[0] == '-')
	{
		_i = 1;
	}
	while (_i < _len)
	{
		if ((_str[_i] >= 'A') && (_str[_i] <= 'F'))
		{
			_val = (int)(_str[_i] - 'A' + 10);
		}
		else
		{
			if ((_str[_i] >= 'a') && (_str[_i] <= 'f'))
			{
				_val = (int)(_str[_i] - 'a' + 10);
			}
			else
			{
				_val =(int)(_str[_i] - '0');
			}
		}

		_num = (_num << 4) + _val;
		_i++;
	}
	if (_str[0] == '-')
	{
		_num *= -1;
	}

	return _num;
};
