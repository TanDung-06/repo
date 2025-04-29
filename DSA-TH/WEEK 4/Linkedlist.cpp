#include <iostream>
#include <cassert>
using namespace std;
struct NODE
{
    int key;
    NODE* p_next;
};

struct List
{
    NODE* p_head;
    NODE* p_tail;
    List(NODE* head = nullptr, NODE* tail = nullptr) : p_head(head), p_tail(tail) {}
};

// --- Define function prototypes ---
NODE* createNode(int data);
List* createList(NODE* p_node);
bool addHead(List*& L, int data);
bool addTail(List*& L, int data);
bool removeHead(List*& L);
void removeTail(List*& L);
void removeAll(List*& L);
void removeBefore(List*& L, int val);
void removeAfter(List*& L, int val);
bool addPos(List*& L, int data, int pos);
void removePos(List*& L, int data, int pos);
bool addBefore(List*& L, int data, int val);
bool addAfter(List*& L, int data, int val);
void printList(List* L);
int countElements(List* L);
List* reverseList(List* L);
void removeDuplicate(List*& L);
bool removeElement(List*& L, int key);

// function to create a list from an array
List* createListFromArray(int arr[], int n)
{
    List* newList = new List();
    newList->p_head = nullptr;
    newList->p_tail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        addTail(newList, arr[i]);
    }
    return newList;
}

// function to compare two lists
bool areListsEqual(List* list1, List* list2)
{
    NODE* current1 = list1 ? list1->p_head : nullptr;
    NODE* current2 = list2 ? list2->p_head : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->p_next;
        current2 = current2->p_next;
    }
    return (current1 == nullptr && current2 == nullptr);
}

// function to free the memory of a list
void freeList(List* L)
{
    NODE* current = L->p_head;
    while (current)
    {
        NODE* next = current->p_next;
        delete current;
        current = next;
    }
    delete L;
}
int length(List*& L) {
    int dem = 0;
    NODE* a = L->p_head;
    while (a != nullptr)
    {
        dem++;
        a = a->p_next;
    }
    return dem;
} 

//Hàm tạo một node.
NODE* createNode(int data)
{
    // Your code here //
    NODE* tmp = new NODE();  //Cấp pháp động cho một con trỏ kiểu NODE.Một node trong danh sách.
    tmp->key = data;  //Phần chứa dữ liệu của node.
    tmp->p_next = nullptr;  //Mỗi lần tạo một node thì phải cho phần next trỏ vào nullptr không thì có thể trỏ đến một vùng nhớ không xác định
    return tmp; // Placeholder return statement
}

//Hàm tạo một danh sách liên kết.
List* createList(NODE* p_node)
{
    // Your code here //
    List* L = new List();  //Khởi tạo một con trỏ kiểu List.
    L->p_head = p_node;  //cho con trỏ p_head trỏ đến node p_node cho trước.
    L->p_tail = p_node;  //cho con trỏ p_tail trỏ đến node p_node cho trước.
    return L; // Placeholder return statement
}

//Hàm thêm một node vào đầu danh sách liên kết.
bool addHead(List*& L, int data)
{
    // Your code here //
    NODE* temp = createNode(data);  //Khởi tạo một node chứa giá trị data.
    if (L->p_head == nullptr) {  //Xét trường hợp danh sách rỗng.
        L->p_head = temp;      //cho con trỏ p_head trỏ tới nút temp.
        L->p_tail = temp;      //cho con trỏ p_tail trỏ tới nút temp.
    }
    else  //trường hợp danh sách đã có các node trước đó.
    {
        temp->p_next = L->p_head;   //gán địa chỉ con trỏ p_head vào phần p_next của con trỏ temp.
        L->p_head = temp;   //di chuyển con trỏ p_head tới node đầu tiên trong danh sách, vì p_head phải luôn trỏ vào node đầu tiên của danh sách liên kết.
    }
    return true;  
}

//Hàm thêm node vào cuối danh sách.
bool addTail(List*& L, int data) // this function is kept for createListfromArray function
{
    NODE* newNode = createNode(data);  //Khởi tạo một node chứa giá trị data.
    if (L->p_head == nullptr)    //Trường hợp danh sách trống.
    {
        L->p_head = newNode;  //Trỏ con trỏ p_head vào node newNode.
        L->p_tail = newNode;  //Trỏ con trỏ p_tail vào node newNode.
    }
    else  //Trường hợp danh sách có các node trước đó.
    {
        L->p_tail->p_next = newNode;    // Gán địa chỉ node newNode cho phần p_next của con trỏ p_tail.
        L->p_tail = newNode;   //Di chuyển con trỏ p_tail tới node cuối cùng trong danh sách là node newNode.
    }
    return true;
}

