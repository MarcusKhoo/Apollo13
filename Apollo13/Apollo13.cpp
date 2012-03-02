#include "Apollo13.h"
#include "WinScene.h"
#include "GameOverScene.h"

void GameScene::Enter()
{
	ShowCursor(false);

	mTransOnTime=2;	// slow fade in
	mTransOffTime=2;	// slow fade out

	mpGroundMesh=new CXMesh(GetDevice(),"media/ground.X");
	mpPlayerMesh=new CXMesh(GetDevice(),"media/BoxHead.X");
	mpCrateMesh=new CXMesh(GetDevice(),"media/spacecrate.X");
	mpSpaceMesh = new CXMesh(GetDevice(), "media/spacesphere.X");
	mpHotCrateMesh = new CXMesh(GetDevice(), "media/hotcrate.X");
	mpAccessCardMesh = new CXMesh(GetDevice(), "media/AccessCard.X");
	mpCrowBarMesh = new CXMesh(GetDevice(), "media/CrowBar.X");
	mpEnemyMesh = new CXMesh(GetDevice(), "media/enemy.X");
	mpPhoneMesh = new CXMesh(GetDevice(), "media/phone.X");
	mpBatteryMesh = new CXMesh(GetDevice(), "media/Battery.X");
	mpCokeMesh = new CXMesh(GetDevice(), "media/Coke.X");
	mpExitMesh = new CXMesh(GetDevice(), "media/exit.X");
	mpHealthMesh = new CXMesh(GetDevice(), "media/health.X");
	mpTimeClockMesh = new CXMesh(GetDevice(), "media/time.X");

	mpAccessCardTex = LoadSpriteTex(GetDevice(), "media/AccessCardTexture.png");
	mpAccessCardTakenTex = LoadSpriteTex(GetDevice(), "media/AccessCardTakenTexture.png");
	mpCrowbarTex = LoadSpriteTex(GetDevice(), "media/CrowbarTexture.png");
	mpCrowbarTakenTex = LoadSpriteTex(GetDevice(), "media/CrowbarTakenTexture.png");
	mpPhoneTex = LoadSpriteTex(GetDevice(), "media/PhoneTexture.png");
	mpPhoneTakenTex = LoadSpriteTex(GetDevice(), "media/PhoneTakenTexture.png");
	mpBatteryTex = LoadSpriteTex(GetDevice(), "media/BatteryTexture.png");
	mpBatteryTakenTex = LoadSpriteTex(GetDevice(), "media/BatteryTakenTexture.png");
	mpCokeTex = LoadSpriteTex(GetDevice(), "media/CokeTexture.png");
	mpCokeTakenTex = LoadSpriteTex(GetDevice(), "media/CokeTakenTexture.png");

	mPlayer.Init(mpPlayerMesh,D3DXVECTOR3(1,0.01f,1));

	mAccessCard = new CMeshNode();
	mCrowBar = new CMeshNode();
	mPhone = new CMeshNode();
	mBattery = new CMeshNode();
	mCoke = new CMeshNode();
	mExit = new CMeshNode();

	mAccessCard->Init(mpAccessCardMesh, D3DXVECTOR3(1,0.1f,8));
	mCrowBar->Init(mpCrowBarMesh, D3DXVECTOR3(48,0.1f,1));
	mPhone->Init(mpPhoneMesh, D3DXVECTOR3(48,0.1f,16));
	mBattery->Init(mpBatteryMesh, D3DXVECTOR3(9,0.1f,25));
	mCoke->Init(mpCokeMesh, D3DXVECTOR3(1,0.1f,46));
	mExit->Init(mpExitMesh, D3DXVECTOR3(39,0,42));

	items.push_back(mAccessCard);
	items.push_back(mCrowBar);
	items.push_back(mPhone);
	items.push_back(mBattery);
	items.push_back(mCoke);

	// load all health packs
	mHealth = new CMeshNode();
	mHealth->Init(mpHealthMesh, D3DXVECTOR3(20,0,10));
	healthPacks.push_back(mHealth);

	mHealth = new CMeshNode();
	mHealth->Init(mpHealthMesh, D3DXVECTOR3(18,0,44));
	healthPacks.push_back(mHealth);

	//load all time clocks
	mTimeClock = new CMeshNode();
	mTimeClock->Init(mpTimeClockMesh, D3DXVECTOR3(32,0,34));
	timeClock.push_back(mTimeClock);

	mTimeClock = new CMeshNode();
	mTimeClock->Init(mpTimeClockMesh, D3DXVECTOR3(8,0,36));
	timeClock.push_back(mTimeClock);

	itemList.push_back(mpAccessCardTex);
	itemList.push_back(mpCrowbarTex);
	itemListTaken.push_back(mpAccessCardTakenTex);
	itemListTaken.push_back(mpCrowbarTakenTex);
	itemList.push_back(mpPhoneTex);
	itemListTaken.push_back(mpPhoneTakenTex);
	itemList.push_back(mpBatteryTex);
	itemList.push_back(mpCokeTex);
	itemListTaken.push_back(mpBatteryTakenTex);
	itemListTaken.push_back(mpCokeTakenTex);

	mpMaze=new CMaze(mpCrateMesh, mpHotCrateMesh);
	mpMaze->Init("media/maze.txt");

	SetupDefaultD3DOptions(GetDevice(), true);
	//more lights
	GetDevice()->SetLight(1, &InitDirectionalLight(D3DXVECTOR3(1,-1,0), D3DXCOLOR(D3DCOLOR_XRGB(255,255,255))));
	GetDevice()->LightEnable(1, true);
	GetDevice()->SetLight(2, &InitDirectionalLight(D3DXVECTOR3(0,-1.0f,-1.0f), D3DXCOLOR(D3DCOLOR_XRGB(255,255,255))));
	GetDevice()->LightEnable(2, true);
	GetDevice()->SetLight(3, &InitDirectionalLight(D3DXVECTOR3(0,-1.0f,1.0f), D3DXCOLOR(D3DCOLOR_XRGB(255,255,255))));
	GetDevice()->LightEnable(3, true);
	//CameraLookAt(GetDevice(),D3DXVECTOR3(5,15,4.9f),D3DXVECTOR3(5,0,5));

	mCamera.SetNearFar(0.1f,1000.0f);

	gameFont = CreateD3DFont(GetDevice(), "Segoe UI", 24, false);
	infoFont = CreateD3DFont(GetDevice(), "Segoe UI", 32, false);

	//init variables
	time = 181.0f;
	itemCount = 0;
	takingDamage = 0.0f;
	takingItems = 0.0f;
	exitTextAlpha = 0.0f;

	//init the camera
	mCamera.SetPos(mPlayer.OffsetPos(D3DXVECTOR3(0,0.7f,-2)));
	mCamera.LookAt(mPlayer.OffsetPos(D3DXVECTOR3(0,0,0.5)));

	//init enemies
	for(int i = 0; i<10; i++)
	{
		mEnemy = new CMeshNode();
		mEnemy->mDirection = D3DXVECTOR3(1,0,0);
		do
		{
			mEnemy->Init(mpEnemyMesh, D3DXVECTOR3(randi(0,49), 0.1f, randi(0,49)));
		}while(!mpMaze->IsClear(mEnemy->GetPos(), 0.75 * mEnemy->GetBoundingRadius()));
		enemies.push_back(mEnemy);
	}
}
void GameScene::Update(float dt)
{
	CScene::Update(dt);	// MUST CALL BASE CLASS'S Update
	if (IsTopMost()==false)	return;	// Pause if I'm not the topmost screen

	//decrease the timer's time
	time -= dt;
	takingDamage -= dt;
	exitTextAlpha -= dt;
	takingItems -= dt;

	if (CGameWindow::KeyPress(VK_ESCAPE))
	{
		CMessageBoxScene* pMsg=new CMessageBoxScene("Quit?");
		pMsg->OnOkCloseScene(this);
		ShowCursor(true);
		GetEngine()->AddScene(pMsg);
	}

	// basic movement:
	const float SPEED=3.0f;
	const float TURN=D2R(60);
	D3DXVECTOR3 move(0,0,0);
	move=GetMouseTurnVector(20,true);
	mPlayer.Yaw(move.x*dt*TURN);
	move = GetKeyboardVector(WSAD_KEYS);

	D3DXVECTOR3 oldPos = mPlayer.GetPos();
	mPlayer.MoveGround(move*dt*SPEED);
	D3DXVECTOR3 newPos = mPlayer.GetPos();

	//set the position
	mPlayer.SetPos(mpMaze->WallSlide(oldPos,newPos,0.5f*mPlayer.GetBoundingRadius()));

	//move enemy
	EnemyAI(dt, 3.0f, enemies);

	//player collide with enemies
	for(int i = enemies.size()-1; i>=0; i--)
	{
		if(CollisionMeshNode(&mPlayer,enemies[i]))
		{
			takingDamage = 1.0f;
			mPlayer.Damage(15);
			enemies[i]->Destroy();
			break;
		}
	}

	// player collide with items
	for(int i = items.size()-1; i>=0; i--)
	{
		if(CollisionMeshNode(&mPlayer, items[i]))
		{
			if(items[i]->IsAlive())
			{
				items[i]->Destroy();
				itemCount += 1;
				cout<< itemCount;
				break;
			}
		}
	}

	// player collide with health pack
	for(int i = healthPacks.size()-1;i>=0;i--)
	{
		if(CollisionMeshNode(&mPlayer, healthPacks[i]))
		{
			takingItems = 0.6f;
			healthPacks[i]->Destroy();
			mPlayer.mLife += 10;
			break;
		}
	}

	//player collide with time clock
	for(int i = timeClock.size()-1;i>=0;i--)
	{
		if(CollisionMeshNode(&mPlayer, timeClock[i]))
		{
			takingItems = 0.6f;
			time += 20;
			timeClock[i]->Destroy();
			break;
		}
	}

	//player collide with exit
	if(CollisionMeshNode(&mPlayer, mExit))
	{

		if(itemCount >= 5)
		{
			GetEngine()->AddScene(new WinScene());
			ExitScene();
		}
		else
		{
			exitTextAlpha = 1.0f;;
		}
	}

	//player collide with hot blocks
	if(mpMaze->IsTouchingHot(mPlayer.GetPos(), 0.75f*mPlayer.GetBoundingRadius()))
	{
		takingDamage = 0.4f;
		mPlayer.Damage(0.35f);	
	}

	//timer reach zero or player's life reach zero
	if(time <= 0 || !mPlayer.IsAlive())
	{
		GetEngine()->AddScene(new GameOverScene());
		ExitScene();
	}

	// the camera stuff
	CameraMode();

	//DeleteDeadMeshNodes(items);
	DeleteDeadMeshNodes(enemies);
	DeleteDeadMeshNodes(timeClock);
	DeleteDeadMeshNodes(healthPacks);

	// TODO: you should replace this with some real code
	// which stops people from walking through walls
	// or even makes them slide on walls
}
void GameScene::Draw(float dt)
{
	//set the camera
	mCamera.SetMatrixes(GetDevice());

	// Clear the backbuffer to a black color
	GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BLUE_COL, 1.0f, 0 );
	GetDevice()->BeginScene();

	// draw ground so its centres on the maze
	mpGroundMesh->Draw(D3DXVECTOR3(25,0,25));
	mpSpaceMesh->Draw(D3DXVECTOR3(15.0f,0.0f,15.0f));
	mpMaze->Draw();
	mPlayer.Draw();

	for(int i = 0; i<enemies.size(); i++)
	{
		enemies[i]->Draw();
	}

	//animation for fun
	for(int i = 0; i<items.size(); i++)
	{
		items[i]->Yaw(D2R(dt*60));
		if(items[i]->IsAlive())
			items[i]->Draw();
	}

	for(int i = 0; i<healthPacks.size(); i++)
	{
		healthPacks[i]->Yaw(D2R(dt*60));
		healthPacks[i]->Draw();
	}

	for(int i = 0; i<timeClock.size(); i++)
	{
		timeClock[i]->Yaw(D2R(dt*60));
		timeClock[i]->Draw();
	}

	mExit->Yaw(D2R(dt*60));
	mExit->Draw();

	//draw ui
	stringstream sout;
	sout << "Life: " << (int)mPlayer.mLife;
	DrawD3DFontEx(gameFont, NULL, sout.str().c_str(),10,10,WHITE_COL);
	sout.str("");
	sout << "Time: " << floor(time);
	DrawD3DFontEx(gameFont, NULL, sout.str().c_str(), 320, 10, WHITE_COL, DT_TOP|DT_CENTER|DT_NOCLIP);
	DrawD3DFontEx(gameFont, NULL, "Collect", 600,10,WHITE_COL,  DT_TOP|DT_CENTER|DT_NOCLIP);

	GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	//draw sprites
	for(int i = 0; i<items.size(); i++)
	{
		if(i<itemList.size())
		{
			if(items[i]->IsAlive())
			{
				DrawSprite(GetSprite(),itemList[i],itemListPosition[i]);
			}
			else
			{
				DrawSprite(GetSprite(),itemListTaken[i], itemListPosition[i]);
			}
		}
	}


	GetSprite()->End();

	if(takingDamage>0)
		GetEngine()->DrawColourTint(D3DXCOLOR(1,0,0,takingDamage));

	if(takingItems>0)
		GetEngine()->DrawColourTint(D3DXCOLOR(1,1,1,takingItems));

	if(exitTextAlpha > 0)
		DrawD3DFontEx(infoFont, NULL, "You have not collect all items!", 180,240, D3DXCOLOR(1,1,1,exitTextAlpha));

	DrawTransitionFade();	// fade, just add it before the EndScene
	GetDevice()->EndScene();
	// note: no need to call Present, that is done in the CSceneEngine
}

