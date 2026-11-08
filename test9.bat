@echo off
setlocal

rem Homework 9 - 문제별 채점 (3개 테스트 케이스 기준)

g++ main.cpp problem1.cpp problem2.cpp problem3.cpp ^
    -o hw9_main.exe -std=c++17

if errorlevel 1 (
    echo Compile Error
    exit /b 1
)

rem 3개 테스트 케이스 실행
for %%j in (1 2 3) do (
    .\hw9_main.exe Test\case%%j.txt > Test\output%%j.txt 2>nul

    if errorlevel 1 (
        echo Runtime Error ^(case%%j^)
        del /q hw9_main.exe 2>nul
        exit /b 1
    )
)

del /q hw9_main.exe 2>nul

rem 각 문제별 검사
for %%i in (1 2 3) do (
    call :check %%i

    if errorlevel 1 (
        echo Problem %%i: FAIL
    ) else (
        echo Problem %%i: PASS
    )
)

exit /b


rem =============================================
rem 문제 i가 3개 테스트 케이스를 모두 통과하는지 확인
rem =============================================
:check

powershell -NoProfile -ExecutionPolicy Bypass -Command "$i=%1; function Extract($file,$num) { $lines=Get-Content $file; $result=@(); $found=$false; $next=$num+1; foreach($line in $lines) { if($line -match ('^=== Problem '+$num+':')) { $found=$true }; if($found -and $num -lt 3 -and $line -match ('^=== Problem '+$next+':')) { break }; if($found) { $result += $line } }; return [string]::Join([char]10,$result) }; foreach($j in 1,2,3) { $actual=Extract ('Test\output'+$j+'.txt') $i; $expected=Extract ('Test\expected'+$j+'.txt') $i; if($actual -ne $expected) { exit 1 } }; exit 0"

exit /b %errorlevel%
