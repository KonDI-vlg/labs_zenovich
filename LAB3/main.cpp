#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<size_t> prefix_function(string s)
{
    size_t n = s.length();
    vector<size_t> pi(n);

    for (size_t i = 1; i < n; ++i)
    {
        // ищем, какой префикс-суффикс можно расширить
        size_t j = pi[i - 1];
        while ((j > 0) && (s[i] != s[j])) // если этот нельзя расширить, то
            j = pi[j - 1];                // берем длину меньшего префикса-суффикса

        if (s[i] == s[j])
            ++j; // расширяем найденный префикс-суффикс
        pi[i] = j;
    }
    return pi;
}

int main()
{
    string word, sample;
    word = "ababcabcacab";
    sample = "abca";
    size_t sample_len = sample.size();
    sample = sample.append("$");
    sample = sample.append(word);
    cout << sample << endl;
    auto pf = prefix_function(sample);
    for (int i = 0; i < sample.length(); i++)
    {
        if (pf[i] == sample_len)
            cout << i - pf[i] - sample_len << ' ';
    }
    cout << endl;
}
