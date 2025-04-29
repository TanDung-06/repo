#include<iostream>
using namespace std;

int LinearSearchwithSentinel(int arr[], int n, int k); //Khai báo hàm.
int main() {
	int n;    //Số phần tử trong mảng.
	cin >> n; 
	int* p = new int[n];      //Nhập giá trị các phần tử trong mảng.
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	int k;  //Số cần tìm trong mảng.
	cin >> k;
	cout << endl << "Index: " << LinearSearchwithSentinel(p, n, k) << endl;    //In ra địa chỉ phần tử trong mảng có giá trị bằng k.
	delete[] p; 
	system("pause");
	return 0;
}
int LinearSearchwithSentinel(int arr[], int n, int k) {  //Định nghĩa hàm.
	int tam = arr[n - 1];  //Gán giá trị phần tử cuối mảng cho biến tam.
	arr[n - 1] = k;        //Gán giá trị k cho phần tử cuối mảng.
	int i = 0;  //Phần tử đầu tiên của mảng.
	while (arr[i] != k) {  //Tìm phần tử trong mảng có giá trị bằng k.
		i++;
	}
	arr[n - 1] = tam;  //Trả lại giá trị ban đầu cho phần tử cuối mảng.
	if (i < (n - 1) or arr[n - 1] == k)  //Trả về địa chỉ nếu thỏa điều kiện.
		return i;

	return -1;  //Trả về -1 khi không tìm thấy k trong mảng.
}