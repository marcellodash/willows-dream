@echo OFF

:START_BUILD

    echo.
    echo       . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
    echo       ^| ^| ^|  ^|  ^|   ^|   ^| ^| ^| ^| ^| `' `-.   ^|  )^|(  ^|-  ^|-^| ^|\/^|
    echo       `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
    echo.
    echo.
    echo This batch script helps to build the Willow's Dream ROM file using
    echo     SGDK and execute it with DGen emulation software.
    echo.
    echo (1) SGDK will be built and should contain .\lib\sgdk\lib\libmd.a if
    echo     successfully compiled
    echo (2) Your system's PATH variable will be temporarily overwritten; this
    echo     script must fully execute to restore your PATH variable to its
    echo     original value
    echo (3) After Willow's Dream is built, the output ROM fill will be located
    echo     at .\out\rom.bin
    echo (4) You will be asked if you would like to open the ROM file in DGen
    echo     to ensure that the ROM was compiled correctly and play the game

    setlocal

:BUILD_LIB

    echo.
    echo 1) Building Dependencies
    echo ------------------------
    echo.

    echo Creating EnvVars and temporarily configuring PATH to avoid conflicts:

    set "str_MyCurrentDir=%cd%\lib\sgdk"

    set "GDK=%str_MyCurrentDir%"
    set "GDK_WIN=%str_MyCurrentDIR%"
    set "GDK=%GDK:\=/%"

    REM Removing C: not necessary in Windows command line
    REM set "GDK=%GDK:~3%"
    REM set "GDK=/%GDK%"

    if %GDK:~-1%==/ set "GDK=%GDK:~0,-1%"
    if %GDK_WIN:~-1%==\ set "GDK_WIN=%GDK_WIN:~0,-1%"

    echo GDK is %GDK%
    echo GDK_WIN is %GDK_WIN%

    REM Temporarily configuring PATH to avoid conflicts
    set "PATHREAL=%PATH%"
    set "PATH=%GDK_WIN%"
    if EXIST %GDK_WIN%\bin set "PATH=%PATH%;%GDK_WIN%\bin"
    echo PATH is %PATH%

    echo.
    echo Checking if SGDK is built...

    if exist %GDK_WIN%\lib\libmd.a (
        echo SGDK build files found.
        goto BUILD_LIB_QUERY
    ) else (
        echo SGDK build files could not be found.
        goto BUILD_LIB_START
    )

:BUILD_LIB_QUERY

    echo.
    echo Would you like to rebuild SGDK? (y/n)
    echo.

    set INPUT=
    set /P INPUT=Type input: %=%

    if /i "%INPUT%"=="y" goto BUILD_LIB_START
    if /i "%INPUT%"=="n" goto BUILD_LIB_SKIP
    echo Incorrect input
    echo.
    goto BUILD_LIB_QUERY

:BUILD_LIB_START

    echo.
    echo Building SGDK...
    echo.
    %GDK_WIN%\bin\make -f %GDK_WIN%\makelib.gen clean
    %GDK_WIN%\bin\make -f %GDK_WIN%\makelib.gen

    if %errorlevel% neq 0 (
        echo.
        echo Failed to build SGDK!
        echo Press any key to exit...
        pause >nul
        exit /b %errorlevel%
    )

    echo.
    echo SGDK build sucessful!

:BUILD_LIB_SKIP

:BUILD_ROM

    echo.
    echo 2) Building ROM
    echo ---------------
    echo.

    REM Set local variables
    set GDK=%GDK%
    set GDK_WIN=%GDK_WIN%
    set PATH=%PATH%

    set BIN=%GDK%/bin
    set LIB=%GDK%/lib

    set SRC=%GDK%/src
    set RES=%GDK%/res
    set INCLUDE=%GDK%/include

    set SHELL=%BIN%/sh
    set AR=%BIN%/ar
    set CC=%BIN%/gcc
    set LD=%BIN%/ld
    set OBJCPY=%BIN%/objcopy
    set ASMZ80=%BIN%/sjasm
    set MACCER=%BIN%/mac68k

    echo Building resources...
    %GDK_WIN%\bin\rescomp .\res\resources.res
    if %errorlevel% neq 0 (
        echo.
        echo Failed to build project resources!
        echo Press any key to exit...
        pause >nul
        exit /b %errorlevel%
    )

    echo.
    echo Building source files...
    %GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen
    if %errorlevel% neq 0 (
        echo.
        echo Failed to build project source files!
        echo Press any key to exit...
        pause >nul
        exit /b %errorlevel%
    )

    echo.
    echo Willow's Dream build successful!

:CLEANUP

    echo.
    echo 3) Cleanup
    echo ----------
    echo.

    echo Resetting PATH variable
    set "PATH=%PATHREAL%"

:EMULATION

    echo.
    echo 4) Genesis Emulation
    echo --------------------
    echo.

:EMULATION_QUERY

    echo Would you like to run Willow's Dream in Sega Genesis/Master
    echo     Drive emulation software? (y/n)
    echo.

    set INPUT=
    set /P INPUT=Type input: %=%

    if /i "%INPUT%"=="y" goto EMULATION_CONFIRM
    if /i "%INPUT%"=="n" goto END_BUILD
    echo Incorrect input
    echo.
    goto EMULATION_QUERY

:EMULATION_CONFIRM

    echo.
    echo Opening Willow's Dream in DGen emulation software...
    echo.
    .\lib\dgen\dgen .\out\rom.bin

:END_BUILD

    echo.
    echo 5) Build Complete
    echo -----------------
    echo.
    echo Willow's Dream build procedure complete.
    echo.

    endlocal
    @echo ON
    exit /b
