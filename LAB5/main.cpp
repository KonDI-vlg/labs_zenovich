#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


ifstream in;


string preprocessString(const string& s) {
    string result = "#";
    for (char c : s) {
        result += c;
        result += "#";
    }
    return result;
}

string findLongestPalindrome(const string& s) {
    string str = preprocessString(s);
    int n = str.length();
    vector<int> P(n, 0); // массив для хранения длин палиндромов

    int center = 0; // текущий центр самого длинного палиндрома
    int right = 0;  // правая граница самого длинного палиндрома

    for (int i = 0; i < n; ++i) {
        int mirror = 2 * center - i;

        if (i < right) {
            P[i] = min(right - i, P[mirror]);
        }

        // Расширение текущего палиндрома
        int a = i + (1 + P[i]);
        int b = i - (1 + P[i]);

        while (a < n && b >= 0 && str[a] == str[b]) {
            ++P[i];
            ++a;
            --b;
        }

        // Обновление центра и границы самого длинного палиндрома
        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    // Нахождение максимальной длины палиндрома в P
    int maxLen = 0;
    int centerIndex = 0;
    for (int i = 0; i < n; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }

    // Получение самого длинного палиндрома из исходной строки
    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    string input;

    in.open("input.txt");
    in >> input;

    string longestPalindrome = findLongestPalindrome(input);
    cout << "Самый длинный палиндром: " << longestPalindrome << endl;

    // Находим количество символов, которые нужно вычеркнуть
    int charsToRemove = input.length() - longestPalindrome.length();
    cout << "Необходимо вычеркнуть " << charsToRemove << " символов." << endl;

    return 0;
}