//Hàm xóa node đầu tiên trong danh sách liên kết.
bool removeHead(List*& L)
{
    // Your code here //
    if (L->p_head != nullptr)  //Khi mà danh sách không rỗng thì mới thực hiện việc xóa node đầu tiên trong danh sách.
    {
        NODE* a = L->p_head;   //Tạo một con trỏ a kiểu NODE, trỏ đến vị trí con trỏ p_head đang trỏ.
        if (L->p_head == L->p_tail)   //Trường hợp danh sách có một node duy nhất.
        {
            L->p_head = L->p_tail = nullptr; //Cho hai con trỏ p_head và p_tail trỏ vào nullptr, vì khi xóa thì danh sách rỗng.
        }
        else   //Trường hợp danh sách có nhiều hơn một node.
        {
            L->p_head = L->p_head->p_next;  //Trỏ con trỏ p_head đến node kế tiếp sau node đầu tiên.
        }
        delete a;  //Thực hiện việc xóa node đầu tiên hay giải phóng vùng nhớ.
        return true;
    }
    return false;   //Trường hợp danh sách rỗng thì trả về false, nghĩa là không thực hiện được việc xóa.
}

//Hàm xóa node cuối danh sách liên kết.
void removeTail(List*& L)
{
   // Your code here //
    NODE* a = L->p_tail;
    NODE* b = L->p_head;
    if (L->p_head != nullptr) //Trường hợp danh sách không rỗng.
    {
        if (L->p_head == L->p_tail) //Trường hợp danh sách có 1 node.
        {
            L->p_head = L->p_tail = nullptr;  //Cho hai con trỏ p_head và p_tail trỏ vào nullptr, vì khi xóa thì danh sách rỗng.
        }
        else //Trường hợp danh sách có nhiều hơn 1 node.
        {
            while (b->p_next != L->p_tail)  //Dùng để tìm node đứng trước node mà con trỏ p_tail đang trỏ đến.
            {
                b = b->p_next;    //Di chuyển con trỏ b đến có node tiếp theo trong danh sách.
            }
            L->p_tail = b; //Cho con trỏ p_tail trỏ đến node con trỏ b đang trỏ vì b đang trỏ đến node đứng trước node cuối danh sách.
            L->p_tail->p_next = nullptr;   //Phải cho con trỏ p_tail->p_next trỏ đến nullptr vì khi đó nó đang trỏ đến node mà b->next trỏ đến mà node đó sẽ bị xóa và dữ liệu không hợp lệ thì chương trình sẽ bị lỗi.
        }
        delete a;  //Xóa node cuối cùng hay giải phóng vùng nhớ.
   }
}

//Hàm xóa tất cả các node trong danh sách.
void removeAll(List*& L)   //Hàm chỉ thực hiện khi danh sách không rỗng.
{
    // Your code here 
    while (L->p_head != nullptr)   //Khi con trỏ p_head khác nullptr nghĩa là danh sách còn node.
    {
        NODE* a = L->p_head;   //Khởi tạo con trỏ a kiểu NODE và ban đầu cho trỏ đến node đầu tiên trong danh sách.
        L->p_head = L->p_head->p_next;  //Di chuyển con trỏ p_head đến các node tiếp theo trong danh sách.
        delete a;   //Xóa node mà a đang trỏ đến hay giải phóng vùng nhớ.
    }
    L->p_tail = nullptr; //Lệnh này để con trỏ p_tail trỏ đến nullptr, do con trỏ p_tail đang trỏ đến vùng nhớ bị xóa sẽ gây lỗi.
}

