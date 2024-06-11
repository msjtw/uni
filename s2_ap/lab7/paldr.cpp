#include<iostream>

using namespace std;

typedef long long int ll;

string  str;

void rtrim(string s, int &len) {
	while(len > 0) {
		if(s[len-1] < 33) len--;
		else break;
	}
	s[len] = 0;
}

bool isreallypalin(int p, int q) {
	for(int i = p, j = q; i <= j; i++, j--) {
		if(str[i] != str[j]) return false;
	}
	return true;
}

int main() {
	int test, cs, len, i, j;
	ll h, hr, p, h1, hr1, p1;
	cin >> test;
	for(cs = 1; cs <= test; cs++) {
		cin >> str;
		len = str.length();
		rtrim(str, len);
		if(len == 0) puts("YES");
		else if(len & 1) puts("NO");
		else {
			for(i = 0; i < len; i++) {
				h = hr = 0; p = 1;
				h1 = hr1 = 0; p1 = 1;
				for(j = i; j < len; j++) {
					h = (31 * h + str[j]);
					hr = (hr + p * str[j]);
					p = (p * 31);

					h1 = (37 * h1 + str[j]);
					hr1 = (hr1 + p1 * str[j]);
					p1 = (p1 * 37);
					if(((j-i+1)&1) == 0 && h == hr && h1 == hr1) {
						i = j;
						break;
					}
				}
				if(j == len) break;
			}
			if(i == len) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}