void GameScene::CameraMode()
{
	if (CGameWindow::KeyPress(VK_F1))		mMode=0;
	if (CGameWindow::KeyPress(VK_F2))		mMode=1;
	if (CGameWindow::KeyPress(VK_F3))		mMode=2;

	switch(mMode)
	{
	case 1: // plank third person
		{
			//camera spring
			D3DXVECTOR3 pos,oldpos,desired;

			oldpos=mCamera.GetPos();
			desired=mPlayer.OffsetPos(D3DXVECTOR3(0,1.0f,-1.0f));
			pos=(oldpos*0.9f)+(desired*0.1f); // 90% of oldPos and 10% of newPos

			mCamera.SetPos(pos);
			mCamera.LookAt(mPlayer.OffsetPos(D3DXVECTOR3(0,0,2.0f)));
			//mCamera.LookAt(mPlayer);
		}
		break;
	case 2:
		mCamera.SetPos(D3DXVECTOR3(25,25,25));
		mCamera.LookAt(mPlayer);
		break;
	default: // first person
		mCamera.SetPos(mPlayer.GetPos().x,mPlayer.GetPos().y+0.5f,mPlayer.GetPos().z);
		mCamera.SetHpr(mPlayer.GetHpr());
		break;
	}
}

void GameScene::EnemyAI(float dt, float speed, vector<CMeshNode*> enemies)
{
	for(int i = 0; i<enemies.size(); i++)
	{
		D3DXVECTOR3 oldPos = enemies[i]->GetPos();
		enemies[i]->MoveGround(enemies[i]->mDirection*dt*speed);
		D3DXVECTOR3 newPos = enemies[i]->GetPos();

		if(!mpMaze->IsClear(enemies[i]->GetPos(), enemies[i]->GetBoundingRadius() * 0.75f))
		{
			int rand = randi(0,3);
			switch(rand)
			{
			case 0:
				enemies[i]->mDirection = D3DXVECTOR3(1,0,0);
				break;
			case 1:
				enemies[i]->mDirection = D3DXVECTOR3(0,0,1);
				break;
			case 2:
				enemies[i]->mDirection = D3DXVECTOR3(-1,0,0);
				break;
			case 3:
				enemies[i]->mDirection = D3DXVECTOR3(0,0,-1);
				break;
			}
		}

		enemies[i]->SetPos(mpMaze->WallSlide(oldPos,newPos,0.75*enemies[i]->GetBoundingRadius()));
	}
}

