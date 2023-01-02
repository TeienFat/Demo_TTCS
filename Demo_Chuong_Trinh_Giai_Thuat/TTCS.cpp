#include<iostream>
using namespace std;

// Khai bao cau truc Node
struct Node{
	int info;
	Node *left, *right;
};
Node *goc; // khai bao con tro Node goc
void khoitao(Node *&goc)
{
	goc = NULL;
}

int tongsonut (Node *goc) //ham tinh tong so nut hien co cua cay
{
	if(goc == NULL) return 0;
	else return 1 + tongsonut(goc->left) + tongsonut(goc->right);
}

void mocnut(Node *&goc, int x) //ham moc mot nut moi vao cay
{
	if(goc == NULL)
	{
		goc = new Node;
		goc->info =x;
		goc->left = NULL;
		goc->right = NULL;
	}
	else
	{
		if(goc->info >= x)
		{
			mocnut(goc->left,x);
		}
		else
		{
			mocnut(goc->right,x);
		}
	}
}
void taocay(Node *&goc) //ham tao cay nhi phan tim kiem moi
{
	int tam;
	do
	{
		cout << "Nhap 1 so nguyen, 0 de dung: ";
		cin >> tam;
		if(tam!=0)
		{
			mocnut(goc,tam);
		}
	}
	while(tam!=0 && tongsonut(goc) <20);
	if(tongsonut(goc) == 20 ) cout << "\nSo nut cua cay la 20 nut! Da du theo yeu cau!!!\n";
}

void NLR(Node *goc) // ham duyet cay theo NLR
{
	if(goc!=NULL)
	{
		cout << goc->info << " ";
		NLR(goc->left);
		NLR(goc->right);
	}
}
void taoCayGuong(Node *&goc) //ham tao cay guong
{
	Node *temp;
	if (goc!=NULL)
	{
		temp = goc->right;
		goc->right = goc->left;
		goc->left = temp;
		taoCayGuong(goc->left);
		taoCayGuong(goc->right);
	}
}


int main()
{
	khoitao(goc);
	cout << "\nNhap lan luot cac nut cua cay\tNhap Node goc dau tien\n";
	taocay(goc);
	cout << "\nDuyet cay nhi phan theo thu tu N L R: ";
	NLR(goc);
	cout << "\nDuyet guong soi cua cay nhi phan theo thu tu N L R: ";
	taoCayGuong(goc);
	NLR(goc);
	
}
