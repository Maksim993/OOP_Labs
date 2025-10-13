#include "my_function.h"
#include <cctype>
#include <iostream>

bool isPalindrome(const std::string & str) {
    int l = 0;
    int r = str.size() - 1;

    while (l < r) {
        //���������� ���������олрмлопмрлпм��� �����
        while (l < r && !isalnum(str[l])) {
            l++;
        }

        //���������� ����������� � ���������� ������� ������
        while (l < r && !isalnum(str[r])) {
            r--;
        }

        //���������� ������� � ������ ��������
        if (tolower(str[l]) != tolower(str[r])) {
            return false;
        }

        l++;
        r--;
    }

    return true;
}