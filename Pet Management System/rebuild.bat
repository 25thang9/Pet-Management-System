@echo off
chcp 65001 >nul
set "APP_NAME=Pet Management System (PMS)"
title %APP_NAME% - Build Tool v1.0
cls

echo ╔══════════════════════════════════════════════════════════╗
echo ║                                                          ║
echo ║             PET MANAGEMENT SYSTEM (PMS)                  ║
echo ║              AUTOMATED BUILD PIPELINE                    ║
echo ║                                                          ║
echo ╚══════════════════════════════════════════════════════════╝
echo.

echo [STEP 1/3] Cleaning workspace...
del /s /q "*.o" "*.gch" "tempCodeRunnerFile*" 2>nul
if exist "doan.exe" del /q "doan.exe"
echo   [+] Status: Ready for a fresh build.
echo [STATUS] Cleanup complete.
echo.

echo [STEP 2/3] Compiling source code...
echo [INFO] Scanning modules: Business, Core, Utils, Menu...

g++ -g -I. main.cpp "Business"/*.cpp "Core"/*.cpp "Utils"/*.cpp -o "doan.exe"

if %errorlevel% NEQ 0 goto ERROR

:SUCCESS
echo.
echo ════════════════════════════════════════════════════════════
echo    BUILD SUCCESSFUL!
echo    Timestamp: %date% %time%
echo ════════════════════════════════════════════════════════════
echo.
echo [OK] Launching %APP_NAME%...
echo ------------------------------------------------------------
"doan.exe"
goto END

:ERROR
echo.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo    BUILD FAILED! 
echo    Please check the compiler logs or source code.
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
pause

:END
echo.
echo [INFO] Build session ended.
pause