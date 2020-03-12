### 命令目录

* [分支常用命令](#to0)

* [git checkout](#to1)

* [git branch](#to2)

* [git merge](#to3)

* [git switch](#to4)

* [git log](#to5)

* [git stash](#to6)

* [git push](#to7)

* [拉取分支](#to9)

* [多人协作](#to10)

* [git clone和git pull的区别](#to8)

----

[万能的命令查询网](https://explainshell.com/explain/1/git-checkout)

----

##### <span id="to1">git checkout</span>

Checkout a branch or paths to the working tree

检出工作树的分支或路径

在本地创建和远程分支对应的分支，使用`git checkout -b branch-name origin/branch-name`，本地和远程分支的名称最好一致

##### <span id="to2">git branch</span>

List, create, or delete branches

列出，创建或删除分支

开发一个新feature，最好新建一个分支；

如果要丢弃一个没有被合并过的分支，可以通过`git branch -D <name>`强行删除

建立本地分支和远程分支的关联，使用`git branch --set-upstream branch-name origin/branch-name`

##### <span id="to3">git merge</span>

Join two or more development histories together

将两个或多个开发历史联系在一起

加上`--no-ff`参数，表示禁用`Fast forward `，保留分支

因为这样合并后要创建一个新的commit,所以加上`-m`参数，添加`commit `描述

eg:`git merge --no-ff -m"description" <branch(分支)>`

##### <span id="to4">git switch</span>

切换分支

创建并切换到新的dev分支：

`$ git switch -c dev`

切换到已有的master分支：

`$ git switch master`

##### <span id="to5">git log</span>

Show commit logs

显示提交日志

`git log --graph --pretty=oneline --abbrev-commit`

用`git log --graph`命令可以看到分支合并图。

##### <span id="to6">git stash</span>

Stash the changes in a dirty working directory away

将更改存储在杂乱工作目录中

当手头工作没有完成时，先把工作现场`git stash`一下，然后去修复bug，修复后，再`git stash pop`，回到工作现场,同时删除`stash`的（存档）内容；

或者用`git stash apply`恢复，但是恢复后，`stash`内容并不删除，你需要用`git stash drop`来删除；

在master分支上修复的bug，想要合并到当前dev分支，可以用`git cherry-pick <commit>`命令，把bug提交的修改“复制”到当前分支，避免重复劳动。

#### <span id="to7">git push</span>

推送分支，就是把该分支上的所有本地提交推送到远程库。推送时，要指定本地分支，这样，Git就会把该分支推送到远程库对应的远程分支上：

`git push origin <branch(分支)>`

本地新建的分支如果不推送到远程，对其他人就是不可见的

从本地推送分支，使用`git push origin branch-name`，如果推送失败，先用`git pull`抓取远程的新提交

##### <span id="to9">拉取分支</span>

在另一台电脑（注意要把SSH Key添加到GitHub）或者同一台电脑的另一个目录下克隆：

`git clone git@github.com:<Github_id/list>`

`git branch `：从远程库clone时，只能看到master

` git checkout -b dev origin/dev`:创建远程`origin`的`dev`分支到本地

进行修改，再`git push origin dev`推送到远程库

从远程抓取分支，使用`git pull`，如果有冲突，要先处理冲突。

#### <span id="to10">多人协作</span>

多人协作的工作模式通常是这样：

首先，可以试图用`git push origin <branch-name>`推送自己的修改；
如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并；
如果合并有冲突，则解决冲突，并在本地提交；
没有冲突或者解决掉冲突后，再用`git push origin <branch-name>`推送就能成功！
如果`git pull`提示`no tracking information`，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream-to <branch-name> origin/<branch-name>`。


#### <span id="to8">git clone 和 git pull 的区别</span>

从远程服务器克隆一个一模一样的版本库到本地,复制的是整个版本库，叫做clone.（clone是将一个库复制到你的本地，是一个本地从无到有的过程）

从远程服务器获取到一个branch分支的更新到本地，并更新本地库，叫做pull.（pull是指同步一个在你本地有版本的库内容更新的部分到你的本地库）

git pull相当于是从远程获取最新版本并merge（合并）到本地 git pull = git fetch + git merge，git fetch更安全一些

git clone是远程操作的第一步，通常是从远程主机克隆一个版本库，eg:$ git clone ## 该命令会在本地主机生成一个目录，与远程主机的版本库同名，如果要是制定不同的目录名，可以将目录名作为git clone 命令的第二个参数。eg：$ git clone #版本库网址# #本地目录名# git clone支持多种协议，除了http（s),还有ssh,git,本地协议。

git pull 作用是，取回远程主机某个分支的更新，再与本地的指定分支合并。它的完整格式稍稍有点复杂。eg:$ git pull ##远程主机（origin） #远程分之(next)#：#本地分之(master)#

如果远程分支是与当前分支合并，则冒号后面的部分可以省略。eg:$ git pull #远程主机(origin)#　 #远程分之(next)#　相当于1. $ git fetch origin 2.$git merge origin/next 

在某些场合，git会自动在本地和远程分之之间，建立一种追踪关系。比如，在git clone 的时候，所有本地分之默认与远程主机的同名分之，建立追踪关系，也就是，本地的master分之自动“追踪”origin/master分之。git 可以手动建立追踪， git branch --set-upstream master origin/next --->指定master分之追踪到origin/next。

如果当前分支只有一个追踪分支，连远程主机名都可以省略。$ git pull 表示当前分之自动与唯一一个追踪分之进行合并。

>参考：[CSDN](https://blog.csdn.net/zhou_xiaomiao/article/details/53185712)



##### <span id ="to0">常用命令</span>

查看分支：`git branch`

创建分支：`git branch `

切换分支：`git checkout `或者`git switch `

创建+切换分支：`git checkout -b `或者`git switch -c `

合并某分支到当前分支：`git merge `

删除分支：`git branch -d `



>参考资料: [explainshell](https://explainshell.com/explain/1/git-checkout)
