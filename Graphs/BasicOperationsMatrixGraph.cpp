//Видалити граф
GraphMatrix::~GraphMatrix()
{
	for (int i = 0; i < Size; ++i)
		delete[] Matrix[i];
	delete[] Matrix;
}

//Додати ребро
void GraphMatrix::AddEdge(int vertex1, int vertex2, int weight)
{
	if (vertex1 >= Size || vertex2 >= Size || weight < 0)
		throw std::out_of_range("Invalid user exception");
	Matrix[vertex1][vertex2] = weight;
}

//Перевірка на зв'язність
bool GraphMatrix::CheckConnectivity()
{
	for (int i = 0; i < Size; i++) 
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;

		MarkVisitedRec(i);

		for (int j = 0; j < Size; j++)
			if (!Visited[j])
				return false;
	}
	return true;
}

//Вага графа
int GraphMatrix::GetSumWeight()
{
	int sum = 0;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			sum += Matrix[i][j];
		}
	}
	return sum;
}

//Відмітити вершину як відвідану
void GraphMatrix::MarkVisitedRec(int vertex)
{
	Visited[vertex] = true;
	for (int j = 0; j < Size; j++) 
	{
		if (Matrix[vertex][j])
		{
			if (!Visited[j])
				MarkVisitedRec(j);
		}
	}
}

//Намалювати / ітерації 
std::string GraphMatrix::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "->";
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[i][j])
				result += std::to_string(j) + "->";
		}
		result += "\n";
	}
	return result;
}

//Пошук в глибину за вершиною
std::string GraphMatrix::DFS_MarkVisitedRec(int vertex) 
{
	std::string subResult;
	Visited[vertex] = true;
	subResult += std::to_string(vertex) + " ";

	for (int j = 0; j < Size; j++)
		if (Matrix[vertex][j])
			if (!Visited[j])
				subResult += DFS_MarkVisitedRec(j);

	return subResult;
}

std::string GraphMatrix::DFS_MarkVisitedRec_Weight(int vertex)
{
	std::string subResult;
	Visited[vertex] = true;
	subResult += std::to_string(vertex) + " ";

	std::vector<std::tuple<int, int, bool>> vect;
	for (int i = 0; i < Size; i++)
		vect.push_back(std::tuple<int, int, bool>(i, Matrix[vertex][i], Visited[i]));
	std::sort(vect.begin(), vect.end(), CustomBiggerThan());

	for (int i = 0; i < Size; i++)
		if (std::get<1>(vect[i]) && !std::get<2>(vect[i]))
			subResult += DFS_MarkVisitedRec(std::get<0>(vect[i]));

	return subResult;
}

//Пошук у глибину за вагою
std::string GraphMatrix::DFS(bool weight = false)
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;
		if (weight)
			result += DFS_MarkVisitedRec_Weight(i) + "\n";
		else
			result += DFS_MarkVisitedRec(i) + "\n";
	}
	return result;
}


//Алгоритм Дейкстри
int GraphMatrix::Dijkstra_MinDistance(int result[], bool shortestPathIncludance[])
{
	int minVal = INT_MAX;
	int minId = -1;
	for (int i = 0; i < Size; i++)
	{
		if (shortestPathIncludance[i] == false &&
			result[i] <= minVal)
		{
			minVal = result[i];
			minId = i;
		}
	}
	return minId;
}

std::string GraphMatrix::Dijkstra()
{
	int* result = new int[Size];
	bool* shortestPathIncludance = new bool[Size];

	std::string resultStr;

	for (int from = 0; from < Size; from++)
	{
		for (int i = 0; i < Size; i++)
		{
			result[i] = INT_MAX;
			shortestPathIncludance[i] = false;
		}
		result[from] = 0;
		for (int i = 0; i < Size - 1; i++)
		{
			int minId = Dijkstra_MinDistance(result, shortestPathIncludance);
			shortestPathIncludance[minId] = true;
			for (int j = 0; j < Size; j++)
			{
				if (!shortestPathIncludance[j] &&
					Matrix[minId][j] &&
					result[minId] != INT_MAX &&
					result[minId] + Matrix[minId][j] < result[j])
				{
					result[j] = result[minId] + Matrix[minId][j];
				}
			}
		}
		for (int i = 0; i < Size; i++)
		{
			resultStr +=
				"From " + std::to_string(from) +
				" to " + std::to_string(i) +
				" = " + std::to_string(result[i]) + "\n";
		}
		resultStr += "\n";
	}
	return resultStr;
}

//Сортування Кана
std::string GraphMatrix::KahnsSort()
{
	std::vector<int> degree(Size, 0);

	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			if(Matrix[i][j])
				degree[j]++;

	std::queue<int> queue;
	for (int i = 0; i < Size; i++)
		if (!degree[i])
			queue.push(i);

	int visitedVerts = 0;
	std::vector <int> result;

	while (!queue.empty())
	{
		int i = queue.front();
		queue.pop();
		result.push_back(i);

		for (int j = 0; j < Size; j++)
			if (!--degree[j])
				queue.push(j);

		visitedVerts++;
	}

	if (visitedVerts != Size)
		return "Impossible to sort with Kahn's method, this is cycle graph.";
	
	std::string resultStr;
	for (int i = 0; i < result.size(); i++)
		resultStr += std::to_string(result[i])  + " ";
	return resultStr;
}


int GraphMatrix::FindMin(int keys[], bool notUsed[])
{
	int min = INT_MAX;
	int minId = 0;
	for (int i = 0; i < Size; i++)
	{
		if (notUsed[i] == false && keys[i] < min)
		{
			min = keys[i];
			minId = i;
		}
	}
	return minId;
}

//Знайти кістякове дерево
GraphMatrix* GraphMatrix::FindMST()
{
	int* result = new int[Size];
	int* keys = new int[Size];
	bool* notUsed = new bool[Size];

	for (int i = 0; i < Size; i++)
	{
		keys[i] = INT_MAX;
		notUsed[i] = false;
	}

	keys[0] = 0;
	result[0] = 0;

	for (int i = 0; i < Size - 1; i++)
	{
		int min = FindMin(keys, notUsed);
		notUsed[min] = true;
		for (int j = 0; j < Size; j++)
		{
			if (Matrix[min][j] &&
				!notUsed[j] &&
				Matrix[min][j] < keys[j])
			{
				result[j] = min;
				keys[j] = Matrix[min][j];
			}
		}
	}


	GraphMatrix* resultGraph = new GraphMatrix(Size);
	for (int i = 1; i < Size; i++)
		if (result[i] < 0 || result[i] >= Size)
			continue;
		else
			resultGraph->AddEdge(result[i], i, Matrix[i][result[i]]);

	auto shit = resultGraph->ToString();


	return resultGraph;
}

//Алгоритм Крускала
GraphMatrix* GraphMatrix::KruskalMST()
{
	GraphMatrix* result = new GraphMatrix(Size);
	std::vector<III> edges;
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			edges.push_back(III(i, j, Matrix[i][j]));
	std::sort(edges.begin(), edges.end());

	int totalWeight = 0;
	DisjointSets disjointSets(Size);
	for (auto &i : edges)
	{
		int vertex_1 = std::get<0>(i);
		int vertex_2 = std::get<1>(i);
		int weight   = std::get<2>(i);

		int set_1 = disjointSets.FindParent(vertex_1);
		int set_2 = disjointSets.FindParent(vertex_2);
		if (set_1 != set_2)
		{
			result->AddEdge(vertex_1, vertex_2, weight);
			disjointSets.MergeSet(set_1, set_2);
			totalWeight += weight;
		}
	}
	return result;
}



