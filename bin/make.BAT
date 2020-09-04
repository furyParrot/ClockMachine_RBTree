gcc ..\lib\ClockMachine\ClockMachine.c ..\lib\RBTree\RBTree.c ..\lib\UsrTime\usr_time.c -shared -o mylib.dll
gcc ..\src\main.c ..\src\StaffManager.c mylib.dll -o StaffManager.exe -g -Wall