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

[example.c] ;源代码文件名称，用来生成一个目标文件
language = c ;使用C编译器（gcc编译器） *必选*
standrand = c11 ;语言标准
optimize = 2 ;O2优化
options = g ;其他选项

[example2.cpp] ;C++文件，需要链接stdc++库
language = c ;使用GCC编译器编译C++
```

目前代码只支持C语言和C++语言，期待大佬改进。

还有，近期我们会推出`require`和`start`功能，敬请期待。

2. 编译项目

```bash
cd ~/xxx/xxx # 进入项目文件夹
vim ac.ini # 编辑配置文件
auto-compile # 编译
```

3. 如何添加新语言模块

在language文件里，加入（语言）.cpp。

在auto-compile.cpp的46行，include语言文件，然后加入该语言的特殊判断即可。

后期我们会使用更简单的方式。

4. Q&A

Q: ld出现这个：`cannot find entry symbol _start; defaulting to 0000000000xxxxxx`，这什么鬼？

A: 这是`gcc`专门的反编译措施，能够隐藏`_start`入口。俗话说的好，既然是`warning`，就不要当`error`（狗头保命）

Q: 出现一大堆链接错误怎么办？

A: 一般最常见的就是“xxx未定义”和“xxx重复定义”的错误。一般来说，你应该重点检查函数声明、定义和模板函数（类）这一部分。

争取把用不到的模板换成非模板，或者用另一种方法定义函数。

当然，也有可能是你没有把相应的库链接好，这个时候，你应该添加需要的库。

Q: 工具有bug？

A: 提交Issue！你的每一个Issue都是我们的进步。

5. 特别鸣谢

AMIRIOX無暝 感谢你给了我这个项目的思想

忠诚的卫士 感谢你给我[INI文件解析的轮子](https://www.cnblogs.com/GuanghuiLiu/p/8832034.html)