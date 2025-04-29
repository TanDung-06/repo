#include<iostream>
using namespace std;

int minlength(int arr[], int n, int k); //Khai báo hàm.
int main() {
	int n; //Số phần tử mảng.
	cin >> n;
	int* p = new int[n];   //Nhập giá trị các phần tử mảng
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	int target;   //Tổng.
	cin >> target;
	cout << endl << minlength(p, n, target) << endl; //In ra độ dài tối thiểu mảng con có tổng các phần tử >= target.
	delete[] p;
	system("pause");
	return 0;
}

int minlength(int arr[], int n, int k) { //Định nghĩa hàm.
	int tong = 0;   //Tổng phần tử.
	int min = n-1;  //Dùng để in ra độ dài mảng con thỏa điều kiện bài toán.
	for (int i = 0;i < n;i++) {  
		if (arr[i] == k)  return 1; //Trả về 1 trong trường hợp arr[i]=k.
		tong += arr[i];
	}
	if (tong == k)  return n;   //Trả về n là độ dài mảng con thỏa tổng các phần tử bằng k.
	if (tong < k) return 0;  //Trả về 0 khi không tìm thấy mảng con thỏa.

	for (int i = 0;i < n-1;i++) { //Mảng con bắt đầu bằng phần tử arr[i].
		tong = arr[i]; 
		int length = 1; //Độ dài mảng con.
		for (int j = i + 1;j < n;j++) { //Tìm các phần tử tiếp theo bắt đầu từ arr[i].
			length++;
			if (tong + arr[j] >= k) {  //Điều kiện dừng vòng lặp.
				if (min > length)  min = length; //So sánh với độ dài các mảng con thỏa trước đó.Nếu nhỏ hơn thì gán giá trị.
				break; //Dừng vòng for. 
			}
			tong += arr[j]; //Cộng giá trị arr[j] vào tong khi chưa > k.
		}
	}
	return min;   //Trả về độ dài nhỏ nhất của mảng con thỏa.
}