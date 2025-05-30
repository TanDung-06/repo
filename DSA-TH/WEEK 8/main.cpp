#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename)  //Hàm chuyển ma trận kề thành danh sách kề.
{
	//mở file.
	ifstream fin(filename);
	if (!fin)
	{
		cout << "Error open file !";
		return {};
	}
	//lấy dữ liệu dòng đầu tiên là số đỉnh của đồ thị.
	int n;
	fin >> n;
	fin.ignore();  //bỏ ký tự xuống dòng.
	//khởi tạo danh sách kề với n+1 hàng rỗng và thêm vào hàng đầu tiên là số đỉnh của đồ thị.
	vector<vector<int>> adjList(n+1);  
	string row;
	adjList[0].push_back(n);
	//dùng vòng for để xử lí từng dòng trong file với điều kiện dừng là đạt đủ số hàng trong danh sách kề (i=n+1) hoặc đã đọc hết có dòng trong file.
	for (int i = 1;i <= n && getline(fin, row);i++)
	{
		if (row.empty())  continue;  //dòng trống.
		adjList[i].push_back(0);     //lưu số lượng đỉnh kề với đỉnh đang xét.
		stringstream ss(row);        
		int token, vertices = 0;
		while (ss >> token)   //đọc tự động 0 và 1 trong chuỗi row bỏ qua khoảng trống.
		{
			if (token == 1)   //khi có đỉnh kề với đỉnh đang xét thì thêm chỉ số của đỉnh kề vào vector adjList[i] và tăng adjList[i][0].
			{
				adjList[i].push_back(vertices);
				adjList[i][0] += 1;
			}
			vertices++;  //xét đỉnh tiếp theo.
		}
	}
	//đóng file và trả về danh sách kề.
	fin.close();
	return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename)  //Hàm chuyển danh sách kề thành ma trận kề.
{
	//mở file.
	ifstream fin(filename);
	if (!fin)
	{
		cout << "Error open file.";
		return {};
	}
	//lấy dữ liệu dòng đầu tiên là số đỉnh của đồ thị.
	int n;
	fin >> n;
	fin.ignore();  //bỏ ký tự xuống dòng.
	//khởi tạo ma trận kề với 1 hàng rỗng và thêm vào hàng là số đỉnh của đồ thị.
	vector<vector<int>> adjMatrix(1);
	string row;
	adjMatrix[0].push_back(n);
	//dùng vòng for để xử lí từng dòng trong file với điều kiện dừng là đạt đủ số hàng trong danh sách kề (i=n+1) hoặc đã đọc hết có dòng trong file.
	for (int i = 1;i <= n && getline(fin, row);i++)
	{
		if (row.empty()) continue;  //dòng rỗng.
		vector<int> rowMatrix(n, 0);  //khởi tạo vector hàng chứa n phần tử 0.
		stringstream ss(row);
		int count;   
		ss >> count;  //lưu số đỉnh kề với đỉnh đang xét.
		for (int j = 0;j < count;j++)   //tìm count đỉnh kề với đỉnh đang xét.
		{
			int token;  //lưu chỉ số của đỉnh kề. 
			if (!ss.eof())  //trường hợp chưa đọc hết dòng row.
			{
				ss >> token;
				if (token >= 0 && token < n)  rowMatrix[token] = 1;  //nếu như chỉ số đỉnh kề (token) nằm trong khoảng từ 0 đến n-1 thì đánh dấu rowMatrix[token] = 1, còn không thì in ra terminal Error.
				else cout << "Error" << endl;
			}
		}
		adjMatrix.push_back(rowMatrix);  //thêm dữ liệu 1 hàng vào ma trận kề.
	}
	//đóng file và trả về ma trận kề.
	fin.close();
	return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix) //Hàm kiểm trả đồ thị có phải là đồ thị có hướng không?
{ 
	//số đỉnh.
	int n = adjMatrix[0][0];
	//duyệt từ dòng 1 đến dòng n (bỏ qua dòng 0 chứa số đỉnh).
	for (int i = 1;i <= n;i++)
	{
		for (int j = 0;j < n;j++)  //vì hàng i ứng với đỉnh i-1, còn cột j ứng với đỉnh j.
		{
			if (adjMatrix[i][j] != adjMatrix[j+1][i-1])   //không đối xứng trả về true.
			{
				return true;  
			}
		}
	}
	return false; //đối xứng trả về false.
}

