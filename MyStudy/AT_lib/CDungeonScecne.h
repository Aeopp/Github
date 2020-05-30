#pragma once
#include "include/Scene/CScene.h"


class CDungeonScecne :
    public CScene
{
public:
    friend class CSceneManager;
    virtual bool Init(); 
    void EndButtonCallback(float fTime); 
        void StartButtonCallback(float fTime); 

};

