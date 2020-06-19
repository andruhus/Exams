//Видалити граф
GraphStructure::~GraphStructure()
{
	delete[] Structure;
}

//Додати ребро
void GraphStructure::AddEdge(int vertex1, int vertex2, int weight)
{
	Structure[vertex1].push_back(VertexRelation(vertex2, weight));
}





//Перевірка на зв'язність
bool GraphStructure::CheckConnectivity()
{
	for (int i = 0; i < Size; i++)
	{
		Visited[i] = false;
		MarkVisitedRec(i);
		for (int i = 0; i < Size; i++)
		{
			if (!Visited[i])
				return false;
		}
	}
	return true;
}


//Вага графа
int GraphStructure::GetSumWeight()
{
	int sum = 0;
	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			sum += j.Weight;
	return sum;
}





//Відмітити вершину як відвідану
void GraphStructure::MarkVisitedRec(int vertex)
{
	Visited[vertex] = true;
	for (auto &j : Structure[vertex])
		if (!Visited[j.Vertex])
			MarkVisitedRec(j.Vertex);
}

std::string GraphStructure::DFS_MarkVisitedRec(int vertex)
{
	std::string subResult;
	Visited[vertex] = true;
subResult += std::to_string(vertex) + " ";

for (auto &j : Structure[vertex])
	if (!Visited[j.Vertex])
		subResult += DFS_MarkVisitedRec(j.Vertex);
return subResult;
}

//Пошук у глибину 
std::string GraphStructure::DFS()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			Visited[j] = false;
		result += DFS_MarkVisitedRec(i) + "\n";
	}
	return result;
}


//Сортування Кана
std::string GraphStructure::KahnsSort()
{
	std::vector<int> degree(Size, 0);

	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			degree[j.Vertex]++;

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
		resultStr += std::to_string(result[i]) + " ";
	return resultStr;
}



int GraphStructure::FindMin(int keys[], bool notUsed[])
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
GraphStructure* GraphStructure::FindMST()
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

		for (auto& j : Structure[min])
		{
			if (j.Weight &&
				!notUsed[j.Vertex] &&
				j.Weight < keys[j.Vertex])
			{
				result[j.Vertex] = min;
				keys[j.Vertex] = j.Weight;
			}
		}
	}


	GraphStructure* resultGraph = new GraphStructure(Size);
	for (int i = 1; i < Size; i++)
	{
		if (result[i] < 0 || result[i] >= Size)
			continue;
		for (auto& j : Structure[i])
		{
			if (j.Vertex == result[i])
			{
				resultGraph->AddEdge(result[i], i, j.Weight);
				break;
			}
		}
	}
	return resultGraph;
}

//Алгоритм Крускала
GraphStructure* GraphStructure::KruskalMST()
{
	GraphStructure* result = new GraphStructure(Size);
	std::vector<III> edges;
	for (int i = 0; i < Size; i++)
		for (auto &j : Structure[i])
			edges.push_back(III(i, j.Vertex, j.Weight));
	std::sort(edges.begin(), edges.end());

	int totalWeight = 0;
	DisjointSets disjointSets(Size);
	for (auto& i : edges)
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



std::string GraphStructure::ToString()
{
	std::string result;
	for (int i = 0; i < Size; i++)
	{
		result += std::to_string(i) + "->";
		for (auto& j : Structure[i])
		{
			result += std::to_string(j.Vertex) + "->";
		}
		result += "\n";
	}
	return result;
}

std::string GraphStructure::ToStringCalc()
{
	std::string result;
	for (int i = 0; i < Size; i++)
		for (auto& j : Structure[i])
			result += std::to_string(i) + " " + std::to_string(j.Vertex) + "\n";

	return result;
}

//--------------------------------------------------

Graph::DisjointSets::DisjointSets(int size)
{
	Size = size;
	Parents = new int[size + 1];
	Ranks = new int[size + 1];
	for (int i = 0; i <= size; i++)
	{
		Ranks[i] = 0;
		Parents[i] = i;
	}
}

int Graph::DisjointSets::FindParent(int vertex)
{
	if (vertex != Parents[vertex])
		Parents[vertex] = FindParent(Parents[vertex]);
	return Parents[vertex];
}

void Graph::DisjointSets::MergeSet(int vertex_1, int vertex_2)
{
	vertex_1 = FindParent(vertex_1), vertex_2 = FindParent(vertex_2);
	if (Ranks[vertex_1] > Ranks[vertex_2])
		Parents[vertex_2] = vertex_1;
	else
		Parents[vertex_1] = vertex_2;
	if (Ranks[vertex_1] == Ranks[vertex_2])
		Ranks[vertex_2]++;
}