void GameScene::Leave()
{
	SAFE_DELETE(mpGroundMesh);
	SAFE_DELETE(mpHotCrateMesh);
	SAFE_DELETE(mpPlayerMesh);
	SAFE_DELETE(mpCrateMesh);
	SAFE_DELETE(mpSpaceMesh);
	SAFE_DELETE(mpMaze);
	SAFE_DELETE(mpAccessCardMesh);
	SAFE_DELETE(mpCrowBarMesh);
	SAFE_DELETE(mpPhoneMesh);
	SAFE_DELETE(mpEnemyMesh);
	SAFE_DELETE(mpBatteryMesh);
	SAFE_DELETE(mpCokeMesh);
	SAFE_DELETE(mpExitMesh);
	SAFE_DELETE(mpHealthMesh);
	SAFE_DELETE(mpTimeClockMesh);
	DeleteMeshNodes(items);
	DeleteMeshNodes(enemies);
	DeleteMeshNodes(healthPacks);
	DeleteMeshNodes(timeClock);
	delete mExit;
	ShowCursor(true);
}



void HelpScene::Enter()
{
	mTransOnTime=2;	// slow fade in
	mTransOffTime=2;	// slow fade out
	// load the media
	mpFont=CreateD3DFont(GetDevice(),"Segoe UI",24,true);
	mpLogoTex=LoadSpriteTex(GetDevice(),"media/helpBackground.png");
	mpButtonTex=LoadSpriteTex(GetDevice(),"media/back_but02.png");
	instructionsTex01 = LoadSpriteTex(GetDevice(), "media/instructionPage01.png");
	instructionsTex02 = LoadSpriteTex(GetDevice(), "media/instructionPage02.png");
	instructionsTex03 = LoadSpriteTex(GetDevice(), "media/instructionPage03.png");
	nextPageTex = LoadSpriteTex(GetDevice(), "media/nextPage.png");
	previousPageTex = LoadSpriteTex(GetDevice(), "media/previousPage.png");

	pageNo = 1;
}
void HelpScene::Update(float dt)
{
	CScene::Update(dt);	// MUST CALL BASE CLASS'S Update
	if (IsTopMost()==false)	return;	// Pause if I'm not the topmost screen

	// WARNING: you cannot have two calls to KeyPress for the same key within a function
	// the second call always gives false
	// therefore one KeyPress with many tests within it
	if (CGameWindow::KeyPress(VK_LBUTTON))
	{
		POINT mouse=CGameWindow::GetMousePos();
		if (InSprite(mouse,BACK_BUT02,mpButtonTex))	// clicked the button
		{
			ExitScene();
		}
		else if(InSprite(mouse,ARROW_NEXT,nextPageTex))
		{
			if(pageNo < 3)
				pageNo += 1;
		}
		else if(InSprite(mouse,ARROW_PREVIOUS, previousPageTex))
		{
			if(pageNo > 1)
				pageNo -= 1;
		}
	}
}
void HelpScene::Draw(float dt)
{
	GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, YELLOW_COL, 1.0f, 0 );
	GetDevice()->BeginScene();

	GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	RECT r=GetEngine()->GetWindowRect();
	DrawSprite(GetSprite(), mpLogoTex, r);
	// you can draw fonts with scaling & other effects using DrawD3DFontEx
	// but it must have a spitebatch set with D3DXSPRITE_ALPHABLEND

	r.top = 100; r.left = 100; r.bottom = 450; r.right = 540;
	
	switch(pageNo)
	{
		case 1:
			DrawSprite(GetSprite(), instructionsTex01, r);
			break;
		case 2:
		{
			DrawSprite(GetSprite(), instructionsTex02, r);
		}
			break;
		case 3:
			DrawSprite(GetSprite(), instructionsTex03, r);
			break;
	}

	DrawSprite(GetSprite(), nextPageTex, ARROW_NEXT);

	DrawSprite(GetSprite(), previousPageTex, ARROW_PREVIOUS);

	// just a normal draw using the spritebatch
	POINT mouse=CGameWindow::GetMousePos();
	if (InSprite(mouse,BACK_BUT02,mpButtonTex))
	{
		DrawSprite(GetSprite(),mpButtonTex,BACK_BUT02);
	}
	else
	{
		DrawSprite(GetSprite(),mpButtonTex,BACK_BUT02, SKY_COL*0.75f);
	}

	if(InSprite(mouse, ARROW_NEXT,nextPageTex))
	{
		DrawSprite(GetSprite(), nextPageTex, ARROW_NEXT);
	}
	else
	{
		DrawSprite(GetSprite(),nextPageTex,ARROW_NEXT, SKY_COL*0.75f);
	}

	if(InSprite(mouse, ARROW_PREVIOUS,previousPageTex))
	{
		DrawSprite(GetSprite(), previousPageTex, ARROW_PREVIOUS);
	}
	else
	{
		DrawSprite(GetSprite(),previousPageTex,ARROW_PREVIOUS, SKY_COL*0.75f);
	}

	stringstream sout;
	sout << pageNo << "/3";
	DrawD3DFontEx(mpFont, GetSprite(), sout.str().c_str(), 500,420, D3DXCOLOR(1,1,1,1)); 
	GetSprite()->End();

	DrawTransitionFade(WHITE_COL);	// fade, just add it before the EndScene
	GetDevice()->EndScene();
	// note: no need to call Present, that is done in the CSceneEngine
}
void HelpScene::Leave()
{
	SAFE_RELEASE(mpFont);
	SAFE_RELEASE(mpButtonTex);
	SAFE_RELEASE(mpLogoTex);
	SAFE_RELEASE(instructionsTex01);
	SAFE_RELEASE(instructionsTex02);
	SAFE_RELEASE(instructionsTex03);
	SAFE_RELEASE(nextPageTex);
	SAFE_RELEASE(previousPageTex);
}


