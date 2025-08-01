#include <iostream>
#include <string>
#include <vector>

// Define a Node structure for a general tree
struct Node {
	std::string data;
	std::vector<Node *> children;

	Node(const std::string &val) : data(val) {}
};

// Recursive DFS function
void depthFirstSearch(Node *node) {
	if (node == nullptr) {
		return;	 // Base case: end of a branch
	}

	// Process the current node (e.g., print its data)
	std::cout << node->data << " ";

	// Recursively call DFS for each child
	for (Node *child: node->children) {
		depthFirstSearch(child);
	}
}

int main() {
	// Create a sample general tree
	Node *root = new Node("A");
	Node *b = new Node("B");
	Node *c = new Node("C");
	Node *d = new Node("D");
	Node *e = new Node("E");
	Node *f = new Node("F");
	Node *g = new Node("G");

	root->children.push_back(b);
	root->children.push_back(c);

	b->children.push_back(d);
	b->children.push_back(e);

	c->children.push_back(f);
	c->children.push_back(g);

	std::cout << "DFS Traversal: ";
	depthFirstSearch(root);
	std::cout << std::endl;

	delete root;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;
	delete g;

	return 0;
}
