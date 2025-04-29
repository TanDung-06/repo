#include<iostream>
using namespace std;

int binaryMin(int arr[], int n,int day); //Khai báo hàm.
int main() {
	int n;    //Nhập số lượng mặt hàng.
	cin >> n;
	int* p = new int[n]; //Nhập khối lượng các mặt hàng.
	for (int i = 0;i < n;i++) {
		cin >> p[i];
	}
	int day;    //Nhập số ngày vận chuyển hết n mặt hàng.
	cin >> day;
	cout<<endl<<binaryMin(p, n, day)<<endl;   //In ra khối lượng tối thiểu vận chuyển n mặt hàng trong day ngày.
	delete[] p;
	system("pause");
	return 0;
}


int binaryMin(int arr[], int n, int day) {
	int max = 0, sum = 0;            
	for (int i = 0;i < n;i++) {    //Tìm khối lượng lớn nhất và tổng khối lượng n mặt hàng.
		if (max < arr[i])  max = arr[i];
		sum += arr[i];
	}

	while (max < sum) {      //Tìm khối lượng tối thiểu vận chuyển hết n mặt hàng trong day ngày.
		int mid = (max + sum) / 2;   
		int dem = 1, tong = 0;    //Khởi tạo biến dem để tính số ngày với mỗi mid, biến tong để xác định khi nào thỏa điều kiện tăng dem.
		for (int i = 0;i < n;i++) {   //Tìm giá trị biến dem với khi khối lượng tối thiểu là mid.
			if (tong + arr[i] > mid) {
				dem++;
				tong = 0;
			}
			tong += arr[i];   
		}
		if (dem > day) {   //So sánh dem với day, để dời max hay sum để xem có tiếp tục vòng lặp while không.
			max = mid + 1;
		}
		else  sum = mid;
	}
	return max; //Khi max=sum thì vòng lặp while kết thúc trả về giá trị max là khối lượng tối thiểu để vận chuyển n mặt hàng trong day ngày.
}