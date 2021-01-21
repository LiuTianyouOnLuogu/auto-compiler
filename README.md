# Auto-Compile By Liu Tianyou

1. 配置项目

通过修改项目下的ac.ini文件进行项目的配置，这样才能让自动编译器知道你的项目是什么样子的。

指定ac.ini文件： --config ac.ini

语法：
```ini
[main] ;这里定义了如何链接这个项目
name = example ;项目名称（将输出为以该名称为名称的可执行文件）
library = mysqlclient&c&m&stdc++ ;将链接libmysqlclient.so库, libc.so库,libm.so库（C++数学库）
;stdc++库可以使用GCC编译C++代码（后文会介绍）
options = -warn-once ;指定运行ld时的其他命令行

[example.c] ;源代码文件名称，用来生成一个目标文件
language = c ;使用C编译器（gcc编译器） *必选*
standrand = c11 ;语言标准
optimize = 2 ;O2优化
define = DEBUG&ONLINE_JUDGE ;定义宏
options = -g ;其他选项

[example2.cpp] ;C++文件，需要链接stdc++库
language = c ;使用GCC编译器编译C++
```

目前代码只支持C语言和C++语言，期待大佬改进。

2. 编译项目

```bash
cd ~/xxx/xxx # 进入项目文件夹
vim ac.ini # 编辑配置文件
auto-compile # 编译
```

3.特别鸣谢

AMIRIOX無暝 感谢你给了我这个项目的思想

忠诚的卫士 感谢你给我[INI文件解析的轮子](https://www.cnblogs.com/GuanghuiLiu/p/8832034.html)