// dllTest.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "dllTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CdllTestApp

BEGIN_MESSAGE_MAP(CdllTestApp, CWinApp)
END_MESSAGE_MAP()


// CdllTestApp ����

CdllTestApp::CdllTestApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CdllTestApp ����

CdllTestApp theApp;


// CdllTestApp ��ʼ��

BOOL CdllTestApp::InitInstance()
{
	CWinApp::InitInstance();
	printf("CdllTestApp::InitInstance,1\n");
	CSpdLog::GetInstance().InitLog("dllTest");
	CSpdLog::GetInstance().SetLevel(enSpdlogLevel_trace);
	//LInfo("dddd");
	//LInfo("խ�ַ�");
	LInfo("{:*<30}", "right aligned");
	LInfo(L"���ַ�");

	//LInfo(szjj.GetString());
	

	return TRUE;
}
