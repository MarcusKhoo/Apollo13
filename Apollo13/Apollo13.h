/*==============================================
 * Assignment1
 *
 * Written by Marcus Khoo 1031582 Class: DIT/FT/2A/07
 *==============================================*/
#pragma once
#include <sstream>
#include <math.h>
#include "GameUtils.h"
#include "SceneEngine.h"
#include "Node.h"
#include "Maze.h"
#include "ConsoleOutput.h"
#include "SpriteUtils.h"
#include "FontUtils.h"
#include "XMesh.h"

#include "SceneEngine.h"
#include "MessageBoxScene.h"

using namespace std;

const POINT itemListPosition[] = {{565,30}, {565,100}, {565,170}, {565,240}, {565,310}};

const POINT BACK_BUT={270,400},
	BACK_BUT02={110,400},
	ARROW_NEXT={550,250},
ARROW_PREVIOUS = {20,250};

const POINT PLAY_BUT={65,150},
	HELP_BUT={65,230},
	CREDITS_BUT = {65,310},
	EXIT_BUT={65,390};


class GameScene: public CScene
{
	CMeshNode mPlayer; 
	CMeshNode* mEnemy;
	CMeshNode* mAccessCard;
	CMeshNode* mCrowBar;
	CMeshNode* mPhone;
	CMeshNode* mBattery;
	CMeshNode* mCoke;
	CMeshNode* mExit;
	CMeshNode* mHealth;
	CMeshNode* mTimeClock;
	CXMesh* mpPhoneMesh;
	CXMesh* mpBatteryMesh;
	CXMesh* mpEnemyMesh;
	CXMesh* mpPlayerMesh;
	CXMesh* mpAccessCardMesh;
	CXMesh* mpCrowBarMesh;
	CXMesh* mpGroundMesh;
	CXMesh* mpCrateMesh;
	CXMesh* mpHotCrateMesh;
	CXMesh* mpSpaceMesh;
	CXMesh* mpCokeMesh;
	CXMesh* mpExitMesh;
	CXMesh* mpHealthMesh;
	CXMesh* mpTimeClockMesh;
	CMaze* mpMaze;
	int mMode, itemCount;
	float time;
	CCameraNode mCamera;
	float takingDamage, takingItems; 
	float exitTextAlpha;

	vector<CMeshNode*> items;
	vector<CMeshNode*> enemies;
	vector<CMeshNode*> healthPacks;
	vector<CMeshNode*> timeClock;
	vector<IDirect3DTexture9*> itemList;
	vector<IDirect3DTexture9*> itemListTaken;
	
	ID3DXFont* gameFont;
	ID3DXFont* infoFont;
	IDirect3DTexture9* mpAccessCardTex;
	IDirect3DTexture9* mpAccessCardTakenTex;
	IDirect3DTexture9* mpCrowbarTex;
	IDirect3DTexture9* mpCrowbarTakenTex;
	IDirect3DTexture9* mpPhoneTex;
	IDirect3DTexture9* mpPhoneTakenTex;
	IDirect3DTexture9* mpBatteryTex;
	IDirect3DTexture9* mpBatteryTakenTex;
	IDirect3DTexture9* mpCokeTex;
	IDirect3DTexture9* mpCokeTakenTex;

	void Enter();
	void Update(float dt);
	void Draw(float dt);
	void CameraMode();

	void EnemyAI(float dt, float speed, vector<CMeshNode*> enemies);

	void Leave();
};

class HelpScene: public CScene
{
	IDirect3DTexture9* mpButtonTex;
	IDirect3DTexture9* mpLogoTex;
	IDirect3DTexture9* instructionsTex01;
	IDirect3DTexture9* instructionsTex02;
	IDirect3DTexture9* instructionsTex03;
	IDirect3DTexture9* nextPageTex;
	IDirect3DTexture9* previousPageTex;

	int pageNo;

	ID3DXFont* mpFont;

	void Enter();

	void Update(float dt);
	
	void Draw(float dt);

	void Leave();
};

class CreditsScene: public CScene
{
	IDirect3DTexture9* mpLogoTex;
	IDirect3DTexture9* mpButtonTex;
	IDirect3DTexture9* creditsTex;

	void Enter();

	void Update(float dt);

	void Draw(float dt);

	void Leave();

};

class MenuScene: public CScene
{
	IDirect3DTexture9* mpButtonTex[4];
	IDirect3DTexture9* mpLogoTex;

	void Enter();

	void Update(float dt);
	
	void Draw(float dt);

	void Leave();

};