int countVertices(const vector<vector<int>>& adjMatrix)  //Hàm đếm số lượng đỉnh trong đồ thị.
{
	if (adjMatrix.empty() || adjMatrix[0].empty())  return 0;
	return adjMatrix[0][0];
}

int countEdges(const vector<vector<int>>& adjMatrix)  //Hàm đếm số cạnh trong đồ thị.
{
	if (adjMatrix.empty() || adjMatrix[0].empty())  return 0;  //ma trận kề rỗng hoặc dòng chứa số lượng đỉnh rỗng.
	int n = adjMatrix[0][0];  //số lượng đỉnh.
	int count = 0;  //đếm cạnh nối hai đỉnh.
	//duyệt hàng ma trận từ hàng 1 đến hàng n (hàng 1 chứa số đỉnh), duyệt cột ma trận từ cột 0 đến cột n-1.
	for (int i = 1;i <= n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1) count++;  //trường hợp tồn tại cạnh nối hai đỉnh.
		}
	}
	if (isDirected(adjMatrix))  return count;  //trả về count khi đồ thị có hướng.
	else return count / 2;  //trả về count khi đồ thị vô hướng.
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)  //Hàm trả về danh sách các đỉnh cô lập.
{
	vector<int> result;  //lưu kết quả.
	if (adjMatrix.empty() || adjMatrix[0].empty())  return result;  //ma trận kề rỗng hoặc dòng chứa số đỉnh rỗng.
	int n = adjMatrix[0][0];  //số đỉnh của đồ thị.
	//duyệt hàng ma trận từ hàng 1 đến hàng n (hàng 1 chứa số đỉnh), duyệt cột ma trận từ cột 0 đến cột n-1.
	for (int i = 1;i <= n;i++)  
	{
		bool isolated = true;  
		for (int j = 0;j < n;j++)
		{
			if (adjMatrix[i][j] == 1 || adjMatrix[j+1][i-1] == 1)  //có cạnh đi vào hoặc đi ra đỉnh i-1.
			{
				isolated = false;
				break;
			}
		}
		if (isolated)  result.push_back(i - 1);  //nếu như isolated = true thì đỉnh độc lập, thêm đỉnh i-1 vào vector result.
	}
	return result;  //trả về kết quả các đỉnh cô lập.
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix)  //Hàm kiểm trả xem đồ thị vô hướng có phải là đồ thị đầy đủ không.
{
	if (!isDirected(adjMatrix))  //đồ thị vô hướng.
	{
		int n = adjMatrix[0][0];  //số lượng đỉnh.
		//duyệt hàng ma trận từ hàng 1 đến hàng n (hàng 1 chứa số đỉnh), duyệt cột ma trận từ cột 0 đến cột n-1.
		for (int i = 1;i <= n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				if ((i-1) != j && adjMatrix[i][j] == 0)  return false;  //nếu không có cạnh nối hai đỉnh phân biệt thì trả về false.
			}
		}
		return true;  //đồ thị vô hướng đầy đủ.
	}
	cout << "Do thi co huong" << endl;
	return false;  //đồ thị có hướng.
}

