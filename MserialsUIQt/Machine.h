#pragma once


//
#include "Common.h"
#include "opencv.hpp"
#include <mutex>
#include <iostream>
#include "MSerialsCam.h"
#include <list>
//多线程保护
#include <atomic>
#include "Ini.h"
#include "global.h"
///<#include <stdatomic.h> 
///<内联
///<机器的算法类和控制类都在这里面


#ifndef _HALCON__
#define _HALCON__

#include "Halconcpp.h"

#ifdef _WIN64
#pragma comment(lib,"../third_party/lib/halcon/x64/halconcpp.lib")
#else
#pragma comment(lib,"../third_party/lib/halcon/x86/halconcpp.lib")
#endif

using namespace Halcon;

#endif

#include "MotionCard.h"

class Machine
{
public:
	enum { BUTTON_VOID = 0, STOP = 1, PAUSE = 2, START = 4, SYS_STATE };
	enum { NO_RECT = 0, CRICLE };
	//瓶盖一共就四种分类，OK，NG，和四档颜色
	enum{UNKOWN_CAP = -1,OK = 0,NG = 1,COLOR1 =2,COLOR2 =3,COLOR3 =4,COLOR4 =5};

	motion_card *m_mc = nullptr;
	//三个相机的触发硬件控制
	//HANDLE _IO_Scanner;
	std::mutex  mtx_line1, mtx_line2, mtx_line3;
	HANDLE _thread_line1 = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE _thread_line2 = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE _thread_line3 = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE _thread_io = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow1 = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow2 = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow3 = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow3c1 = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow3c2 = CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE _thread_blow3c3 = CreateEvent(NULL, TRUE, FALSE, NULL);

private:
	//DWORD参数是延时，为了控制吹气时间
	//int参数是为了知道该瓶盖的检查结果，如果OK那么就什么都不管了，如果NG就吹掉，如果UNKOWN说明没有检测过
	//采用list 比 vector更好，因为会对list进行频繁的操作，导致内存碎片增多，如果vector就容易让本来频繁的操作更加频繁
	std::list<std::pair<clock_t,int>>	Camera1Delay, Camera2Delay, Camera3Delay;
	//设计因素，将延时进行传导到delay里的变量
	std::atomic<clock_t> Cam1Tick, Cam2Tick, Cam3Tick;
	std::list<std::pair<clock_t,int>>	Camera1DelayBlow, Camera2DelayBlow, Camera3DelayBlow;

	Machine()
		:alert(0)
	{
		m_system_state = STOP;
		RectInfo = NO_RECT;
		Camera1DelayBlow.clear(); 
		Camera2DelayBlow.clear();
		Camera3DelayBlow.clear();
		m_mc = new motion_card();
		if (!m_mc->InitOk()) { delete m_mc; m_mc = nullptr; }
		enum_cameras(TRIGGER_HARDWARE);
		//enum_cameras();
		//Init();
	}

