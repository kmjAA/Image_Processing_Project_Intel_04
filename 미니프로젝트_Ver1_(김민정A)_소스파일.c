#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h> // GUI �������
#include <math.h>


/////////////// ���� ������

HWND hwnd;// ������ ȭ��(�ܺ�, ������)
HDC hdc; // ������ ȭ��(����, ����)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;

// �޸� Ȯ��

unsigned char** inImage = NULL;
unsigned char** outImage = NULL;

/////////////// �Լ� �����

void loadImage(); int getIntValue(); void printImage();  void printMenu(); void saveImage();
void freeInputImage(); void freeOutputImage(); void mallocInputMemory(); void mallocOutputMemory();
double** mallocDoubleMemory(int, int); void freeDoubleMemory(double**, int);


void equalImage(); void addImage(); void subImage(); void reverseImage(); void darkImage();
void mulImage(); void divImage();  void zoomIn(); void zoomOut(); void rotate(); void rotate2();
void moveImage(); void rotationImage(); void rotationImage2();
void histoStretch(); void endIN(); void histoEqual();
void emboss(); void blurr(); void smoot(); void sharp(); void sharp2(); void blurr2();
void edge1(); void edge2(); void edge3(); void edge4(); void edge5();
//void rotate3();


void main() {

	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL);

	char inKey = 0;
	while (inKey != '9') {
		printMenu();
		inKey = _getch();
		system("cls");
		switch (inKey)
		{
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9': break;
		case 'a': case 'A': equalImage(); break;
		case 'b': case 'B': addImage(); break;
		case 'c': case 'C': subImage(); break;
		case 'd': case 'D': reverseImage(); break;
		case 'e': case 'E': darkImage(); break;
		case 'f': case 'F': mulImage(); break;
		case 'g': case 'G': divImage(); break;
		case 'h': case 'H': zoomIn(); break;
		case 'i': case 'I': zoomOut(); break;
		case 'j': case 'J': rotate(); break;	
		case 'k': case 'K': rotate2(); break;
		case 'l': case 'L': moveImage(); break;
		case 'm': case 'M': rotationImage(); break;
		case 'n': case 'N': rotationImage2(); break;
		case 'o': case 'O': histoStretch(); break;
		case 'p': case 'P': endIN(); break;
		case 'q': case 'Q':	histoEqual(); break;
		case 'r': case 'R':	emboss(); break;
		case 's': case 'S':	blurr(); break;
		case 't': case 'T':	smoot(); break;
		case 'u': case 'U':	sharp(); break;
		case 'v': case 'V':	sharp2(); break;
		case 'w': case 'W':	blurr2(); break;
		case 'x': case 'X': edge1(); break;
		case 'y': case 'Y': edge2(); break;
		case 'z': case 'Z': edge3(); break;
		case '!': edge4(); break;
		case '@': edge5(); break;
		//case '#': rotate3(); break;

		}
	
		
	}
	freeInputImage();
	freeOutputImage();
}

////////// �Լ� ���Ǻ�
/////////////////////
//////// ���� �Լ�


void printMenu() {

	puts("\n ## GrayScale Image Processing (preview 3) ##");
	puts("0.����  1.����  9.����");
	puts("A.���� B.���ϱ� C.���� D.���� E.��� F.���� G.������");
	puts("H.Ȯ�� I.��� J.ȸ�� K.ȸ��(�����) L.�̵� M.�¿�̷��� N.���Ϲ̷���");
	puts("O.������׷� ��Ʈ��Ī P.����-�� Q.������׷� ��Ȱȭ");
	puts("R.������ S.���� T.������ U.������ V.������2 W.����(9x9) X.��輱1 Y.��輱2(������) Z.��輱3(�ι���)");
	puts("!.��輱4(�Һ�) @.��輱5 #.ȸ��");
	
}


void printImage() {

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int px = outImage[i][k];
			SetPixel(hdc, k + 50, i + 250, RGB(px, px, px));
		}
	}
}

