#include<iostream>
using namespace std;

void triplet(int a[], int n);  //Khai báo hàm.
void sort(int a[], int n);
int main() {
	int n;    //Số phần tử mảng.
	cin >> n;
	int* p = new int[n];
	for (int i = 0;i < n;i++) {   //Nhập giá trị có phần tử trong mảng.
		cin >> p[i];
	}
	triplet(p, n);  //In ra 3 có tổng bằng 0.
	delete[] p;
	system("pause");
	return 0;
}

void sort(int a[], int n) { //Hàm sắp xếp các phần tử trong mảng tăng dần.
	int min, tam;
	for (int i = 0;i < n - 1;i++) {  
	    min =i;
		for (int j = i;j < n;j++) {
			if (a[j] < a[min])  min = j;  //Tìm phần tử nhỏ nhất trong khoảng từ i->n-1.
		}
		tam = a[i];    //Thực hiện swap.
		a[i] = a[min];
		a[min] = tam;
	}
}
void triplet(int a[], int n) {  //Hàm tìm và in ra 3 số có tổng =0.
	sort(a, n);     
	cout << "[ ";
	for (int i = 0;i < n - 2;i++) {  //Duyệt từ phần tử 0 đến n-2.
		if (i > 0 && a[i] == a[i - 1])   continue; //có xem chat gpt.Dùng để bỏ qua các trường hợp trùng lặp.

		int le = i + 1, ri = n - 1; //Khai báo biến le với giá trị ban đầu là i+1 và ri với giá trị n-1 với mỗi giá trị i.
		while (le < ri) {  //chạy vòng lặp while thì hai chỉ số le và ri.
			if (a[i] + a[le] + a[ri] == 0) {  //Điều kiện để in ra 3 số trong mảng có tổng bằng 0.
				cout << "[" << a[i] << "," << a[le] << "," << a[ri] << "]"<<" "; //In ra 3 số thỏa điều kiện.
				ri--;  //Giảm biến ri, tăng biến le để tìm các phần tử nằm giữa hai phần tử le ri ban đầu xem còn hai phần tử nào khác thỏa không.
				le++;
				while (le < ri && a[le] == a[le - 1])  le++; //có xem chat gpt.Dùng để bỏ qua các trường hợp trùng lặp.
				while (le < ri && a[ri] == a[ri + 1])  ri--; //có xem chat gpt.Dùng để bỏ qua các trường hợp trùng lặp.
			}
			else if (a[i] + a[le] + a[ri] > 0)    ri--;  //Khi chưa thỏa điều kiện tổng =0 thì tăng le nếu <0 và giảm ri nếu >0.
			else le++;
		}
	}
	cout << "]" << endl;
}
