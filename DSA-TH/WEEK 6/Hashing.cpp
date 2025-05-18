#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

struct HashTable {
	Company table[2000];   //chứa thông tin công ty.
	bool not_empty[2000] = {};  //khởi tạo mảng kiểu bool,khi ghi bool not_empty[2000]={} có nghĩa là giá trị các phần tử ban đầu là 0 thì sẽ false. Ô mang giá trị false là ô trống.
};
//Khai báo hàm.
vector<Company> readCompanyList(string file_name); 
HashTable* createHashTable(vector<Company> list_company);
long long hashString(string company_name);  
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);
//Định nghĩa hàm.
vector<Company> readCompanyList(string file_name)  //Hàm mở file .txt để đọc dữ liệu.
{
	string infor; //chứa dữ liệu 1 dòng trong file đầu vào.
	vector<Company> list;  //lưu dữ liệu về Company của từng dòng trong file.
	int count = 0;  //biến đếm để bỏ qua không xử lí dòng đầu tiên trong file.
	ifstream in(file_name);  //mở file.
	if (!in)  //trường hợp file lỗi.
	{
		cout << "Error file" << endl;
		return list;
	}
	while (getline(in, infor))  //đọc hết 1 dòng từ file có luôn dấu cách rồi bắt đầu xử lý.
	{
		count++;  
		if (count == 1)  continue;
		
		Company company;  
		int pos1 = infor.find('|');  //tìm vị trí của kí tự '|' đầu tiên trong chuỗi infor.
		int pos2 = infor.find('|', pos1 + 1);  //tìm vị trí của kí tự '|' thứ hai trong chuỗi infor.
		if (0<pos1 && pos1 < pos2 && pos2 < infor.length() - 1)  //trường hợp tìm được hai kí tự '|' và nằm trong phạm vi của chuỗi infor. Thực hiện tách chuỗi infor thành 3 chuỗi thành phần như cấu trúc Company.
		{
			company.name = infor.substr(0, pos1);  
			company.profit_tax = infor.substr(pos1 + 1, pos2-pos1-1);
			company.address = infor.substr(pos2 + 1);
			list.push_back(company);  //lệnh thêm một phần tử company vào vector list.
		}
		else  //trường hợp khác, in ra terminal Error-read báo dữ liệu dòng này không hợp lệ.
		{
			cout << "Error-read" << endl;
		}
	}
	in.close();  //đóng file.
	return list; //trả về vecto list.
}

long long hashString(string company_name)  //Hàm băm chuyển tên công ty thành một số nguyên long long.
{
	string temp; //khởi tạo chuỗi lưu.
	long long hash = 0;  //lưu kết quả của hàm.
	int s = 0;  //dùng để chuyển một kí tự sang giá trị ASCII.
	long long p = 1;      //khi i=0 thì p^i=31^0=1 nên khởi tạo p=1. Phải khai báo kiểu long long là vì khi s*p nếu cả 2 là kiểu int thì khi nhân nhau nó có thể tràn số trước dẫn đến trả kết quả sai rồi mới modulo cho m, vậy nên cần 1 trong hai biến s hoặc p là kiểu long long.
	int m = 2000;  //số lượng ô trong bảng băm.
		
	if (company_name.length() <= 20)  //nếu tên công ty không quá 20 ký tự thì chuỗi temp sẽ được gán bằng toàn bộ chuỗi company_name.
	{
		temp = company_name;
	}
	else  //nếu tên công ty nhiều hơn 20 ký tự thì chuỗi temp sẽ được gán bằng 20 kí tự cuối chuỗi company_name.
	{
		temp = company_name.substr(company_name.length() - 20);
	} //true
	for (int i = 0;i < temp.length();i++)  //duyệt qua từng ký tự trong chuỗi temp, bắt đầu từ kí tự đầu tiên.
	{
	    s = temp[i];  //biến s sẽ mang giá trị ASCII của kí tự temp[i].
		hash = (hash+(s * p)%m) % m;  //áp dụng công thức thầy cho. Nhưng tích s*p có modulo cho m, để giảm giá trị trước khi cộng với hash nếu không có thể tràn số.
		p = (p * 31) % m;  //có modulo cho m vì để không bị tràn số, nếu không modulo cho m thì 31^20 là quá lớn so vói kiểu dữ liệu long long mà còn nhân với s nữa.
	}
	return hash; //trả về giá trị chuỗi temp sau khi băm theo công thức thầy cho.
}

