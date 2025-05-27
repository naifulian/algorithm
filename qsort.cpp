#include <iostream>
#include <vector>

using namespace std;


void qsort(vector<int>& arr, int l, int r) {
	if(l >= r) return;
	int head = l, tail = r, stand = arr[l];
	while(head < tail) {
		while(head < tail && arr[tail] >= stand) {tail--;}
		if(head < tail) {
			arr[head] = arr[tail];
			head++;
		}
		while(head < tail && arr[head] <= stand) {head++;}
		if(head < tail) {
			arr[tail] = arr[head];
			tail--;
		}
	}
	arr[head] = stand;
	qsort(arr, l, head - 1);
	qsort(arr, head + 1, r);
	
}

void print_arr(const vector<int>& arr) {
	for(auto val : arr) {
		cout << val << " ";
	}
	cout << endl;
}

int main() {

	vector<int> arr = { 4, 1 , 5 , 6, 7, 9, 4, 2, 11, 5, 8};
	print_arr(arr);
	qsort(arr, 0, arr.size() - 1);
	print_arr(arr);
	return 0;

}
