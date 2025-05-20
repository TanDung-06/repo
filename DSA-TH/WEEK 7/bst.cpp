#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* Search(NODE* pRoot, int x)  //Hàm tìm một node trong cây có key=x.
{
	if (pRoot == nullptr) //trường hợp không tìm thấy node trong cây có key=x.
	{
		return nullptr;
	}
	if (pRoot->key == x) //trường hợp tìm thấy node trong cây có key=x.
	{
		return pRoot;
	}
	else if (pRoot->key < x) //trường hợp node có key<x gọi đệ quy hàm Search với cây con phải và return.
	{
		return Search(pRoot->p_right,x);
	}
	else //trường hợp node có key>x gọi đệ quy hàm Search với cây con trái và return.
	{
		return Search(pRoot->p_left, x);
	}
}

void Insert(NODE* &pRoot, int x) //Hàm chèn một node có key=x vào trong cây có node gốc là pRoot.
{
	if (pRoot == nullptr) //trường hợp tìm được chỗ để chèn, tạo node với key=x rồi cho pRoot đang trỏ đến nullptr trỏ đến node mới tạo và return.
	{ 
		pRoot = new NODE{ x,nullptr,nullptr };
		return;
	}
	if (pRoot->key < x) //khi key<x thì gọi đệ quy hàm Insert với cây con bên phải.
	{
		Insert(pRoot->p_right, x);
	}
	else if(pRoot->key > x)  //khi key>x thì gọi đệ quy hàm Insert với cây con bên trái.
	{
		Insert(pRoot->p_left, x);
	}
}

void Remove(NODE*& pRoot, int x)
{
	//trường hợp cây rỗng.
	if (pRoot == nullptr) return; 
	
	if (pRoot->key < x)  //trường hợp key node gốc pRoot bé hơn x thì gọi đệ quy hàm Remove với cây con bên phải.
	{
		Remove(pRoot->p_right, x);
	}
	else if (pRoot->key > x)  //trường hợp key node gốc pRoot lớn hơn x thì gọi đệ quy hàm Remove với cây con bên trái.
	{
		Remove(pRoot->p_left, x);
	}
	else  //trường hợp tìm được node cần xóa.
	{
		if (pRoot->p_left != nullptr && pRoot->p_right != nullptr)  //trường hợp node tìm được có 2 node con. 
		{  //gán key của node con có giá trị key lớn nhất trong cây con bên trái cho node cần xóa, sau đó gọi hàm đệ quy Remove xóa node có key=a->key của cây con bên trái.
			NODE* a = pRoot->p_left;  
			while (a->p_right != nullptr)
			{
				a = a->p_right;
			}
			pRoot->key = a->key;
			Remove(pRoot->p_left, a->key);
		}
		else if (pRoot->p_left != nullptr && pRoot->p_right == nullptr)  //trường hợp node tìm được có node con bên trái.
		{  //xóa vùng nhớ pRoot đang trỏ đến, sau đó trỏ pRoot đến vùng nhớ pRoot->p_left đang trỏ.
			delete pRoot;  
			pRoot = pRoot->p_left;
		}
		else if (pRoot->p_left == nullptr && pRoot->p_right != nullptr)  //trường hợp node tìm được có node con bên phải.
		{  //xóa vùng nhớ pRoot đang trỏ đến, sau đó trỏ pRoot đến vùng nhớ pRoot->p_left đang trỏ.
			delete pRoot;
			pRoot = pRoot->p_right;
		}
		else  //trường hợp node tìm được là node lá.
		{  //xóa vùng nhớ pRoot đang trỏ đến, sau đó trỏ pRoot đến nullptr.
			delete pRoot;
			pRoot = nullptr;
		}
	}
}

NODE* createTree(int a[], int n)
{
	NODE* pRoot = nullptr;
	for (int i = 0;i < n;i++)
	{
		Insert(pRoot,a[i]);
	}
	return pRoot;
}