void CreditsScene::Enter()
{
	mTransOnTime=2;	// slow fade in
	mTransOffTime=2;	// slow fade out
	mpLogoTex=LoadSpriteTex(GetDevice(),"media/creditsBackground.png");
	mpButtonTex=LoadSpriteTex(GetDevice(),"media/back_but02.png");
	creditsTex = LoadSpriteTex(GetDevice(), "media/creditsPage.png");
}
void CreditsScene::Update(float dt)
{
	CScene::Update(dt);	// MUST CALL BASE CLASS'S Update
	if (IsTopMost()==false)	return;	// Pause if I'm not the topmost screen

	// WARNING: you cannot have two calls to KeyPress for the same key within a function
	// the second call always gives false
	// therefore one KeyPress with many tests within it
	if (CGameWindow::KeyPress(VK_LBUTTON))
	{
		POINT mouse=CGameWindow::GetMousePos();
		if (InSprite(mouse,BACK_BUT,mpButtonTex))	// clicked the button
		{
			ExitScene();
		}
	}
}
void CreditsScene::Draw(float dt)
{
	GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BLACK_COL, 1.0f, 0 );
	GetDevice()->BeginScene();

	GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	RECT r=GetEngine()->GetWindowRect();
	DrawSprite(GetSprite(), mpLogoTex, r);

	r.top = 100; r.left = 100; r.bottom = 450; r.right = 540;
	DrawSprite(GetSprite(), creditsTex, r);

	//mouse over the button
	POINT mouse=CGameWindow::GetMousePos();
	if (InSprite(mouse,BACK_BUT,mpButtonTex))
	{
		DrawSprite(GetSprite(),mpButtonTex,BACK_BUT);
	}
	else
	{
		DrawSprite(GetSprite(),mpButtonTex,BACK_BUT, SKY_COL*0.75f);
	}

	GetSprite()->End();


	DrawTransitionFade(WHITE_COL);// fade, just add it before the EndScene
	GetDevice()->EndScene();
}
void CreditsScene::Leave()
{
	SAFE_RELEASE(mpLogoTex);
	SAFE_RELEASE(mpButtonTex);
}


