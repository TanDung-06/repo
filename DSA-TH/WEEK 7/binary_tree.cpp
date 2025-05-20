#include<iostream>
#include<vector>
#include<fstream>
#include<queue>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data)  //Hàm tạo một node mới với key=data.
{
	return new NODE{ data,nullptr,nullptr };
}

vector<int> NLR(NODE* pRoot)  //Hàm duyệt cây theo kiểu Pre-order.
{
	vector<int> arrNLR;   //Khai báo vector arrNLR để lưu giá trị các node trong cây theo cách duyệt NLR.
	if (pRoot == nullptr)  return arrNLR; //trường hợp tree rỗng.
	
	arrNLR.push_back(pRoot->key);  //thêm giá trị key của Node pRoot vào trong vector arrNLR.
	//gọi đệ quy NLR(pRoot->p_left) để duyệt cây con trái Node pRoot, dùng insert trong thư viện vector để thêm kết quả duyệt vào trong vector arrNLR.  
	vector<int> left = NLR(pRoot->p_left);  
	arrNLR.insert(arrNLR.end(), left.begin(), left.end());
	//gọi đệ quy NLR(pRoot->p_right) để duyệt cây con phải Node pRoot, dùng insert trong thư viện vector để thêm kết quả duyệt vào trong vector arrNLR.  
	vector<int> right = NLR(pRoot->p_right);
	arrNLR.insert(arrNLR.end(), right.begin(), right.end());
	return arrNLR;  //trả về kết quả duyệt.
}

vector<int> LNR(NODE* pRoot)  //Hàm duyệt cây theo kiểu In-order. Câu lệnh tương đương như hàm NLR chỉ thay đổi là chèn vector left rồi thêm pRoot->key và cuối cùng là chèn vector right vào vector arrLNR.
{
	vector<int> arrLNR;
	if (pRoot == nullptr)  return arrLNR;

	vector<int>left = LNR(pRoot->p_left);
	arrLNR.insert(arrLNR.end(), left.begin(), left.end());

	arrLNR.push_back(pRoot->key);

	vector<int> right = LNR(pRoot->p_right);
	arrLNR.insert(arrLNR.end(), right.begin(), right.end());
	return arrLNR;
}

vector<int> LRN(NODE* pRoot) //Hàm duyệt cây theo kiểu Post-order. Câu lệnh tương đương như hàm NLR chỉ thay đổi là chèn vector left rồi chèn vector right và cuối cùng là thêm pRoot->key vào vector arrLRN.
{
	vector<int> arrLRN;
	if (pRoot == nullptr)  return arrLRN;
	
	vector<int> left = LRN(pRoot->p_left);
	arrLRN.insert(arrLRN.end(), left.begin(), left.end());

	vector<int> right = LRN(pRoot->p_right);
	arrLRN.insert(arrLRN.end(), right.begin(), right.end());

	arrLRN.push_back(pRoot->key);
	return arrLRN;
}

vector<vector<int>> LevelOrder(NODE* pRoot)  //Hàm duyệt cây và lưu giá trị (key) các node trong cây theo từng level vào vector hai chiều.
{
	vector<vector<int>> result;  //vector hai chiều lưu kết quả duyệt theo từng level.
	vector<int> level;  //dùng để lưu giá trị các node trong cùng 1 level.
	//trường hợp cây rỗng trả về vector hai chiều result.
	if (pRoot == nullptr)  
	{
		return result;
	}
	//khởi tạo queue temp kiểu NODE* để thêm các node trong cây theo từng level và xử lí các node trong cây theo từng level. Khởi đầu bằng việc thêm node gốc của cây vào temp.
	queue<NODE*> temp;  
	temp.push(pRoot);
	//duyệt đến khi queue temp rỗng (duyệt toàn bộ các node trong cây).
	while (!temp.empty())
	{
		int levelSize = temp.size();   //lưu size temp, để duyệt đúng số node cùng level.
		for (int i = 0;i < levelSize;i++)  //duyệt tới node nào thì xét xem có node con trái, phải không nếu có thì đẩy vào trong temp đợi duyệt cho level tiếp theo và loại bỏ node đang duyệt khỏi temp.
		{
			NODE* a = temp.front();
			level.push_back(a->key);
			if (a->p_left != nullptr)
			{
				temp.push(a->p_left);
			}
			if (a->p_right != nullptr)
			{
				temp.push(a->p_right);
			}
			temp.pop();
		}
		result.push_back(level);  //thêm vector level vào vector hai chiều result.
		level = {}; //làm rỗng vector level.
	}
	return result;  //trả về kết quả duyệt cây.
}

