class AVLTree : public OrderedList {
private:
	struct Node {
		Node(const std::string& val, Node* l, Node* r, Node* parent, const int& height) {
			this->value = val;
			this->left = l;
			this->right = r;
			this->parent = parent;
			this->height = height;
		}
		std::string value;
		int height;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* root;

public:
	AVLTree() {
		root = nullptr;
	}

	AVLTree& add(const std::string& newItem) {
		if (this->root) {
			this->root = this->insert(this->root, newItem);
			this->fixParenthood(this->root);
		}
		else {
			this->root = new Node(newItem, nullptr, nullptr, nullptr, 1);
		}
		return *this;
	}

	AVLTree& remove(const std::string& newItem) {
		if (this->root) {
			this->root = this->removeRec(this->root, newItem);
			this->fixParenthood(this->root);
		}
		return *this;
	}

	std::string& findItem(const std::string& newItem) {
		Node* resNode = root;
		while (true) {
			if (resNode == nullptr) throw std::exception("Unexpected Item to find");
			if (resNode->value == newItem) {
				break;
			}
			else {
				if (isFirstBigger(resNode->value,newItem)) {
					resNode = resNode->left;
				}
				else resNode = resNode->right;
			}
		}
		return resNode->value;
	}

	//Find item in AVL-Tree with value between min and max
	std::string& findItem(const std::string& min, const std::string& max) {
		Node* resNode = root;
		while (true) {
			if (resNode == nullptr) throw std::exception("Unexpected Item to find");
			if (isFirstBiggerOrEqual(resNode->value, min) && isFirstBiggerOrEqual(max, resNode->value)) {
				break;
			}
			else {
				if (isFirstBigger(resNode->value, max)) {
					resNode = resNode->left;
				}
				else resNode = resNode->right;
			}
		}
		return resNode->value;
	}

	AVLTree& implementFunc(std::function<void(std::string&)> func) {
		if (this->root) {
			this->implementRec(this->root, func);
		}
		return *this;
	}

private:
	unsigned height(Node* p)
	{
		return p ? p->height : 0;
	}

	int balanceFactor(Node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(Node* p)
	{
		unsigned hleft = height(p->left);
		unsigned hright = height(p->right);
		p->height = (hleft > hright ? hleft : hright) + 1;
	}

	void fixParenthood(Node* p) {
		if (p) {
			if (p->left) {
				p->left->parent = p;
				this->fixParenthood(p->left);
			}
			if (p->right) {
				p->right->parent = p;
				this->fixParenthood(p->right);
			}
		}
	}

	Node* rotateright(Node* p) // right rotate around p-node
	{
		Node* parentOfP = p->parent;
		Node* q = p->left;
		p->parent = q;
		q->parent = parentOfP;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node* rotateleft(Node* q) // left rotate around p-node
	{
		Node* parentOfQ = q->parent;
		Node* p = q->right;
		q->parent = p;
		p->parent = parentOfQ;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	Node* balance(Node* p) 
	{
		fixheight(p);
		if (balanceFactor(p) == 2)
		{
			if (balanceFactor(p->right) < 0) {
				p->right = rotateright(p->right);
			}
			return rotateleft(p);
		}
		if (balanceFactor(p) == -2)
		{
			if (balanceFactor(p->left) > 0) {
				p->left = rotateleft(p->left);
			}
			return rotateright(p);
		}
		return p;
	}

	//These functions are needed for adding

	Node* insert(Node* p, const std::string& newItem)
	{
		if (!p) p = new Node(newItem,nullptr,nullptr,nullptr,1);
		if (isFirstBigger(p->value,newItem)) {
			if (p->left) p->left = insert(p->left, newItem);
			else {
				p->left = new Node(newItem, nullptr, nullptr, p, 1);
			}
		}
		else {
			if(p->right) p->right = insert(p->right, newItem);
			else {
				p->right = new Node(newItem, nullptr, nullptr, p, 1);
			}
		}
		return balance(p);
	}

	//These functions are needed for cout
	void implementRec(Node* upperNode, std::function<void(std::string & item)> func) {
		Node* leftIter = findTheMostLeftOne(upperNode);
		while (leftIter != upperNode->parent) {
			func(leftIter->value);
			if (leftIter->right) {
				this->implementRec(leftIter->right,func);
			}
			leftIter = leftIter->parent;
		}
	}

	Node* findTheMostLeftOne(Node* upperNode) {
		Node* left = upperNode;
		while (left->left) {
			left = left->left;
		}
		return left;
	}

	//These functions are needed for removing
	Node* findmin(Node* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	Node* removemin(Node* p) 
	{
		if (p->left == nullptr)  return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	Node* removeRec(Node* p, std::string newItem)
	{
		if (!p) throw std::exception("Nonexistent element you want to remove");
		if (isFirstBigger(p->value,newItem)) p->left = this->removeRec(p->left, newItem);
		else if (isFirstBigger(newItem, p->value)) p->right = this->removeRec(p->right, newItem);
		else //  k == p->key 
		{
			Node* q = p->left;
			Node* r = p->right;
			Node* ParOfP = p->parent;
			if (!r) {
				if (this->root == p) this->root = q;
				if(q) q->parent = ParOfP;
				return q;
			}
			Node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			if(min)min->parent = ParOfP;
			if (this->root == p) this->root = min;
			delete p;
			return balance(min);
		}
		return balance(p);
	}
};
