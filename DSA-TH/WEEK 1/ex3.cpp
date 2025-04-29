#include<iostream>
using namespace std;

void generateBinaryStrings(int n, string str);//Khai báo hàm.
int main() {
    int a;            //Khai báo biến a và chuỗi str.
	string str;
	cout << "Length n: ";  
	cin >> a;     //Nhập giá trị cho a.
	generateBinaryStrings(a, str);    //Gọi hàm để thực hiện việc in ra tất cả chuỗi nhị phân với độ dài bằng n.
	system("pause");  //Dừng màn hình để xem kết quả.
	return 0;
}

void generateBinaryStrings(int n, string str) {//Định nghĩa hàm in ra các chuỗi nhị phân với độ dài chuỗi bằng n.
	if (str.length() == n) {//Điều kiện dừng hàm đệ quy khi độ dài chuỗi bằng n.
		cout << str << endl;//In ra chuỗi.
		return;//Dừng hàm.
	}

	generateBinaryStrings(n, str + "0"); //Đệ quy hàm generateBinaryString với độ dài chuỗi +1, và thêm kí tự "0" vào chuỗi str.
	generateBinaryStrings(n, str + "1"); //Đệ quy hàm generateBinaryString với độ dài chuỗi +1, và thêm kí tự "1" vào chuỗi str.
}