int countNode(NODE* pRoot)  //Hàm đếm số node trong cây.
{
	return NLR(pRoot).size();  
}

int sumNode(NODE* pRoot) //Hàm cộng tất cả giá trị key của các node trong cây.
{
	vector<int> temp = LNR(pRoot);  //khởi tạo vector temp lưu kết quả duyệt cây theo kiểu In-order.
	int sum = 0;
	for (int i = 0;i < temp.size();i++)  //chạy vòng lặp for để cộng các phần tử trong vector temp.
	{
		sum += temp[i];
	}
	return sum; //trả về kết quả cộng.
}

int heightNode(NODE* pRoot, int value)  //Hàm tìm chiều cao của node có key=value trong cây.
{
	//trường hợp cây rỗng, không tìm được value trả về -1.
	if (pRoot == nullptr) 
	{
		return -1;
	}
	//khởi tạo queue search kiểu NODE* dùng thực hiện cho việc tìm node trong cây có key=value. Đầu tiên là thêm node gốc của cây vào search.
	queue<NODE*> search;
	search.push(pRoot);
	//duyệt cây.
	while (!search.empty())
	{
		NODE* a = search.front();  //lấy node ở đầu queue search ra để xét.
		//trường hợp giá trị key của node a khác value, xét nếu a có node con trái hay node con phải thì thêm những node đó vào queue search và loại bỏ node a (node đầu tiên trong search hiện tại) khỏi search.
		if (a->key != value)
		{
			if (a->p_left != nullptr)
			{
				search.push(a->p_left);
			}
			if (a->p_right != nullptr)
			{
				search.push(a->p_right);
			}
			search.pop();
		}
		//trường hợp tìm được node a trong cây có key=value, tạo vector hai chiều height để lưu kết quả hàm LevelOrder(a) và cuối cùng là trả về kích thước height trừ đi 1 chính là chiều cao của node trong cây có key=value.
		else
		{
			vector<vector<int>> height = LevelOrder(a);
			return height.size() - 1;
		}
	}
	return -1; //khi duyệt cây không tìm thấy node có key=value thì trả về -1.
}

int Level(NODE* pRoot, NODE* p)  //Hàm tìm level của node p trong cây.
{	
	if (pRoot == nullptr) return -1;  //trường hợp cây rỗng, không tìm được trả về -1.
	//khởi tạo queue search để lưu node đợi duyệt theo từng level. Thêm node gốc pRoot vào search.
	queue<NODE*> search;
	search.push(pRoot);
	int countlevel = 0;  //lưu level của node p trong cây có node gốc pRoot.
	//duyệt từng node trong cây bắt đầu từ node gốc pRoot, nếu node đó là node p thì trả về countlevel (level node p trong cây).  
	//nếu node đang duyệt không phải node p thì xét node con trái, node con phải của node đó, nếu khác nullptr thì đẩy vào search, loại bỏ node vừa xét. Duyệt hết một level thì tăng giá trị countlevel và tiếp tục duyệt.
	while (!search.empty())
	{
		int levelSize = search.size();
		for (int i = 0;i < levelSize;i++)
		{
			NODE* temp = search.front();
			if (temp==p)
			{
				return countlevel;
			}
			if (temp->p_left != nullptr)  search.push(temp->p_left);
			if (temp->p_right != nullptr) search.push(temp->p_right);
			search.pop();
		}
		countlevel++;
	}
	return -1;  //trường hợp không tìm được, trả về -1. 
}

int countLeaf(NODE* pRoot)  //Hàm đếm số node lá trong cây.
{
	int count = 0; //biến đếm số lá trong cây.
	if (pRoot == nullptr)  return count; //trường hợp node gốc trong 1 cây bằng nullptr thì trả về count (=0).
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)  count++; //trường hợp con trỏ pRoot đang trỏ đến node lá thì count++.
	//gọi đệ quy đến cây con bên trái và cây con bên phải để đếm số node lá.
	count += countLeaf(pRoot->p_left);  
	count += countLeaf(pRoot->p_right);
	return count;  //trả về số node lá trong cây.
}