void loadImage() {

	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ� : ");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);
	//(�߿�!!) �̹����� ���� ���̰� ����

	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // �� ���������?
	fclose(rfp);

	//�޸� ����
	freeInputImage();

	// ����, �� ���ϱ�
	inH = inW = (int)sqrt(fsize);

	//�޸� �Ҵ�
	mallocInputMemory();

	//���Ͽ��� �޸�
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
	
}

void saveImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("���ϸ� : ");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb"); // �޸𸮿��� ����(���྿) ����
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	//MessageBox(hwnd, L"����Ϸ�", L"����â", NULL);
	printf("����Ϸ�");
}

int getIntValue() {
	int retValue;
	printf("�� �Է� : "); scanf("%d", &retValue);
	return retValue;
}

void freeInputImage() {
	if (inImage == NULL)
		return;

	for (int i = 0; i < inH; i++)
		free(inImage[i]);
	free(inImage);
	inImage = NULL;
}

void freeOutputImage() {
	if (outImage == NULL)
		return;

	for (int i = 0; i < outH; i++)
		free(outImage[i]);
	free(outImage);
	outImage = NULL;
}

void mallocInputMemory() {

	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++)
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
}

void mallocOutputMemory() {

	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++)
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
}

double** mallocDoubleMemory(int h, int w) {

	double** retMemory;
	retMemory = (double**)malloc(sizeof(double*) * h);

	for (int i = 0; i < h; i++)
		retMemory[i] = (double*)malloc(sizeof(double) * w);
	return retMemory;
}
void freeDoubleMemory(double** memory, int h) {
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
	memory = NULL;
}


//////////////////
//  ����ó�� �Լ�
////////////////////
void equalImage() { // ���Ͽ��� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // ���ϱ� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] + val < 255)
				outImage[i][k] = inImage[i][k] + val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void subImage() { // ���� �˰���


	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] - val > 0)
				outImage[i][k] = inImage[i][k] - val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void mulImage() {// ���� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] * val < 255)
				outImage[i][k] = inImage[i][k] * val;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void divImage() {//������ �˰���
	freeOutputImage();

	outH = inH;
	outW = inW;

	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] / val > 0)
				outImage[i][k] = inImage[i][k] / val;
			else
				outImage[i][k] = 0;
		}
	}
	printImage();
}

void reverseImage() {//���� �˰���


	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();

}

void darkImage() { //��� �˰���


	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] <= 128)
				outImage[i][k] = 0;
			else
				outImage[i][k] = 255;
		}
	}
	printImage();
}

void zoomIn() { //Ȯ�� �˰���
	int scale = getIntValue();

	// �޸� ����
	freeOutputImage();

	// (�߿�!) ��� �̹����� ũ�⸦ ���� 
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}

void zoomOut() { //��� �˰���
	int scale = getIntValue();

	// �޸� ����
	freeOutputImage();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� 
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// �޸� �Ҵ�	
	mallocOutputMemory();

	// �Է� �迭 --> ��� �迭
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}

	}
	printImage();

}


void rotate() { // ȸ�� �˰���

	// �޸� ����
	freeOutputImage();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)(cos(radian) * xs - sin(radian) * ys);
			int yd = (int)(sin(radian) * xs + cos(radian) * ys);

			if ((0 <= xd && xd < outH) && (0 <= yd && yd < outW))
				outImage[xd][yd] = inImage[xs][ys];

		}
	}
	printImage();
}

void rotate2() { // ȸ�� �˰��� + �߾� �����

	// �޸� ����
	freeOutputImage();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;
	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭

	int degree = getIntValue();
	double radian = degree * 3.141592 / 180.0;
	// xd = cos*xs - sin*ys
	// yd = sin*xs + cos*ys

	int cx = inH / 2;
	int cy = inW / 2;
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;

			if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[xd][yd] = inImage[xs][ys];

		}
	}
	printImage();
}


