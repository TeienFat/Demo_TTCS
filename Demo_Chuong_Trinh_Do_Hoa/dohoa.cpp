// Chuong trinh hien thi cay guong cua cay nhi phan tim kiem
// Minh hoa bang do hoa 
#include <graphics.h>
#include <iostream>
using namespace std;
int NGANG = 1920;
int DOC = 800;
int Radio = 23;
int DistanciaX = 20;
int DistanciaY = 80;

struct Node{
	int info;
	Node *left, *right;
};
Node *goc;
Node *goc1; // khai bao con tro Node goc
//------------------------------------Cac ham xu ly cay nhi phan tim kiem----------------------------------------------
void khoitao(Node*&);
void mocnut(Node*&, int);
int tongsonut (Node*);
int tongsonuttrai (Node*);
int tongsonutphai (Node*);
void saoChep(Node*, Node*&);
void taoCayGuong(Node*&);
void taocay(Node*&);

//-----------------------------------Cac ham tao giao dien va xu ly do hoa---------------------------------------------
bool inputAscii(char);
void setTextPrintStyle(int);
bool getInputChar(char*, int, bool(*)(char ));
int veNODE(int, int, int);
int veEdge(int, int, int, int);
void veCay(Node*, int, int);
void taomanhinh();
void drawWorkingZone();
void drawWorkingZone2();
void drawWindow();
void drawTextZone();
//------------------------------------------------Ham main-------------------------------------------------------------
int main()
{
	khoitao(goc);
	khoitao(goc1);
	drawWindow();
	taocay(goc);
	getch();
	closegraph();
}
//----------------------------------------------------------------------------------------------------------------------
void khoitao(Node *&goc)
{
	goc = NULL;
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
int tongsonut (Node *goc) //ham tinh tong so nut hien co cua cay
{
	if(goc == NULL) return 0;
	else return 1 + tongsonut(goc->left) + tongsonut(goc->right);
}

int tongsonuttrai (Node *goc) //ham tinh tong so con trai cua 1 goc
{
	if(goc == NULL) return 0;
	else return 1 + tongsonut(goc->left);
}
int tongsonutphai (Node *goc) //ham tinh tong so con phai cua 1 goc
{
	if(goc == NULL) return 0;
	else return 1 + tongsonut(goc->right);
}
void taocay(Node *&goc) //ham tao cay nhi phan tim kiem moi
{
	char ip[3];
	int tam;
	do
	{
		getInputChar(ip,3,inputAscii);
		tam = atoi(ip);
		if(tam!=0)
		{
			mocnut(goc,tam);
			drawWorkingZone();
			drawTextZone();
			veCay(goc,350,100);
			drawWorkingZone2();
			drawTextZone();
			veCay(goc,1150,100);
			saoChep(goc,goc1);
			taoCayGuong(goc1);
			delay(500);
			drawWorkingZone2();
			drawTextZone();
			veCay(goc1,1150,100);
		}
	}
	while(tam!=0 && tongsonut(goc) <20);
	

}
void saoChep(Node *goc, Node *&goc1)
{
	if(goc == NULL)
	goc1 = NULL;
	else
	{
	goc1 = new Node;
	goc1->info = goc->info;
	saoChep(goc->left, goc1->left);
	saoChep(goc->right, goc1->right);
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
bool inputAscii(char k)
{
	k = toupper(k);
	return (k >= 'A' && k <= 'Z') || (k >= '0' && k <= '9');
}
void setTextPrintStyle(int color)
{
	setusercharsize(9, 10, 9, 10);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	setbkcolor(BLACK);
	setcolor(color);
	settextjustify(LEFT_TEXT, TOP_TEXT);
}
bool getInputChar(char *str, int max, bool (*checkKey)(char key))
{
	setTextPrintStyle(BLUE);
	int i = 0; str[0] = '\0';
	char key[2] = {'\0', '\0'};
	while (i < max)
	{
		if (kbhit())
		{
			key[0] = getch();
			if (key[0] == 13) break;
			if (key[0] == 27) closegraph();
			if (key[0] == 8 && i > 0) 
			{
				--i; 
				key[0] = str[i]; 
				str[i] = '\0';
				drawTextZone();
			}
			else if (checkKey(key[0])) 
			{
				strcat(str, key);
				++i;
				settextstyle(COMPLEX_FONT, HORIZ_DIR,8);
				settextjustify(LEFT_TEXT, TOP_TEXT);
				setcolor(BLUE);
				setbkcolor(WHITE);
				outtextxy(730,DOC-120, str);
			}
		}
	}
	return (i > 0);
}

int veNODE(int x, int y, int value)
{

	ostringstream str1;
	str1 << value;

	string str2 = str1.str();
	char* str = &str2[0u];

	setlinestyle(SOLID_LINE, 0, 2);
	setcolor(BLACK);

	
	setfillstyle(1,GREEN); 
 	fillellipse( x, y, Radio, Radio);

	
	settextstyle(COMPLEX_FONT, HORIZ_DIR,2);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(YELLOW);
	setbkcolor(GREEN);
	outtextxy(x - 10, y - 12, str);
}

int veEdge(int x1, int y1, int x2, int y2)
{
	setlinestyle(SOLID_LINE, 0, 3);
	setcolor(RED);
	line(x1,y1+Radio,x2,y2-Radio);
	
}

void veCay(Node *goc, int x, int y)
{
	int nl = tongsonuttrai(goc) -1;
	int nr = tongsonutphai(goc) -1;

	if(goc!=NULL)
	{
		veNODE(x, y,goc->info);
		if(goc->left != NULL) veEdge(x,y,x-(DistanciaX * nl),y+DistanciaY);
		if(goc->right!= NULL) veEdge(x,y,x+(DistanciaX * nr),y+DistanciaY);
		veCay(goc->left,x-(DistanciaX * nl),y+DistanciaY);
		veCay(goc->right,x+(DistanciaX * nr),y+DistanciaY);
	}
}
void taomanhinh()
{
	setusercharsize(1, 1, 1, 1);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(RED);
	setbkcolor(YELLOW);
	
	setusercharsize(1, 1, 1, 1);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setcolor(RED);
	setbkcolor(YELLOW);
}

void drawWorkingZone()
{
	setfillstyle(SOLID_FILL,11);
	bar(0, 0, 760, DOC);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 1, 3);
	rectangle(0, 0, 760, DOC);
	setusercharsize(1, 1, 1, 1);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setbkcolor(GREEN);
	setcolor(YELLOW);
	outtextxy(280, 5, "CAY GOC");
}
void drawWorkingZone2()
{
	setfillstyle(SOLID_FILL,11);
	bar(760, 0, 1920, DOC);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 1, 3);
	rectangle(760, 0, 1920, DOC);
	setusercharsize(1, 1, 1, 1);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setbkcolor(GREEN);
	setcolor(YELLOW);
	outtextxy(1080, 5, "CAY GUONG");
}
void drawTextZone()
{
	setfillstyle(SOLID_FILL, WHITE);
	bar(640, DOC-250, 880,DOC-16);
	setcolor(BLACK);
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(640, DOC-250, 880,DOC-16);
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setbkcolor(WHITE);
	setcolor(RED);
	outtextxy(670, DOC-245, "NHAP GIA TRI NODE");
	outtextxy(710, DOC-225, "MUON THEM");
	outtextxy(665, DOC-205, "NHAN ENTER DE THEM");
	outtextxy(670, DOC-185, "NHAN ESC DE THOAT");
	if(tongsonut(goc) == 20)
	{
		settextstyle(COMPLEX_FONT, HORIZ_DIR,1);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		setcolor(BLUE);
		setbkcolor(WHITE);
		outtextxy(645,DOC-155, "SO LUONG NUT HIEN TAI");
		outtextxy(655,DOC-55, "DA QUA GIOI HAN NUT");		
		settextstyle(COMPLEX_FONT, HORIZ_DIR,8);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		setcolor(BLUE);
		setbkcolor(WHITE);
		outtextxy(710,DOC-135, "20");
	}
}
void drawWindow()
{
	initwindow(NGANG,DOC);
	setbkcolor(WHITE);
	setfillstyle(CLOSE_DOT_FILL, BLACK);
	bar(0, 0, NGANG, DOC);
	taomanhinh();
	drawWorkingZone();
	drawWorkingZone2();
	drawTextZone();
}


