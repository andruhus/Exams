Node* nwnode(Data v, Node* pl, Node* pr, Node* kor) {
	Node* p = new Node;
	p->data = v;
	p->left = pl;
	p->right = pr;
	p->root = kor;
	return p;
}
Node* insert(Node* p, Data v, Node* kor) {
	if (!p)
		return nwnode(v, NULL, NULL, kor);
	if (p->data > v)
		p->left = insert(p->left, v, p);

	else if (p->data < v)
		p->right = insert(p->right, v, p);
	else
		p->right = insert(p->right, v, p);
	return p;
}
