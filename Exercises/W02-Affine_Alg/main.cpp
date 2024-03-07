/*
Đề bài :
    - Thuật toán mã hóa Affine, cho nhập a, kiểm tra nếu a không khả nghịch thì thông báo nhập lại, nếu thỏa mãn thì tiến hành mã hóa
*/

#include <bits/stdc++.h>
using namespace std;

// hàm tìm ước chung lớn nhất
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// thuật toán euclide mở rộng tìm phần tử nghịch đảo
int extended_euclide(int a, int m)
{
    vector<int> Xi = {0, 1};
    int r = m % a;
    int q = m / a;
    while (r != 0)
    {
        int Xi_2 = Xi[0];
        int Xi_1 = Xi[1];
        int x = Xi_2 - q * Xi_1;
        Xi[0] = Xi_1;
        Xi[1] = x;
        m = a;
        a = r;
        r = m % a;
        q = m / a;
    }
    return Xi[1];
}

int modInverse(int a, int m)
{
    int i = extended_euclide(a, m);
    if (i < 0)
    {
        int k = i / m + 1;
        i = i + k * m;
    }
    return i;
}

// hàm mã hóa affine
string affineEncrypt(int a, int b, int m, string plaintext)
{
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i++)
    {
        if (plaintext[i] == ' ')
        {
            ciphertext += ' ';
        }
        else if (isupper(plaintext[i]))
        {
            ciphertext += (char)((a * (plaintext[i] - 'A') + b) % m + 'A');
        }
        else
        {
            ciphertext += (char)((a * (plaintext[i] - 'a') + b) % m + 'a');
        }
    }
    return ciphertext;
}

// hàm giải mã affine
string affineDecrypt(int a, int b, int m, string ciphertext)
{
    string plaintext = "";
    int aInverse = modInverse(a, m);
    for (int i = 0; i < ciphertext.length(); i++)
    {
        if (ciphertext[i] == ' ')
        {
            plaintext += ' ';
        }
        else if (isupper(ciphertext[i]))
        {
            plaintext += (char)(aInverse * (ciphertext[i] - 'A' - b + m) % m + 'A');
        }
        else
        {
            plaintext += (char)(aInverse * (ciphertext[i] - 'a' - b + m) % m + 'a');
        }
    }
    return plaintext;
}

int main()
{
    int a, b;
    int m = 26;
    bool isInvertible = false;

    // display menu with options
    while (true)
    {
        cout << "\n\n1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose option: ";
        int option;
        cin >> option;
        if (option == 1)
        {
            // get value of a and check if it is invertible
            do
            {
                cout << "Enter value of a | gcd(a, 26) = 1 : ";
                cin >> a;

                if (gcd(a, m) != 1)
                {
                    cout << "a is not invertible, please enter again!" << endl;
                }
                else
                {
                    isInvertible = true;
                }
            } while (!isInvertible);

            // generate b with random value
            srand(time(0));
            b = rand() % 26;

            // start encrypting
            string plaintext, ciphertext;
            cout << "Enter plaintext: ";
            cin.ignore();
            getline(cin, plaintext);

            cout << "\nCiphertext with k = (" << a << ", " << b << "): " << affineEncrypt(a, b, m, plaintext) << endl;
        }
        else if (option == 2)
        {
            // get a and b
            cout << "Enter value of a: ";
            cin >> a;
            cout << "Enter value of b: ";
            cin >> b;
            
            string ciphertext, plaintext;
            cout << "Enter ciphertext: ";
            cin.ignore();
            getline(cin, ciphertext);

            cout << "\nPlaintext with k = (" << a << ", " << b << "): " << affineDecrypt(a, b, m, ciphertext) << endl;
        }
        else if (option == 3)
        {
            return 22;
        }
        else
        {
            cout << "Invalid option, please choose again!" << endl;
        }
    }

    return 22;
}