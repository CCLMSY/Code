:: 在文件夹`Temp`中创建`1.cpp`-`9.cpp`文件，并将工作文件夹下的`0_Cpp_Head.cpp`的内容复制到每个文件中
@echo off
setlocal enabledelayedexpansion

rem 复制 0_Cpp_Head.cpp 的内容到 1.cpp - 9.cpp
for /l %%i in (1, 1, 9) do (
    copy 0_Cpp_Head.cpp Temp\%%i.cpp
)

echo Done.