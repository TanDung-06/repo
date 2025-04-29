#include<iostream>
using namespace std;

bool sum(int a[], int n, int k); //Khai báo hàm.
int main() {
	int n;  //Số phần tử mảng
	cin >> n;
	int* p = new int[n];  //Nhập giá trị các phần tử mảng.
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	int target;  //Tổng hai phần tử trong mảng cần tìm.
	cin >> target;
	if (sum(p, n, target)) {   //Nếu thỏa hàm sum thì in ra Yes còn không thì in ra No.
		cout << "Yes" << endl;
	}
	else cout << "No" << endl;
	system("pause");
	return 0;
}

bool sum(int a[], int n, int k) { //Định nghĩa hàm.
	int* le = a;   //Con trỏ le trỏ tới a[0].
	int* ri = a + n - 1;   //Con trỏ ri trỏ tới a[n-1].

	while (le < ri) {    //Vòng lặp để hai con trỏ trỏ tới hai phần tử trong mảng có tổng bằng k.
		if (*le + *ri == k)   //Nếu tìm thấy trả về true và dừng hàm.
			return true;
		else if (*le + *ri < k) {  //Tăng địa chỉ của con trỏ le hoặc giảm địa chỉ của con trỏ ri, rồi tiếp tục kiểm tra.
			le = le + 1;
		}
		else ri = ri - 1;
	}
	return false; //Trả về false nếu không tìm thấy.
}

