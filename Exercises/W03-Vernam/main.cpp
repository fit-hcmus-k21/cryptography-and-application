/*
Đề bài:
- Xây dựng các hàm Vernam với biến thể mod 26 để chạy chương trình main
*/

#include <bits/stdc++.h>
using namespace std;

string keyGen(int n)
{
    string key = "";
    for (int i = 0; i < n; i++)
    {
        int code = rand() % 1000;
        bool uppercase = rand() % 2;
        key += uppercase ? 'A' + code % 26 : 'a' + code % 26;
    }
    return key;
}

string vernamEnc(string plaintext, string key)
{
    string cipher = "";

    for (int i = 0; i < key.length(); i++)
    {
        if (plaintext[i] == ' ')
        {
            cipher += ' ';
            continue;
        }
        char value = isupper(key[i]) ? 'A' : 'a';
        if (isupper(plaintext[i]))
        {
            cipher += 'A' + (plaintext[i] - 'A' + key[i] - value) % 26;
        }
        else
        {
            cipher += 'a' + (plaintext[i] - 'a' + key[i] - value) % 26;
        }
    }

    return cipher;
}

string vernamDec(string ciphertext, string key)
{
    string plain = "";

    for (int i = 0; i < key.length(); i++)
    {

        if (ciphertext[i] == ' ')
        {
            plain += ' ';
            continue;
        }

        char value = isupper(key[i]) ? 'A' : 'a';
        if (isupper(ciphertext[i]))
        {
            int code = (ciphertext[i] - 'A' - (key[i] - value));
            while (code < 0)
            {
                code += 26;
            }
            plain += 'A' + code;
        }
        else
        {
            int code = (ciphertext[i] - 'a' - (key[i] - value));
            while (code < 0)
            {
                code += 26;
            }
            plain += 'a' + code;
        }
    }

    return plain;
}

int main()
{
    string plain = "hElLo WoRld", cipher = "", key = "", temp = "";
    for (int i = 0; i < 16; i++)
    {
        key = keyGen(plain.length());
        cout << "Key: " << key << endl;
        cipher = vernamEnc(plain, key);
        cout << "Cipher: " << cipher << endl;
        temp = vernamDec(cipher, key);
        cout << "Plain: " << temp << endl;
        cout << endl;
    }

    return 22;
}
