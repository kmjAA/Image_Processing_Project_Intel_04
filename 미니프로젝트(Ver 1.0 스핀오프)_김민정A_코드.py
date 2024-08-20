import math
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import os.path

# 함수부
#****************
# 공통 함수부
#*****************

def malloc2D(h, w, initValue=0) :
    memory = [[initValue for _ in range(w)] for _ in range(h)]
    return memory
def openImage() :
    global window, canvas, paper,fullname
    global inImage, outImage, inH, inW, outH, outW
    fullname = askopenfilename(parent=window, filetypes=(('RAW파일', '*.raw'), ('모든파일', '*.*')))
    #중요! 입력 이미지 크기를 결정
    fsize = os.path.getsize(fullname) #파일 크기(byte)
    inH =inW= int(math.sqrt(fsize))

    #메모리 할당
    inImage =malloc2D(inH, inW)

    #파일 -> 메모리
    rfp = open(fullname, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage[i][k] = ord(rfp.read(1))
    rfp.close()
    equalImage()


def saveImage():
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    if (outImage == None or len(outImage)==0):  # 영상처리를 한적이 없다면
        return

    wfp = asksaveasfile(parent=window, mode="wb", defaultextension='*.raw',
                        filetypes=(('RAW파일', '*.raw'), ('모든파일', '*.*')))
    import struct
    for i in range(outH):
        for k in range(outW):
            wfp.write(struct.pack('B', outImage[i][k]))

    wfp.close()
    messagebox.showinfo("성공", wfp.name + "저장완료")

def displayImage() :
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 기존에 이미지를 오픈한적이 있으면 캔버스 뜯어내기
    if (canvas != None) :
        canvas.destroy()

    # 벽, 캔벗, 종이 설정
    window.geometry(str(outH)+"x"+str(outW)) # 512x512
    canvas = Canvas(window, height=outH, width=outW, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outW)  # 종이
    canvas.create_image((outH // 2, outW // 2), image=paper, state='normal')

    #더블 버퍼링 과 비슷한 기법(모두 다 메모리상에 출력형태로 생성한 후에, 한방에 출력)
    rgbString = "" #전체에 대한 16진수 문자열
    for i in range(outH) :
        oneString = "" #한줄에 대한 16진수 문자열
        for k in range(outW) :
            r = g= b = outImage[i][k]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += "{" + oneString + "} "
    paper.put(rgbString)

    canvas.pack()

#****************
# 영상 처리 함수부
#*****************
def equalImage() : # 동일 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(inH) :
        for k in range(inW) :
            outImage[i][k] = inImage[i][k]

    displayImage()

def addImage() : # 밝게/어둡게 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    value = askinteger("정수 입력", "-255~255 입력", maxvalue=255, minvalue=-255)
    for i in range(inH) :
        for k in range(inW) :
            px = inImage[i][k] + value
            if(px > 255) :
                px = 255
            if (px < 0) :
                px = 0
            outImage[i][k] = px

    displayImage()

def mulImage() : # 밝게/어둡게 이미지
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    #중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    value = askinteger("정수 입력", "-5~5 입력", maxvalue=5, minvalue=-5)
    for i in range(inH) :
        for k in range(inW) :
            if (value > 0) :
                px = inImage[i][k] * value
                if(px > 255) :
                    px = 255
                if (px < 0) :
                    px = 0
                outImage[i][k] = px
            if (value < 0) :
                px = inImage[i][k] // abs(value)
                if (px > 255):
                    px = 255
                if (px < 0):
                    px = 0
                outImage[i][k] = px

    displayImage()

def andImage() : # and연산 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    value = askinteger("정수 입력", "0~255 입력", maxvalue=255, minvalue=0)
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] & value
            if(px > 255) :
                px = 255
            if(px < 0) :
                px = 0
            outImage[i][k] = px
    displayImage()

def orImage() : # or연산 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    value = askinteger("정수 입력", "0~255 입력", maxvalue=255, minvalue=0)
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] | value
            if(px > 255) :
                px = 255
            if(px < 0) :
                px = 0
            outImage[i][k] = px
    displayImage()

def xorImage() : # xor연산 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    value = askinteger("정수 입력", "0~255 입력", maxvalue=255, minvalue=0)
    for i in range(inH):
        for k in range(inW):
            px = inImage[i][k] ^ value
            if(px > 255) :
                px = 255
            if(px < 0) :
                px = 0
            outImage[i][k] = px
    displayImage()



def reverseImage() : # 반전 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = 255- inImage[i][k]

    displayImage()

def blackImage() : # 흑백 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW
    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            if(inImage[i][k] < 128) :
                outImage[i][k] = 0
            else :
                outImage[i][k] = 255

    displayImage()


def zoomIn() : # 확대 포워딩 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("확대 입력", "0~5 입력", maxvalue=5, minvalue=0)

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = int(inH * value)
    outW = int(inW * value)
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            outImage[int(i*value)][int(k*value)] = inImage[i][k]

    displayImage()
def zoomIn2() : # 확대 백워딩 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("확대 입력", "0~5 입력", maxvalue=5, minvalue=0)

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = int(inH * value)
    outW = int(inW * value)
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(outH):
        for k in range(outW):
            outImage[i][k] = inImage[int(i/value)][int(k/value)]

    displayImage()


def zoomOut() : # 축소 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("축소 입력", "0~5 입력", maxvalue=5, minvalue=0)

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = int(inH / value)
    outW = int(inW / value)
    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            outImage[int(i/value)][int(k/value)] = inImage[i][k]

    displayImage()
def rotate():  # 회전 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("정수 입력", "0~360 입력", maxvalue=360, minvalue=0)

    radian = math.radians(value)

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 메모리 할당
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            xs = i
            ys = k
            xd = int(math.cos(radian) * xs - math.sin(radian) * ys)
            yd = int(math.sin(radian) * xs + math.cos(radian) * ys)

            if((0 <=xd and xd < outH) and (0<=yd and yd <outW)):
                outImage[xd][yd] = inImage[xs][ys]

    displayImage()



def rotate2():  # 회전 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("정수 입력", "0~360 입력", maxvalue=360, minvalue=0)
    radian = int(math.radians(value))

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    cx = inH // 2
    cy = inW // 2
    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            xd = i
            yd = k

            xs = int(math.cos(radian) * (xd - cx) + math.sin(radian) * (yd - cy))
            ys = int(-math.sin(radian) * (xd - cx) + math.cos(radian) * (yd - cy))
            xs += cx
            ys += cy

            if ((0 <= xs and xs < outH) and (0 <= ys and ys < outW)):
                outImage[xd][yd] = inImage[xs][ys]

    displayImage()

def moveImage():  # 이동 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    value = askinteger("정수 입력", "0~300 입력", maxvalue=300, minvalue=0)

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    for i in range(inH - value):
        for k in range(inW - value):
            outImage[i][k] = inImage[i + value][k + value]

    displayImage()


def rotationImage():  # 좌우 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = inImage[i][inW-k-1]

    displayImage()

def rotation2Image():  # 상하 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = inImage[inH-i-1][k]

    displayImage()

def histoStretch():  # 히스토그램 스트레칭
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < low) :
                low = inImage[i][k]
            if (inImage[i][k] > high) :
                high = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = (int)((old - low) / (high - low) * 255.0)
            if (new > 255):
                new = 255
            if (new < 0):
                new = 0
            outImage[i][k] = new

    displayImage()

