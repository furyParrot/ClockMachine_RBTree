执行 bin\make.BAT
    编译出mylib.dll 并编译出StaffManager.exe

要点：
1。红黑树    lib\RBTree\RBTree.c
2。函数指针  lib\RBTree\RBTree.h    line:8   line:9
3。文件保存  lib\RBTree\RBTree.c    line:400
4。文件加载  lib\RBTree\RBTree.c    line:411

目录说明：
    lib|---   存放了建立打卡机动态库的必要源文件。
       |---CLockMachine:定义了红黑树的节点结构体，以及对红黑树的基本封装，使之适应需要
       |                以及两个函数指针，
       |
       |---RBTree     :红黑树节点的增删改查操作。
       |
       |---UsrTime   ：一些好用的时间函数。
    src|---主程序所在的位置