void MenuScene::Enter()
{
	GetEngine()->SetTitle("Apollo 13");
	mTransOnTime=2;	// slow fade in
	mTransOffTime=2;	// slow fade out
	mpLogoTex=LoadSpriteTex(GetDevice(),"media/menuBackground.png");
	mpButtonTex[0] = LoadSpriteTex(GetDevice(),"media/play_but02.png");
	mpButtonTex[1] = LoadSpriteTex(GetDevice(),"media/help_but02.png");
	mpButtonTex[2] = LoadSpriteTex(GetDevice(), "media/credits_but.png");
	mpButtonTex[3] = LoadSpriteTex(GetDevice(),"media/exit_but02.png");

}
void MenuScene::Update(float dt)
{
	CScene::Update(dt);	// MUST CALL BASE CLASS'S Update
	if (IsTopMost()==false)	return;	// Pause if I'm not the topmost screen

	if (CGameWindow::KeyPress(VK_LBUTTON))
	{
		POINT mouse=CGameWindow::GetMousePos();
		if (InSprite(mouse,PLAY_BUT,mpButtonTex[0]))	// clicked the button
		{
			ShowCursor(false);
			GetEngine()->AddScene(new GameScene());
		}
		else if(InSprite(mouse,HELP_BUT,mpButtonTex[1]))
		{
			GetEngine()->AddScene(new HelpScene());
		}
		else if(InSprite(mouse, CREDITS_BUT, mpButtonTex[2]))
		{
			GetEngine()->AddScene(new CreditsScene());
		}
		else if(InSprite(mouse,EXIT_BUT,mpButtonTex[3]))
		{
			ExitScene();
		}
	}
	// you will need to detect the mouse clicks
	// using InSprite() from SpriteUtils
	// to go to a new scene you will need to 
	// GetEngine()->AddScene(new TheSceneClass());
	// you will also need to call ExitScene() when you want the menu to close

}
void MenuScene::Draw(float dt)
{
	GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BLACK_COL, 1.0f, 0 );
	GetDevice()->BeginScene();

	// textures must be within BeginScene()..EndScene
	// and within a SpriteBatches Begin..End
	// we need the D3DXSPRITE_ALPHABLEND to enable transparency
	// you need the background and three buttons
	// at PLAY_BUT,HELP_BUT & EXIT_BUT locations
	GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	RECT r=GetEngine()->GetWindowRect();
	DrawSprite(GetSprite(), mpLogoTex, r);


	//mouse over the button
	POINT mouse=CGameWindow::GetMousePos();
	//play button
	if (InSprite(mouse,PLAY_BUT,mpButtonTex[0]))
	{
		DrawSprite(GetSprite(),mpButtonTex[0],PLAY_BUT);
	}
	else
	{
		DrawSprite(GetSprite(),mpButtonTex[0],PLAY_BUT, SKY_COL*0.75f);
	}
	//help button
	if(InSprite(mouse,HELP_BUT,mpButtonTex[1]))
	{
		DrawSprite(GetSprite(),mpButtonTex[1],HELP_BUT);
	}
	else 
	{
		DrawSprite(GetSprite(),mpButtonTex[1],HELP_BUT, SKY_COL*0.75f);
	}
	//credits button
	if(InSprite(mouse, CREDITS_BUT, mpButtonTex[2]))
	{
		DrawSprite(GetSprite(), mpButtonTex[2], CREDITS_BUT);
	}
	else
	{
		DrawSprite(GetSprite(), mpButtonTex[2], CREDITS_BUT, SKY_COL*0.75f);
	}
	//exit button
	if(InSprite(mouse,EXIT_BUT,mpButtonTex[3]))
	{
		DrawSprite(GetSprite(),mpButtonTex[3],EXIT_BUT);
	}
	else
	{
		DrawSprite(GetSprite(),mpButtonTex[3],EXIT_BUT, SKY_COL*0.75f);
	}


	GetSprite()->End();


	DrawTransitionFade();// fade, just add it before the EndScene
	GetDevice()->EndScene();
	// note: no need to call Present, that is done in the CSceneEngine
}
void MenuScene::Leave()
{
	std::cout<<"MenuScene::Leave\n";
	SAFE_RELEASE(mpLogoTex);
	for(int i=0;i<3;i++)
		SAFE_RELEASE(mpButtonTex[i]);
}

int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR lpCmdLine, int nCmdShow)
{

	bool full = false;
	if (MessageBox(NULL, "Fullscreen?", "GameWindow", MB_YESNO)==IDYES)
	{
		full=true;
	}
	ENABLE_LEAK_DETECTION();	// Enable run-time memory check for debug builds.
	CSceneEngine eng(640,480, full);
	eng.AddScene(new MenuScene());
	return eng.Go(hInstance);	// runs everything
}