def endIN():  # 엔드 - 인
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    high = inImage[0][0]
    low = inImage[0][0]
    for i in range(inH):
        for k in range(inW):
            if (inImage[i][k] < low):
                low = inImage[i][k]
            if (inImage[i][k] > high):
                high = inImage[i][k]

    high -= 50
    low += 50

    for i in range(inH):
        for k in range(inW):
            old = inImage[i][k]
            new = int(((old - low) / (high - low) * 255))
            if (new > 255):
                new = 255
            if (new < 0):
                new = 0
            outImage[i][k] = new

    displayImage()

def histoEqual():  # 히스토그램 평활화
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    # 진짜 영상처리 알고리즘
    histo = [0 for _ in range(256)]
    for i in range(inH):
        for k in range(inW):
            histo[inImage[i][k]] += 1

    sumhisto = [0 for _ in range(256)]
    sumhisto[0] = histo[0]
    for i in range(256):
        sumhisto[i] = sumhisto[i - 1] + histo[i]

    normalhisto = [1 for _ in range(256)]
    for i in range(256):
        normalhisto[i] = sumhisto[i] * (1 / (inH * inW)) * 255

    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = (int)(normalhisto[inImage[i][k]])

    displayImage()

def emboss():  #  영역처리 : 엠보싱
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)


    mask = [[-1, 0, 0],  ## 마스크
            [0, 0, 0],
            [0, 0, 1]]


    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH) :
        for k in range(inW) :
            tmpInImage[i+1][k+1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3) :
                for n in range(3) :
                    B += tmpInImage[i+m][k+n] * mask[m][n]

            tmpOutImage[i][k] = B

    for i in range(outH) : # 후처리
        for k in range(outW) :
            tmpOutImage[i][k] += 128

    for i in range(outH) :
        for k in range(outW) :
            if(tmpOutImage[i][k] < 0) :
                outImage[i][k] = 0
            elif(tmpOutImage[i][k] > 255) :
                outImage[i][k] = 255
            else :
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def blurr() :  #화소 영역처리 : 블러링 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[1./9, 1./9, 1./9],  ## 마스크
            [1./9, 1./9, 1./9],
            [1./9, 1./9, 1./9]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

            tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def blurr2() :  #화소 영역처리 : 블러링 알고리즘(9x9)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],  ## 마스크
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81],
            [1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81, 1./81]]

    tmpInImage = malloc2D(inH + 8, inW + 8)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 8):
        for k in range(inW + 8):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(9):
                for n in range(9):
                    B += tmpInImage[i + m][k + n] * mask[m][n]
                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def smoot() : #화소 영역처리 : 스무딩 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[1. / 16, 1. / 8, 1. / 16],  ## 마스크
            [1. / 8, 1. / 4, 1. / 8],
            [1. / 16, 1. / 8, 1. / 16]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

            tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def sharp() : #화소 영역처리 : 샤프닝 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[-1, -1, -1],  ## 마스크
            [-1, 9, -1],
            [-1, -1, -1]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]


    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def sharp2() : #화소 영역처리 : 샤프닝 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[0, -1, 0],  ## 마스크
            [-1, 5, -1],
            [0, -1, 0]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]


    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def sharp3() : #화소 영역처리 : 고주파 샤프닝 알고리즘
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[-1. / 9, -1. / 9, -1. / 9],  ## 마스크
            [-1. / 9, 8. / 9, -1. / 9],
            [-1. / 9, -1. / 9, -1. / 9]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]


    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge1() : #화소 영역처리 : 이동과 차분 (수직에지)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[0, 0, 0],  ## 마스크
            [-1, 1, 0],
            [0, 0, 0]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge1_1() : #화소 영역처리 : 이동과 차분 (수평에지)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[0, -1, 0],  ## 마스크
            [0, 1, 0],
            [0, 0, 0]]

    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]

                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge2() : #화소 영역처리 : 1차 미분 에지검출 (프리윗)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[0, -1, -2],  ## 프리윗마스크(합성에지)
             [1, 0, -1],
             [2, 1, 0]]


    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]
                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge3() : #화소 영역처리 : 1차 미분 에지검출 (로버츠)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)


    mask = [[-1, 0, -1],  ## 로버츠마스크(합성에지)
             [0, 2, 0],
             [0, 0, 0]]


    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                    B += tmpInImage[i + m][k + n] * mask[m][n]
                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge4() : #화소 영역처리 : 1차 미분 에지검출 (소벨)
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)


    mask = [[0, -2, -2],  ## 소벨(합성에지)
             [2, 0, -2],
             [2, 2, 0]]


    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):

                    B += tmpInImage[i + m][k + n] * mask[m][n]
                    tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()

