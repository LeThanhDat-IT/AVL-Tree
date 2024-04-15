#include "Header.h"
void init(AVL& t) {
	t = NULL;
}
node makeNode(int x) {
	node p = new Node;
	if (p == NULL)	return NULL;//thieu bo nho
	p->info = x;
	p->balFactor = EH;
	p->left = p->right = NULL;
	return p;
}
void rotateLL(AVL& T) {
	AVL T1 = T->left;
	T->left = T1->right;
	T1->right = T;
	switch (T1->balFactor)
	{
		case LH:T->balFactor = EH; T1->balFactor = EH;break;
		case EH:T->balFactor = LH; T1->balFactor = RH;break;
	}
	T = T1;
}
void rotateRR(AVL& T) {
	AVL T1 = T->right;
	T->right = T1->left;
	T1->left = T;
	switch (T1->balFactor)
	{
		case RH:T->balFactor = EH; T1->balFactor = EH;break;
		case EH:T->balFactor = RH; T1->balFactor = LH;break;
	}
	T = T1;
}
void rotateLR(AVL& T) {
	AVL T1 = T->left;
	AVL T2 = T1->right;
	T->left = T2->right;
	T2->right = T;
	T1->right = T2->left;
	T2->left = T1;
	switch (T2->balFactor)
	{
		case LH:T->balFactor = RH; T1->balFactor = EH; break;
		case EH:T->balFactor = EH; T1->balFactor = EH; break;
		case RH:T->balFactor = EH; T1->balFactor = LH; break;
	}
	T2->balFactor = EH;
	T = T2;
}
void rotateRL(AVL& T) {
	AVL T1 = T->right;
	AVL T2 = T1->left;
	T->right = T2->left;
	T2->left = T;
	T1->left = T2->right;
	T2->right = T1;
	switch (T2->balFactor)
	{
		case LH:T->balFactor = LH; T1->balFactor = EH; break;
		case EH:T->balFactor = EH; T1->balFactor = EH; break;
		case RH:T->balFactor = EH; T1->balFactor = RH; break;
	}
	T2->balFactor = EH;
	T = T2;
}
int balanceLeft(AVL& T) {
	AVL T1 = T->left;
	switch (T1->balFactor)
	{
		case LH:rotateLL(T); return 2;
		case EH:rotateLL(T); return 1;
		case RH:rotateLR(T); return 2;
	}
	return 0;
}
int balanceRight(AVL& T) {
	AVL T1 = T->right;
	switch (T1->balFactor)
	{
		case LH:rotateRL(T); return 2;
		case EH:rotateRR(T); return 1;
		case RH:rotateRR(T); return 2;
	}
	return 0;
}
int insertNode(AVL& T, int x) {
	int res;
	if (!T) {
		T = makeNode(x);
		return 2;
	}
	else {
		if (T->info == x)	return 0;//da co
		if (T->info > x) {
			res = insertNode(T->left, x);
			if (res < 2)	return res;
			switch (T->balFactor)
			{
			case RH:T->balFactor = EH; return 1;
			case EH:T->balFactor = LH; return 2;
			case LH:balanceLeft(T);    return 1;
			}
		}
		else {
			res = insertNode(T->right, x);
			if (res < 2)
				return res;
			switch (T->balFactor)
			{
			case LH:T->balFactor = EH; return 1;
			case EH:T->balFactor = RH; return 2;
			case RH:balanceRight(T);   return 1;
			}
		}
	}
	
}
int delNode(AVL& T, int x) {
	int res;
	if (T == NULL)	return 0;
	if (T->info > x) {
		res = delNode(T->left, x);
		if (res < 2)	return res;
		switch (T->balFactor)
		{
			case LH:T->balFactor = EH; return 2;
			case EH:T->balFactor = RH; return 1;
			case RH:return balanceRight(T);
		}
	}
	if (T->info < x) {
		res = delNode(T->right, x);
		if (res < 2)	return res;
		switch (T->balFactor)
		{
			case RH:T->balFactor = EH; return 2;
			case EH:T->balFactor = LH; return 1;
			case LH:return balanceLeft(T);
		}
	}
	else {//T->info == x
		AVL p = T;
		if (T->left == NULL) {
			T = T->right; res = 2;
		}
		else if (T->right == NULL) {
			T = T->left; res = 2;
		}
		else {//T co ca 2 cay con
			res = searchFor(p, T->right);
			if (res < 2)	return res;
			switch (T->balFactor)
			{
				case RH:T->balFactor = EH; return 2;
				case EH:T->balFactor = LH; return 1;
				case LH:return balanceLeft(T);
			}
		}
		delete p;
		return res;
	}
}

