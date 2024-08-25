@echo off
g++ Temp/%1.cpp -o Temp/%1.exe
g++ Temp/std.cpp -o Temp/std.exe
g++ Temp/gen.cpp -o Temp/gen.exe

:loop
    gen.exe > Temp/1.in
    std.exe < Temp/1.in > Temp/1.out
    %1.exe < Temp/1.in > Temp/1.ans
    fc Temp/1.out Temp/1.ans
if not errorlevel 1 goto loop
pause
goto loop