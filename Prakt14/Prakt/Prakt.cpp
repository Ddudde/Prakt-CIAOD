﻿#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class Node
{
public:
	int count;
	char symbol;
	Node* left;
	Node* right;

	Node()
	{
		symbol = 0;
		left = NULL;
		right = NULL;
		count = 0;
	}

	Node(char __symbol, int __count)
	{
		symbol = __symbol;
		count = __count;
		left = NULL;
		right = NULL;
	}

	Node(Node* l, Node* r)
	{
		symbol = 0;
		left = l;
		right = r;
		count = l->count + r->count;
	}

	static void Print(Node* root, int depth = 0)
	{
		if (!root) return;
		if (root->symbol)
		{
			for (int i = 0; i < depth; i++)
				cout << ".";
			cout << root->symbol << endl;
		}
		else depth++;
		Print(root->left, depth);
		Print(root->right, depth);
	}
};

void BuildTable(Node* root, vector<bool>& code, map<char, vector<bool>>& table)
{
	if (root->left)
	{
		code.push_back(0);
		BuildTable(root->left, code, table);
	}
	if (root->right)
	{
		code.push_back(1);
		BuildTable(root->right, code, table);
	}
	if (root->symbol)
		table[root->symbol] = code;
	if (code.size())
		code.pop_back();
}

bool SortNode(const Node* a, const Node* b)
{
	return a->count < b->count;
}

string Decode(string& str, map<vector<bool>, char>& table)
{
	string out = "";
	vector<bool> code;
	for (size_t i = 0; i < str.length(); i++)
	{
		code.push_back(str[i] == '0' ? false : true);
		if (table[code])
		{
			out += table[code];
			code.clear();
		}
	}
	return out;
}

int main()
{
	string raw = "Pupcin Vasiliy Kirilovich";
	map<char, int> symbols;
	for (size_t i = 0; i < raw.length(); i++)
		symbols[raw[i]]++;
	list<Node*> trees;
	map<char, int>::iterator itr;
	for (itr = symbols.begin(); itr != symbols.end(); itr++)
	{
		Node* p = new Node(itr->first, itr->second);
		trees.push_back(p);
	}
	while (trees.size() != 1)
	{
		trees.sort(SortNode);

		Node* l = trees.front();
		trees.pop_front();
		Node* r = trees.front();
		trees.pop_front();

		Node* parent = new Node(l, r);
		trees.push_back(parent);
	}
	Node* root = trees.front();
	root->Print(root);
	vector<bool> code;
	map<char, vector<bool> > table;
	BuildTable(root, code, table);
	for (itr = symbols.begin(); itr != symbols.end(); itr++)
	{
		cout << itr->first << " - ";
		for (size_t j = 0; j < table[itr->first].size(); j++)
			cout << table[itr->first][j];
		cout << endl;
	}
	string out = "";
	for (size_t i = 0; i < raw.length(); i++)
		for (size_t j = 0; j < table[raw[i]].size(); j++)
		{
			out += table[raw[i]][j] + '0';
			cout << table[raw[i]][j];
		}
	cout << endl;
	cout << out.c_str() << endl;
	map<vector<bool>, char> ftable;
	for (auto i = table.begin(); i != table.end(); i++)
		ftable[i->second] = i->first;
	cout << Decode(out, ftable).c_str() << endl;
	while (true);
}