// Remove a node before a given value in the list if it exists, otherwise do nothing
void removeBefore(List*& L, int val)
{
    // Your code here //
    if (L->p_head != nullptr && L->p_head->p_next != nullptr)   //Hàm thực hiện khi danh sách có hai node hoặc hơn, và node đầu tiên có key != val.
    {
        if (L->p_head->p_next->key == val)   //Khi node đứng liền sau node đầu tiên có key = val.
        {
            removeHead(L);  //Dùng hàm xóa node đầu tiên trong danh sách liên kết.
        }
        else   
        {
            NODE* a = L->p_head->p_next;  //Khởi tạo con trỏ a kiểu NODE trỏ đến node liền sau node đầu tiên.
            while (a->p_next != nullptr && a->p_next->key != val)   //Dùng vòng lặp while để tìm node có key=val.Có điều kiệu dừng là tìm thấy node thỏa hoặc không tìm thấy node thỏa khi a->next trỏ đến nullptr.
            {
                a = a->p_next; //Di chuyển con trỏ a đến các node phía sau.
            }
            if (a->p_next != nullptr)    //Trường hợp có node có key= val.
            {
                NODE* b = L->p_head;   //Khởi tạo một con trỏ b kiểu NODE, trỏ đến node đầu tiên.
                while (b->p_next != a)  //Dùng vòng while để tìm node trước node mà con trỏ a đang trỏ đến.
                {
                    b = b->p_next;  //Di chuyển con trỏ b đến các node phía sau.
                }
                b->p_next = a->p_next; //Gán địa chỉ của node có key=val cho phần p_next của con trỏ b.
                delete a; //Xóa con trỏ a hay giải phóng vùng nhớ.
            }
        }
    }
}

//Hàm xóa node phía sau node có key=val.
void removeAfter(List*& L, int val)
{
    // Your code here //
    if (L->p_head != nullptr && L->p_head->p_next != nullptr) //Hàm thực hiện khi danh sách có hai node hoặc hơn, và node cuối cùng có key != val.
    {
        NODE* a = L->p_head;  //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
        while (a != nullptr && a->key != val)  //Tìm node có key = val, với điều kiện dừng vòng while là con trỏ a trỏ đến nullptr hoặc a->key = val.
        {
            a = a->p_next;  //Di chuyển con trỏ a đến các node phía sau.
        }
        if (a != nullptr && a != L->p_tail)  //Trường hợp trong danh sách có node có key = val và node đó không phải là node cuối cùng.
        {
             if (a->p_next == L->p_tail) //Trường hợp node kế node cuối cùng có key=val.
             {
                 removeTail(L);  //Dùng hàm xóa node cuối cùng.
             }
             else  
             {
                 NODE*b = a->p_next; //Khởi tạo con trỏ b kiểu NODE để trỏ đến node cần xóa.
                 a->p_next = a->p_next->p_next; //Cho phần p_next của con trỏ a chứa địa chỉ của node đứng liền sau node bị xóa.
                 delete b; //Xóa con trỏ b hay giải phóng vùng nhớ.
             }
        }
    }
}

//Thêm một node có key=data vào vị trí pos.
bool addPos(List*& L, int data, int pos)
{
    // Your code here //  
    if (length(L) < pos or pos < 0)  //Nếu pos <0 hoặc pos lớn hơn số node trong danh sách thì trả về false.
    {
        return false;
    }
    if (length(L) == pos)  // Nếu pos bằng số node trong danh sách liên kết thì dùng hàm addTail để thêm node mới vào cuối danh sách.
    {
        addTail(L, data);
        return true; 
    }
    if (pos == 0)   //Nếu pos bằng 0 thì chèn node mới vào đầu danh sách bằng hàm addHead.
    {
        addHead(L,data);
        return true; 
    }
    int cnt = 0; //Để tìm vị trí chèn node mới vào danh sách liên kết.
    NODE* a = createNode(data);  //Tạo node a với key=val bằng hàm createNode.
    NODE* b = L->p_head; //Tạo con trỏ b kiểu NODE, trỏ đến node đầu danh sách.
    while (cnt < pos-1)   //Dùng vòng lặp while để tìm vị trí chèn node mới.
    {
        cnt++;
        b = b->p_next;  //Di chuyển con trỏ b đến các node phía sau trong danh sách.
    }
    a->p_next = b->p_next;  //Hai dòng lệnh này là thao tác chèn node a vào vị trí pos trong danh sách.
    b->p_next = a;
    return true; 
}

