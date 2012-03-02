#pragma once
// include directx9
#include <d3dx9.h>
#include "Node.h"

void CameraThirdPerson(CNode& cam,CNode& tgt,		
                D3DXVECTOR3 offset=D3DXVECTOR3(0,3,-10));
