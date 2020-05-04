#include "Sound.h"
#include <utility>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <ostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Util.h"
//#define _CRT_SECURE_NO_WARNINGS

Sound::Sound():
	F_System{nullptr},
	F_Sound{ nullptr },
	Volume{ 0.5f } ,
	Length{}
{}

bool Sound::Init()noexcept{
	return true;
}

bool Sound::Render()const{
	std::wcout << played_time << std::endl; 
	return true; 
}

bool Sound::Clear()noexcept{
	return false;
}

bool Sound::Frame(){
	using std::to_wstring;
	// ä���� ���� ���� �Ǿ� ���� �ʴٸ� �ƹ��͵� ���� �ʴ´�.
	// ���ܸ� ������. 
	if (F_Channel == nullptr)
		//throw std::exception(Log("FMod Channel Not ready")); 
		 return false;

	uint32_t milisec{};
	F_Channel->getPosition(&milisec, FMOD_TIMEUNIT_MS);
	// ����ϰ����� �ð��� ���ϰ� �������Ͽ� ����

	std::wstringstream wss;

	wss << milisec / 1000 / 60 << L":"
		<< milisec / 1000 % 60 << L":"
		<< milisec / 10 % 100 << L" "
		<< Length / 1000 / 60 << L":"
		<< Length / 1000 % 60 << L":"
		<< Length / 10 % 100;

	played_time = L"Played Time : " + wss.str();
	
	return true;
}

Sound::~Sound()
{
	Clear(); 
}

void Sound::Pause() {
	bool isplay = false;

	if (F_Channel != nullptr)
		F_Channel->isPlaying(&isplay);

	if (isplay == true) {
		bool is_pause = false;
		F_Channel->getPaused(&is_pause);
		F_Channel->setPaused(!is_pause);
	}
};

void Sound::Stop(){
	
	F_Channel->stop();
}

void Sound::SetMode(uint32_t mode_param){
	F_Sound->setMode(mode_param);
}

bool Sound::Load(ReadType P_ReadType, FMOD::System* const P_System) {
	if (P_ReadType.empty() || P_System == nullptr)
		// Param �� ��������� Ȯ���ڰ� ��ȿ���� ������
		// Param ���� �� Sound �� �ε��Ҽ� ���� ��
		// System �� �غ���� �ʾ�����
		throw std::invalid_argument(__FUNCTION__"Param Empty");
	// return false; 
	F_System = P_System;
	ReadKey = std::move(P_ReadType);
	FMOD_RESULT HR;

	std::string convert_string(std::begin(ReadKey), std::end(ReadKey));
	//  ���带 �ҷ����� ������ ���� üũ�� �Ѵ�
	HR = F_System->createSound
	(convert_string.c_str(), FMOD_DEFAULT, 0, &F_Sound);

	if (HR != FMOD_OK)
		return false;

	F_Sound->getLength(&Length, FMOD_TIMEUNIT_MS);
	F_Channel->setVolume(Volume/*0.5f default*/);

	return true;
};

bool Sound::Play() {
	// Play !!
	if (ReadKey.empty())
		return false;
	
	FMOD_RESULT HR;
	bool isplay = false; 

	// ä���� �˻��ϰ� �÷��������� �ƴ��� üŷ
	if (F_Channel != nullptr)
		F_Channel->isPlaying(&isplay);

	// �̹� ��� ���̿��ٸ� ����� �����ϱ�
	// BGM �� ��ġ�� ��Ȳ ����
	if (isplay)
	{
		Stop();
	}
	
	{
		HR = F_System->playSound(F_Sound,nullptr, false, &F_Channel); 

		if (HR != FMOD_OK){
			return false;
		}
		else if	(HR == FMOD_OK){
			return true;
		}
	} 
	
	return false;  
}; 
bool Sound::PlayEffect() {
	FMOD_RESULT HR;
	
	HR = F_System->playSound(F_Sound, nullptr, false,&F_Channel);
	
	if (HR != FMOD_OK)
		return false;
		//throw std::exception(Log("HR != FMOD_OK"));

	return true; 
}




