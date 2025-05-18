


#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		




class CStudentFilterAppApp : public CWinApp
{
public:
	CStudentFilterAppApp();


public:
	virtual BOOL InitInstance();



	DECLARE_MESSAGE_MAP()
};

extern CStudentFilterAppApp theApp;
