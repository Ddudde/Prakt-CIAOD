#include <queue>
#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    string value, code;
    unsigned amount;
    Node* left;
    Node* right;

    bool operator() (const Node& x, const Node& y) const {
        return x.amount > y.amount;
    }

    Node(const string& value = "", unsigned amount = 0, Node* left = 0, Node* right = 0) {
        this->value = value;
        this->code = "";
        this->amount = amount;
        this->left = left;
        this->right = right;
    }

    string to_str() {
        ostringstream x;
        if (left != 0 || right != 0) {
            x << "\t\"" << code << ": " << value << "[" << amount << "]\" -> \"" << left->code << ": " << left->value << "[" << left->amount << "]\";\n";
            x << left->to_str();
            x << "\t\"" << code << ": " << value << "[" << amount << "]\" -> \"" << right->code << ": " << right->value << "[" << right->amount << "]\";\n";
            x << right->to_str();
        }
        else {
            x << "\t\"" << code << ": " << value << "[" << amount << "]\" [shape=box, style=filled, fillcolor=green];\n";
        }
        return x.str();
    }

    Node* join(Node x) {
        return new Node(x.value + value, x.amount + amount, new Node(x), this);
    }

    void traversal_code(string code) {
        this->code = code;
        if (left != 0 || right != 0) {
            left->traversal_code(code + "1");
            right->traversal_code(code + "0");
        }
    }

    static Node* builder(priority_queue<Node, vector<Node>, Node> graph) {
        while (graph.size() > 1) {
            Node* n = new Node(graph.top());
            graph.pop();
            graph.push(*n->join(*new Node(graph.top())));
            graph.pop();
        }
        return new Node(graph.top());
    }
};

unsigned amounts[256];
int main() {
    string s;
    getline(std::cin, s);
    for (auto i : s) amounts[i]++;
    priority_queue<Node, vector<Node>, Node> graph;
    for (int i = 'a'; i <= 'z'; i++)
        if (amounts[i] > 0) graph.emplace(s = (char)i, amounts[i]);
    Node* n = Node::builder(graph);
    n->traversal_code("");
    cout << "Digraph G {\n" << n->to_str() << "}";
}