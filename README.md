# FLTK_2048
a 2048 game based on FLTK library and vs2017
2048_,Debug,lib,include文件夹和2048_.sln合在一起为整个vs解决项目文件夹，直接打开后通过vs2017打开2048_.sln即可

启动程序通过打开路径2048_/Debug/2048_.exe即可，运行的效果和vs中运行2048_.cpp相同。

2048_/lib和2048_/include已在vs中设置好了路径，2048程序使用的FL文件夹放在2048_/include路径下，lib文件夹也自带有，但是引用路径中也设置了本身电脑中vs的路径

如果打开v2048_.sln后想要更改源码，直接更改后在Debug x86模式下运行主程序2048_.cpp即可，不要重新生成项目

移动为方向键上下左右

各按键鼠标点击和按键文字括号内说明的键盘按键是一样的效果

Reset为重新开始
Clear Max Score为将最高分清零
Regret为悔棋（最多十次，分数也会变化)
Quit为退出
Make current score to be Max score为将目前分数直接设置为最高分
Save game为存盘（包括分数）
Reload game为载入之前存的游戏（包括分数）

最高分存储在2048_/2048_/data.txt中
存储的游戏在2048_/2048_/game_save.txt中

根据大作业要求：
菜单功能有、多于5个、并且有相应快捷键、有状态信息反应当前得分和最高分（考虑一般习惯放在了上面）
各功能见报告，有使用模板类（STL库）