	~Machine()
	{
	}
	//显示错误信息
	void Error_Show(const char* e)
	{
		DLOG(LOG_INFO, e);
		printf("%s", e);
		if (alert) return;
		QMessageBox::information(NULL, "exception", e, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		exit(0);
	}

	//抛出异常
	void MExceptionCatchInstall(const char* error_info)
	{
		Error_Show(error_info);
	}



public:
	//启动机器
	void Start() {
		//仅仅三个相机需要去硬件触发
		SetEvent(_thread_io);
		ResetEvent(_thread_line1);
		ResetEvent(_thread_line2);
		ResetEvent(_thread_line3);
		//指定在一个核心上运行
		SetThreadAffinityMask(CreateThread(NULL, 0, IO_Scanner, this, 0, NULL),1);
		CreateThread(NULL, 0, Line1_Camera, this, 0, NULL);
		CreateThread(NULL, 0, Line2_Camera, this, 0, NULL);
		CreateThread(NULL, 0, Line3_Camera, this, 0, NULL);

		ResetEvent(_thread_blow1);
		ResetEvent(_thread_blow2);
		ResetEvent(_thread_blow3);
		ResetEvent(_thread_blow3c1);
		ResetEvent(_thread_blow3c2);
		ResetEvent(_thread_blow3c3);

		CreateThread(NULL, 0, Cam1NGBlow, this, 0, NULL);
		CreateThread(NULL, 0, Cam2NGBlow, this, 0, NULL);
		CreateThread(NULL, 0, Cam3NGBlow, this, 0, NULL);
		CreateThread(NULL, 0, Cam3BlowC1, this, 0, NULL);
		CreateThread(NULL, 0, Cam3BlowC2, this, 0, NULL);
		CreateThread(NULL, 0, Cam3BlowC3, this, 0, NULL);
	}

	static QString show_rect_info(int info)
	{ 
		switch (info)
		{
		case NO_RECT:return "";
		case CRICLE:return QString::fromLocal8Bit("请画完颜色框");
		default:
			return "";
		}
	}
	int RectInfo;
	static Machine* GetIns() { static Machine lm; return &lm; }
	char *MachineName() { return "瓶盖检测机"; }


	void blow(unsigned int port, unsigned int bit)
	{
		m_mc->Write_Output_Ex(port, bit, 1);
		Sleep(50);
		m_mc->Write_Output_Ex(port, bit, 0);
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam1NGBlow(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow1, INFINITE);
			ResetEvent(pDlg->_thread_blow1);
			//第一个口
			pDlg->m_mc->Write_Output_Ex(1, 1, 1);
			Sleep(55);
			pDlg->m_mc->Write_Output_Ex(1, 1, 0);
		}
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam2NGBlow(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow2,INFINITE);
			ResetEvent(pDlg->_thread_blow2);
			pDlg->m_mc->Write_Output_Ex(1, 4, 1);
			Sleep(55);
			pDlg->m_mc->Write_Output_Ex(1, 4, 0);
		}
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam3NGBlow(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow3, INFINITE);
			ResetEvent(pDlg->_thread_blow3);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 1);
			Sleep(50);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 0);
		}
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam3BlowC1(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow3c1, INFINITE);
			ResetEvent(pDlg->_thread_blow3c1);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 1);
			Sleep(50);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 0);
		}
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam3BlowC2(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow3c2, INFINITE);
			ResetEvent(pDlg->_thread_blow3c2);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 1);
			Sleep(50);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 0);
		}
	}

	//为了不阻塞程序
	static DWORD WINAPI Cam3BlowC3(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		//让线程挂起，而不是每次都启动
		for (;;)
		{
			::WaitForSingleObject(pDlg->_thread_blow3c3, INFINITE);
			ResetEvent(pDlg->_thread_blow3c3);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 1);
			Sleep(50);
			//pDlg->m_mc->Write_Output_Ex(1, 4, 0);
		}
	}



	//IO扫描口
	static DWORD WINAPI IO_Scanner(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		Sleep(50);
		//不能找到板卡的时候就退出
		if (nullptr == pDlg->m_mc) { std::cout << "can not find any motion card" << std::endl; return 0; }
		uint8 new_state = pDlg->m_mc->Read_Input(0);
		uint8 old_state = new_state;
		//掩膜获取应该触发的IO口	
		//工位编号和相机延时时间
		//DWORD Tick = GetTickCount();
		clock_t Tick = clock();
		clock_t o = Tick;
		for (;;) {
			::WaitForSingleObject(pDlg->_thread_io, INFINITE);
			//Sleep(1);
			//8个IO为一个组
			Sleep(1);
			new_state = pDlg->m_mc->Read_Input(0); 
			Tick = clock();
			
			int NCT1 = Camera_Trigger1 & new_state;
			int OCT1 = Camera_Trigger1 & old_state;

			int NCT2 = Camera_Trigger2 & new_state;
			int OCT2 = Camera_Trigger2 & old_state;

			int NCT3 = Camera_Trigger3 & new_state;
			int OCT3 = Camera_Trigger3 & old_state;

			if (NCT1 && NCT1 != OCT1) {
				pDlg->Camera1Delay.push_back(std::pair<clock_t,int>(Tick,Machine::UNKOWN_CAP));
			}
			if (NCT2 && NCT2 != OCT2) {
				pDlg->Camera2Delay.push_back(std::pair<clock_t, int>(Tick, Machine::UNKOWN_CAP));
			}
			if (NCT3 && NCT3 != OCT3) {
				pDlg->Camera3Delay.push_back(std::pair<clock_t, int>(Tick, Machine::UNKOWN_CAP));
			}
			old_state = new_state;

			//严格的，如果这个地方超出了界限，会崩溃
			try {
				//触发相机1
				if (pDlg->Camera1Delay.size() > 0 && (Tick-pDlg->Camera1Delay.begin()->first) > CAM1DELAY)
				{
					//注意顺序，防止bug，要进行多线程保护
					pDlg->Cam1Tick = static_cast<clock_t>(pDlg->Camera1Delay.begin()->first);
					pDlg->Camera1Delay.pop_front();
					SetEvent(pDlg->_thread_line1);

				}

				//触发相机2
				if (pDlg->Camera2Delay.size() > 0 && (Tick-pDlg->Camera2Delay.begin()->first) > CAM2DELAY)
				{
					pDlg->Cam2Tick = static_cast<clock_t>(pDlg->Camera2Delay.begin()->first);
					pDlg->Camera2Delay.pop_front();
					SetEvent(pDlg->_thread_line2);
				}

				//触发相机3
				if (pDlg->Camera3Delay.size() > 0 && (Tick-pDlg->Camera3Delay.begin()->first) > CAM3DELAY)
				{
					pDlg->Cam3Tick = static_cast<clock_t>(pDlg->Camera3Delay.begin()->first);
					pDlg->Camera3Delay.pop_front();
					SetEvent(pDlg->_thread_line3);
				}

				int co = 0;
				//工位1的要求
				for (std::list<std::pair<clock_t, int>>::iterator it = pDlg->Camera1DelayBlow.begin(); it != pDlg->Camera1DelayBlow.end(); it++) {
					//printf("conter = %d\n",co++);
					switch (it->second) {
						//没有任何检查的结果，什么事也不干
					case 	Machine::UNKOWN_CAP:break;
						//NG就开始吹气,不过多线程删除得保证安全
					case Machine::NG:
						if ((Tick - it->first) > POS1BLOW_DELAY)
						{
							//阻塞的函数
							//工位1吹气
							SetEvent(pDlg->_thread_blow1);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line1);
							pDlg->Camera1DelayBlow.erase(it);
						}
					break;
						//OK的就删除掉吧，也没什么用了,不过多线程删除得保证安全
					case Machine::OK: {
						//std::lock_guard<std::mutex>  lck(pDlg->mtx_line1); 
						pDlg->Camera1DelayBlow.erase(it); 
					} 
					break;
					}

				}


				for (std::list<std::pair<clock_t, int>>::iterator it = pDlg->Camera2DelayBlow.begin(); it != pDlg->Camera2DelayBlow.end(); it++) {
					switch (it->second) {
						//没有任何检查的结果，什么事也不干
					case 	Machine::UNKOWN_CAP:break;
						//NG就开始吹气,不过多线程删除得保证安全
					case Machine::NG:
						if ((Tick - it->first) > POS2BLOW_DELAY)
						{
							//函数是被阻塞的，所以不可取
							//工位2吹气
							SetEvent(pDlg->_thread_blow2);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
							pDlg->Camera2DelayBlow.erase(it);
						}
						break;
						//OK的就删除掉吧，也没什么用了,不过多线程删除得保证安全
					case Machine::OK: {
						//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
						pDlg->Camera2DelayBlow.erase(it);
					}
					break;
					}

				}



				for (std::list<std::pair<clock_t, int>>::iterator it = pDlg->Camera3DelayBlow.begin(); it != pDlg->Camera3DelayBlow.end(); it++) {
					switch (it->second) {
						//没有任何检查的结果，什么事也不干
					case 	Machine::UNKOWN_CAP:break;
						//NG就开始吹气,不过多线程删除得保证安全
					case Machine::NG:
						if ((Tick - it->first) > POS3BLOW_DELAY)
						{
							//函数是被阻塞的，所以不可取
							//工位2吹气
							SetEvent(pDlg->_thread_blow3);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
							pDlg->Camera3DelayBlow.erase(it);
						}
						break;
					case Machine::COLOR1:
						if ((Tick - it->first) > POS3BLOW_COLOR1_DELAY)
						{
							//函数是被阻塞的，所以不可取
							//工位2吹气
							SetEvent(pDlg->_thread_blow3c1);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
							pDlg->Camera3DelayBlow.erase(it);
						}
						break;
					case Machine::COLOR2:
						if ((Tick - it->first) > POS3BLOW_COLOR2_DELAY)
						{
							//函数是被阻塞的，所以不可取
							//工位2吹气
							SetEvent(pDlg->_thread_blow3c2);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
							pDlg->Camera3DelayBlow.erase(it);
						}
						break;

					case Machine::COLOR3:
						if ((Tick - it->first) > POS3BLOW_COLOR3_DELAY)
						{
							//函数是被阻塞的，所以不可取
							//工位2吹气
							SetEvent(pDlg->_thread_blow3c3);
							//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
							pDlg->Camera3DelayBlow.erase(it);
						}
						break;
						//COLOR4就留在最后一个工位，也不需要吹气了
					case Machine::COLOR4:
						
						pDlg->Camera3DelayBlow.erase(it);
						break;
						//OK的就删除掉吧，也没什么用了,不过多线程删除得保证安全
					case Machine::OK: {
						//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
						pDlg->Camera3DelayBlow.erase(it);
					}
									  break;
									  
					}

				}
			}


			//for第三工位
			catch (std::out_of_range e)
			{
				std::cout << "error in vector to trigger camera" << std::endl;
			}
			
		}
	}