void removePos(List*& L, int data, int pos)
{
    // Your code here //
    if (length(L) < pos or pos < 0 or L->p_head == nullptr)  //Hàm dừng khi pos > số node trong danh sách, pos < 0, khi danh sách rỗng. 
    {
        return;
    }
    if (length(L)-1 == pos)  //Xóa node cuối cùng khi pos =length(L)-1 và node đó có key=val.Xóa bằng hàm removeTail.
    {
        if (L->p_tail->key == data)
        {
            removeTail(L);
        }
        return;
    }
    if (pos == 0)   //Xóa node đầu tiên và key node đầu tiên = val. Xóa bằng hàm removeHead.
    { 
        if (L->p_head->key == data) {
            removeHead(L);
        }
        return;
    }
    int cnt = 0;
    NODE* b = L->p_head; //Khởi tạo con trỏ b kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    while (cnt < pos-1)  //Vòng lặp while để tìm vị trí node cần xóa.
    {
        cnt++;
        b = b->p_next; //Di chuyển con trỏ đến có node phía sau trong danh sách.
    }
    if (b->p_next->key == data)  //Xét điều kiện key của node tại vị trí pos có bằng val hay không ?
    {
        NODE* a = b->p_next;  //Khởi tạo con trỏ a trỏ đến node cần xóa.
        b->p_next = b->p_next->p_next;  
        delete a;  //Xóa con trỏ a hay giải phóng vùng nhớ.
    }
    return;
}

// Insert an integer before a value of a given List:
bool addBefore(List*& L, int data, int val)
{
    // Your code here //
    if (L->p_head == nullptr) //Danh sách rỗng thì trả về false và dừng hàm.
    {
        return false;
    }
    NODE* b = L->p_head; //Khởi tạo con trỏ b kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    if (b->key == val)  //Nếu như key của con trỏ b =val thì chèn node mới vào đầu danh sách bằng hàm addHead, và return true.
    {
        addHead(L, data);
        return true;
    }
    while (b->p_next != nullptr && b->p_next->key != val)  //Tìm node trong danh sách có key = val, với điều kiện dừng vòng while là tìm thấy node thỏa hoặc không tìm thấy.
    {
        b = b->p_next;  //Di chuyển con trỏ b đến các node phía sau trong danh sách.
    }
    if (b->p_next!=nullptr)  //Khi tìm thấy node thỏa key=val.
    {
        NODE* a = createNode(data);  //Tạo một node a mới với key=data.
        a->p_next = b->p_next;   //Thao tác chèn node a vào trước node có key=val.
        b->p_next = a;
        return true;  //Trả về true và dừng hàm.
    }
    return false;  //Trả về false.
}

bool addAfter(List*& L, int data, int val)
{
    // Your code here //
    if (L->p_head == nullptr)  //Danh sách rỗng, trả về false và dừng hàm.
    {
        return false;
    }
    NODE* b = L->p_head;  //Tạo con trỏ b kiểu NODE, trỏ đến node đầu tiên.
    while (b != nullptr && b->key != val)   //Dùng vòng lặp while để tìm node có key=val, với điều kiện dừng là tìm thấy node thỏa hoặc không tìm thấy.
    {
        b = b->p_next;  //Di chuyển con trỏ b đến có node phía sau trong danh sách.
    }
    if (b != nullptr)  //Khi tìm thấy node thỏa key=val.
    {
        NODE* a = createNode(data);  //Tạo một node a mới với key=data.
        a->p_next = b->p_next;     //Thao tác chèn node a vào sau node có key=val.
        b->p_next = a;
        if (b == L->p_tail)   //Nếu node thỏa key=val là node cuối danh sách thì di chuyển con trỏ p_tail đến node a.
        {
            L->p_tail = a;
        }
        return true; //Trả về true và dừng hàm.
    }
    return false; //Trả về false và dừng hàm
}

void printList(List* L)
{
    // Your code here //
    NODE* a = L->p_head; //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    while (a != nullptr)  //Dùng vòng lặp while với điều kiện dừng là a=nullptr để in ra giá trị key của các node trong danh sách.
    {
        cout << a->key << "->";
        a = a->p_next;  //Di chuyển con trỏ a đến có node phía sau trong danh sách.
    }
    cout << "NULL";
}

int countElements(List* L)
{
    // Your code here //
    NODE* a = L->p_head;  //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    int cnt = 0;
    while (a != nullptr) //Dùng vòng lặp while với điều kiện dừng a=nullptr để đếm số node trong danh sách.
    {
        cnt++;
        a = a->p_next; //Di chuyển con trỏ a đến có node phía sau trong danh sách. 
    }
    return cnt;  //trả về giá trị biến cnt là số node trong danh sách liên kết.
}