def edge5() : #화소 영역처리 : 라플라시안 에지검출
    global window, canvas, paper, fullname
    global inImage, outImage, inH, inW, outH, outW

    # 중요! 출력 영상 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW

    # 메모리 할당
    outImage = malloc2D(outH, outW)

    mask = [[-1, -1, -1],  ## 라플라시안 마스크
            [-1, 8, -1],
            [-1, -1, -1]]


    tmpInImage = malloc2D(inH + 2, inW + 2)
    tmpOutImage = malloc2D(outH, outW)

    for i in range(inH + 2):
        for k in range(inW + 2):
            tmpInImage[i][k] = 128

    for i in range(inH):
        for k in range(inW):
            tmpInImage[i + 1][k + 1] = inImage[i][k]

    for i in range(inH):
        for k in range(inW):
            B = 0
            for m in range(3):
                for n in range(3):
                     B += tmpInImage[i + m][k + n] * mask[m][n]

                     tmpOutImage[i][k] = B

    for i in range(outH):
        for k in range(outW):
            if (tmpOutImage[i][k] < 0):
                outImage[i][k] = 0
            elif (tmpOutImage[i][k] > 255):
                outImage[i][k] = 255
            else:
                outImage[i][k] = (int)(tmpOutImage[i][k])

    displayImage()






