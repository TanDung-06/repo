#include<iostream>     //Khai báo thư viện để dùng hàm có sẵn.
using namespace std;

int fibonacci(int n);    //Khai báo hàm.
void out(int n,int i);   
int main() {
	int a,i=0;           //Khai báo biến a,biến i với giá trị =0.
	cout << "Nhap so nguyen n: ";    
	cin >> a;        //Nhập giá trị cho biến a.
	out(a, i);       //Gọi hàm out để in ra dãy n số fibonacci.
	cout << endl;    //Định dạng.
	system("pause");
	return 0;
}

int fibonacci(int n) {     //Viết hàm tính số Fibonacci (định nghĩa hàm).
	if (n<=1)
		return n;          //Trả về giá trị n khi n<=1 (điều kiện dừng đệ quy).
	else 
		return fibonacci(n - 1) + fibonacci(n - 2);  //Gọi đệ quy với giá trị n-1,n-2 đến khi thỏa điều kiện dừng rồi tính toán để tìm số Fiboonacci thứ n.   
}
void out(int n,int i) {    //Viết hàm in ra dãy n số Fibonacci (định nghĩa hàm).
	if (i >= n)  return;   //Thoát khỏi hàm out khi if thỏa (điều kiện dừng của đệ quy).
	else {                 //In ra số fibonacci, rồi gọi đệ quy với biến i tăng thêm 1 đơn vị đến khi thỏa điều kiện dừng. 
		cout << fibonacci(i) << " ";  
		out(n, i + 1);
	}
}