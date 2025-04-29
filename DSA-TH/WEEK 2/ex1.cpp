#include<iostream>
using namespace std;

int LinearSearch(int a[],int n, int k); //Khai báo hàm.
int main() {
	int n;      //Số lượng phần tử.
	cin >>n;
	int* p = new int[n]; //Nhập giá trị n phần tử.
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	int k;   //Số cần tìm trong dãy n số.
	cin >> k;
	cout << LinearSearch(p, n, k) << endl;  //In ra địa chỉ có giá trị phần tử bằng k.
	delete[] p;
	system("pause");
	return 0;
}

int LinearSearch(int a[],int n, int k) {  //Định nghĩa hàm.
	for (int i = 0;i < n;i++) { //Tìm phần tử k có trong mảng.
		if (a[i] == k) {        // Nếu có trả về địa chỉ i.
			return i;
		}
	}
	return -1;       //Không tìm thấy thì trả về -1.
}

