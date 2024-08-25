:: 在文件夹`Temp`中创建`A.cpp`-`J.cpp`文件，并将工作文件夹下的`0_Cpp_Head.cpp`的内容复制到每个文件中
@echo off
setlocal enabledelayedexpansion

rem 删除文件夹`Temp`中的所有文件和文件夹
if exist Temp (
    rmdir /s /q Temp
)
mkdir Temp

rem 复制 0_Cpp_Head.cpp 的内容到 Temp 文件夹下的 A.cpp-J.cpp 文件中
for %%i in (A B C D E F G H I J K L M N) do (
    copy 0_Cpp_Head.cpp Temp\%%i.cpp
)

echo Done.