#define OUT_CAM1	(1<<1)
#define OUT_CAM2	(1<<3)
	//对应
#define OUT_CAM3	(1<<5)
	static DWORD WINAPI Line1_Camera(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		if (nullptr == pDlg->m_mc) {
			std::cout << " Line1 End Cz No Card " << std::endl;
			return 0;
		}
		Halcon::Hobject image;
		for (;;) {
			::WaitForSingleObject(pDlg->_thread_line1, INFINITE);
			//延时拍照
			ResetEvent(pDlg->_thread_line1);
			//硬件触发相机
			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM1, 1);
			try {
				Halcon::set_check("~give_error");
				Sleep(1);
				SnapHobj(image, 0, 0, 10);
				//pDlg->h_disp_obj(image, pDlg->hdisp_hand.at(0));
			}
			catch (Halcon::HException e)
			{
				std::cout << "failed to capture" << std::endl;
			}
			catch (std::out_of_range out)
			{
				std::cout << out.what() << std::endl;
				continue;
			}
			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM1, 0);

			//进行检测
			int res = pDlg->back_cap_detect(image, pDlg->hdisp_hand.at(0), Preference::GetIns()->prj->para);
			{
				//std::lock_guard<std::mutex>  lck(pDlg->mtx_line1);
				pDlg->Camera1DelayBlow.push_back(std::pair<DWORD, int>(pDlg->Cam1Tick, res));
			}


		}
		return 0;

	}

	static DWORD WINAPI Line2_Camera(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		if (nullptr == pDlg->m_mc) {
			std::cout << " Line2 End Cz No Card " << std::endl;
			return 0;
		}
		Halcon::Hobject image;
		for (;;) {
			::WaitForSingleObject(pDlg->_thread_line2, INFINITE);
			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM2, 1);
			ResetEvent(pDlg->_thread_line2);
			//延时拍照
			try {
				Halcon::set_check("~give_error");
				Sleep(1);
				SnapHobj(image, 0, 1, 10);
				pDlg->h_disp_obj(image, pDlg->hdisp_hand.at(1));
			}
			catch (Halcon::HException e)
			{
				std::cout << "failed to capture" << std::endl;
			}
			catch (std::out_of_range out)
			{
				std::cout << out.what() << std::endl;
			}
			
			//硬件触发相机

			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM2, 0);

			//进行检测
			int res = pDlg->side_cap_detect(image, pDlg->hdisp_hand.at(1));
			{
				//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
				pDlg->Camera2DelayBlow.push_back(std::pair<clock_t, int>(pDlg->Cam2Tick, res));
			}

		}
		return 0;
		//Edit
	}

	static DWORD WINAPI Line3_Camera(LPVOID lpParameter) {
		Machine * pDlg = (Machine*)lpParameter;
		if (nullptr == pDlg->m_mc) {
			std::cout << " Line3 End Cz No Card " << std::endl;
			return 0;
		}
		Halcon::Hobject image;
		for (;;) {
			::WaitForSingleObject(pDlg->_thread_line3, INFINITE);
			//硬件触发相机
			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM3, 1);
			//延时拍照
			ResetEvent(pDlg->_thread_line3);
			//延时拍照
			try {
				Halcon::set_check("~give_error");
				//反应太快造成触发无效，所以等待1ms
				Sleep(1);
				//no thrid camera so using second came instead
				SnapHobj(image, 0, 1, 10);
				pDlg->h_disp_obj(image, pDlg->hdisp_hand.at(5));

			}
			catch (Halcon::HException e)
			{
				std::cout << "failed to capture" << std::endl;
			}
			catch (std::out_of_range out)
			{
				std::cout << out.what() << std::endl;
			}

			//硬件触发相机

			pDlg->m_mc->Write_Output_Ex(0, OUT_CAM3, 0);

			//进行检测
			int res = pDlg->front_cap_detect(image, pDlg->hdisp_hand.at(5));
			{
				//std::lock_guard<std::mutex>  lck(pDlg->mtx_line2);
				pDlg->Camera2DelayBlow.push_back(std::pair<clock_t, int>(pDlg->Cam2Tick, res));
			}


		}
		return 0;

	}

	/************************************图像检测部分************************************************************/

	//背面检测函数
	int back_cap_detect(const Halcon::Hobject &src, Halcon::HTuple &Disp_Hd, _Param &p = _Param()) {
		using namespace Halcon;
		int res = UNKOWN_CAP;
		
		Hobject  Regions, Red, Green, Blue, Hue;
		Hobject  Saturation, Intensity, inner, innerFillUp, ConnectedRegions;
		Hobject  MaxArea, Saturated, cap_contour, ContoursSplit;
		Hobject  SortedContours, ObjectSelected;

		// Local control variables 
		HTuple  Rows, Columns, Circularity;
		try
		{
			Halcon::set_check("~give_error");
			Halcon::set_draw(Disp_Hd,"margin");
			Halcon::decompose3(src, &Red, &Green, &Blue);
			Halcon::trans_from_rgb(Red, Green, Blue, &Hue, &Saturation, &Intensity, "hsv");
			threshold(Saturation, &inner, p.threshold_back_cap, 255);
			fill_up(inner, &innerFillUp);
			connection(innerFillUp, &ConnectedRegions);
			select_shape_std(ConnectedRegions, &MaxArea, "max_area", 0);
			get_region_contour(MaxArea, &Rows, &Columns);
			circularity(MaxArea, &Circularity);
			if (Circularity < p.back_circularity)
			{
				set_color(Disp_Hd, "red");
				res = NG;
			}
			else
			{
				set_color(Disp_Hd, "green");
				res = OK;
			}
			h_disp_obj(src, Disp_Hd);
			h_disp_obj(MaxArea, Disp_Hd);
			set_tposition(Disp_Hd, 10, 10);
			write_string(Disp_Hd, "C:" + Circularity);
		}
		catch (Halcon::HException e)
		{
			set_tposition(Disp_Hd, 10, 10);
			write_string(Disp_Hd, "分割错误");
			return NG;
		}
		return res;
		/**
		//参数1
		threshold_sub_pix(Saturation, &Saturated, 128);
		segment_contours_xld(Saturated, &ContoursSplit, "lines_circles", 5, 4, 3);
		sort_contours_xld(ContoursSplit, &SortedContours, "upper_left", "true", "row");
		count_obj(SortedContours, &Number);
		//if (HDevWindowStack::IsOpen())
		//	set_color(HDevWindowStack::GetActive(), "red");
		h_disp_obj(src, Disp_Hd);
		for (i = 1; i <= Number; i += 1)
		{
			select_obj(SortedContours, &ObjectSelected, i);
			circularity_xld(ObjectSelected, &Circularity);
			if (Circularity < p.back_circularity)
			{
				set_color(Disp_Hd,"red");
				res = NG;
			}
			else
			{
				set_color(Disp_Hd, "green");
				res = OK;
			}
			set_tposition(Disp_Hd,10,10);
			write_string(Disp_Hd,"C:"+ Circularity);
			break;
		}
		return res;
		*/
	}

	//侧面检查函数
	int side_cap_detect(const Halcon::Hobject &src, Halcon::HTuple &Disp_Hd, _Param p = _Param()) {
		return NG;
	}

	//正面检测函数,用于分选颜色
	int front_cap_detect(const Halcon::Hobject &src, Halcon::HTuple &Disp_Hd, _Param p = _Param()) {
		using namespace Halcon;

		int error_information = 0;
		int txt_y_pos = 10;
		// Local iconic variables 
		Hobject  ROI_0, Red, Green, Blue, Hue;
		Hobject  Saturation, Intensity, ROI_1_0, reduced, RegionsMean;
		Hobject  ContourSubPix, SelectedContours, SortedContours;
		Hobject  selobj, thresRegion, CapRegion, ConnectedRegions,MaxArea;


		// Local control variables 
		HTuple  Width, Height, WindowHandle, Row, Column;
		HTuple  Num, Mean1, Deviation1, i;

		double r1 = p.front.r1;
		double r2 = p.front.r2;
		double c1 = p.front.c1;
		double c2 = p.front.c2;
		try {
			h_disp_obj(src, Disp_Hd);
			//area to detect 大致定位瓶盖区域
			gen_rectangle1(&ROI_0, r1, c1, r2, c2);

			decompose3(src, &Red, &Green, &Blue);

			trans_from_rgb(Red, Green, Blue, &Hue, &Saturation, &Intensity, "hsv");
			get_image_size(src, &Width, &Height);

	
			gen_circle(&ROI_0, 550.5, 557.5, 88.459);
			reduce_domain(src, ROI_0, &reduced);

			//regiongrowing_mean (Image, RegionsMean, Row, Column, 3, 50)


			threshold(reduced, &CapRegion, 20, 255);
			connection(CapRegion, &ConnectedRegions);
			select_shape_std(ConnectedRegions, &MaxArea, "max_area", 50);
			reduce_domain(src, MaxArea, &reduced);


			//找出需要检测的颜色区域
			threshold(reduced, &thresRegion, 64, 255);

			
			intensity(thresRegion, Hue, &Mean1, &Deviation1);


			
			//红移 和 蓝移
			if (Mean1 < p.red_limt || Mean1 > p.blue_limit)
			{
				error_information  |= NG;
				set_color(Disp_Hd, "red");
			}
			else
			{
				set_color(Disp_Hd, "green");
			}
			Halcon::set_tposition(Disp_Hd, txt_y_pos += 20, 20);
			Halcon::write_string(Disp_Hd, "H:" + Mean1);

			intensity(thresRegion, Saturation, &Mean1, &Deviation1);
			if (Mean1 < p.saturation_limit_lower) {
				error_information |= NG;
				set_color(Disp_Hd, "red");
			}
			else
			{
				int color = COLOR1;
				set_color(Disp_Hd, "green");
				if (Mean1 > (p.saturation_limit_lower + 0*p.saturation_limit_sigma))
				{
					color = COLOR1;
				}
				//no else if 
				if (Mean1 > (p.saturation_limit_lower + 1*p.saturation_limit_sigma))
				{
					color = COLOR2;
				}

				if (Mean1 > (p.saturation_limit_lower + 2*p.saturation_limit_sigma))
				{
					color = COLOR3;
				}

				if (Mean1 > (p.saturation_limit_lower + 3* p.saturation_limit_sigma))
				{
					color = COLOR4;
					error_information |= color;
				}
				
			}
			Halcon::set_tposition(Disp_Hd, txt_y_pos += 20, 20);
			Halcon::write_string(Disp_Hd, "S:" + Mean1);

			intensity(thresRegion, Intensity, &Mean1, &Deviation1);
			set_color(Disp_Hd, "green");
			Halcon::set_tposition(Disp_Hd, txt_y_pos += 20, 20);
			Halcon::write_string(Disp_Hd, "G:" + Mean1);

			//检测

		}
		catch (Halcon::HException e)
		{
			Halcon::write_string(Disp_Hd, "No Image");
			return NG;
		}
		if (NG == NG&error_information) {
			return NG;
		}
		set_color(Disp_Hd, "blue");
		Halcon::set_tposition(Disp_Hd, txt_y_pos += 20, 20);
		switch (error_information)
		{
			
		case COLOR1:Halcon::write_string(Disp_Hd, "色号1"); break;
		case COLOR2:Halcon::write_string(Disp_Hd, "色号2"); break;
		case COLOR3:Halcon::write_string(Disp_Hd, "色号3"); break;
		case COLOR4:Halcon::write_string(Disp_Hd, "色号4"); break;
		default:
			break;
		}
		return error_information;
	}

	/************************************图像检测部分END*********************************************************/



	int push_button(int sel) {
		static std::mutex mtx;
		std::lock_guard<std::mutex> lck(mtx);
		switch (sel) {
		case STOP:stop(); return m_system_state;
		case PAUSE:pause(); return m_system_state;
		case START:start(); return m_system_state;
		case SYS_STATE: return m_system_state;
		default: return m_system_state;
		}
	}

	//record system state
	void record_state() {
		std::lock_guard<std::mutex> lck(m_system_state_mutex);
		m_system_rec = m_system_state;
		DLOG(LOG_INFO, "sytem_record");
	}

	//resume
	void resume_state() {
		static std::mutex m_mtx;
		std::lock_guard<std::mutex> lck(m_mtx);
		switch (m_system_rec)
		{
		case STOP:  stop(); break;
		case PAUSE: pause(); break;
		case START: start(); break;
		default:    stop(); break;
		}
		DLOG(LOG_INFO, "sytem_resume");
	}

	private:
	/***************** SYSTEM CONTROL ***********************/
	//system pause
	void pause() { 
		_pause();
		m_system_state = PAUSE; 
		DLOG(LOG_INFO, "sytem_pause");
	}
	//system_stop
	void stop() { 
		_stop();
		m_system_state = STOP; 
		DLOG(LOG_INFO, "sytem_stop");
	}
	//system start
	void start() { 
		_start();
		m_system_state = START; 
		DLOG(LOG_INFO, "sytem_start");
	}



	int get_system_state() { return m_system_state; }


