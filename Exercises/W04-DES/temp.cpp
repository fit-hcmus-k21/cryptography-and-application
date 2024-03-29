


#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
#define maxM 1000

const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4

};

const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

string decToBinary(int n) {
	string res = "";
	int binaryNum[8] = { 0 };
	int i = 0;
	while (n > 0) {
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}
	for (int j = 7; j >= 0; j--) {
		res += to_string(binaryNum[j]);

	}
	return res;
}

string charToBinary(string key) {
	string res = "";
	for (int i = 0; i < key.length(); i++) {
		res += decToBinary(int(key[i]));
	}
	return res;

}
int  stringBinaryToHex(string b) {
	int res = 0;
	for (int i = 0; i < b.length(); i++) {
		if (b[i] == '1') {
			res += pow(2, 7 - i);
		}
	}
	return res;
}


string shift_left_once(string key_chunk) {
	string shifted = "";
	for (int i = 1; i < 28; i++) {
		shifted += key_chunk[i];
	}
	shifted += key_chunk[0];
	return shifted;
}

string shift_left_twice(string key_chunk) {
	string shifted = "";
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 28; j++) {
			shifted += key_chunk[j];
		}
		shifted += key_chunk[0];
		key_chunk = shifted;
		shifted = "";
	}
	return key_chunk;
}
vector<string> KeySchedule(string key) {
    vector<string> res;
	key = charToBinary(key);
	
	string perm_key = "";
	for (int i = 0; i < 56; i++) {
		int temp = (PC1[i] - 1) / 8;
		perm_key += key[PC1[i] - 1 - temp]  ;
	}

	string left = perm_key.substr(0, 28);
	string right = perm_key.substr(28, 28);

    cout << "\nafter first permute Left: " ;
    for (int i = 0; i < 28; i++) {
        cout << left[i] ;
        if ((i+1) % 8 == 0) {
            cout << " ";
        }
    }
        cout << "\nafter first permute Right: " ;
    for (int i = 0; i < 28; i++) {
        cout << right[i] ;
        if ((i+1) % 8 == 0) {
            cout << " ";
        }
    }

    cout << endl;

	for (int i = 0; i < 16; i++) {
	
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			left = shift_left_once(left);
			right = shift_left_once(right);
		}
	
		else {
			left = shift_left_twice(left);
			right = shift_left_twice(right);
		}

		string combined_key = left + right;
		string round_key = "";
	
		for (int i = 0; i < 48; i++) {
			round_key += combined_key[PC2[i] - 1];
		}
		res.push_back( round_key );
		cout << "Key " << i + 1 << ": " << res[i] << endl;
	}

    return res;
}

int main()
{
    string Key = "abcdefgh";
    vector<string> Keys = KeySchedule(Key);

	for (int i = 0; i < 16; i++) {
		string str1 = Keys[i].substr(0, 8);
		string str2 = Keys[i].substr(8, 8);
		string str3 = Keys[i].substr(16, 8);
		string str4 = Keys[i].substr(24, 8);
		string str5 = Keys[i].substr(32, 8);
		string str6 = Keys[i].substr(40, 8);
		

		int int1 = stringBinaryToHex(str1);

		int int2 = stringBinaryToHex(str2);

		int int3 = stringBinaryToHex(str3);

		int int4 = stringBinaryToHex(str4);

		int int5 = stringBinaryToHex(str5);

		int int6 = stringBinaryToHex(str6);
	
		cout << "SubKey " <<std::dec<< i << ": ";

		cout<< std::hex << int1 <<" "<<int2<<" "<<int3<<" "<<int4<<" "<<int5<<" "<<int6<<endl;
		



	}


    return 0;
}