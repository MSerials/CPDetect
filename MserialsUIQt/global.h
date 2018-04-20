#pragma once
#include "Ini.h"
//该项目最多包含6个相机
#define MAX_CAM		6
#define Camera_Trigger1 (1<<2)
#define Camera_Trigger2 (1<<4)
#define Camera_Trigger3 (1<<6)

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

#define SAVE_PARA_IO			Preference::GetIns()->prj->WriteSettings(PARA_IO);



#ifndef __GLOBAL_VARS__
#define __GLOBAL_VARS__
class global
{
private:
	global() {};
	~global() {};

public:
	static global* GetIns() { static global _g; return &_g; }

private:

};
#endif