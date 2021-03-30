// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test.h"
#include "../Public/CmmLibPort.h"

#include "../dllTest/Hello.h"
#pragma comment(lib,"../Release/dllTest.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

bool isGBK(unsigned char* data, int len) {
	int i = 0;
	while (i < len) {
		if (data[i] <= 0x7f) {
			//编码小于等于127,只有一个字节的编码，兼容ASCII
			i++;
			continue;
		}
		else {
			//大于127的使用双字节编码
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
				//判断后面num - 1 个字节是不是都是10开
				if ((data[i] & 0xc0) != 0x80) {
					return false;
				}
				i++;
			}
		}
		else {
			//其他情况说明不是utf-8
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
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。
			CSpdLog::GetInstance().InitLog("Test");
			CSpdLog::GetInstance().SetLevel(enSpdlogLevel_trace);
			int i = 10;
			double d_number = 10.01;
			LInfo("主进程窄字符");
			LInfo(_T("主进程宽字符"));
			CHello  hello;

// 			CStringA szAA = "你好";
// 			bool bRet = isUtf8((unsigned char*)szAA.GetString(),szAA.GetLength());
// 			bool bRet2 = isGBK((unsigned char*)szAA.GetString(), szAA.GetLength());
// 			printf("szAA,bRet=%d,bRet2=%d\n",bRet, bRet2);
// 			CStringA szBB = "hehe";
// 			bRet = isUtf8((unsigned char*)szBB.GetString(), szBB.GetLength());
// 			bRet2 = isGBK((unsigned char*)szBB.GetString(), szBB.GetLength());
// 			printf("szBB,bRet=%d,bRet2=%d\n", bRet, bRet2);
// 
// 			CStringW szCC = L"你好";
// 			bRet = isUtf8((unsigned char*)szCC.GetString(), szCC.GetLength()*2);
// 			bRet2 = isGBK((unsigned char*)szCC.GetString(), szCC.GetLength()*2);
// 			printf("szCC,bRet=%d,bRet2=%d\n", bRet, bRet2);


        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
		

	
		
        nRetCode = 1;
    }
	//system("pause");
	

    return nRetCode;
}
