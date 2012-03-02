#include "Apollo13.h"

const POINT MENU_BUT = {245, 240},
			TRYAGAIN_BUT={245,330};


class GameOverScene: public CScene
{
	IDirect3DTexture9* mpLogoTex;
	IDirect3DTexture9* mpTryAgainTex;
	IDirect3DTexture9* mpExitMenuTex;

	void Enter()
	{
		ShowCursor(true);
		mTransOnTime=2;	// slow fade in
		mTransOffTime=2;	// slow fade out
		mpLogoTex=LoadSpriteTex(GetDevice(),"media/gameOverBackground.png");
		mpTryAgainTex=LoadSpriteTex(GetDevice(),"media/tryAgain_but.png");
		mpExitMenuTex=LoadSpriteTex(GetDevice(),"media/menu_but.png");
	}

	void Update(float dt)
	{
		CScene::Update(dt);
		if(IsTopMost()==false) return;

		if (CGameWindow::KeyPress(VK_LBUTTON))
		{
			POINT mouse=CGameWindow::GetMousePos();
			if (InSprite(mouse,TRYAGAIN_BUT,mpTryAgainTex))	// clicked the button
			{
				ShowCursor(false);
				GetEngine()->AddScene(new GameScene());
				ExitScene();
			}
			else if(InSprite(mouse, MENU_BUT, mpExitMenuTex))
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
		if (InSprite(mouse,TRYAGAIN_BUT,mpTryAgainTex))
		{
			DrawSprite(GetSprite(),mpTryAgainTex,TRYAGAIN_BUT);
		}
		else
		{
			DrawSprite(GetSprite(),mpTryAgainTex,TRYAGAIN_BUT, SKY_COL*0.75f);
		}

		if(InSprite(mouse,MENU_BUT,mpExitMenuTex))
		{
			DrawSprite(GetSprite(),mpExitMenuTex,MENU_BUT);
		}
		else
		{
			DrawSprite(GetSprite(),mpExitMenuTex,MENU_BUT, SKY_COL*0.75f);
		}
	
		GetSprite()->End();

		DrawTransitionFade(WHITE_COL);	// fade, just add it before the EndScene
		GetDevice()->EndScene();
	}

	void Leave()
	{
		SAFE_RELEASE(mpTryAgainTex);
		SAFE_RELEASE(mpExitMenuTex);
		SAFE_RELEASE(mpLogoTex);
	}
};

