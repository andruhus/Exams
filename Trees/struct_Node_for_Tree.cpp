struct Data
{
	char english[64];
	char ukrainian[64];
	int counter;
};

struct Node
{
	Data data;
	int data_size;

	Node* left = nullptr;
	Node* right = nullptr;
	Node* root = nullptr;

} ;
