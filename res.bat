@echo OFF

:BUILD_START

    echo.
    echo       . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
    echo       ^| ^| ^|  ^|  ^|   ^|   ^| ^| ^| ^| ^| `' `-.   ^|  )^|(  ^|-  ^|-^| ^|\/^|
    echo       `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
    echo.
    echo.
    echo This batch script helps to build resource files for the Genesis with SGDK.

    setlocal enableextensions

:BUILD_RES

    echo.
    echo Building resource file...
    echo.

    REM Set SGDK variables

    set "str_MyCurrentDir=%cd%\lib\sgdk"

    set "GDK=%str_MyCurrentDir%"
    set "GDK_WIN=%str_MyCurrentDIR%"
    set "GDK=%GDK:\=/%"

    REM Removing C: not necessary in Windows command line
    REM set "GDK=%GDK:~3%"
    REM set "GDK=/%GDK%"

    if %GDK:~-1%==/ set "GDK=%GDK:~0,-1%"
    if %GDK_WIN:~-1%==\ set "GDK_WIN=%GDK_WIN:~0,-1%"

    REM Set command line argument variables

    SET self=%~n0
    SET parent=%~dp0
    SET dir=%~dp1
    SET file=%~f1

    %GDK_WIN%\bin\rescomp %file%

    echo.
    echo Resource compiled successfully

:BUILD_END

    endlocal
    @echo ON
    exit /b
