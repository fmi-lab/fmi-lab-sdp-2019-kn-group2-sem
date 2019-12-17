#include <iostream>
// #include <pair>

using namespace std;

template <typename KEY, typename VALUE, int SIZE>
class Dictionary {
public:
	VALUE& operator[](KEY key) {
		int keyHash = hash(key);
		// check for collisions
		if (data[keyHash].first == key || data[keyHash].first == 0) {
			data[keyHash].first = key;
			data[keyHash].second;
		} else {
			// collision detected:
				// 1. hash2 and iterate
				// keyHash = (keyHash + 5) % SIZE;
				// 2. VALUE -> vector<VALUE>
		}
		return ;
	}

	const VALUE& operator[](KEY key) const {
		int keyHash = hash(key);
		KEY bucketKey = data[keyHash].first;
		if (bucketKey == key) {
			return data[keyHash].second;
		}
		throw "Key mismatch";
	}

	int hash(KEY key) {
		return key % SIZE;
	}

private:
	pair<KEY, VALUE> data[SIZE];
};


int main() {
	Dictionary<int, double, 20> dict;
	dict[5] = 5.1123;
	dict[1] = 2.13;
	dict[4] = 4.1123;
	dict[10024] = 5123.9888;

	cout << dict[5] << endl;
	cout << dict[1] << endl;
	cout << dict[4] << endl;
	// cout << dict[3] << endl;
	cout << dict[10024] << endl;

	return 0;
}







