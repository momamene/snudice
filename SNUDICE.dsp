# Microsoft Developer Studio Project File - Name="SNUDICE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SNUDICE - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SNUDICE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SNUDICE.mak" CFG="SNUDICE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SNUDICE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SNUDICE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SNUDICE - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SNUDICE - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SNUDICE___Win32_Debug"
# PROP BASE Intermediate_Dir "SNUDICE___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "SNUDICE___Win32_Debug"
# PROP Intermediate_Dir "SNUDICE___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SNUDICE - Win32 Release"
# Name "SNUDICE - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Core.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CSelectCore.cpp
# End Source File
# Begin Source File

SOURCE=.\GameCore.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\PSelectCore.cpp
# End Source File
# Begin Source File

SOURCE=.\SubmitCore.cpp
# End Source File
# Begin Source File

SOURCE=.\TitleCore.cpp
# End Source File
# End Group
# Begin Group "Graphic.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\ImgButton.cpp
# End Source File
# End Group
# Begin Group "Char.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Char.cpp
# End Source File
# Begin Source File

SOURCE=.\CharContainer.cpp
# End Source File
# End Group
# Begin Group "Item.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemContainer.cpp
# End Source File
# End Group
# Begin Group "Util.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mouse.cpp
# End Source File
# Begin Source File

SOURCE=.\PopUp.cpp
# End Source File
# Begin Source File

SOURCE=.\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\Util.cpp
# End Source File
# End Group
# Begin Group "Map.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\TileContainer.cpp
# End Source File
# End Group
# Begin Group "Player.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Grade.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerContainer.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\MainWin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Core.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Core.h
# End Source File
# Begin Source File

SOURCE=.\coreconst.h
# End Source File
# Begin Source File

SOURCE=.\CSelectCore.h
# End Source File
# Begin Source File

SOURCE=.\GameCore.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\PSelectCore.h
# End Source File
# Begin Source File

SOURCE=.\SubmitCore.h
# End Source File
# Begin Source File

SOURCE=.\TitleCore.h
# End Source File
# End Group
# Begin Group "Graphic.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\graphicconst.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\ImgButton.h
# End Source File
# End Group
# Begin Group "Char.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Char.h
# End Source File
# Begin Source File

SOURCE=.\charconst.h
# End Source File
# Begin Source File

SOURCE=.\CharContainer.h
# End Source File
# End Group
# Begin Group "Item.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\itemconst.h
# End Source File
# Begin Source File

SOURCE=.\ItemContainer.h
# End Source File
# End Group
# Begin Group "Util.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\PopUp.h
# End Source File
# Begin Source File

SOURCE=.\Timer.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# Begin Source File

SOURCE=.\utilconst.h
# End Source File
# End Group
# Begin Group "Map.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mapconst.h
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\TileContainer.h
# End Source File
# End Group
# Begin Group "Player.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Grade.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\playerconst.h
# End Source File
# Begin Source File

SOURCE=.\PlayerContainer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\const.h
# End Source File
# Begin Source File

SOURCE=.\MainWin.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\read.txt
# End Source File
# End Target
# End Project
