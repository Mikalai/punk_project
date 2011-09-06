/*
File: DP5.h
Author: Abramov Nickolai
Description: Contains a description of the DP-5V entity
*/

#ifndef _H_DP5V
#define _H_DP5V

#include "DP5Geometry.h"

namespace Device
{
	namespace DP
	{

		class Case					//�����
		{
			
		public:

		};

		class Panel					//������
		{
		};

		class ResetButton			//	������ ������ ��������� ���������������
		{
		};

		class PhoneSlot				//������ ��������� ���������
		{
		};

		class ModeTuner				// ����� ������������� ����������� ������ ������
		{
		};

		class MicroAmperMeter		//���������������
		{
		};

		class EnligthenButton		//������� �������� ����
		{
		};

		class SubRangeSwitcher		//������������� �������������
		{
		};

		class CabelSlot				//��������� ���������� ��� ����������� ������ �����
		{
		};

		class TunerStaff			//������ ���������� ������������ ��������� ����
		{
		};

		class DP5 : public DP5Geometry
		{
		public:
			Case m_case;
			Panel m_panel;
			ResetButton m_resetButton;
			PhoneSlot m_phoneSlot;
			ModeTuner m_modeTuner;
			MicroAmperMeter m_microAmperMeter;
			EnligthenButton m_enlightenButton;
			SubRangeSwitcher m_subRangeSwitcher;
			CabelSlot m_cabelSlot;
			TunerStaff m_tunerStaff;
		};
	}
}
#endif	//	_H_DP5V