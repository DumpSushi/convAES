// convertAES.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

#include <openssl/aes.h>
#include <ImageHlp.h>

#pragma comment(lib, "imagehlp.lib")
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

int main()
{
    using namespace std;

    static const size_t	iv_size = 16;
    static const size_t	key_size = 16;
    static const char*	iv_str = "0123456789abcdef";
    static const char*	key_str = "abcdefghij012345";

    // 変換テストデータ。
    const size_t    dataSize = 32;
    const size_t    buffSize = dataSize + 32;
    unsigned char   data[dataSize];
    unsigned char   encryptData[buffSize];
    unsigned char   decryptData[buffSize];
    for (size_t i = 0; i < dataSize; ++i)
    {
        data[i] = static_cast<char>(i);
    }
    memset(encryptData, 0, sizeof(encryptData));
    memset(decryptData, 0, sizeof(decryptData));

    cout << "BaseData" << endl;
    for (size_t i = 0; i < dataSize; ++i)
    {
        unsigned char   tmp = data[i];
        //cout << hex << setw(2) << setfill('0') << tmp << ", ";
        printf("%02x, ", tmp);
        if ((i & 0x07) == 7)
        {
            cout << endl;
        }
    }
    cout << endl << endl;

    // encrypt.
    {
        unsigned char	aes_iv[iv_size];
        unsigned char	aes_key[key_size];
        memcpy_s(aes_iv, iv_size, iv_str, iv_size);
        memcpy_s(aes_key, key_size, key_str, key_size);
        AES_KEY encryptKey;
        AES_set_encrypt_key(aes_key, 128, &encryptKey);
        AES_cbc_encrypt(data, encryptData,
            dataSize, &encryptKey, aes_iv, AES_ENCRYPT);

        cout << "EncrytData" << endl;
        for (size_t i = 0; i < sizeof(encryptData); ++i)
        {
            unsigned char   tmp = encryptData[i];
            //cout << hex << setw(2) << setfill('0') << tmp << ", ";
            printf("%02x, ", tmp);
            if ((i & 0x07) == 7)
            {
                cout << endl;
            }
        }
        cout << endl << endl;
    }


    // decrypt.
    {
        unsigned char	aes_iv[iv_size];
        unsigned char	aes_key[key_size];
        memcpy_s(aes_iv, iv_size, iv_str, iv_size);
        memcpy_s(aes_key, key_size, key_str, key_size);
        AES_KEY decryptKey;
        AES_set_decrypt_key(aes_key, 128, &decryptKey);
        AES_cbc_encrypt(encryptData, decryptData,
            dataSize, &decryptKey, aes_iv, AES_DECRYPT);
        cout << "DecryptData" << endl;
        for (size_t i = 0; i < sizeof(decryptData); ++i)
        {
            unsigned char   tmp = decryptData[i];
            //cout << hex << setw(2) << setfill('0') << tmp << ", ";
            printf("%02x, ", tmp);
            if ((i & 0x07) == 7)
            {
                cout << endl;
            }
        }
        cout << endl;
    }

    system("pause");

    return 0;
}