private:
	void _pause() {
		ResetEvent(_thread_io);
		return;
	}

	void _start()
	{
		SetEvent(_thread_io);
		return;
	}

	void _stop()
	{
		return;
	}



	/***************** SYSTEM CONTROL END ********************/

	/***************** VIDEO DISPLAY *************************/
public:
#ifdef QT_VERSION
	[[noreturn]] _CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL __out_of_range(_In_z_ const char *);
	[[noreturn]] void m_set_check(const char* check_name) {
		if (0 == strcmp(check_name, "give_error"))
		{
			alert = 1;
		}
		else if (0 == strcmp(check_name, "~give_error"))
		{
			alert = 0;
		}
	}

	//注册显示区域
	void _open_window(QLabel *Label_window, QLabel *disp_hand, int method = 0)
	{
		disp_hand = Label_window;
	}

	void h_open_window(const std::vector<QWidget*> &rt)
	{
		using namespace Halcon;
		Halcon::set_check("give_error");
		for (int i = 0; i < MAX_WINDOW_NUM; i++)
		{
			Halcon::set_check("~father");
			Halcon::HTuple hdph;
			open_window(0, 0, (Hlong)rt[i]->width(), (Hlong)rt[i]->height(), (Hlong)rt[i]->winId(), "visible", "", &hdph);
			hdisp_hand.push_back(hdph);
		}
	}


	void h_disp_obj(const Halcon::Hobject & obj, const Halcon::HTuple & disp_hand)
	{
		try
		{
			Halcon::set_check("~give_error");
			Hlong w, h;
			Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
			Halcon::HDevWindowStack::Push(disp_hand);
			Halcon::HDevWindowStack::SetActive(disp_hand);
			Halcon::set_part(disp_hand, NULL, NULL, h, w);
			disp_obj(obj, disp_hand);
		}
		catch (Halcon::HException &except)
		{
			//Halcon::set_check("give_error");
			Halcon::set_tposition(disp_hand, 0, 1);
			Halcon::write_string(disp_hand, except.message);
		}
	}

