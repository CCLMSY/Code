:: 在文件夹`Temp`中创建`A.cpp`-`J.cpp`文件，并将工作文件夹下的`0_Cpp_Head.cpp`的内容复制到每个文件中
@echo off
setlocal enabledelayedexpansion

rem 删除文件夹`.cph`
if exist Temp\.cph rmdir /s /q Temp\.cph
if exist .cph rmdir /s /q .cph

rem 复制 0_Cpp_Head.cpp 的内容到 1.cpp - 9.cpp
for %%i in (A B C D E F G H I J) do (
    copy 0_Cpp_Head.cpp Temp\%%i.cpp
)

echo Done.