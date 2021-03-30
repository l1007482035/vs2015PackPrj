// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Test.h"
#include "../Public/CmmLibPort.h"

#include "../dllTest/Hello.h"
#pragma comment(lib,"../Release/dllTest.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

bool isGBK(unsigned char* data, int len) {
	int i = 0;
	while (i < len) {
		if (data[i] <= 0x7f) {
			//����С�ڵ���127,ֻ��һ���ֽڵı��룬����ASCII
			i++;
			continue;
		}
		else {
			//����127��ʹ��˫�ֽڱ���
			if (data[i] >= 0x81 &&
				data[i] <= 0xfe &&
				data[i + 1] >= 0x40 &&
				data[i + 1] <= 0xfe &&
				data[i + 1] != 0xf7) {
				i += 2;
				continue;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

int preNUm(unsigned char byte) {
	unsigned char mask = 0x80;
	int num = 0;
	for (int i = 0; i < 8; i++) {
		if ((byte & mask) == mask) {
			mask = mask >> 1;
			num++;
		}
		else {
			break;
		}
	}
	return num;
}

bool isUtf8(unsigned char* data, int len) {
	int num = 0;
	int i = 0;
	while (i < len) {
		if ((data[i] & 0x80) == 0x00) {
			// 0XXX_XXXX
			i++;
			continue;
		}
		else if ((num = preNUm(data[i])) > 2) {
			i++;
			for (int j = 0; j < num - 1; j++) {
				//�жϺ���num - 1 ���ֽ��ǲ��Ƕ���10��
				if ((data[i] & 0xc0) != 0x80) {
					return false;
				}
				i++;
			}
		}
		else {
			//�������˵������utf-8
			return false;
		}
	}
	return true;
}


int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���Ĵ�������Է���������Ҫ
            wprintf(L"����: MFC ��ʼ��ʧ��\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			CSpdLog::GetInstance().InitLog("Test");
			CSpdLog::GetInstance().SetLevel(enSpdlogLevel_trace);
			int i = 10;
			double d_number = 10.01;
			LInfo("������խ�ַ�");
			LInfo(_T("�����̿��ַ�"));
			CHello  hello;

// 			CStringA szAA = "���";
// 			bool bRet = isUtf8((unsigned char*)szAA.GetString(),szAA.GetLength());
// 			bool bRet2 = isGBK((unsigned char*)szAA.GetString(), szAA.GetLength());
// 			printf("szAA,bRet=%d,bRet2=%d\n",bRet, bRet2);
// 			CStringA szBB = "hehe";
// 			bRet = isUtf8((unsigned char*)szBB.GetString(), szBB.GetLength());
// 			bRet2 = isGBK((unsigned char*)szBB.GetString(), szBB.GetLength());
// 			printf("szBB,bRet=%d,bRet2=%d\n", bRet, bRet2);
// 
// 			CStringW szCC = L"���";
// 			bRet = isUtf8((unsigned char*)szCC.GetString(), szCC.GetLength()*2);
// 			bRet2 = isGBK((unsigned char*)szCC.GetString(), szCC.GetLength()*2);
// 			printf("szCC,bRet=%d,bRet2=%d\n", bRet, bRet2);


        }
    }
    else
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
		

	
		
        nRetCode = 1;
    }
	//system("pause");
	

    return nRetCode;
}