int searchFor(AVL& p, AVL& q) {
	int res;
	if (q->left) {
		res = searchFor(p, q->left);
		if (res < 2)	return res;
		switch (q->balFactor)
		{
			case LH:q->balFactor = EH; return 2;
			case EH:q->balFactor = LH; return 1;
			case RH:return balanceRight(q);
		}
	}
	else {
		p->info = q->info;
		p = q;
		q = q->right;
		return 2;
	}
}
void createAVL(AVL& t) {
	int x;
	do {
		cout << "\nNhap gia tri x = ";
		cin >> x;
		if (x == 0)	break;
		insertNode(t, x);
	} while (true);
}
int heightTree(AVL t) {
	if (!t)
		return 0;
	int trai = heightTree(t->left);
	int phai = heightTree(t->right);
	if (trai > phai)
		return trai + 1;
	else
		return phai + 1;
}
node searchX(AVL t, int x) {
	if (t)
	{
		if (t->info == x)		return t;
		if (t->info < x)		return searchX(t->right, x);
		else					return searchX(t->left, x);
	}
	return NULL;
}
void removeTree(AVL& t) {
	if (t) {
		removeTree(t->left);
		removeTree(t->right);
		delete(t);
	}
}
//xuat tang
void levelTraverse(AVL t, int k) {
	if (!t)
		return;
	if (k == 0) {
		cout << t->info << "\t";
		return;
	}
	levelTraverse(t->left, k - 1);
	levelTraverse(t->right, k - 1);
}
void LNR(AVL t) {
	if (t)
	{
		LNR(t->left);
		cout << t->info << "\t";
		LNR(t->right);
	}
}

void NLR(AVL t) {
	if (t) {
		cout << t->info << "\t";
		NLR(t->left);
		NLR(t->right);
	}
}

void LRN(AVL t) {
	if (t) {
		LRN(t->left);
		LRN(t->right);
		cout << t->info << "\t";
	}
}
void menu(AVL t) {
	int chon, x, k;
	char ch;
	do {
		cout << "\n0.Exit";
		cout << "\n1.Creat AVL Tree";
		cout << "\n2.Add a node to the AVL tree";
		cout << "\n3.Deelete a node in AVL tree";
		cout << "\n4.Approve LNR tree";
		cout << "\n5.Approve NLR tree";
		cout << "\n6.Approve LRN tree";
		cout << "\n7.Approve by floor";
		cout << "\n8.Approve the entire AVL tree floor";
		cout << "\n9.Find a node in AVL tree";
		cout << "\n10.Delete all node in AVL tree";
		cout << "\n11.Height of the tree";
		cout << "\n12.Write AVL file";
		cout << "\n13.Read AVL file";
		cout << "\n==> Please select a function ";
		cin >> chon;
		if (chon == 0)	break;
		switch (chon)
		{
			case 1:
				createAVL(t);
				cout << "\n-->Creat tree success, Please review ";
				break;
			case 2:
				cout << "\nPlease enter the value to add ";cin >> x;
				insertNode(t, x);
				cout << "\n-->Add success, Please review ";
				break;
			case 3:
				cout << "\nPlease enter node to delete";cin >> x;
				delNode(t, x);
				cout << "\n-->Delete success, Please review ";
				break;
			case 4:
				cout << "\nApprove LNR tree";
				LNR(t);
				break;
			case 5:
				cout << "\nApprove NLR tree";
				NLR(t);
				break;
			case 6:
				cout << "\nApprove LRN tree";
				LRN(t);
				break;
			case 7:
				cout << "\nPlease enter the floor to export";cin >> k;
				levelTraverse(t, k);
				break;
			case 8:
				cout << "\nAll AVL tree export by floor"<<endl;
				for (int i = 0; i < heightTree(t); i++)
				{
					levelTraverse(t, i);
					cout << endl;
				}
				break;
			case 9:
				cout << "\nPlease enter the value to find";
				cin >> x;
				searchX(t, x);
				break;
			case 10:
				cout << "\nAre you sure to delete the tree (Y/N)";
				cin >> ch;
				if (ch == 'y' || ch == 'Y') {
					removeTree(t);
					cout << "\nDeleted all node in tree";
				}
				t = NULL;
				break;
			case 11:
				cout << "\nHeight of AVL tree";
				cout << heightTree(t);
				break;
		}
	} while (true);
}
