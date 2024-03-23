/*
Đề bài:
- Xây dựng hàm tạo khóa "Key Schedule" để chạy đoạn mã sau:

[...]

- Gợi ý: cố gắng xây dựng hai hàm cơ bản (idx tính từ 0)
+ void replaceBit(unsigned char* s, size_t idx, bool v) gán giá trị v vào bit thứ idx của chuỗi s, ví dụ replaceBit("ab", 0, 1) -> "ac"

+ bool extractBit(unsigned char* s, size_t idx): trả ra giá trị bit thứ idx của chuỗi s, ví dụ extractBit("ab", 0) -> false

- Thuật toán sinh khóa vòng KS:
+ Key gốc sẽ được thực hiện hoán vị lựa chọn PC-1. Key được đánh số từ 1 - 64 từ trái qua phải
    -- Bảng hoán vị lựa chọn có hai phần, phần đầu dùng xác định C0, phần sau là D0.
+ Khóa vòng Kn (n: 1-16) được xác định theo nguyên tắc : Kn = PC-2(CnDn)
    -- Trong đó, Cn và Dn được tạo từ Cn-1 và Dn-1 bằng cách dịch trái các giá trị này với số bit được quy định
        --- Các vòng 1, 2, 9, 16: 1 bit
        --- Còn lại: 2 bits


*/

#include <bits/stdc++.h>
using namespace std;

const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,

    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32 };

void replaceBit(unsigned char *s, size_t idx, bool v)
{
    size_t byteIdx = idx / 8;
    size_t bitIdx = idx % 8;
    unsigned char mask = (1 << bitIdx);

    if (v) {
        s[byteIdx] |= mask;
    } else {
        s[byteIdx] &= ~mask;
    }
}

bool extractBit(unsigned char *s, size_t idx)
{
    size_t byteIdx = idx / 8;
    size_t bitIdx = idx % 8;
    unsigned char mask = (1 << bitIdx);

    return  s[byteIdx] & mask ;
}

void GenerateKey(unsigned char *L, unsigned char *R, int iterate_num, unsigned char* res) {

    cout << "come into Generate key func \n";

    // left shift L and R
    if (iterate_num == 1 || iterate_num == 2 || iterate_num == 9 || iterate_num == 16) {
        // left shift 1 bit
        bool value = extractBit(L, 0);
        *L = *L << 1;
        replaceBit(L, 27, value);

        value = extractBit(R, 0);
        *R = *R << 1;
        replaceBit(R, 27, value);

    } else {
        // left shift 2 bits
        bool valueBit1 = extractBit(L, 0);
        bool valueBit2 = extractBit(L, 1);
        *L = *L << 2;
        replaceBit(L, 26, valueBit1);
        replaceBit(L, 27, valueBit2);

        valueBit1 = extractBit(R, 0);
        valueBit2 = extractBit(R, 1);
        *R = *R << 2;
        replaceBit(R, 26, valueBit1);
        replaceBit(R, 27, valueBit2);
    }

    // permutation choice 2
    for (int i = 0; i < 48; i++) {
        size_t idx = PC2[i];
        bool value = 0;
        if (idx <= 28) {
            value = extractBit(L, idx - 1);
        } else {
            value = extractBit(R, idx % 28 - 1);
        }
        replaceBit(res, i, value);
    }

}

unsigned char **KeySchedule(unsigned char *key)
{
    cout << "come into key schedule func\n";

    unsigned char **Keys = new unsigned char*[16];
    unsigned char L[] = "0000";
    unsigned char R[] = "0000";
    unsigned char res[] = "000000";


    // permutation choice 1 -> L0 and R0
    for (int i = 0; i < 28; i++) {
        bool valueL = extractBit(key, PC1[i]-1);
        replaceBit(L, i, valueL);

        bool valueR = extractBit(key, PC1[i+28]-1);
        replaceBit(R, i, valueR);
    }

    for (int i = 0; i < 16; i++) {
        GenerateKey(L, R, i + 1, res);
        *Keys[i] = *res;
    }

    cout << "\n after key schedule: \n";

    return Keys;

}

int main()
{
    unsigned char Key[] = "abcdefgh"; // chuỗi 64 bits = 8 bytes = 8 character
    unsigned char **Keys = KeySchedule(Key);

    cout << "come here\n";

    // unsigned char str[] = "ab";
    // replaceBit(str, 8,1);
    // cout << str;

    // cout << "\nExtract bit: " << extractBit(str, 0);

    for (size_t k = 0; k < 16; k++)
    {
        cout << "SubKey " << k << ": \t";
        for (size_t i = 0; i < 6; i++)
        {
            cout << hex << (unsigned short)Keys[k][i] << " ";
        }
        cout << endl;
    }

    return 0;
}