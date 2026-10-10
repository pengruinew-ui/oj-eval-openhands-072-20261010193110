#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    long long answer = 0;
    bool found = false;
    while (getline(cin, line)) {
        // Check for // comment
        size_t commentPos = line.find("//");
        string comment = (commentPos != string::npos) ? line.substr(commentPos + 2) : string();
        // Also handle block comment start and end on same line
        size_t blockStart = line.find("/*");
        size_t blockEnd = line.find("*/");
        if (blockStart != string::npos && blockEnd != string::npos && blockEnd > blockStart) {
            comment = line.substr(blockStart + 2, blockEnd - blockStart - 2);
        }
        // Search for the word "return" in the comment
        size_t retPos = comment.find("return");
        if (retPos != string::npos) {
            size_t pos = retPos + 6; // after "return"
            // skip non-digit and non-minus
            while (pos < comment.size() && !isdigit(comment[pos]) && comment[pos] != '-') ++pos;
            bool neg = false;
            if (pos < comment.size() && comment[pos] == '-') { neg = true; ++pos; }
            long long val = 0;
            while (pos < comment.size() && isdigit(comment[pos])) {
                val = val * 10 + (comment[pos] - '0');
                ++pos;
            }
            answer = neg ? -val : val;
            found = true;
            break;
        }
    }
    if (!found) {
        // fallback: find last integer in whole input
        cin.clear();
        cin.seekg(0);
        string all((istreambuf_iterator<char>(cin)), {});
        long long last = 0;
        bool any = false;
        for (size_t i = 0; i < all.size(); ++i) {
            if (isdigit(all[i]) || (all[i] == '-' && i + 1 < all.size() && isdigit(all[i+1]))) {
                bool neg = false;
                if (all[i] == '-') { neg = true; ++i; }
                long long val = 0;
                while (i < all.size() && isdigit(all[i])) {
                    val = val * 10 + (all[i] - '0');
                    ++i;
                }
                if (neg) val = -val;
                last = val;
                any = true;
            }
        }
        answer = any ? last : 0;
    }
    cout << answer;
    return 0;
}