bool isBipartite(const vector<vector<int>>& adjMatrix)  //Hàm kiểm tra xem đồ thị có phải là đồ thị hai phía không.
{
	if (!isDirected(adjMatrix))  //đồ thị vô hướng.
	{
		int n = adjMatrix[0][0];  //số lượng đỉnh.
		vector<int> color(n, -1);  //dùng để tô màu các đỉnh trong đồ thị.

		for (int i = 0;i < n;i++)  //duyệt qua từng đỉnh từ 0 đến n-1.
		{
			if (color[i] == -1)  //đỉnh chưa tô màu thì mới thực hiện.
			{
				color[i] = 0;  //tô màu 0
				queue<int> q;
				q.push(i+1);  //hàng trong ma trận kề.
				//duyệt theo chiều rộng (BFS).
				while (!q.empty())
				{
					int a = q.front();  //lấy đỉnh ra để tìm đỉnh kề.
					q.pop();
					for (int b = 0;b < n;b++)  //duyệt trên hàng a xem có đỉnh nào nối với đỉnh a không.
					{
						if (adjMatrix[a][b] == 1)  //có cạnh nối a và b.
						{
							if (color[b] == -1)  //đỉnh chưa tô màu thì tô màu khác với màu đỉnh a.
							{
								color[b] = 1 - color[a];
								q.push(b+1);  //để duyệt hết tất cả các đỉnh có đường đi tới đỉnh a.
							}
							else if (color[b] == color[a])  return false;  //hai đỉnh kề nhau có cùng màu.
						}
					}
				}
			}
		}
		return true;  //duyệt xong và thỏa. 
	}
	//đồ thị có hướng.
	cout << "Do thi co huong" << endl;
	return false;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix)  //Hàm kiểm tra xem có phải là đồ thị hai hướng đầy đủ không.
{
	if (!isDirected(adjMatrix))  //đồ thị vô hướng.
	{
		int n = adjMatrix[0][0];  //số lượng đỉnh.
		vector<int> color(n, -1);  //dùng để tô màu các đỉnh trong đồ thị.

		for (int i = 0;i < n;i++)  //duyệt qua từng đỉnh từ 0 đến n-1.
		{
			if (color[i] == -1)  //đỉnh chưa tô màu thì mới thực hiện.
			{
				color[i] = 0;  //tô màu 0
				queue<int> q;
				q.push(i + 1);  //hàng trong ma trận kề.
				//duyệt theo chiều rộng (BFS).
				while (!q.empty())
				{
					int a = q.front();  //lấy đỉnh ra để tìm đỉnh kề.
					q.pop();
					for (int b = 0;b < n;b++)  //duyệt trên hàng a xem có đỉnh nào nối với đỉnh a không.
					{
						if (adjMatrix[a][b] == 1)  //có cạnh nối a và b.
						{
							if (color[b] == -1)  //đỉnh chưa tô màu thì tô màu khác với màu đỉnh a.
							{
								color[b] = 1 - color[a];
								q.push(b + 1);  //để duyệt hết tất cả các đỉnh có đường đi tới đỉnh a.
							}
							else if (color[b] == color[a])  return false;  //hai đỉnh kề nhau có cùng màu.
						}
					}
				}
			}
		}
		//tách thành 2 nhóm màu 0 và 1.
		vector<int> co0, co1;
		for (int i = 0; i < n; i++) {
			if (color[i] == 0) co0.push_back(i);
			else co1.push_back(i);
		}
		//kiểm tra 1 đỉnh thuộc nhóm màu 0 có nối với tất cả các đỉnh ở nhóm màu 1 không.
		for (int i = 0;i < co0.size();i++)
		{
			int u = co0[i];
			for (int j = 0;j < co1.size();j++)
			{
				int v = co1[j];
				if (adjMatrix[u][v] == 0) return false;  //nếu không nối ít nhất một đỉnh ở nhóm màu 1 thì return false.
			}
		}
		//kiểm tra 1 đỉnh thuộc nhóm màu 1 có nối với tất cả các đỉnh ở nhóm màu 0 không.
		for (int i = 0;i < co1.size();i++)
		{
			int u = co1[i];
			for (int j = 0;j < co0.size();j++)
			{
				int v = co0[j];
				if (adjMatrix[u][v] == 0) return false;  //nếu không nối ít nhất một đỉnh ở nhóm màu 0 thì return false.
			}
		}
		//thỏa hết thì return true.
		return true;
	}
	//đồ thị có hướng.
	cout << "Do thi co huong" << endl;
	return false;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)  //Hàm chuyển đồ thị có hướng thành đồ thị vô hướng tương ứng.
{
	if (adjMatrix.empty() || adjMatrix[0].empty())  return {};  //ma trận rỗng hoặc dòng đầu không có số lượng đỉnh.
	int n = adjMatrix[0][0];   //số đỉnh.
	vector<vector<int>> undirected=adjMatrix;  //gán toàn bộ ma trận có hướng vào undirected.
 	//duyệt từng hàng (1->n), từng cột (0->n-1) ma trận undirected, nếu undirected[i][j]=1 thì cũng gán 1 cho phần tử đối xứng qua đường chéo chính.
	for (int i = 1;i <= n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (undirected[i][j] == 1)  undirected[j + 1][i - 1] = 1;
		}
	}
	return undirected;  //trả về đồ thị vô hướng dưới dạng ma trận kề.
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)  //Hàm chuyển đồ thị vô hướng 
{
	if (!isDirected(adjMatrix))  //đồ thị vô hướng.
	{
		if (adjMatrix.empty() || adjMatrix[0].empty())  return {};  //ma trận rỗng hoặc dòng đầu không có số lượng đỉnh.
		int n = adjMatrix[0][0];
		vector<vector<int>> complement = adjMatrix;
		//duyệt từng hàng (1->n), từng cột (0->n-1) ma trận complement, nếu complement[i][j]=1 thì gán complement[i][j]=0, còn complement[i][j]=0 thì gán complement[i][j]=1.
		for (int i = 1;i <= n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				if (complement[i][j] == 0)  complement[i][j] = 1;
				else complement[i][j] = 0;
			}
		}
		return complement; //trả về đồ thị bù ở dạng ma trận kề.
	}
	//đồ thị có hướng.
	cout << "Do thi co huong" << endl;
	return {};
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix)  //Hàm tìm chu trình Euler trong đồ thị.
{
	int n = adjMatrix[0][0];  //số đỉnh.
	//kiểm tra bậc chẵn của từng đỉnh.
	for (int i = 1;i <= n;i++)
	{
		int degree = 0;
		for (int j = 0;j < n;j++)
		{
			degree += adjMatrix[i][j];  //khi có cạnh nối đỉnh i-1 và j phần tử ma trận bằng 1.
		}
		if (degree % 2 != 0)  return {};  //không có chu trình Euler nếu có đỉnh bậc lẻ trong đồ thị.
	}
	//tạo một vector 2 chiều lưu ma trận 0 1, bỏ qua dòng đầu ma trận adjMatrix.Để xóa cạnh đi khi duyệt.
	vector<vector<int>> matrix(adjMatrix.begin() + 1, adjMatrix.end());
	//chọn một đỉnh có ít nhất 1 cạnh để bắt đầu duyệt chu trình.
	int start = 0;
	while (start < n)
	{
		int degree = 0;
		for (int j = 0;j < n;j++)
		{
			degree += matrix[start][j];
		}
		if (degree > 0) break;
		start++;
	}
	if (start == n) return {};  //đồ thị không có cạnh.
	//bắt đầu duyệt với đỉnh start có bậc >0.
	stack<int> s;
	vector<int> euler;  //chứa kết quả chu trình.
	s.push(start); 
	//dùng stack và lặp để xóa đến khi không còn cạnh để đi tiếp
	while (!s.empty())
	{
		int a = s.top();  //lấy đỉnh trên cùng s.
		//tìm đỉnh kề b mà vẫn còn cạnh.
		int b = -1;
		for (int i = 0;i < n;i++)
		{
			if (matrix[a][i] > 0)
			{
				b= i;
				break;
			}
		}
		if (b == -1)  //không tìm được cạnh mới.
		{
			//dừng đi, thêm vào kết quả euler và loại a khởi stack s.
			euler.push_back(a);
			s.pop();
		}
		else
		{
			//đi qua cạnh a-b, giảm số lượng cạnh.
			matrix[a][b]--;
			matrix[b][a]--;
			s.push(b);  //duyệt tiếp đến b.
		}
	}
	//đảo ngược chu trình và trả về kết quả.
	reverse(euler.begin(), euler.end());
	return euler;
}

