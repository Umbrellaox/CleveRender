#pragma once
#pragma comment(lib, "winmm.lib")

#ifndef CONSOLE_GAME_ENGINE_H
#define CONSOLE_GAME_ENGINE_H


#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

#include "sprite.h"


class ConsoleGameEngine
{
public:
	ConsoleGameEngine();

	int ConstructConsole(int width, int height, int fontw, int fonth);

	virtual void Draw(int x, int y, short c = 0x2588, short col = 0x000F);

	void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);

	void Clip(int& x, int& y);

	void DrawLine(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);

	~ConsoleGameEngine();

public:
	void Start();

	int ScreenWidth()
	{
		return m_nScreenWidth;
	}

	int ScreenHeight()
	{
		return m_nScreenHeight;
	}

private:
	void GameThread();
	
public:
	virtual bool OnUserCreate() = 0;
	virtual bool OnUserUpdate(float fElapsedTime) = 0;

	virtual bool OnUserDestroy() { return true; }



/*Key Setting*/
protected:
	struct sKeyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	} m_keys[256];

public:
	sKeyState GetKey(int nKeyID) { return m_keys[nKeyID]; }
	bool IsFocused() { return m_bConsoleInFocus; }

protected:
	int Error(const wchar_t* msg);
	static BOOL CloseHandler(DWORD evt);

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO* m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;
	short m_keyOldState[256] = { 0 };
	short m_keyNewState[256] = { 0 };
	bool m_bConsoleInFocus = true;


	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};


#endif // !CONSOLE_GAME_ENGINE_H