# 전역 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0]*4
fullname =" "

# 메인 코드부
window = Tk() # 벽
window.geometry("500x500")
window.resizable(width=False, height=False)
window.title("영상처리 Preview 1")

mainMenu = Menu(window) # 메뉴의 틀
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu,  tearoff = 0)# 상위 메뉴 (파일)
mainMenu.add_cascade(label='파일', menu=fileMenu)
fileMenu.add_command(label='열기', command=openImage)
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=None)


pixelMenu = Menu(mainMenu,  tearoff = 0)  # 상위 메뉴 (화소점처리)
mainMenu.add_cascade(label='화소점처리', menu=pixelMenu)
pixelMenu.add_command(label='동일이미지', command=equalImage)
pixelMenu.add_command(label='밝게/어둡게', command=addImage)
pixelMenu.add_command(label='밝게/어둡게2', command=mulImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='And연산', command=andImage)
pixelMenu.add_command(label='OR연산', command=orImage)
pixelMenu.add_command(label='XOR연산', command=xorImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='반전', command=reverseImage)
pixelMenu.add_command(label='흑백', command=blackImage)


geometryMenu = Menu(mainMenu,  tearoff = 0)  # 상위 메뉴 (기하학적처리)
mainMenu.add_cascade(label='기하학적처리', menu=geometryMenu)
geometryMenu.add_command(label='확대(포워딩)', command=zoomIn)
geometryMenu.add_command(label='확대(백워딩)', command=zoomIn2)
geometryMenu.add_command(label='축소', command=zoomOut)
geometryMenu.add_command(label='회전', command=rotate)
geometryMenu.add_command(label='회전(중앙+백워딩)', command=rotate2)
geometryMenu.add_command(label='이동', command=moveImage)
geometryMenu.add_command(label='좌우대칭', command=rotationImage)
geometryMenu.add_command(label='상하대칭', command=rotation2Image)

histoMenu = Menu(mainMenu,  tearoff = 0)  # 상위 메뉴 (히스토그램)
mainMenu.add_cascade(label='히스토그램', menu=histoMenu)
histoMenu.add_command(label='히스토그램 스트레칭', command=histoStretch)
histoMenu.add_command(label='엔드 -인', command=endIN)
histoMenu.add_command(label='히스토그램 평활화', command=histoEqual)

AreaMenu = Menu(mainMenu,  tearoff = 0)  # 상위 메뉴 (영역처리)
mainMenu.add_cascade(label='영역처리', menu=AreaMenu)
AreaMenu.add_command(label='엠보싱', command=emboss)
AreaMenu.add_command(label='블러링', command=blurr)
AreaMenu.add_command(label='블러링(9x9)', command=blurr2)
AreaMenu.add_command(label='스무딩', command=smoot)
AreaMenu.add_command(label='샤프닝', command=sharp)
AreaMenu.add_command(label='샤프닝2', command=sharp2)
AreaMenu.add_command(label='고주파샤프닝', command=sharp3)


EdgeMenu = Menu(mainMenu,  tearoff = 0)  # 상위 메뉴 (에지검출)
mainMenu.add_cascade(label='에지검출', menu=EdgeMenu)
EdgeMenu.add_command(label='이동과차분(수직)', command=edge1)
EdgeMenu.add_command(label='이동과차분(수평)', command=edge1_1)
EdgeMenu.add_command(label='프리윗', command=edge2)
EdgeMenu.add_command(label='로버츠', command=edge3)
EdgeMenu.add_command(label='소벨', command=edge4)
EdgeMenu.add_command(label='라플라시안', command=edge5)




window.mainloop()
