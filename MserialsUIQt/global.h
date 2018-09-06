#pragma once
#include "halconcpp.h"
using namespace Halcon;
#include "MSerialsCam.h"
#include "Ini.h"




#ifndef __GLOBAL_VARS__
#define __GLOBAL_VARS__















#define SNAP_DELAY	2

//该项目最多包含6个相机
#define MAX_CAM		6

//相机的触发输入口 port是0
#define Camera_Trigger1 (1<<2)
#define Camera_Trigger2 (1<<4)
#define Camera_Trigger3 (1<<6)

//相机的触发输出口 port是0
#define OUT_CAM1	(1<<1)
#define OUT_CAM2	(1<<3)
#define OUT_CAM3	(1<<5)


#define MEASURE_SPEED			Preference::GetIns()->prj->para.speed
#define MEASURE_DIS				Preference::GetIns()->prj->para.Sensor1_Sensor2_distance

#define STC1					Preference::GetIns()->prj->para.Sensor1_To_Cam1		
#define CAM1DELAY				Preference::GetIns()->prj->para.Sensor1_To_Cam1_Delay
#define STB1					Preference::GetIns()->prj->para.Sensor1_To_Blow1
#define POS1BLOW_DELAY			Preference::GetIns()->prj->para.Sensor1_To_Blow1_Delay

#define STC2					Preference::GetIns()->prj->para.Sensor2_To_Cam2		
#define CAM2DELAY				Preference::GetIns()->prj->para.Sensor2_To_Cam2_Delay
#define STB2					Preference::GetIns()->prj->para.Sensor2_To_Blow2
#define POS2BLOW_DELAY			Preference::GetIns()->prj->para.Sensor2_To_Blow2_Delay

#define STC3					Preference::GetIns()->prj->para.Sensor3_To_Cam3		
#define CAM3DELAY				Preference::GetIns()->prj->para.Sensor3_To_Cam3_Delay
#define STB3					Preference::GetIns()->prj->para.Sensor3_To_Blow3
#define POS3BLOW_DELAY			Preference::GetIns()->prj->para.Sensor3_To_Blow3_Delay

//工位3色差1吹气延时
#define STCOLOR1				Preference::GetIns()->prj->para.Sensor3_To_Color1
#define POS3BLOW_COLOR1_DELAY	Preference::GetIns()->prj->para.Sensor3_To_Color1_Delay
#define STCOLOR2				Preference::GetIns()->prj->para.Sensor3_To_Color2
#define POS3BLOW_COLOR2_DELAY	Preference::GetIns()->prj->para.Sensor3_To_Color2_Delay
#define STCOLOR3				Preference::GetIns()->prj->para.Sensor3_To_Color3
#define POS3BLOW_COLOR3_DELAY	Preference::GetIns()->prj->para.Sensor3_To_Color3_Delay

#define CARD_NO					Preference::GetIns()->sys->card_num
#define SAVE_PARA_IO			Preference::GetIns()->prj->WriteSettings(PARA_IO);
//#define _LOG


class global
{
public:
	HTuple AcqHandle[MAX_CAM];
private:
	global() {
		for (int i = 0; i < MAX_CAM; i++)
		{
			AcqHandle[i] = NULL;
		}
		camera_found = 0;
	};
	~global() {};

	
	static const int max_cam = MAX_CAM;
	


public:
	int camera_found = 0;

	static global* GetIns() { static global _g; return &_g; }

	
	static void grab(Hobject &Image,int idx)
	{
		using namespace Halcon;
		
		try {
			grab_image_start(global::GetIns()->AcqHandle[idx], -1);
			grab_image_async(&Image, global::GetIns()->AcqHandle[idx], -1);
		}
		catch (HException ex)
		{
			throw ex;
		}
	}

	static int InitCamera() {
		int cam_num = 0;
		int idx = 0;
		using namespace Halcon;
		try
		{
			InitCam(idx++, "A");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
			HTuple res;
			ex.ToHTuple(&res);

			
		}

		try
		{
			InitCam(idx++, "B");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
		}

		try
		{
			InitCam(idx++, "C");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
		}

		try
		{
			InitCam(idx++, "D");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
		}

		try
		{
			InitCam(idx++, "E");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
		}

		try
		{
			InitCam(idx++, "F");
			cam_num++;
		}
		catch (Halcon::HException ex)
		{
		}

		return cam_num;
	}

	static bool InitCam(int idx, char *name = "A") 
	{
		printf("正在初始化相机%s\n", name);
		set_check("~give_error");
		try {
			open_framegrabber("GigEVision", 0, 0, 0, 0, 0, 0, "progressive", -1, "default",
				-1, "false", "default", name, 0, -1, &global::GetIns()->AcqHandle[idx]);
			//
			set_framegrabber_param(global::GetIns()->AcqHandle[idx], "ExposureTime", 350);
			//set_framegrabber_param (AcqHandle, 'Gain', 0)
			set_framegrabber_param(global::GetIns()->AcqHandle[idx], "TriggerMode", "Off");
			set_framegrabber_param(global::GetIns()->AcqHandle[idx], "TriggerSource", "Line0");
			grab_image_start(global::GetIns()->AcqHandle[idx], -1);
		}
		catch (Halcon::HException ex)
		{
			printf("初始化%s失败\n",name);
			throw ex;
		}
		return true;
	}

};
#endif