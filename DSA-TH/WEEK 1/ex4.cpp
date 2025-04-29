#include<iostream>
using namespace std;

void TowersofHanoi(int n, char be, char mi, char af);//Khai báo hàm.
int main() {
	int n;  //Khai báo biến n.
	cout << "Nhap so dia n: ";
	cin >> n;
	TowersofHanoi(n, 'A', 'B', 'C');//Gọi hàm TowersofHanoi.
	system("pause");  
	return 0;
}

void TowersofHanoi(int n, char be, char mi, char af) {  //Định nghĩa hàm.
	if (n == 1) {   //Điều kiện dừng hàm đệ quy.
		cout << n <<":"<<be << "->" << af << endl;   //Chuyển đĩa từ A->C.
		return;    //Dừng hàm TowersofHanoi.
	}
	else {
		TowersofHanoi(n - 1, be, af, mi);  //Chuyển tất cả n-1 đĩa trên cùng từ A->B.
		cout << n<<":"<<be << "->" << af << endl;//Chuyển đĩa cuối cùng từ A->C.
		TowersofHanoi(n - 1, mi, be, af);// Chuyển tất cả n-1 đĩa từ B->C và kết thúc hàm.
	}
}