void removeTree(NODE*& pRoot) //Hàm xóa các node trong cây. Xóa từ node lá đến node gốc.
{
	if (pRoot == nullptr) return; //trường hợp cây rỗng.
	//xóa theo trình tự xóa cây con trái trước tới xóa node gốc rồi cuối cùng là xóa cây con bên phải.
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot)  //Hàm tìm chiều cao cây.
{
	if (pRoot == nullptr) return -1; //trường hợp cây rỗng return -1.
	//
	queue<NODE*> temp;
	temp.push(pRoot);
	//
	int height = 0;
	while (!temp.empty())
	{
		int sizeLevel = temp.size();
		for (int i = 0;i < sizeLevel;i++) 
		{
			NODE* a = temp.front();
			if (a->p_left != nullptr)  temp.push(a->p_left);
			if (a->p_right != nullptr) temp.push(a->p_right);
			temp.pop();
		}
		height++;
	}
	return height-1;
}

int countLess(NODE* pRoot, int x) //Hàm tìm trong cây số node có key < x.
{
	if (pRoot == nullptr) return 0;  //trường hợp cây rỗng.
	int countL = 0; //biến đếm.
	if (pRoot->key < x) //trường hợp node gốc pRoot có key<x.
	{
		countL++; //đếm node pRoot.
		countL += countLess(pRoot->p_right, x); //gọi đệ quy vì có thể còn tồn tại node có key<x trong cây con phải.
		countL += countLess(pRoot->p_left, x);  //gọi đệ quy để dùng lại countL++ để đếm số node ở cây con trái.
	}
	else //trường hợp node gốc pRoot có key>=x.
	{
		countL += countLess(pRoot->p_left, x);  //gọi đệ quy để tìm các node có key<x trong cây con trái.
	}
	return countL;  //trả về kết quả đếm số node trong cây thỏa key<x.
}

int countGreater(NODE* pRoot, int x) //Hàm tìm trong cây số node có key > x.
{
	if (pRoot == nullptr) return 0; //trường hợp cây rỗng.
	if (pRoot->key > x) //trường hợp node gốc pRoot có key>x.
	{
		return 1 + countGreater(pRoot->p_right, x) + countGreater(pRoot->p_left, x);  //trả về kết quả đếm là tổng đếm node gốc và đếm các node trong cây con trái, các node trong cây con phải thỏa điều kiện.
	}
	else //trường hợp node gốc pRoot có key<x.
	{
		return countGreater(pRoot->p_right, x); //trả về kết quả đếm các node trong cây con phải thỏa key>x.
	}
}

bool isBST(NODE* pRoot)  //Hàm kiểm tra xem cây có phải binany search không.
{
	if (pRoot == nullptr) return true; //cây rỗng return true.
	//nếu có cây con trái thì tìm node có key lớn nhất.
	if (pRoot->p_left != nullptr) 
	{
		NODE* maxleft = pRoot->p_left;
		while (maxleft->p_right != nullptr)
		{
			maxleft = maxleft->p_right;
		}
		if (maxleft->key >= pRoot->key)  return false; //nếu key của maxleft >= pRoot thì không thỏa tính chất binary serach tree nên return false.
	}
	//nếu có cây con phải thì tìm node có key nhỏ nhất.
	if (pRoot->p_right != nullptr) 
	{
		NODE* minright = pRoot->p_right;
		while (minright->p_left != nullptr)
		{
			minright = minright->p_left;
		}
		if (minright->key <= pRoot->key)  return false; //nếu key của minright <= pRoot thì không thỏa tính chất binary search tree nên return false.
	}

	return isBST(pRoot->p_left) && isBST(pRoot->p_right);  //gọi đệ quy hàm isBST với cây con trái và cây con phải.
}


bool isfull(NODE* pRoot) //Hàm kiểm tra cây có full không.
{
	if (pRoot == nullptr) return true; //cây rỗng return true. 
	if ((pRoot->p_left == nullptr && pRoot->p_right == nullptr) || (pRoot->p_left != nullptr && pRoot->p_right != nullptr)) //trường hợp pRoot là node lá hay node có cây con trái và cây con phải.
	{
		return isfull(pRoot->p_left) && isfull(pRoot->p_right); //gọi đệ quy hàm isfull với cây con trái và cây con phải.
	}
	return false;
}
bool isFullBST(NODE* pRoot) //Hàm kiểm tra cây có phải là binary search tree và full không.
{
	return isBST(pRoot) && isfull(pRoot);
}