void moveImage() { // �̵� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH - val; i++) {
		for (int k = 0; k < inW - val; k++) {
			outImage[i][k] = inImage[i + val][k + val];
		}
	}
	printImage();
}

void rotationImage() { // �¿� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[i][inW - k - 1];
		}
	}
	printImage();

}

void rotationImage2() { // ���� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[inH - i - 1][k];
		}
	}
	printImage();

}

void histoStretch() {// ������׷� ��Ʈ��Ī �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int old = inImage[i][k];
			int new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}
	printImage();
}

void endIN() { // ����-�� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int val = getIntValue();

	int high = inImage[0][0], low = inImage[0][0];
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (inImage[i][k] < low)
				low = inImage[i][k];
			if (inImage[i][k] > high)
				high = inImage[i][k];
		}
	}
	high -= val;
	low += val;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			int old = inImage[i][k];
			int new = (int)((double)(old - low) / (double)(high - low) * 255.0);
			if (new > 255)
				new = 255;
			if (new < 0)
				new = 0;
			outImage[i][k] = new;
		}
	}

	printImage();
}
void histoEqual() {// ������׷� ��Ȱȭ �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	int histo[256] = { 0, };
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			histo[inImage[i][k]]++;
		}
	}

	int sumhisto[256] = { 0, };
	sumhisto[0] = histo[0];
	for (int i = 0; i < 256; i++)
		sumhisto[i] = sumhisto[i - 1] + histo[i];


	double normalhisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++)
		normalhisto[i] = sumhisto[i] * (1.0 / (inH * inW)) * 255.0;

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = (unsigned char)normalhisto[inImage[i][k]];
		}
	}

	printImage();
}

void emboss() { //ȭ�� ����ó�� : ������ �˰���
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // ����ũ
						  {0.0, 0.0, 0.0},
						  {0.0, 0.0, 1.0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					B += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = B;
		}
	}
	//��ó��
	for (int i = 0; i < outH; i++)
		for (int k = 0; k < outW; k++)
			tmpOutImage[i][k] += 128.0;


	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}

void blurr() { //ȭ�� ����ó�� : ���� �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {1. / 9,1. / 9,1. / 9}, //����ũ
						  {1. / 9,1. / 9,1. / 9},
						  {1. / 9,1. / 9,1. / 9} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					B += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();

}

void smoot() { //ȭ�� ����ó�� : ������ �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, //����ũ
						  {1. / 8, 1. / 4, 1. / 8},
						  {1. / 16, 1. / 8, 1. / 16} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					B += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();

}
void sharp() { //ȭ�� ����ó�� : ������ �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {-1, -1, -1}, //����ũ
						  {-1,  9, -1},
						  {-1, -1, -1} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					B += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();

}

void sharp2() { //ȭ�� ����ó�� : ������ �˰���

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {0, -1, 0}, //����ũ
						   {-1, 5, -1},
						   {0, -1, -0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;

		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int n = 0; n < 3; n++) {
				for (int m = 0; m < 3; m++)
					B += tmpInImage[i + n][k + m] * mask[n][m];

				tmpOutImage[i][k] = B;
			}
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();
}

void blurr2() { //ȭ�� ����ó�� : ���� �˰��� (9x9)

	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[9][9] = { {1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81},
						  { 1. / 81, 1. / 81, 1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81,  1. / 81} };

	double** tmpInImage = mallocDoubleMemory(inH + 8, inW + 8);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 8; i++) {
		for (int k = 0; k < inW + 8; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int n = 0; n < 9; n++) {
				for (int m = 0; m < 9; m++) {
					B += tmpInImage[i + n][k + m] * mask[n][m];
					tmpOutImage[i][k] = B;
				}
			}
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];


		}
	}

	freeDoubleMemory(tmpInImage, inH + 8);
	freeDoubleMemory(tmpOutImage, outH);
	printImage();

}

