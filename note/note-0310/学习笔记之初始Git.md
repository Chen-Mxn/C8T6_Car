## 一. Git之git使用

* Git Bash: Git配套的一个控制台

* Git CMD(Deprecated): 通过CMD使用Git

* Git GUI: Git的可视化操作工具

[1.创建一个空目录](#jump1)

[2.把目录变成Git可管理的仓库](#jump2)

[3.添加文件到仓库](#jump3)

[4.文件修改记录](#jump4)

[5.版本回退](#jump5)

[6.显示记录命令](#jump6)

[7. 工作区，暂存区，仓库区](#jump7)

[8.查看工作区和版本库里面最新版本的区别](#jump8)

[9.撤销工作区修改](#jump9)

[10.删除操作](#jump10)

[遇到的问题](#flag)


### Git原理

仓库： ***本地仓库***和***远程仓库***（托管在网络端的仓库）

本地仓库： ***工作区，版本区***，其中版本区包含***暂存区，仓库区***

从本地仓库将文件git到远程仓库的流程：***工作区>>暂存区>>仓库区>>远程仓库***

----

##### <span id="jump1">1.创建一个空目录</span>

```

$ mkdir learngit

$ cd learngit

$ pwd

```

pwd命令用于显示当前目录

注：确保目录名（路径）不包含中文

##### <span id="jump2">2.通过git init命令把这个目录变成Git可以管理的仓库：</span>

```

$ git init

```

如果没有看到`.git`目录，则是默认隐藏了。发送命令`ls -ah`可以察看

##### <span id="jump3">3.添加文件到仓库</span>

注：一定要放到learngit目录下（子目录也行）

(1)  命令`git add`,把文件添加到仓库：

```

$ git add readme.txt

```

其中“readme.txt”为添加的文件

(2) 命令`git commit`,把文件提交到仓库：

`git commit`命令，`-m`后面输入的是本次**提交的说明(标签)**，可以输入任意内容，当然最好是有意义的，这样你就能从历史记录里方便地找到改动记录。

```

$ git commit -m "wrote a readme file"

[master (root-commit) eaadf4e] wrote a readme file

1 file changed, 2 insertions(+)

create mode 100644 readme.txt

```

`commit`可以一次提交很多文件，所以可以多次`add`不同的文件，比如：

```

$ git add file1.txt

$ git add file2.txt file3.txt

$ git commit -m "add 3 files."

```

##### <span id="jump4">4.文件修改历史记录</span>

输入命令：`git log` 和 `git log --pretty=oneline`

版本号：`commit id`

##### <span id="jump5">5.回退到上一个版本</span>

输入命令：`git reset`

```

$ git reset --hard HEAD^

$ git reset --hard 1094a

```

`HEAD`表示当前版本

`HEAD^`表示上一个版本

`HEAD^^`表示上上个版本

`HEAD~100`表示网上100个版本

查看文件内容：`cat xxxx.xxx`

##### <span id="jump6">6.显示记录命令</span>

`git reflog`

##### <span id="jump7">7. 工作区，暂存区，仓库区</span>

工作区：本地文件夹，**操作文件**

通过`git status`查看与暂存区的差异

暂存区：暂存工作区提交过来的操作，**记录更改**


##### <span id="jump8">8.查看工作区和版本库里面最新版本的区别</span>

命令：`git diff HEAD -- xxxx.xxx(file)`

##### <span id="jump9">9.撤销工作区修改</span>

命令：`git checkout -- xxxx.xxx(file)`

或`git restore xxxx.xxx(file)`

注：两个命令作用一样，这里的`--`不能漏

作用：把文件在工作区的修改全部撤销

(1) 修改后还没有被放到暂存区——撤销修改就回到和版本库一模一样的状态；

(2) 已经添加到暂存区后，又作了修改——撤销修改就回到添加到暂存区后的状态。

命令：`git reset HEAD `或`git restore --staged `

作用：把暂存区的修改撤销掉（unstage），重新放回工作区：

`git reset`命令既可以回退版本，也可以把暂存区的修改回退到工作区。当我们用`HEAD`时，表示最新的版本。

**注：若已经`git commit -m""`提交到版本库，则用上面第4、5点修改为之前的版本！**

##### <span id="jump10">10.删除操作</span>

`rm ` ：删除工作区某个文件，也可以打开目录手动删除

`git rm `+`git commit -m"flag"`: 从版本库中删除文件

`git checkout -- `: 用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”

注：从来没有被添加到版本库就被删除的文件，是无法恢复的。

###总结

* 初始化一个Git仓库，使用`git init`命令。

* 添加文件到Git仓库，分两步：

a. 使用命令`git add` ，注意，可反复多次使用，添加多个文件；

b. 使用命令`git commit -m `，完成。

* `HEAD`指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令`git reset --hard commit_id`。

穿梭前，用`git log`可以查看提交历史，以便确定要回退到哪个版本。

要重返未来，用`git reflog`查看命令历史，以便确定要回到未来的哪个版本。

* 命令`git rm`用于删除一个文件。如果一个文件已经被提交到版本库，永远不用担心误删，但是只能恢复文件到最新版本，你会丢失最近一次提交后你修改的内容。

## <span id="flag">二. 遇到的问题</span>

##### 1.please tell me who you are

在git创建项目时出现，

是因为在创建git文件夹的时候信息不完善导致的

**解决方法：**

```

git config --global user.email “邮箱”

git config --global user.name “名字”

```

>附：Git查看并修改name和email

显示name的方法：

```

git config user.name

git config --list

```

或者查看`~/.gitconfig`文件。

改名字：

```

git config --global user.name "Furzoom"

# or

vi ~/.gitconfig

```

如果不加`--global`就是修改当前仓库的下的配置。

```

git config user.name "Furzoom"

```

或者直接修改当前仓库的`.git/config`文件。

修改email，与上面是同样的操作，只不过需要将name换行email即可。

##### 2. LF will be replaced by CRLF

**原因**：因为Git的换行符检查功能。LF是linux下的换行符，而CRLF是enter + 换行。

Git提供了一个换行符检查功能（core.safecrlf），可以在提交时检查文件是否混用了不同风格的换行符。这个功能的选项如下：

+ false - 不做任何检查

+ warn - 在提交时检查并警告

+ true - 在提交时检查，如果发现混用则拒绝提交

windows下可以设置false取消此功能，把回车符记录在库中：

```

$ git config --global core.autocrlf false

```

Git可以在提交时自动地把行结束符CRLF转换成LF，而在签出代码时把LF转换成CRLF。用core.autocrlf来打开此项功能，如果是在Windows系统上，把它设置成true，这样当签出代码时，LF会被转换成CRLF：

```

$ git config --global core.autocrlf true

```

Linux或Mac系统使用LF作为行结束符，因此不想 Git 在签出文件时进行自动的转换；当一个以CRLF为行结束符的文件不小心被引入时你肯定想进行修正，把core.autocrlf设置成input来告诉 Git 在提交时把CRLF转换成LF，签出时不转换：

```

$ git config --global core.autocrlf input

```

这样会在Windows系统上的签出文件中保留CRLF，会在Mac和Linux系统上，包括仓库中保留LF。



##### 3.重新进入仓库

(1) 启动master

(2) `cd~`回到用户主目录

(3) `pwd`查看当前目录

(4) `cd learngit/`进入git库

如果需要工作的仓库在当前目录下就直接执行 git xxx目录名称 命令进入库，如果不在当前目录再进行回退命令进入文件目录即可。



>参考来源：

[Git学习网站](https://www.liaoxuefeng.com/wiki/896043488029600/896827951938304)

[CSDN](https://blog.csdn.net/furzoom/article/details/50504425)

[CSDN](https://blog.csdn.net/GSH_Hello_World/article/details/53351869?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522158375493819195239804372%2522%252C%2522scm%2522%253A%252220140713.130056874..%2522%257D&request_id=158375493819195239804372&biz_id=0&utm_source=distribute.pc_search_result.none-task)

[CSDN](https://blog.csdn.net/weixin_38149909/article/details/88841967?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522158376890019725247612523%2522%252C%2522scm%2522%253A%252220140713.130056874..%2522%257D&request_id=158376890019725247612523&biz_id=0&utm_source=distribute.pc_search_result.none-task)
