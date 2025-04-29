#include<iostream>
using namespace std;

bool Sort(int a[], int n);  //Khai báo hàm.
int main() {
	int n;    //Khai báo biến n.
	cout << "Nhap so phan tu mang: ";
	cin >> n;
	int* p = new int[n];    //Khai báo con trỏ mảng có n phần tử.
	for (int i = 0;i < n;i++) {  //Nhập giá trị cho các phần tử trong mảng.
		cin >> p[i];
	}
	if (Sort(p, n))     //In ra kết quả là mảng đã sắp xếp hay mảng chưa sắp xếp.
		cout << "Mang da sap xep! " << endl;
	else
		cout << "Mang chua sap xep! " << endl;
	delete[] p;
	system("pause");
	return 0;
}

bool Sort(int arr[], int n) {  //Định nghĩa hàm kiểm tra xem mảng đã sắp xếp chưa.
	if (n == 0 or n == 1)      //Điều kiện dừng của hàm và trả về true.
		return true;           
	if (arr[0] > arr[1])      //Điều kiện dừng của hàm và trả về false.
		return false;

	return Sort(arr + 1, n - 1); //Gọi hàm đệ quy Sort khi độ dài mảng đang xét >1 và arr[0]<arr[1] thỏa.
}