void edge1() { // 
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {0.0, 0.0, 0.0}, // ���� ���� ���⸶��ũ
						  {-1.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };
;

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					B += tmpInImage[i + m][k + n] * mask[m][n];

			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edge2() { // ȭ�� ����ó�� : 1�� �̺� ��������
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // ����������ũ (�����)
						  {0.0, 0.0, 0.0},
						  {1.0, 1.0, 1.0} };
	
	double mask2[3][3] = { {1.0, 0.0, -1.0}, // ����������ũ (������)
						  {1.0, 0.0, -1.0},
						  {1.0, 0.0, -1.0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B,C,D;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0,C=0.0,D=0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++) {
					B += tmpInImage[i + m][k + n] * mask[m][n];
					C += tmpInImage[i + m][k + n] * mask2[m][n];
				}
			D = B + C;
			tmpOutImage[i][k] = D;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}
void edge3() { // ȭ�� ����ó�� : 1�� �̺� ��������
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // �ι�������ũ (�����)
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };

	double mask2[3][3] = { {0.0, 0.0, -1.0}, // �ι�������ũ (������)
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B, C, D;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0, C = 0.0, D = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++) {
					B += tmpInImage[i + m][k + n] * mask[m][n];
					C += tmpInImage[i + m][k + n] * mask2[m][n];
				}
			D = B + C;
			tmpOutImage[i][k] = D;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edge4() { // ȭ�� ����ó�� : 1�� �̺� ��������
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();
	double mask[3][3] = { {0.0, -2.0, -2.0},  //�Һ�����ũ 
						  {2.0, 0.0, -2.0},
						  {2.0, 2.0, 0.0} };

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++) {
					B += tmpInImage[i + m][k + n] * mask[m][n];
				}
			
			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

void edge5() { // ȭ�� ����ó�� : ���ö�þ� ��������
	freeOutputImage();

	outH = inH;
	outW = inW;

	//�޸� �Ҵ�
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // ���ö�þ� ����ũ
						  {-1.0, 8.0, -1.0},
						  {-1.0, -1.0, -1.0} };

	

	double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
	double** tmpOutImage = mallocDoubleMemory(outH, outW);

	for (int i = 0; i < inH + 2; i++) {
		for (int k = 0; k < inW + 2; k++) {
			tmpInImage[i][k] = 128;
		}
	}

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			tmpInImage[i + 1][k + 1] = inImage[i][k];
		}
	}

	double B;
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			B = 0.0;
			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++) {
					B += tmpInImage[i + m][k + n] * mask[m][n];
					
				}
			
			tmpOutImage[i][k] = B;
		}
	}

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				outImage[i][k] = 255;
			else
				outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}

	}

	freeDoubleMemory(tmpInImage, inH + 2);
	freeDoubleMemory(tmpOutImage, outH);

	printImage();
}

/*void rotate3() { // ȸ�� �˰��� + ����X

	// �޸� ����
	freeOutputImage();
	// (�߿�!) ��� �̹����� ũ�⸦ ���� ---> �˰��� ����
	outH = inH;
	outW = inW;

	// �޸� �Ҵ�	
	mallocOutputMemory();
	// �Է� �迭 --> ��� �迭

	int degree = getIntValue();
	//double radian = degree * 3.141592 / 180.0;
	
	int cx = inH / 2;
	int cy = inW / 2;
	//int xd = (int)inH * cos(90 - degree) + cos(degree);
	//int yd = (int)inH * cos(degree) + inW * cos(90 - degree);

	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			int xs = i;
			int ys = k;
			int xd = (int)inH * cos(90 - degree) + cos(degree);
			int yd = (int)inH * cos(degree) + inW * cos(90 - degree);


			if ((0 <= xd || xd > outH) && (0 <= yd || yd > outW))
				outImage[xd][yd] = 0;
			else
				outImage[xd][yd] = inImage[xs][ys];
		}
	}
	printImage();
}*/