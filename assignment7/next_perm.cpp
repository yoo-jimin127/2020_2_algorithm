#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
	int cnt = 0;

	vector<int> v(4);

	for (int i = 0; i < 4; i++) {
		v[i] = i + 2;
	}

	do {
		cout << cnt + 1 <<" : ";
		for (int i = 0; i < 4; i++) {
			cout << v[i] << " ";
		}
		cout << endl;
		cnt++;
	} while (next_permutation(v.begin(), v.end()));


	cout << cnt;
	return 0;
}