#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")
#define Width 640
#define High 480

IMAGE createMask(IMAGE aa);//获取掩码图的函数

//水果运动速度
float vx  = 1;     //x轴速度
float v0y = -2.5;    //y轴初速度
float  a  = 0.01;  //y轴加速度
typedef struct FruitPos    //水果坐标
{
	int x;
	int y;
};
FruitPos pos0 = { 10,High+10 }; //水果初始坐标
FruitPos pos = { 0,0 };  //坐标变量，保存水果运动位置，初始化为0，0
	

FruitPos move(unsigned t)  //水果运动过程,返回每一瞬间的坐标信息   //有关展现水果这一功能，可以不通过调用函数的，结合上一瞬间所在位置计算当前位置会更好（性能上）
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

	

	FruitPos motion_pos = { 0,0 };  //运动轨迹每一瞬间的坐标变量
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
	//SetWorkingImage(&aa);// 设置绘图目标为 img 对象
	int width = img.getwidth();
	int height = img.getheight();//获取长和宽
	IMAGE maskbitmap(width, height); //创建一个掩码图
	DWORD* pmemflower = GetImageBuffer(&img);
	DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);
	COLORREF maskbk = pmemflower[0];//这里0应该是左上角的像素的颜色值 //这行代码有diao用？
	for (int i = 0; i < width * height; i++)
	{
		if (pmemflower[i] <= 0x010101 && pmemflower[i] >= 0)//0x55555555是深灰色  xAAAAAA 浅灰 0XF5F5F5 烟白 && pmemflower[i] >= 0
		{
			pmemmaskbitmap[i] = WHITE;
			//白色是背景,我想让背景少一点,大于的颜色越白,进这里的机会越少
		}
		else
			pmemmaskbitmap[i] = BLACK;
	}
	//for 遍历每个像素值,如果颜色小于灰色 ,掩码图对应像素值为 纯白,否则为纯黑
	//得到 黑白相间 的掩码图
	return maskbitmap;
}