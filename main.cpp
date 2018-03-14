#include <iostream>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <chrono>

int main()
{
	time_t czas;
	std::string tekst, time;
	
	HANDLE uchwyt;
	HWND hwnd;
	std::fstream plik;
	plik.open("archive.txt",  std::ios::out);
	
	while(true)
	{
		OpenClipboard(hwnd);
		if (OpenClipboard(NULL) && IsClipboardFormatAvailable(CF_TEXT))
		{
			uchwyt = GetClipboardData(CF_TEXT);
			
			if((LPSTR)GlobalLock(uchwyt) != tekst) 
			{
				tekst = (LPSTR)GlobalLock(uchwyt);
				czas = std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now() );
				
				time= ctime(&czas);
				time.erase(time.length()-1, time.length());
				
				plik << time << ": " << tekst << "\n\n";
				plik.flush();
			}
		}
	
		
		CloseClipboard();
		if(GetAsyncKeyState(0x26)) break;
		Sleep(1500);
	}
	plik.close();
	
	return 0;
}