List* reverseList(List* L)
{
    // Your code here //
    List* D = new List();  //Khởi tạo một danh sách liên kết.
    NODE* a = L->p_head;   //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    while (a != nullptr)  //Dùng vòng lặp while với điều kiện dừng là a=nullptr và dùng hàm addHead để thêm lần lượt các node trong danh sách L sang danh sách D với giá trị key của các node bị đảo ngược.
    {
        addHead(D, a->key);
        a = a->p_next;  //Di chuyển con trỏ a đến có node phía sau trong danh sách. 
    }
    return D;  //Trả về danh sách đã đảo ngược.
}

void removeDuplicate(List*& L)
{
    // Your code here //
    if (L->p_head != nullptr && L->p_head->p_next != nullptr)  //Trường hợp danh sách có từ hai node trở lên.
    {
        bool check[10000]{};  //tạo một cái mảng với các phần tử là 0 mang ý nghĩa là false.
        NODE* a = L->p_head; //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
        while (a != nullptr) 
        {
            if (!check[a->key])   //kiểm tra xem giá trị key đã có chưa, nếu chưa thì !check[a->key]=false thì cho check[a->key]=true
            {
                check[a->key] = true;
            }
            else
            {
                removeElement(L, a->key);  //thực hiện khi check[a->key]=true.
            }
            a = a->p_next;  //Di chuyển con trỏ a đến có node phía sau trong danh sách.
        }
    }
}

bool removeElement(List*& L, int key)
{
    // Your code here // 
    if (L->p_head == nullptr) //  Danh sách rỗng, trả về false và dừng hàm.
    {
        return false;
    }
    NODE* a = L->p_head;  //Khởi tạo con trỏ a kiểu NODE, trỏ đến node đầu tiên trong danh sách.
    if (a->key == key)   //Khi key của node đầu tiên bằng key thì dùng hàm removeHead để xóa node đầu tiên.
    {
        removeHead(L);
        return true;  //Trả về true và dừng hàm.
    }
    while (a->p_next != nullptr && a->p_next->key != key)  //Dùng vòng while với điều kiện dừng là tìm thấy node có key=key hoặc không tìm thấy.Để tìm node có key=key.
    {
        a = a->p_next; //Di chuyển con trỏ a đến có node phía sau trong danh sách. 
    }
    if (a->p_next != nullptr)  //Khi tìm thấy node trong danh sách có key=key.
    {
        NODE* b = a->p_next;  //Khởi tạo con trỏ b kiểu NODE, trỏ đến node có key=key.
        if (a->p_next == L->p_tail)  //Nếu node thỏa là node cuối cùng thì di chuyển con trỏ tail đến node con trỏ a đang trỏ và cho p_next của p_tail trỏ đến nullptr.
        {
            L->p_tail = a;
            L->p_tail->p_next = nullptr;
        }
        else   //Không phải node cuối.
        {
            a->p_next = a->p_next->p_next; //Cho p_next của node trước node thỏa trỏ vô node sau node thỏa.
        }
        delete b;  //Xóa con trỏ b hay giải phóng vùng nhớ.
        return true; //Trả về true và dừng hàm.
    }
    return false; //Trả về false và dừng hàm.
}

// --- Function main to test the above functions ---

