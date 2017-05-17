
// ZombieApocalypse.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CZombieApocalypseApp:
// See ZombieApocalypse.cpp for the implementation of this class
//

class CZombieApocalypseApp : public CWinApp
{
public:
	CZombieApocalypseApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CZombieApocalypseApp theApp;