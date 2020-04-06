#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
#define Width 640
#define High 480

IMAGE createMask(IMAGE aa);//��ȡ����ͼ�ĺ���

//ˮ���˶��ٶ�
float vx  = 1;     //x���ٶ�
float v0y = -2.5;    //y����ٶ�
float  a  = 0.01;  //y����ٶ�
typedef struct FruitPos    //ˮ������
{
	int x;
	int y;
};
FruitPos pos0 = { 10,High+10 }; //ˮ����ʼ����
FruitPos pos = { 0,0 };  //�������������ˮ���˶�λ�ã���ʼ��Ϊ0��0
	

FruitPos move(unsigned t)  //ˮ���˶�����,����ÿһ˲���������Ϣ   //�й�չ��ˮ����һ���ܣ����Բ�ͨ�����ú����ģ������һ˲������λ�ü��㵱ǰλ�û���ã������ϣ�
{
	FruitPos tempPos;
	tempPos.x = pos0.x + vx * t;
	tempPos.y = pos0.y +( v0y*t + (a * t*t)/2);

	return tempPos;
}

int main(void)
{
	initgraph(Width, High);

	IMAGE bkg, apple, apple_mask;
	loadimage(&bkg, ".\\source\\images\\background.jpg");
	loadimage(&apple, ".\\source\\images\\apple.png");
	apple_mask = createMask(apple);

	

	FruitPos motion_pos = { 0,0 };  //�˶��켣ÿһ˲����������
	unsigned t = 0;
	while (1)
	{
		motion_pos = move(t);

		BeginBatchDraw();
		putimage(0, 0, &bkg);
		putimage(motion_pos.x, motion_pos.y, &apple_mask, SRCAND);
		putimage(motion_pos.x, motion_pos.y, &apple, SRCPAINT);
		FlushBatchDraw();
		t++;
		Sleep(5);
	}
	















	system("pause");
	return 0;
}




IMAGE createMask(IMAGE img) {
	//SetWorkingImage(&aa);// ���û�ͼĿ��Ϊ img ����
	int width = img.getwidth();
	int height = img.getheight();//��ȡ���Ϳ�
	IMAGE maskbitmap(width, height); //����һ������ͼ
	DWORD* pmemflower = GetImageBuffer(&img);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//����0Ӧ�������Ͻǵ����ص���ɫֵ //���д�����diao�ã�
	for (int i = 0; i < width * height; i++)
	{
		if (pmemflower[i] <= 0x010101 && pmemflower[i] >= 0)//0x55555555�����ɫ  xAAAAAA ǳ�� 0XF5F5F5 �̰� && pmemflower[i] >= 0
		{
			pmemmaskbitmap[i] = WHITE;
			//��ɫ�Ǳ���,�����ñ�����һ��,���ڵ���ɫԽ��,������Ļ���Խ��
		}
		else
			pmemmaskbitmap[i] = BLACK;
	}
	//for ����ÿ������ֵ,�����ɫС�ڻ�ɫ ,����ͼ��Ӧ����ֵΪ ����,����Ϊ����
	//�õ� �ڰ���� ������ͼ
	return maskbitmap;
}