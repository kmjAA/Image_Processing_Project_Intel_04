#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h> // GUI 지원기능
#include <math.h>


/////////////// 전역 변수부

HWND hwnd;// 윈도우 화면(외부, 물리적)
HDC hdc; // 윈도우 화면(내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;

// 메모리 확보

unsigned char** inImage = NULL;
unsigned char** outImage = NULL;

/////////////// 함수 선언부

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

////////// 함수 정의부
/////////////////////
//////// 공통 함수


void printMenu() {

	puts("\n ## GrayScale Image Processing (preview 3) ##");
	puts("0.열기  1.저장  9.종료");
	puts("A.동일 B.더하기 C.빼기 D.반전 E.흑백 F.곱셈 G.나누기");
	puts("H.확대 I.축소 J.회전 K.회전(백워딩) L.이동 M.좌우미러링 N.상하미러링");
	puts("O.히스토그램 스트레칭 P.엔드-인 Q.히스토그램 평활화");
	puts("R.엠보싱 S.블러링 T.스무딩 U.샤프닝 V.샤프닝2 W.블러링(9x9) X.경계선1 Y.경계선2(프리윗) Z.경계선3(로버츠)");
	puts("!.경계선4(소벨) @.경계선5 #.회전");
	
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
	printf("파일명 : ");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);
	//(중요!!) 이미지의 폭과 높이가 결정

	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
	long long fsize = ftell(rfp); // 나 어디쯤이지?
	fclose(rfp);

	//메모리 해제
	freeInputImage();

	// 높이, 폭 구하기
	inH = inW = (int)sqrt(fsize);

	//메모리 할당
	mallocInputMemory();

	//파일에서 메모리
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++)
		fread(inImage[i], sizeof(unsigned char), inW, rfp);
	fclose(rfp);

	equalImage();
	
}

void saveImage() {
	char fullName[200] = "D:/RAW/Etc_Raw(squre)/";
	char tmpName[50];
	printf("파일명 : ");
	scanf("%s", tmpName);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");
	strcpy(fileName, fullName);

	wfp = fopen(fileName, "wb"); // 메모리에서 파일(한행씩) 저장
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	//MessageBox(hwnd, L"저장완료", L"저장창", NULL);
	printf("저장완료");
}

int getIntValue() {
	int retValue;
	printf("값 입력 : "); scanf("%d", &retValue);
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
//  영상처리 함수
////////////////////
void equalImage() { // 동일영상 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = inImage[i][k];
		}
	}
	printImage();
}

void addImage() { // 더하기 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

void subImage() { // 빼기 알고리즘


	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

void mulImage() {// 곱셈 알고리즘

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

void divImage() {//나누기 알고리즘
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

void reverseImage() {//반전 알고리즘


	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();


	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[i][k] = 255 - inImage[i][k];
		}
	}
	printImage();

}

void darkImage() { //흑백 알고리즘


	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

void zoomIn() { //확대 알고리즘
	int scale = getIntValue();

	// 메모리 해제
	freeOutputImage();

	// (중요!) 출력 이미지의 크기를 결정 
	outH = (int)(inH * scale);
	outW = (int)(inW * scale);
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < outH; i++) {
		for (int k = 0; k < outW; k++) {
			outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
	printImage();
}

void zoomOut() { //축소 알고리즘
	int scale = getIntValue();

	// 메모리 해제
	freeOutputImage();
	// (중요!) 출력 이미지의 크기를 결정 
	outH = (int)(inH / scale);
	outW = (int)(inW / scale);
	// 메모리 할당	
	mallocOutputMemory();

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {
			outImage[(int)(i / scale)][(int)(k / scale)] = inImage[i][k];
		}

	}
	printImage();

}


void rotate() { // 회전 알고리즘

	// 메모리 해제
	freeOutputImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열

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

void rotate2() { // 회전 알고리즘 + 중앙 백워딩

	// 메모리 해제
	freeOutputImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;
	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열

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


void moveImage() { // 이동 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	int val = getIntValue();
	for (int i = 0; i < inH - val; i++) {
		for (int k = 0; k < inW - val; k++) {
			outImage[i][k] = inImage[i + val][k + val];
		}
	}
	printImage();
}

void rotationImage() { // 좌우 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[i][inW - k - 1];
		}
	}
	printImage();

}

void rotationImage2() { // 상하 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int k = 0; k < inW; k++) {

			outImage[i][k] = inImage[inH - i - 1][k];
		}
	}
	printImage();

}

void histoStretch() {// 히스토그램 스트레칭 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

void endIN() { // 엔드-인 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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
void histoEqual() {// 히스토그램 평활화 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

void emboss() { //화소 영역처리 : 엠보싱 알고리즘
	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 마스크
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
	//후처리
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

void blurr() { //화소 영역처리 : 블러링 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {1. / 9,1. / 9,1. / 9}, //마스크
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

void smoot() { //화소 영역처리 : 스무딩 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {1. / 16, 1. / 8, 1. / 16}, //마스크
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
void sharp() { //화소 영역처리 : 샤프닝 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {-1, -1, -1}, //마스크
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

void sharp2() { //화소 영역처리 : 샤프닝 알고리즘

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {0, -1, 0}, //마스크
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

void blurr2() { //화소 영역처리 : 블러링 알고리즘 (9x9)

	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
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

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {0.0, 0.0, 0.0}, // 수직 에지 검출마스크
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

void edge2() { // 화소 영역처리 : 1차 미분 에지검출
	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 프리윗마스크 (행검출)
						  {0.0, 0.0, 0.0},
						  {1.0, 1.0, 1.0} };
	
	double mask2[3][3] = { {1.0, 0.0, -1.0}, // 프리윗마스크 (열검출)
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
void edge3() { // 화소 영역처리 : 1차 미분 에지검출
	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, 0.0, 0.0}, // 로버츠마스크 (행검출)
						  {0.0, 1.0, 0.0},
						  {0.0, 0.0, 0.0} };

	double mask2[3][3] = { {0.0, 0.0, -1.0}, // 로버츠마스크 (열검출)
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

void edge4() { // 화소 영역처리 : 1차 미분 에지검출
	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();
	double mask[3][3] = { {0.0, -2.0, -2.0},  //소벨마스크 
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

void edge5() { // 화소 영역처리 : 라플라시안 에지검출
	freeOutputImage();

	outH = inH;
	outW = inW;

	//메모리 할당
	mallocOutputMemory();

	double mask[3][3] = { {-1.0, -1.0, -1.0}, // 라플라시안 마스크
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

/*void rotate3() { // 회전 알고리즘 + 삭제X

	// 메모리 해제
	freeOutputImage();
	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	outH = inH;
	outW = inW;

	// 메모리 할당	
	mallocOutputMemory();
	// 입력 배열 --> 출력 배열

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