// dllTest.h : dllTest DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CdllTestApp
// �йش���ʵ�ֵ���Ϣ������� dllTest.cpp
//

class CdllTestApp : public CWinApp
{
public:
	CdllTestApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
