#include "SceneEngine.h"
#include "SpriteUtils.h"

const POINT menu_but = {245,240};

class WinScene: public CScene
{
	IDirect3DTexture9* mpLogoTex;
	IDirect3DTexture9* mpButtonTex;
	void Enter()
	{
		ShowCursor(true);
		mTransOnTime=2;	// slow fade in
		mTransOffTime=2;	// slow fade out
		mpButtonTex=LoadSpriteTex(GetDevice(),"media/menu_but.png");
		mpLogoTex=LoadSpriteTex(GetDevice(),"media/winBackground.png");
	}

	void Update(float dt)
	{
		CScene::Update(dt);	// MUST CALL BASE CLASS'S Update
		if (IsTopMost()==false)	return;	// Pause if I'm not the topmost screen
		if (CGameWindow::KeyPress(VK_LBUTTON))
		{
			POINT mouse=CGameWindow::GetMousePos();
			if (InSprite(mouse,menu_but,mpButtonTex))	// clicked the button
			{
				ExitScene();
			}
		}
	}

	void Draw(float dt)
	{
		GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, YELLOW_COL, 1.0f, 0 );
		GetDevice()->BeginScene();

		GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

		RECT r=GetEngine()->GetWindowRect();
		DrawSprite(GetSprite(), mpLogoTex, r);

		POINT mouse=CGameWindow::GetMousePos();
		if (InSprite(mouse,menu_but,mpButtonTex))
		{
			DrawSprite(GetSprite(),mpButtonTex,menu_but);
		}
		else
		{
			DrawSprite(GetSprite(),mpButtonTex,menu_but, SKY_COL*0.75f);
		}	
	
		GetSprite()->End();

		DrawTransitionFade(WHITE_COL);	// fade, just add it before the EndScene
		GetDevice()->EndScene();
	}

	void Leave()
	{
		SAFE_RELEASE(mpLogoTex);
		SAFE_RELEASE(mpButtonTex);
	}
};

