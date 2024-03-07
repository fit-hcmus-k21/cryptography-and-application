/*
Đề bài:
    - Tích các mssv của nhóm lại và modulo cho 197
    - Dùng thuật toán euclide mở rộng để tìm phần tử nghịch đảo của kết quả trên cho Z197,

*/

#include <bits/stdc++.h>
using namespace std;

int calculateProductModulo(vector<int> nums, int m) {
    int res = 1;
    for (int x : nums) {
        res = (res * (x % m)) % m;
    }
    return res;
}

int extendedEuclidean(int a, int m) {
    int x2 = 0, x1 = 1;
    int r = m % a;
    int q = m / a;

    while (r > 0) {
        int x = x2 - q * x1;
        x2 = x1;
        x1 = x;
        m = a;
        a = r;
        q = m / a;
        r = m % a;

    }

    return x1;
}




int main () {
    vector<int> nums;
    
    string numsStr; 
    cout << "Enter numbers, separated by space: ";
    getline(cin, numsStr);
    stringstream ss(numsStr);

    int num;
    while (ss >> num) {
        nums.push_back(num);
    }

    int m;
    cout << "Enter modulo: ";
    cin >> m;

    int prodMod = calculateProductModulo(nums, m);
    cout << "Product Modulo " << prodMod << endl;
    cout << "Inverse of  " << prodMod << ": " << extendedEuclidean(prodMod, m) << endl;

    return 22;
    
}