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

		class Case					//кожух
		{
			
		public:

		};

		class Panel					//панель
		{
		};

		class ResetButton			//	кнопка сброса показаний микроамперметра
		{
		};

		class PhoneSlot				//гнездо включения телефонов
		{
		};

		class ModeTuner				// ручка потенциометра регулировки режима работы
		{
		};

		class MicroAmperMeter		//микроамперметер
		{
		};

		class EnligthenButton		//тумблер подсвета шкал
		{
		};

		class SubRangeSwitcher		//переключатель поддиапазонов
		{
		};

		class CabelSlot				//разъемное соединение для подключения кабеля зонда
		{
		};

		class TunerStaff			//пробка корректора механической установки нуля
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