void dfs(int a, const vector<vector<int>>& adjMatrix, vector<vector<int>>& temp, vector<bool>& visited) {  //Hàm duyệt đồ thị theo kiểu DFS.
	visited[a] = true;  //đánh dấu đã duyệt.
	int n = visited.size();
	//dùng a+1 là vì trong ma trận kề thì hàng a+1 biểu diễn đỉnh a.
	for (int b = 0; b < n; b++) 
	{
		if (adjMatrix[a + 1][b] == 1 && !visited[b])  //có cạnh nối đỉnh hai a,b và đỉnh b chưa được duyệt. 
		{
			temp[a][b] = temp[b][a] = 1;  //do đồ thị vô hướng.
			dfs(b, adjMatrix, temp, visited);  //gọi đệ quy hàm dfs với đỉnh b.
		}
	}
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)  //Hàm tìm cây bao trùm theo kiểu duyệt DFS.
{
	if (!isDirected(adjMatrix))
	{
		int n = adjMatrix[0][0];
		vector<bool> visited(n, false);
		vector<vector<int>> spanningTree;
		spanningTree.push_back({ n });
		vector<vector<int>> temp(n, vector<int>(n, 0));
		//gọi hàm để duyệt DFS.
		dfs(start, adjMatrix, temp, visited);
		// thêm ma trận temp vào ma trận spanningTree.
		for (int i = 0;i < n;i++)
		{
			spanningTree.push_back(temp[i]);
		}
		return spanningTree;  //trả về cây bao trùm duyệt theo kiểu DFS.
	}
	return {};
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)  //Hàm tìm cây bao trùm theo kiểu duyệt BFS.
{
	if (!isDirected(adjMatrix)) //đồ thị vô hướng.
	{
		
		int n = adjMatrix[0][0];  //số đỉnh.
		vector<bool> visited(n, false); //để biết đỉnh đã được duyệt qua chưa.
		vector<vector<int>> spanningTree; //khởi tạo vector hai chiều spanningTree và thêm số lượng đỉnh vào hàng đầu tiên.
		spanningTree.push_back({ n });
		vector<vector<int>> temp(n, vector<int>(n, 0));  //dùng để lưu tạm kết quả duyệt BFS tìm cây bao trùm.
		//chuẩn bị cho việc duyệt BFS.
		queue<int> q;
		q.push(start);
		visited[start] = true;
		//duyệt BFS để tìm các đỉnh trong cây bao trùm gốc từ start.
		while (!q.empty())
		{
			int a = q.front();
			q.pop();
			for (int b = 0;b < n;b++)
			{
				if (adjMatrix[a + 1][b] == 1 && !visited[b])  //có cạnh nối hai đỉnh a,b và đỉnh b chưa từng được duyệt qua.
				{
					visited[b] = true;
					temp[a][b] = 1;
					temp[b][a] = 1;  //do đồ thị vô hướng.
					q.push(b);
				}
			}
		}
		// thêm ma trận temp vào ma trận spanningTree.
		for (int i = 0;i < n;i++) 
		{
			spanningTree.push_back(temp[i]);
		}
		return spanningTree; //trả về cây bao trùm duyệt theo kiểu BFS.
	}
	//đồ thị có hướng.
	return {};
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) //Hàm kiểm tra xem có đường đi từ đỉnh u đến v hay không.
{
	int n = adjMatrix[0][0];  //số đỉnh.
	vector<bool> visited(n, false); //kiểm tra xem đã duyệt qua đỉnh nào đó chưa.
	queue<int> q;
	q.push(u);
	visited[u] = true;
	//duyệt theo chiều rộng BFS để tìm đường đi từ đỉnh u tới đỉnh v.
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		if (x == v) return true;  //tìm thấy đỉnh v.
		for (int j = 0;j < n;j++)  //duyệt từng đỉnh từ 0->n-1.
		{
			if (adjMatrix[x + 1][j] == 1 && !visited[j])  //dùng x+1 là vì theo ma trận thì hàng x+1 sẽ biểu diễn cho đỉnh x, khi có đường đi (adjMatrix[x+1][j]=1) và đỉnh j chưa được duyệt qua thì thêm đỉnh j vào q và đánh dấu là đã duyệt.
			{
				q.push(j);
				visited[j] = true;
			}
		}
	}
	return false;  //không tìm thấy đường đến đỉnh v.
}
