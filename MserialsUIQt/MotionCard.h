#pragma once

#include "../../../third_party/yanhua_pci1730u/bdaqctrl.h"
using namespace Automation::BDaq;

class motion_card {
private:
	bool isInitOK = false;
public:
	motion_card() {
		Init();
	}
	~motion_card() {}

	bool Init() {
		int cardno = 0;
		int tmp = 0;
		//提取出来的

		HMODULE h_m = LoadLibrary(TEXT("biodaq.dll"));
		if (NULL == h_m)
		{
			return false;
		}
		else
		{
			FreeLibrary(h_m);
		}
		
		
		
		m_instantDiCtrl = AdxInstantDiCtrlCreate();
		m_instantDoCtrl = AdxInstantDoCtrlCreate();

		if ((m_instantDiCtrl != NULL) && (NULL != m_instantDoCtrl))
		{
			cardno++;
			isInitOK = true;

			int deviceNum = 1;
			DeviceInformation devInfo(deviceNum);

			ErrorCode errorCode = m_instantDiCtrl->setSelectedDevice(devInfo);
			if (errorCode != Success)
			{
				//CheckError(errorCode);
				return false;
			}
			m_instantDiCtrl->getSelectedDevice(devInfo);
			errorCode = m_instantDoCtrl->setSelectedDevice(devInfo);
			if (errorCode != Success)
				return false;//CheckError(errorCode);
			m_instantDoCtrl->getSelectedDevice(devInfo);

			m_IportCount = m_instantDiCtrl->getFeatures()->getPortCount();
			m_portData = new byte[m_IportCount];
			memset(m_portData, 0, m_IportCount);


			int portcount = m_instantDoCtrl->getFeatures()->getPortCount();
			errorCode = m_instantDiCtrl->setSelectedDevice(devInfo);
			if (errorCode != Success)
			{
				return false;
			}
			m_instantDiCtrl->getSelectedDevice(devInfo);
			errorCode = m_instantDoCtrl->setSelectedDevice(devInfo);
			if (errorCode != Success)
			{
				return false;
			}
			m_instantDoCtrl->getSelectedDevice(devInfo);
		}
		else
		{
			isInitOK = false;
			return false;
		}
		if (0 == cardno) return false;
		else return true;
	}
private:
	//掩码操作
	void Write_Output(uint32 port, uint8 bValue)
	{
		if (!isInitOK) return;
		ErrorCode errorCode = m_instantDoCtrl->Write(port, bValue);
	}
public:
	bool InitOk() { return isInitOK; }

	uint8 Read_Input(int32 port, int32 portcounter = 0 )
	{
		if (!isInitOK) return 0;
		ErrorCode errorCode;
		uint8 outportValue;
		errorCode = m_instantDiCtrl->Read(port, m_instantDiCtrl->getFeatures()->getPortCount(), &outportValue);
		return outportValue;
	}



	void Write_Output_Ex(uint32 port, uint8 bValue, int level = 0)
	{
		static uint8 hValue = 0;
		static uint8 lValue = 0;
		printf("hex %x\n", hValue);
		switch (port)
		{
		case 0:if (0 == level) { hValue &= ~bValue; } else { hValue |= bValue; }	Write_Output(0, hValue);	break;
		case 1:if (0 == level) { lValue &= ~bValue; } else { lValue |= bValue; }	Write_Output(1, lValue);	break;
		default:
			break;
		}
	}



	int m_IportCount = 0;
	byte* m_portData;
	InstantDiCtrl		*m_instantDiCtrl = NULL;
	InstantDoCtrl		*m_instantDoCtrl = NULL;
};