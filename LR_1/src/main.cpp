#include <iostream>
#include <string>
#include "my_function.h"
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    string input;
    cout << "������� ������ ��� �������� �� ���������: ";
    getline(cin, input);

    if (isPalindrome(input)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}