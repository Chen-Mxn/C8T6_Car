### 待解决问题

在ubuntu中实现中文输入。

目前存在的问题是：安装sogou拼音后，输入候选项为空

sogou 五笔的候选项为乱码

### GCC编译器

 `GNU C Compiler`是GNU推出的功能强大，性能优越的多平台编译器。 

 ubuntu下查看gcc的版本：在终端上输入`gcc -v` 或者 `gcc --version` 就会显示版本信息和它配置的编译脚本参数

**编译时分四个阶段**

1. 预处理：

   `gcc -E test.c -o test.i`

2. 编译：生成`.o`文件

    `gcc -S test.i -o test.s`

3. 汇编

   ` gcc -c test.s -o test.o`

4. 链接：生成可执行文件  

    `gcc test.o -o test` 

> [参考网址]( [https://blog.csdn.net/smallerxuan/article/details/81736693?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522158403207919725222441780%2522%252C%2522scm%2522%253A%252220140713.130056874..%2522%257D&request_id=158403207919725222441780&biz_id=0&utm_source=distribute.pc_search_result.none-task](https://blog.csdn.net/smallerxuan/article/details/81736693?ops_request_misc=%7B%22request%5Fid%22%3A%22158403207919725222441780%22%2C%22scm%22%3A%2220140713.130056874..%22%7D&request_id=158403207919725222441780&biz_id=0&utm_source=distribute.pc_search_result.none-task) )

### 安装VIM

`sudo apt-get install vim-gtk`

