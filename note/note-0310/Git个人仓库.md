#### 个人仓库
[Github_STM32仓库](https://github.com/Chen-Mxn/STM32/tree/master/C8T6_Car)

#### 添加远程库

命令:`git remote add origin git@github.com:Chen-Mxn/learngit.git`

添加后，远程库的名字就是`origin`，git默认叫法。

#### 推送内容

命令：`git push -u origin master`

#### 完成后

从现在起，只要本地作了提交，就可以通过命令：

`git push origin master`

把本地master分支的最新修改推送至GitHub，现在就拥有了真正的分布式版本库

#### 查看远程库

命令：`git remote`

详细信息：`git remote -v`

```

$ git remote -v

origin git@github.com:michaelliao/learngit.git (fetch) 

origin git@github.com:michaelliao/learngit.git (push)

```

上面显示了可以抓取和推送的`origin`的地址。如果没有推送权限，就看不到`push`的地址。

#### SSH警告

第一次使用Git的clone或者push命令连接GitHub时，会得到警告：

```

The authenticity of host 'github.com (xx.xx.xx.xx)' can't be established.

RSA key fingerprint is xx.xx.xx.xx.xx.

Are you sure you want to continue connecting (yes/no)?

```

因为Git使用SSH连接，而SSH连接在第一次验证GitHub服务器的Key时，需要确认GitHub的Key的指纹信息是否真的来自GitHub的服务器，输入`yes`回车即可。

Git会输出一个警告，告诉你已经把GitHub的Key添加到本机的一个信任列表里了：

`Warning: Permanently added 'github.com' (RSA) to the list of known hosts.`

这个警告只会出现一次，后面的操作就不会有任何警告了。

如果你实在担心有人冒充GitHub服务器，输入`yes`前可以对照`GitHub的RSA Key的指纹信息`是否与SSH连接给出的一致。



#### 克隆远程库到本地

`git clone git@github.com:Chen-Mxn(user)/newgitskills(repository)`





#### 小结

要关联一个远程库，使用命令`git remote add origin git@server-name:path/repo-name.git`；

关联后，使用命令`git push -u origin master`第一次推送master分支的所有内容；

此后，每次本地提交后，只要有必要，就可以使用命令`git push origin master`推送最新修改；

分布式版本系统在本地工作完全不需要考虑远程库的存在，有没有联网都可以正常工作，当有网络的时候，再把本地提交推送一下就完成同步

### 遇到的问题

##### 1.

发送命令`git push -u origin master`后出现：

The authenticity of host 'github.com (52.74.223.119)' can't be established.

RSA key fingerprint is `SHA256`:nThbg6kXUpJWGl7E1IGOCspRomTxdCARLviKw6E5SY8.

Are you sure you want to continue connecting (yes/no/[fingerprint])?

解决方法：发送`yes`

##### 2.

发送`yes`后出现警告：

Warning: Permanently added 'github.com,52.74.223.119' (RSA) to the list of known hosts.

git@github.com: Permission denied (publickey).

fatal: Could not read from remote repository.Please make sure you have the correct access rights and the repository exists.

无法读取远程仓库。请确认您有正确的访问权限并且仓库存在。

解决：（1）发送`$ ssh-keygen -t rsa -C "email@example.com"`然后一路回车，设置密码为空

（2）登陆GitHub，打开“settings”，“SSH Keys”页面：

然后，点“New SSH Key”，填上Title，在Key文本框里粘贴id_rsa.pub文件的内容。

添加密匙完成。

#### 参考资料：

[CSDN:问题2](https://blog.csdn.net/qq_36770641/article/details/88638573?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)

[CSDN:问题2](https://blog.csdn.net/weixin_30849591/article/details/99397962?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)

[Git学习网站](https://www.liaoxuefeng.com/wiki/896043488029600/898732864121440)