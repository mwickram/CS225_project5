// project5.cpp : Defines the entry point for the console application.
//Praminda M Imaduwa-Gamage CS225

#include "stdafx.h"
#include "iostream"
#include "string"
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

vector <char> alist;

//function prototypes
void showContent(string filename, bool &fileOpen, string & emsg);
void getLetters(string &str);

//class defition for BinaryTree
class BinaryTree {

private:
	struct node {
		char character;
		node* left;
		node* right;
	};

	node * root;
	void insert(node *&, node *&);
	void destroySubTree(node *);
	void displayInOrder(node *) const;

public:

	BinaryTree() { root = nullptr;}
	~BinaryTree() { destroySubTree(root); }

	void insertNode(char);
	void displayInOrder() const 
	{
		displayInOrder(root);
	};

};

//destroySubTree function in deconstructor
void BinaryTree::destroySubTree(node * nodePtr) {

	if (nodePtr) {
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}


//inserNode function defitioon in BinaryTree class
void BinaryTree::insertNode(char character) {

	node * newNode = nullptr;
	//create a new node an store character
	newNode = new node;
	newNode->character = character;
	newNode->left = newNode->right = nullptr;

	insert(root, newNode);
}

//insert function defitioon in BinaryTree class
void BinaryTree::insert(node *&nodePtr, node *&newNode) {

	if (nodePtr == nullptr) {
		nodePtr = newNode;
	}
	else if (newNode->character < nodePtr->character) {
		insert(nodePtr->left, newNode);
	}
	else {
		insert(nodePtr->right, newNode);
	}
}

//displayInOrder function defitioon in BinaryTree class
void BinaryTree::displayInOrder(node * nodePtr) const{
	
	if (nodePtr) {
		displayInOrder(nodePtr->left);
		alist.push_back(nodePtr->character);
		displayInOrder(nodePtr->right);
	}

}

//showContent function defition
void showContent(string filename, bool &fileOpen, string & emsg) {
	
	ifstream file;
	string input;

	try {

		file.open(filename, ios::in);

		if (file.fail()) {
			fileOpen = false;
			throw string("File does not exist or fail to open");
		}
		else {

			getline(file, input);
			cout << "--- FILE CONTENT --- \n\n";

			while (file) {
				cout << input << endl;
				getline(file, input);
			}
			file.close();
		}

	}
	catch(string fileNOTexist){

		emsg = fileNOTexist;
	}
}

//getLetters function defition
void getLetters(string &str) {

	int num_of_char = 1;
	int ind = 0;

	while (str[ind] != '\0') {

		if (!isalpha(str[ind])) {
			str.erase(ind, num_of_char);
		}
		else {
			ind++;
		}
	}

	if (str != "") {
		cout << str << endl;
	}

}

//main function
int main()
{
	BinaryTree tree;
	string user, temp, fileName = "";
	int count = 0;
	int start = 0;
	bool fileOpen = true;
	string emsg = "";

	//fileName = "NoDemoText.txt";
	fileName = "DemoText.txt";

	cout << "FILE: " << fileName << "\n\n";
	
	showContent(fileName, fileOpen, emsg);


	if (fileOpen) {

		ifstream textFile;
		textFile.open(fileName, ios::in);

		if (textFile.fail()) {
			cout << "File does not exit or open to fail";
		}
		else {
			cout << "\n\n--- SELECTED WORDS ---\n\n";
			while (textFile >> temp) {
				getLetters(temp);
				user.append(temp);
			}
		}
		textFile.close();

		for (int ind = 0; ind < user.length(); ind++) {
			tree.insertNode(user[ind]);
		}

		cout << "\n\n--- LETTERS: FREQUENCY --- \n\n" << endl;
		tree.displayInOrder();

		char testChar = alist[start];

		for (int ind = 0; ind < alist.size(); ind++) {

			if (alist[ind] == testChar) {
				count++;
			}
			else {
				cout << testChar << " : " << count << endl;
				count = 1;
				testChar = alist[ind];
			}
		}
		cout << testChar << " : " << count << endl << endl;


	}
	else {

		cout << emsg << endl << endl;;

	}
	
	system("pause");
	return 0;
}

