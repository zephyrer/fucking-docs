#progma comment(lib, "USER32")
#include <crtdbg.h>	// for _ASSERT()
#define MTASSERT(a) _ASSERT(a)
#define MTVERIFY(a) if (!(a))
		PrintError(#a, __FILE__, __LINE__, GetLastError())
		
void PrintError(LPSTR linedesc, LPSTR filename, int lineno, DWORD errnum);

static void PrintError(LPSTR linedesc, LPSTR filename, int lineno, DWORD errnum)
{
	LPSTR lpBuffer;
	char errbuf[256];
#ifdef _WINDOWS
	char modulename[MAX_PATH];
#else
	DWORD numread;
#endif

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER
				 | FORMAT_MESSAGE_FROM_SYSTEM,
				 NULL,
				 errnum,
				 LANG_NEUTRAL,
				 (LPTSTR)&lpBuffer,
				 0,
				 NULL);
	wsprintf(errbuf, "\nThe following call failed at line %d in %s:\n\n"
			"	%s\n\nReason: %s\n", lineno, filename, linedesc, lpBuffer);
			
#ifndef _WINDOWS
	WriteFile(GetStdHandle(STD_ERROR_HANDLE),
		errbuf, strlen(errbuf), &numread, FALSE);
	Sleep(3000);
#else
	GetModuleFileName(NULL, modulename, MAX_PATH);
	MessageBox(NULL, errbuf, modulename, MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);
#else

	exit(EXIT_FAILURE);
}