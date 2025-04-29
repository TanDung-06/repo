#include<iostream>     //Khai báo thư viện để dùng hàm có sẵn.
using namespace std;   

int factorial(int n);  //Khai báo hàm.
int main() {
	int a;             //Khai báo biến a.
	cout << "Nhap so nguyen a: ";
	cin >> a;          //Nhập giá trị cho a.
	cout<<factorial(a)<<endl;      //Gọi hàm factorial và in ra kết quả tính n!.
	system("pause");
	return 0;
}
int factorial(int n) {  //Định nghĩa hàm tính n!
	if (n == 0)         //Điều kiện dừng của hàm factorial.
		return 1;       
	else                //Gọi hàm factorial với giá trị giảm đến khi thỏa điều kiện dừng rồi tính ngược lại để tìm n!.
		return n * factorial(n - 1);
}