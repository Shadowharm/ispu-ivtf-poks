//
// Created by Максим Прохоров on 05.03.2025.
//

#include "rle_proto.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string bwtTransform(const string& input, int &originalIndex) {
    int n = input.size();
    vector<pair<string, int>> rotations;

    for (int i = 0; i < n; i++) {
        rotations.emplace_back(input.substr(i) + input.substr(0, i), i);
    }

    sort(rotations.begin(), rotations.end());

    for (int i = 0; i < n; i++) {
        if (rotations[i].second == 0) {
            originalIndex = i;
            break;
        }
    }

    string bwt;
    for (const auto& rot : rotations) {
        bwt += rot.first[n - 1];
    }

    return bwt;
}

string rleEncode(const string& input) {
    string encoded;
    int count = 1;
    for (size_t i = 1; i <= input.size(); i++) {
        if (i < input.size() && input[i] == input[i - 1]) {
            count++;
        } else {
            encoded += input[i - 1] + to_string(count);
            count = 1;
        }
    }
    return encoded;
}

string rleDecode(const string& input) {
    string decoded;
    for (size_t i = 0; i < input.size(); i++) {
        char ch = input[i];
        string countStr;
        while (isdigit(input[++i])) {
            countStr += input[i];
        }
        i--;
        int count = stoi(countStr);
        decoded.append(count, ch);
    }
    return decoded;
}

string bwtInverse(const string& bwt, int originalIndex) {
    int n = bwt.size();
    vector<string> table(n, "");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[j] = bwt[j] + table[j];
        }
        sort(table.begin(), table.end());
    }

    return table[originalIndex];
}

void rle_proto() {
    string input;
    cout << "Введите строчку: ";
    cin >> input;

    int originalIndex; // индекс исходной строчки в матрице для bwt
    string bwt = bwtTransform(input, originalIndex);
    string compressed = rleEncode(bwt);

    cout << "Сжатая строчка: " << compressed << endl;

    string decompressed = rleDecode(compressed);
    string original = bwtInverse(decompressed, originalIndex);

    cout << "Исходная строчка: " << original << endl;

}
