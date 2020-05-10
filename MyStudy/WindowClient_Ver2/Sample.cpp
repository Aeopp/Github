#include "Sample.h"

bool Sample::RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
bool Sample::RectInRect(RECT src, RECT desk)
{
	POINT cSrcCenter, cDeskCenter;
	// 100  150  200 -> 300 /2 = 150
	// 150
	// 200  ==> (150,150)
	cSrcCenter.x = (src.left + src.right) / 2;
	cSrcCenter.y = (src.top + src.bottom) / 2;
	cDeskCenter.x = (desk.left + desk.right) / 2;
	cDeskCenter.y = (desk.top + desk.bottom) / 2;

	POINT Distance;
	Distance.x = abs(cSrcCenter.x - cDeskCenter.x);
	Distance.y = abs(cSrcCenter.y - cDeskCenter.y);
	POINT RadiusSrc;
	POINT RadiusDesk;
	RadiusSrc.x = src.right - cSrcCenter.x;
	RadiusSrc.y = src.bottom - cSrcCenter.y;
	RadiusDesk.x = desk.right - cDeskCenter.x;
	RadiusDesk.y = desk.bottom - cDeskCenter.y;
	if (Distance.x <= (RadiusSrc.x+RadiusDesk.x) &&
		Distance.y <= (RadiusSrc.y + RadiusDesk.y))
	{
		return true;
	}
	return false;
}
void Sample::SetLifeCounter()
{
	if (HeroLifeTime > 3.0f)
	{
		if (auto SharedSound = GetSoundManager.GetSound(L"Gun2.wav").lock();
			SharedSound) {
			SharedSound->PlayEffect();
		}
		LifeCounter--;
		HeroLifeTime = 0.0f;
	}
}
TNpcObj* Sample::AddNpc()
{
	TNpcObj*  npc = new TNpcObj;
	if (npc->Load(ScreenHDC, L"../../../Data/Bitmap/1945.bmp"))
	{
		RECT rtSrc, rtDesk;
		rtSrc.left = 307;
		rtSrc.top = 248;
		//rtSrc.right = 61;
		//rtSrc.bottom = 1;
		rtDesk.left = rand() % 800;
		rtDesk.top = 0;
		rtDesk.right = 59;
		rtDesk.bottom = 48;
		npc->SetRect(rtSrc, rtDesk);
	}
	return npc;
}
bool	Sample::Init()
{	
	GetSoundManager.Load(L"../../../Data/Sound/romance.mid");
	GetSoundManager.Load(L"../../../Data/Sound/Gun1.wav");
	GetSoundManager.Load(L"../../../Data/Sound/Gun2.wav");
	m_BackGround.Load(ScreenHDC, L"../../../Data/Bitmap/lobby.bmp");
	if (m_Hero.Load(ScreenHDC, L"../../../Data/Bitmap/1945.bmp"))
	{
		RECT rtSrc, rtDesk;
		rtSrc.left = 206;
		rtSrc.top = 413;
		//rtSrc.right = 61;
		//rtSrc.bottom = 1;
		rtDesk.left = World::ClientRect.right / 2;
		rtDesk.top = World::ClientRect.bottom / 2;
		rtDesk.right = 60;
		rtDesk.bottom = 47;
		m_Hero.SetRect(rtSrc, rtDesk);
	}
	if (m_Projectile.Load(ScreenHDC, L"../../../Data/Bitmap/bitmap1.bmp"))
	{
		RECT rtSrc, rtDesk;
		rtSrc.left = 276;
		rtSrc.top = 1;
		rtDesk.left = m_Hero.X;
		rtDesk.top  = m_Hero.Y;
		rtDesk.right = 8;
		rtDesk.bottom = 24;
		m_Projectile.SetRect(rtSrc, rtDesk);
	}
	for (int iNpc = 0; iNpc < 1; iNpc++)
	{
		m_NpcList.push_back(AddNpc());
	}
	
	if (auto SharedSound = GetSoundManager.GetSound(L"romance.mid").lock(); SharedSound) {
		SharedSound->Play();
	}

	return true;
}
bool	Sample::Frame()
{
	m_Hero.Frame();
	m_Projectile.Frame();
	if (World::InputMapState.Attack == EKeyState::Push)
	{
		TProjectile item;
		item.fLifeTime  = 2.0f;
		item.rtDesk		= m_Projectile.RectDestnation;
		item.SetPos(m_Hero.Vector[0], m_Hero.Vector[1]);
		m_ProjectileList.insert(m_ProjectileList.end(),
			item);
		if (auto SharedSound = GetSoundManager.GetSound(L"Gun1.wav").lock(); SharedSound) {
			SharedSound->PlayEffect();
		}
	}
	list<TProjectile>::iterator iter;
	for (iter = m_ProjectileList.begin();
		iter != m_ProjectileList.end(); )
	{
		(*iter).fLifeTime -= World::FramePerSecond;
		(*iter).pos[1] -= World::FramePerSecond * 500.0f;
		(*iter).SetPos((*iter).pos[0], (*iter).pos[1]);

		if ((*iter).fLifeTime < 0.0f)
		{
			iter = m_ProjectileList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_fNpcTime += World::FramePerSecond;
	if (m_fNpcTime > 1.0f)
	{
		m_NpcList.push_back(AddNpc());
		m_fNpcTime -= 1.0f;
	}

	for (TNpcObj* npc : m_NpcList)
	{
		if (npc->m_bDead == true) continue;
		npc->Frame();
		// Collision
		list<TProjectile>::iterator iter;
		for (iter = m_ProjectileList.begin();
			iter != m_ProjectileList.end();
			iter++)
		{
			if (RectInRect( npc->Collision, 
							(*iter).rtCollision))
			{
				npc->m_bDead = true;
				break;
			}
		}
		if (RectInRect(npc->Collision,
			m_Hero.Collision))
		{
			//m_bExit = true;
			
			SetLifeCounter();
			break;
		}
		if (RectInPt(npc->Collision,World::MousePosition))
		{
			npc->SetPos(0, 0);
		}
	}
	if (LifeCounter <= 0)
	{
		Exit = true;
	}
	HeroLifeTime += World::FramePerSecond;
	return true;
}
bool	Sample::Render()
{
	m_BackGround.Render(OffScreenDC);
	m_Hero.Render(OffScreenDC);
	list<TProjectile>::iterator iter;
	for (iter = m_ProjectileList.begin();
		iter != m_ProjectileList.end(); iter++)
	{
		m_Projectile.SetPos((*iter).pos[0], (*iter).pos[1]);
		m_Projectile.Render(OffScreenDC);
	}
	for (TNpcObj* npc : m_NpcList)
	{
		if (npc->m_bDead == true) continue;
		npc->Render(OffScreenDC);
	}

	HFONT hOldFont = (HFONT)SelectObject(OffScreenDC.get(), GameFont.get());
	tstring strBuffer = L"LIFE :";
	strBuffer += std::to_wstring(LifeCounter);
	SetTextColor(OffScreenDC.get(), RGB(255, 0, 0));
	SetBkColor(OffScreenDC.get(), RGB(0, 0, 255));
	SetBkMode(OffScreenDC.get(), TRANSPARENT);
	RECT rt = World::ClientRect;
	rt.left = 400;
	DrawText(OffScreenDC.get(), strBuffer.c_str(),
		-1, &rt,
		DT_LEFT | DT_VCENTER);
	SelectObject(OffScreenDC.get(), hOldFont);
	return true;
}
bool	Sample::Release()
{



	for (TNpcObj* npc : m_NpcList)
	{
		delete npc;
	}
	m_NpcList.clear();
	return true;
}

Sample::Sample()
{
	m_fNpcTime = 0.0f;
	HeroLifeTime = 0.0f;
	LifeCounter = 3;
}
Sample::~Sample()
{
	
}
TWINGAME;