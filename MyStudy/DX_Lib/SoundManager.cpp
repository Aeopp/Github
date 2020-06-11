#include "SoundManager.h"

 bool SoundManager::Play(const std::string& SoundKey,
	 bool IsBgm) {

	if ( Sounds.empty() ||  (IsBgm == true && CurrentBgmKey == SoundKey) ) {
		return false; 
	}

	FMOD_RESULT HR;
	bool isplay = false;

	if (auto iter = Sounds.find(SoundKey);
		iter != std::end(Sounds)) {
		auto& [System, Sound, Channel] = iter->second;
		/*if (Channel != nullptr)*/ {
			Channel->isPlaying(&isplay);

			if (isplay == true && IsBgm==true) {
				Channel->stop();
			};
			HR = System->playSound(Sound, nullptr, false,
			&Channel);

			if (HR != FMOD_OK) {
				return  false;
			}
			else if(IsBgm==true){
				if (auto iter = Sounds.find(CurrentBgmKey);
					iter != std::end(Sounds)) {
					auto&[System,Sound,Channel]=iter->second;
					Channel->stop();
				}
				CurrentBgmKey = SoundKey;
			}
			return  true;
		}
	}
	else {

	}
	return false;
}

 bool SoundManager::Load( std::string FullPath) {
	 if (FMOD_System == nullptr) {
		 return false;
	 };
	 // ���� ���� �����ؼ� ����
	 if (auto iter = Sounds.find(FullPath);
		 iter == std::end(Sounds) == true) {
		 SoundType InsertSound;
		 auto& [System, Sound, Channel] = InsertSound;
		 System = FMOD_System;

		 FMOD_RESULT HR = System->createSound(FullPath.c_str(), FMOD_DEFAULT, 0, &Sound);

		 if (HR != FMOD_OK) {
			 return false;
		 };

		 Channel->setVolume(DefaultVolume);
		 Sounds.insert(iter,{ std::move(FullPath)  , InsertSound });
	 }
	 // �̹� ���尡 ������
	 else {

	 }
	 return true;
 };


 bool SoundManager::Frame() {
	 if (FMOD_System == nullptr) return false;
	 // update �Լ��� �������Ӹ��� �ݵ�� ȣ����������� �䱸��
	 FMOD_System->update();
	 return true;
 }
 bool SoundManager::Release()
 {
	 return true;
 }
 bool SoundManager::Init()
 {
	 FMOD_RESULT F_Result;

	 F_Result = FMOD::System_Create(&FMOD_System);

	 {
		 // FMOD �ý��� �ε� ����
		 if (F_Result != FMOD_OK)
			 return false;
		 F_Result = FMOD_System->init(32, FMOD_INIT_NORMAL, 0);
		 if (F_Result != FMOD_OK)
			 return false;
	 }

	 return true;
 }
