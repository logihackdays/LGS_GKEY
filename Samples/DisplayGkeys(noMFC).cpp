// DisplayGkeys.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "LogitechGkeyLib.lib")

#include <stdlib.h>
#include "LogitechGkeyLib.h"
#include <iostream>
#include "windows.h"
#include <ctime>
#include <string>
#include <vector>
using namespace std;

//Comment this to enable the polling method and disable the callback
#define USE_CALLBACK

BOOL saveKeyPress(WPARAM wParam, LPARAM lParam);
void showGKey();

void __cdecl GkeySDKCallback(GkeyCode gkeyCode, wchar_t* gkeyOrButtonString, void* /*context*/) 
{ 	
	saveKeyPress(  (WPARAM)&gkeyCode, (LPARAM)gkeyOrButtonString);
}

vector<wstring> m_vectorGkeys;

int main()
{
	logiGkeyCBContext gkeyContext;
	ZeroMemory(&gkeyContext, sizeof(gkeyContext)); 
	gkeyContext.gkeyCallBack = (logiGkeyCB)GkeySDKCallback;
	gkeyContext.gkeyContext = NULL;

	// If polling instead of callback use NULL as argument 
	#ifdef USE_CALLBACK
		LogiGkeyInit(&gkeyContext);
	#else
		LogiGkeyInit(NULL);
	#endif // USE_CALLBACK	
	//ios_base::sync_with_stdio(false);
	cout << "LogiGkeyInit success"	<< "\n";
	 //If not using callback, check all G-keys to see if they are being pressed 
	while(1)
	{
		for (int index = 6; index <= LOGITECH_MAX_MOUSE_BUTTONS; index++)
		{
			if (LogiGkeyIsMouseButtonPressed(index))
			{
				m_vectorGkeys.push_back( LogiGkeyGetMouseButtonString(index) );
			}
		}

		for (int index = 1; index <= LOGITECH_MAX_GKEYS; index++)
		{
			for (int mKeyIndex = 1; mKeyIndex <= LOGITECH_MAX_M_STATES; mKeyIndex++)
			{
				if (LogiGkeyIsKeyboardGkeyPressed(index, mKeyIndex))
				{
					m_vectorGkeys.push_back( LogiGkeyGetKeyboardGkeyString(index, mKeyIndex) );
				}
			}
		}
		Sleep(30);
		showGKey();
	}
		
	LogiGkeyShutdown();
	return 0;
}

void showGKey()
{
	for(int i=0 ;i< m_vectorGkeys.size(); i++ )
	{	
		wcout << m_vectorGkeys[i] << "\n";
	}
	m_vectorGkeys.clear();
}

BOOL saveKeyPress(WPARAM wParam, LPARAM lParam)
{
    // TODO: Add your specialized code here and/or call the base class
    GkeyCode* gkeyCode = (GkeyCode*)wParam;
    //wchar_t* text = (wchar_t*)lParam; // Can use text from callback, or use SDK function
    wchar_t* text = NULL;
	
    if (gkeyCode->mouse)
    {
        text = LogiGkeyGetMouseButtonString(gkeyCode->keyIdx);
		lstrcatW(text, (1 == gkeyCode->keyDown) ? L" down" : L" up");
		m_vectorGkeys.push_back( text );
    }
    else
    {	
        text = LogiGkeyGetKeyboardGkeyString(gkeyCode->keyIdx, gkeyCode->mState);
		lstrcatW(text, (1 == gkeyCode->keyDown) ? L" down" : L" up");
		m_vectorGkeys.push_back( text );
    }
    
	
   return true;
}