HashTable* createHashTable(vector<Company> list_company)  //Hàm trả về địa chỉ một bảng băm.
{
	HashTable* table=new HashTable();  //khởi tạo con trỏ trỏ đến vùng nhớ chứa một HashTable.
	for (int i = 0;i < list_company.size();i++)  //chèn từng tên công ty đã được chuyển sang kiểu long long vào bảng băm.
	{
		insert(table, list_company[i]);
	}
	return table; //trả về địa chỉ của bảng băm.
} 

void insert(HashTable* hash_table, Company company)  //Hàm chèn một công ty vào bảng băm.
{
	long long index = hashString(company.name);  //0<=index<2000. Dùng hàm hashString để băm tên công ty thành một số nguyên.
	int count = 0; //đếm số vòng lặp.
	while (count < 2000 && hash_table->not_empty[index] == true) //tìm 1 vị trí trong bảng băm để chèn thông tin công ty. 
	{
		count++;   //tăng biến đếm.
		index = (index + count) % 2000;  //đảm bảo không duyệt quá phạm vi bảng băm.
	}
	if (count == 2000) return;  // return khi không tìm được vị trí để chèn.
	else
	{
		hash_table->table[index] = company;  //thao tác chèn thông tin công ty (company) vào vị trí trong bảng băm (index).
		hash_table->not_empty[index] = true; //chuyển not_empty tại vị trí đó từ false thành true có nghĩa là đã có thông tin của 1 công ty tại index.
	}
}

Company* search(HashTable* hash_table, string company_name)  //Hàm tìm thông tin 1 công ty trong bảng băm thông qua tên công ty.
{
	long long index = hashString(company_name); //băm tên công ty cần tìm thành số nguyên.
	int count = 0;  //biến đếm để xác định có tìm được thông tin công ty trong bảng băm không.
	while (count < 2000 && (hash_table->not_empty[index]== false || (hash_table->not_empty[index] == true && hash_table->table[index].name != company_name)))  //khi gặp ô trống hoặc ô có thông tin nhưng tên công ty không khớp với tên công ty cần tìm thì bỏ qua.
	{
		count++;  //tăng biến đếm.
		index = (index + count) % 2000;  //đảm bảo không duyệt quá phạm vi bảng băm.
	}
	if (count == 2000)  //trường hợp duyệt hết bảng băm không tìm được tên công ty cần tìm thì in ra terminal Error-search và trả về nullptr.
	{
		cout << "Error-search" << endl;
		return nullptr;
	}
	else return &hash_table->table[index];  //trường hợp tìm được tên công ty cần tìm thì trả về địa chỉ ô nhớ chứa thông tin công ty.
}
//Hàm main.
int main(int N,char*A[])
{
	HashTable* list_company = createHashTable(readCompanyList(A[1])); //tạo một con trỏ trỏ đến một bảng băm có thể chứa thông tin 2000 công ty.
	ifstream in(A[2]);  //mở file.
	ofstream out(A[3]);
	if (!in || !out) //kiểm trả xem file có tồn tại không.
	{
		cout << "Error file" << endl;
		return 1;
	}

	string company_name;  //lưu tên công ty.
	while (getline(in, company_name))  //lấy tên từng công ty từ file, để tìm thông tin. 
	{
		Company* result = search(list_company, company_name);  
		if (result == nullptr) 
		{
			out << "Error search" << endl;
		}
		else
		{
			cout << result->name << "|" << result->profit_tax << "|" << result->address << endl; //in kết quả tìm kiếm ra terminal.
			out << result->name << "|" << result->profit_tax << "|" << result->address << endl;  //in kết quả tìm kiếm vào file.
		}
	}
	return 0;
}