#include <iostream>
#include<iomanip>
#define LH -1
#define EH	0
#define RH 1
using namespace std;
struct Node
{
	int info;
	char balFactor;
	Node* left, * right;
};
typedef Node* node;
typedef node AVL;
void init(AVL& t);
node makeNode(int x);
void createAVL(AVL& t);
void rotateLL(AVL& T);
void rotateRR(AVL& T);
void rotateLR(AVL& T);
void rotateRL(AVL& T);
int balanceLeft(AVL& T);
int balanceRight(AVL& T);
int insertNode(AVL& T, int x);
int delNode(AVL& T, int x);
int searchFor(AVL& p, AVL& q);
void menu(AVL T);
int heightTree(AVL t);
node searchX(AVL t, int x);
void removeTree(AVL& t);
void levelTraverse(AVL t, int k);
void LNR(AVL t);
void NLR(AVL t);
void LRN(AVL t);