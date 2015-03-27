#pragma once

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.


#ifndef _WIN32_WINNT            
#define _WIN32_WINNT 0x0500     // Specifies that the minimum required platform is Windows 2000
#endif

// http://msdn.microsoft.com/en-us/library/aa383745%28VS.85%29.aspx
/*
Windows 7											0x0601
Windows Server 2008									0x0600
Windows Vista										0x0600
Windows Server 2003 with SP1, Windows XP with SP2	0x0502
Windows Server 2003, Windows XP						0x0501
Windows 2000										0x0500
*/