int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    NODE* node1 = createNode(10);
    assert(node1 != nullptr && node1->key == 10 && node1->p_next == nullptr);
    std::cout << "Passed" << std::endl;
    delete node1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    NODE* head2 = createNode(20);
    List* list2 = createList(head2);
    assert(list2 != nullptr && list2->p_head == head2 && list2->p_tail == head2);
    std::cout << "Passed" << std::endl;
    freeList(list2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    List* list3 = new List();
    assert(addHead(list3, 30));
    assert(list3->p_head != nullptr && list3->p_head->key == 30 && list3->p_tail->key == 30);
    assert(addHead(list3, 40));
    assert(list3->p_head->key == 40 && list3->p_head->p_next->key == 30 && list3->p_tail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(list3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    List* list4 = new List();
    assert(addTail(list4, 50));
    assert(list4->p_head != nullptr && list4->p_head->key == 50 && list4->p_tail->key == 50);
    assert(addTail(list4, 60));
    assert(list4->p_head->key == 50 && list4->p_tail->key == 60 && list4->p_head->p_next->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(list4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = { 70, 80, 90 };
    List* list5 = createListFromArray(arr1, 3);
    assert(removeHead(list5) && list5->p_head->key == 80);
    assert(removeHead(list5) && list5->p_head->key == 90);
    assert(removeHead(list5) && list5->p_head == nullptr && list5->p_tail == nullptr);
    assert(!removeHead(list5)); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(list5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = { 100, 110, 120 };
    List* list6 = createListFromArray(arr2, 3);
    removeTail(list6);
    assert(list6->p_tail->key == 110 && list6->p_tail->p_next == nullptr);
    removeTail(list6);
    assert(list6->p_tail->key == 100 && list6->p_tail->p_next == nullptr && list6->p_head == list6->p_tail);
    removeTail(list6);
    assert(list6->p_head == nullptr && list6->p_tail == nullptr);
    List* emptyList6 = new List();
    removeTail(emptyList6); // Remove from empty list
    std::cout << "Passed" << std::endl;
    freeList(emptyList6);
    freeList(list6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = { 130, 140, 150 };
    List* list7 = createListFromArray(arr3, 3);
    removeAll(list7);
    assert(list7->p_head == nullptr && list7->p_tail == nullptr);
    List* emptyList7 = new List();
    removeAll(emptyList7); // Remove from empty list
    assert(emptyList7->p_head == nullptr && emptyList7->p_tail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyList7);
    freeList(list7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = { 160, 170, 180, 190, 200 };
    List* list8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(list8, 180);
    int expectedArr8[4] = { 160, 180, 190, 200 };
    List* expectedList8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(list8, expectedList8));

    // testcase 2
    removeBefore(list8, 200);
    int expectedArr8_2[3] = { 160, 180, 200 };
    List* expectedList8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(list8, expectedList8_2));

    // testcase 3
    removeBefore(list8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = { 160, 180, 200 };
    List* expectedList8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(list8, expectedList8_2_2));

    // free memory
    freeList(expectedList8);
    freeList(expectedList8_2);
    freeList(expectedList8_2_2);
    freeList(list8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = { 220, 230, 240, 250 };
    List* list9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(list9, 220);
    int expectedArr9[3] = { 220, 240, 250 };
    List* expectedList9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(list9, expectedList9));
    // testcase 2
    removeAfter(list9, 250); // Don't have any element after
    int expectedArr9_2[3] = { 220, 240, 250 };
    List* expectedList9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(list9, expectedList9_2));
    // testcase 3
    removeAfter(list9, 240);
    int expectedArr9_3[2] = { 220, 240 };
    List* expectedList9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(list9, expectedList9_3));
    // testcase 4
    int arr9_single[1] = { 260 };
    List* list9_single = createListFromArray(arr9_single, 1);
    removeAfter(list9_single, 260);
    int expectedArr9_single[1] = { 260 };
    List* expectedList9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(list9_single, expectedList9_single));
    // testcase 5
    List* emptyList9 = new List();
    removeAfter(emptyList9, 270);
    assert(areListsEqual(emptyList9, new List()));
    // free memory
    freeList(expectedList9);
    freeList(expectedList9_2);
    freeList(expectedList9_3);
    freeList(expectedList9_single);
    freeList(list9);
    freeList(list9_single);
    freeList(emptyList9);
    std::cout << "Passed" << std::endl;

    // // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addPos: ";
    List* list10 = new List();
    assert(addPos(list10, 280, 0));
    assert(list10->p_head != nullptr && list10->p_head->key == 280 && list10->p_tail->key == 280);
    assert(addPos(list10, 290, 1));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 290 && list10->p_head->p_next->key == 290);
    assert(addPos(list10, 300, 1));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 290 && list10->p_head->p_next->key == 300);
    assert(list10->p_head->p_next->p_next->key == 290);
    assert(addPos(list10, 310, 3));
    assert(list10->p_head->key == 280 && list10->p_tail->key == 310 && list10->p_head->p_next->key == 300);
    assert(list10->p_head->p_next->p_next->key == 290 && list10->p_head->p_next->p_next->p_next->key == 310);
    assert(!addPos(list10, 320, 5));  // Positions out of range
    assert(!addPos(list10, 330, -1)); // Negative position
    // free memory
    freeList(list10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemovePos: ";
    int arr11[5] = { 340, 350, 360, 370, 380 };
    List* list11 = createListFromArray(arr11, 5);
    assert(list11->p_head->key == 340 && list11->p_tail->key == 380);
    // testcase 1
    removePos(list11, 340, 0);
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 370 && list11->p_head->p_next->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next->p_next == nullptr);
    // testcase 2
    removePos(list11, 370, 2);
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next == nullptr);
    // testcase 3
    removePos(list11, 350, 5); // Positions out of range
    assert(list11->p_head->key == 350 && list11->p_tail->key == 380);
    assert(list11->p_head->p_next->key == 360 && list11->p_head->p_next->p_next->key == 380);
    assert(list11->p_head->p_next->p_next->p_next == nullptr);
    // free memory
    freeList(list11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addBefore: ";
    int arr12[4] = { 390, 400, 410, 420 };
    List* list12 = createListFromArray(arr12, 4);
    assert(list12->p_head->key == 390 && list12->p_tail->key == 420);
    // testcase 1
    addBefore(list12, 380, 400);
    int arr12_1[5] = { 390, 380, 400, 410, 420 };
    List* expectedList12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(list12, expectedList12_1));
    // testcase 2
    addBefore(list12, 370, 390);
    int arr12_2[6] = { 370, 390, 380, 400, 410, 420 };
    List* expectedList12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(list12, expectedList12_2));
    // testcase 3
    addBefore(list12, 360, 350); // Don't have any element before
    int arr12_3[6] = { 370, 390, 380, 400, 410, 420 };
    List* expectedList12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(list12, expectedList12_3));
    // free memory
    freeList(list12);
    freeList(expectedList12_1);
    freeList(expectedList12_2);
    freeList(expectedList12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addAfter: ";
    int arr13[4] = { 430, 440, 450, 460 };
    List* list13 = createListFromArray(arr13, 4);
    assert(list13->p_head->key == 430 && list13->p_tail->key == 460);
    // testcase 1
    addAfter(list13, 470, 440);
    int arr13_1[5] = { 430, 440, 470, 450, 460 };
    List* expectedList13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(list13, expectedList13_1));
    // testcase 2
    addAfter(list13, 480, 460);
    int arr13_2[6] = { 430, 440, 470, 450, 460, 480 };
    List* expectedList13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(list13, expectedList13_2));
    // testcase 3
    addAfter(list13, 490, 200); // Don't have any element after
    int arr13_3[6] = { 430, 440, 470, 450, 460, 480 };
    List* expectedList13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(list13, expectedList13_3));
    // free memory
    freeList(expectedList13_1);
    freeList(expectedList13_2);
    freeList(expectedList13_3);
    freeList(list13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printList /////////////////////////////////////////////////////////
    std::cout << "Test printList: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countElements: ";
    // Test case 1
    int arr15[5] = { 500, 510, 520, 530, 540 };
    List* list15 = createListFromArray(arr15, 5);
    assert(countElements(list15) == 5);
    // Test case 2
    int arr15_2[3] = { 550, 560, 570 };
    List* list15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(list15_2) == 3);
    // Test case 3
    int arr15_3[1] = { 580 };
    List* list15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(list15_3) == 1);
    // Test case 4
    List* emptyList15 = new List();
    assert(countElements(emptyList15) == 0);
    // free memory
    freeList(list15);
    freeList(list15_2);
    freeList(list15_3);
    freeList(emptyList15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseList: ";
    // Test case 1
    int arr16[5] = { 590, 600, 610, 620, 630 };
    List* list16 = createListFromArray(arr16, 5);
    List* reversedList16 = reverseList(list16);
    int expectedArr16[5] = { 630, 620, 610, 600, 590 };
    List* expectedList16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedList16, expectedList16));
    // Test case 2
    int arr16_2[3] = { 640, 650, 660 };
    List* list16_2 = createListFromArray(arr16_2, 3);
    List* reversedList16_2 = reverseList(list16_2);
    int expectedArr16_2[3] = { 660, 650, 640 };
    List* expectedList16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedList16_2, expectedList16_2));
    // Test case 3
    int arr16_3[1] = { 670 };
    List* list16_3 = createListFromArray(arr16_3, 1);
    List* reversedList16_3 = reverseList(list16_3);
    int expectedArr16_3[1] = { 670 };
    List* expectedList16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedList16_3, expectedList16_3));
    // Test case 4
    List* emptyList16 = new List();
    List* reversedList16_4 = reverseList(emptyList16);
    assert(reversedList16_4->p_head == nullptr && reversedList16_4->p_tail == nullptr);
    // free memory
    freeList(expectedList16);
    freeList(expectedList16_2);
    freeList(expectedList16_3);
    freeList(reversedList16);
    freeList(reversedList16_2);
    freeList(reversedList16_3);
    freeList(reversedList16_4);
    freeList(list16);
    freeList(list16_2);
    freeList(list16_3);
    freeList(emptyList16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDuplicate: ";
    // Test case 1
    int arr17[6] = { 680, 690, 690, 700, 710, 710 };
    List* list17 = createListFromArray(arr17, 6);
    removeDuplicate(list17);
    int expectedArr17[4] = { 680, 690, 700, 710 };
    List* expectedList17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(list17, expectedList17));
    // Test case 2
    int arr17_2[5] = { 720, 730, 740, 740, 740 };
    List* list17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(list17_2);
    int expectedArr17_2[3] = { 720, 730, 740 };
    List* expectedList17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(list17_2, expectedList17_2));
    // Test case 3
    int arr17_3[4] = { 750, 760, 760, 770 };
    List* list17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(list17_3);
    int expectedArr17_3[3] = { 750, 760, 770 };
    List* expectedList17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(list17_3, expectedList17_3));
    // Test case 4
    int arr17_4[2] = { 780, 780 };
    List* list17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(list17_4);
    int expectedArr17_4[1] = { 780 };
    List* expectedList17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(list17_4, expectedList17_4));
    // Test case 5
    int arr17_5[1] = { 790 };
    List* list17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(list17_5);
    int expectedArr17_5[1] = { 790 };
    List* expectedList17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(list17_5, expectedList17_5));
    // Test case 6
    List* emptyList17 = new List();
    removeDuplicate(emptyList17);
    assert(emptyList17->p_head == nullptr && emptyList17->p_tail == nullptr);
    // free memory
    freeList(expectedList17);
    freeList(expectedList17_2);
    freeList(expectedList17_3);
    freeList(expectedList17_4);
    freeList(expectedList17_5);
    freeList(list17);
    freeList(list17_2);
    freeList(list17_3);
    freeList(list17_4);
    freeList(list17_5);
    freeList(emptyList17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeElement: ";
    // Test case 1
    int arr18[5] = { 800, 810, 820, 830, 840 };
    List* list18 = createListFromArray(arr18, 5);
    assert(removeElement(list18, 820));
    int expectedArr18[4] = { 800, 810, 830, 840 };
    List* expectedList18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(list18, expectedList18));
    // Test case 2
    int arr18_2[3] = { 850, 860, 870 };
    List* list18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(list18_2, 850));
    int expectedArr18_2[2] = { 860, 870 };
    List* expectedList18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(list18_2, expectedList18_2));
    // Test case 3
    int arr18_3[4] = { 880, 890, 900, 910 };
    List* list18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(list18_3, 910));
    int expectedArr18_3[3] = { 880, 890, 900 };
    List* expectedList18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(list18_3, expectedList18_3));
    // Test case 4
    int arr18_4[2] = { 920, 930 };
    List* list18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(list18_4, 920));
    int expectedArr18_4[1] = { 930 };
    List* expectedList18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(list18_4, expectedList18_4));
    // Test case 5
    int arr18_5[1] = { 940 };
    List* list18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(list18_5, 940));
    int expectedArr18_5[1] = {10}; //Sua 
    List* expectedList18_5 = createListFromArray(expectedArr18_5, 0);
    assert(areListsEqual(list18_5, expectedList18_5));
    // Test case 6
    List* emptyList18 = new List();
    assert(!removeElement(emptyList18, 950)); // Remove from empty list
    assert(emptyList18->p_head == nullptr && emptyList18->p_tail == nullptr);
    // free memory
    freeList(expectedList18);
    freeList(expectedList18_2);
    freeList(expectedList18_3);
    freeList(expectedList18_4);
    freeList(expectedList18_5);
    freeList(list18);
    freeList(list18_2);
    freeList(list18_3);
    freeList(list18_4);
    freeList(list18_5);
    freeList(emptyList18);
    std::cout << "Passed" << std::endl;
    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}