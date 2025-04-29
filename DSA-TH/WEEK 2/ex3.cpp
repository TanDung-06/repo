#include<iostream>
using namespace std;

int binary(int arr[], int le, int ri); //Khai báo hàm.
int main() {
	int n;   //Số phần tử trong mảng
	cin >> n;
	int* p = new int[n];  //Nhập giá trị cho n phần tử trong mảng.
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	cout << endl << binary(p, 0, n - 1) << endl;  //In ra số lần thay đổi mảng.
	system("pause");
	return 0;
}

int  binary(int arr[], int le, int ri) {   //Định nghĩa hàm.
	while (le < ri) {  //Tìm số lần thay đổi mảng, với điều kiện dừng là le>ri
		int mid = (le + ri) / 2;   //Phần tử ở giữa.
		if (arr[mid] < arr[mid - 1] and arr[mid] < arr[mid + 1])  //Điều kiện để thỏa yêu cầu.
			return mid;  //Trả về mid tương đương số lần mảng thay đổi.
		else {   //Thay đổi giá trị le hoặc ri, nếu thỏa điều kiện vòng lặp thì tiếp tục thực hiện.
			if (arr[mid] < arr[le]) {  
				ri = mid - 1;
			}
			else
				le = mid + 1;
		}
	}
	return le; //Trả về giá trị le là số lần mảng thay đổi khi kết thúc vòng lặp while.
}


