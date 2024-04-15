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
		cout << "\n0.Thoat";
		cout << "\n1.Tao cay AVL";
		cout << "\n2.Them mot nut vao cay AVL";
		cout << "\n3.Xoa mot nut trong cay AVL";
		cout << "\n4.Duyet cay LNR";
		cout << "\n5.Duyet cay NLR";
		cout << "\n6.Duyet cay LRN";
		cout << "\n7.Duyet theo tang";
		cout << "\n8.Duyet theo tang toan bo cay AVL";
		cout << "\n9.Tim kiem mot nut trong cay AVL";
		cout << "\n10.Xoa toan bo cac nut trong cay AVL";
		cout << "\n11.Chieu cao cua cay AVL";
		cout << "\n12.Ghi File AVL";
		cout << "\n13.Doc File AVL";
		cout << "\n==> Vui long chon chuc nang ";
		cin >> chon;
		if (chon == 0)	break;
		switch (chon)
		{
			case 1:
				createAVL(t);
				cout << "\n-->Da tao cay thanh cong, vui long xem lai ";
				break;
			case 2:
				cout << "\nVui long nhap gia tri can them ";cin >> x;
				insertNode(t, x);
				cout << "\n-->Da them thanh cong, vui long xem lai ";
				break;
			case 3:
				cout << "\nVui long nhap nut can xoa";cin >> x;
				delNode(t, x);
				cout << "\n-->Da xoa thanh cong, vui long xem lai ";
				break;
			case 4:
				cout << "\nDuyet cay LNR";
				LNR(t);
				break;
			case 5:
				cout << "\nDuyet cay NLR";
				NLR(t);
				break;
			case 6:
				cout << "\nDuyet cay LRN";
				LRN(t);
				break;
			case 7:
				cout << "\nVui long nhap ta^`ng can xuat ra";cin >> k;
				levelTraverse(t, k);
				break;
			case 8:
				cout << "\nToan bo cay AVL xuat theo tang"<<endl;
				for (int i = 0; i < heightTree(t); i++)
				{
					levelTraverse(t, i);
					cout << endl;
				}
				break;
			case 9:
				cout << "\nVui long nhap gia tri can tim";
				cin >> x;
				searchX(t, x);
				break;
			case 10:
				cout << "\nBan co chac xoa toan bo cay AVL (Y/N)";
				cin >> ch;
				if (ch == 'y' || ch == 'Y') {
					removeTree(t);
					cout << "\nDa xoa toan bo cac nut trong cay";
				}
				t = NULL;
				break;
			case 11:
				cout << "\nChieu cao cua cay AVL";
				cout << heightTree(t);
				break;
		}
	} while (true);
}