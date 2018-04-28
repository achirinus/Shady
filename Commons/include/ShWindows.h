#pragma once


#define FALSE 0
#define TRUE 1

#define WINAPI __stdcall
#define APIENTRY WINAPI
#define CALLBACK __stdcall
#define CONST const
#define VOID void

typedef void* HANDLE;
typedef HANDLE HBITMAP;
typedef HANDLE HBRUSH;
typedef HANDLE HDC;
typedef HANDLE HFONT;
typedef HANDLE HINSTANCE;
typedef HINSTANCE HMODULE;
typedef HANDLE HICON;
typedef HICON HCURSOR;


typedef wchar_t WCHAR;
typedef unsigned short WORD;
typedef WORD *LPWORD;
typedef unsigned int UINT;
typedef int  INT;

typedef INT HFILE;

#if defined(_WIN64)
typedef __int64 LONG_PTR;
#else
typedef long LONG_PTR;
#endif
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
typedef long LONG;
typedef long HRESULT;
typedef UINT* UINT_PTR;
typedef UINT_PTR WPARAM;
typedef int BOOL;
typedef unsigned char BYTE;
typedef BYTE BOOLEAN;
typedef char CCHAR;
typedef char CHAR;
typedef unsigned long DWORD; // 32 bit unsigned
typedef unsigned __int64 DWORDLONG;
typedef float FLOAT;

typedef __nullterminated CONST CHAR *LPCSTR;
#ifdef UNICODE
typedef LPCWSTR LPCTSTR;
#else
typedef LPCSTR LPCTSTR;
#endif

typedef CONST void *LPCVOID;
typedef CONST WCHAR *LPCWSTR;
typedef CHAR *LPSTR;

#ifdef UNICODE
typedef LPWSTR LPTSTR;
#else
typedef LPSTR LPTSTR;
#endif

typedef WCHAR *LPWSTR;

#ifdef UNICODE
typedef WCHAR TCHAR;
#else
typedef char TCHAR;
#endif

typedef unsigned char UCHAR;