#endif

	/***************** VIDEO DISPLAY END**********************/



	//大概思路是，找某个色差的范围内像素点，转成单通道图像，然后查看面积
	int chromatism(const cv::Mat &Input, cv::Mat& Output, cv::Rect rt, double accurcy) {
		return 0;
	}


	//检测圆。opnecv
	//目标 验证圆的概率
	/*find circle begin*/
	float verifyCircle(cv::Mat dt, cv::Point2f center, float radius, std::vector<cv::Point2f> & inlierSet)
	{
		unsigned int counter = 0;
		unsigned int inlier = 0;
		float minInlierDist = 2.0f;
		float maxInlierDistMax = 100.0f;
		float maxInlierDist = radius / 25.0f;
		if (maxInlierDist<minInlierDist) maxInlierDist = minInlierDist;
		if (maxInlierDist>maxInlierDistMax) maxInlierDist = maxInlierDistMax;

		// choose samples along the circle and count inlier percentage
		for (float t = 0; t<2 * 3.14159265359f; t += 0.05f)
		{
			counter++;
			float cX = radius*cos(t) + center.x;
			float cY = radius*sin(t) + center.y;

			if (cX < dt.cols)
				if (cX >= 0)
					if (cY < dt.rows)
						if (cY >= 0)
							if (dt.at<float>(cY, cX) < maxInlierDist)
							{
								inlier++;
								inlierSet.push_back(cv::Point2f(cX, cY));
							}
		}

		return (float)inlier / float(counter);
	}


	inline void getCircle(cv::Point2f& p1, cv::Point2f& p2, cv::Point2f& p3, cv::Point2f& center, float& radius)
	{
		float x1 = p1.x;
		float x2 = p2.x;
		float x3 = p3.x;

		float y1 = p1.y;
		float y2 = p2.y;
		float y3 = p3.y;

		// PLEASE CHECK FOR TYPOS IN THE FORMULA :)
		center.x = (x1*x1 + y1*y1)*(y2 - y3) + (x2*x2 + y2*y2)*(y3 - y1) + (x3*x3 + y3*y3)*(y1 - y2);
		center.x /= (2 * (x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));

		center.y = (x1*x1 + y1*y1)*(x3 - x2) + (x2*x2 + y2*y2)*(x1 - x3) + (x3*x3 + y3*y3)*(x2 - x1);
		center.y /= (2 * (x1*(y2 - y3) - y1*(x2 - x3) + x2*y3 - x3*y2));

		radius = sqrt((center.x - x1)*(center.x - x1) + (center.y - y1)*(center.y - y1));
	}



	std::vector<cv::Point2f> getPointPositions(cv::Mat binaryImage)
	{
		std::vector<cv::Point2f> pointPositions;

		for (unsigned int y = 0; y<binaryImage.rows; ++y)
		{
			//unsigned char* rowPtr = binaryImage.ptr<unsigned char>(y);
			for (unsigned int x = 0; x<binaryImage.cols; ++x)
			{
				//if(rowPtr[x] > 0) pointPositions.push_back(cv::Point2i(x,y));
				if (binaryImage.at<unsigned char>(y, x) > 0) pointPositions.push_back(cv::Point2f(x, y));
			}
		}

		return pointPositions;
	}


	//随机采样算法找圆
	int mainRANSAC_circle()
	{
		cv::Mat color = cv::imread("../inputData/CircleDetectGray.jpg");
		cv::Mat gray;

		// convert to grayscale
		// you could load as grayscale if you want, but I used it for (colored) output too
		cv::cvtColor(color, gray, CV_BGR2GRAY);


		cv::Mat mask;

		float canny1 = 100;
		float canny2 = 20;

		cv::Mat canny;
		cv::Canny(gray, canny, canny1, canny2);
		cv::imshow("canny", canny);

		mask = canny;


		//  
		std::vector<cv::Point2f> edgePositions;
		edgePositions = getPointPositions(mask);

		// create distance transform to efficiently evaluate distance to nearest edge
		cv::Mat dt;
		cv::distanceTransform(255 - mask, dt, CV_DIST_L1, 3);

		//TODO: maybe seed random variable for real random numbers.

		unsigned int nIterations = 0;

		cv::Point2f bestCircleCenter;
		float bestCircleRadius;
		float bestCirclePercentage = 0;
		float minRadius = 10;   // TODO: ADJUST THIS PARAMETER TO YOUR NEEDS, otherwise smaller circles wont be detected or "small noise circles" will have a high percentage of completion

								//float minCirclePercentage = 0.2f;
		float minCirclePercentage = 0.05f;  // at least 5% of a circle must be present? maybe more...

		int maxNrOfIterations = edgePositions.size();   // TODO: adjust this parameter or include some real ransac criteria with inlier/outlier percentages to decide when to stop

		for (unsigned int its = 0; its< maxNrOfIterations; ++its)
		{
			//RANSAC: randomly choose 3 point and create a circle:
			//TODO: choose randomly but more intelligent, 
			//so that it is more likely to choose three points of a circle. 
			//For example if there are many small circles, it is unlikely to randomly choose 3 points of the same circle.
			unsigned int idx1 = rand() % edgePositions.size();
			unsigned int idx2 = rand() % edgePositions.size();
			unsigned int idx3 = rand() % edgePositions.size();

			// we need 3 different samples:
			if (idx1 == idx2 || idx1 == idx3 || idx3 == idx2)	continue;


			// create circle from 3 points:
			cv::Point2f center; float radius;
			//随机采样三个点进行检测
			getCircle(edgePositions[idx1], edgePositions[idx2], edgePositions[idx3], center, radius);

			// inlier set unused at the moment but could be used to approximate a (more robust) circle from alle inlier
			std::vector<cv::Point2f> inlierSet;

			//verify or falsify the circle by inlier counting:
			float cPerc = verifyCircle(dt, center, radius, inlierSet);

			// update best circle information if necessary
			if (cPerc >= bestCirclePercentage)
				if (radius >= minRadius)
				{
					bestCirclePercentage = cPerc;
					bestCircleRadius = radius;
					bestCircleCenter = center;
				}

		}

		std::cout << "bestCirclePerc: " << bestCirclePercentage << std::endl;
		std::cout << "bestCircleRadius: " << bestCircleRadius << std::endl;

		// draw if good circle was found
		if (bestCirclePercentage >= minCirclePercentage)
			if (bestCircleRadius >= minRadius);
		cv::circle(color, bestCircleCenter, bestCircleRadius, cv::Scalar(255, 255, 0), 1);


		cv::imshow("output", color);
		cv::imshow("mask", mask);
		cv::imwrite("../outputData/1_circle_color.png", color);
		cv::imwrite("../outputData/1_circle_mask.png", mask);
		//cv::imwrite("../outputData/1_circle_normalized.png", normalized);
		cv::waitKey(0);

		return 0;
	}





	/*find circle end*/
	

	//disp_hand
	QLabel *disp_hd;
	QLabel *disp_hd1;
	QLabel *disp_hd2;
	QLabel *disp_hd3;
	QLabel *disp_hd4;
	QLabel *disp_hd5;
	QLabel *disp_hd6;
	QLabel *disp_hd7;
	QLabel *disp_hd8;
	QLabel *disp_hd9;
	QLabel *disp_hd10;
	QLabel *disp_hd11;

	QRect win_rect[MAX_WINDOW_NUM];

	//HTuple hwindow_hand[MAX_WINDOW_NUM];
	//halcon显示图片用
	//HTuple hdisp_hand[MAX_WINDOW_NUM];
	std::vector<HTuple> hdisp_hand;






private:


	int m_system_rec;
	int m_system_state;
	std::mutex m_system_state_mutex;
public:
	int alert;


};

