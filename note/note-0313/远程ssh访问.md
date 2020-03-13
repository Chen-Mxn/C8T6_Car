### SSH是什么

 SSH是一种网络协议，用于计算机之间的加密登录。如果一个用户从本地计算机，使用SSH协议登录另一台远程计算机 

>  [SSH参考资料]( https://blog.csdn.net/u013452337/article/details/80847113 ) 

### Linux操作

**安装`openssh-server` **

打开`terminal` 

输入` sudo apt-get install openssh-server `

**获取IP**

输入`ifconfig` 

如果提示没有安装，则进行安装，输入`sudo apt install net-tools` (我的虚拟机上默认安装了)

 查看ssh是否运行: `ps -ef | grep ssh `





### window'操作

**安装`Putty`**

 在 `Host name (or IP address)`填上被控制的 Linux 的 IP 

 不用修改 port 的数值 

点击`Open` 第一次打开时会出现安全警告窗口，点击`yes` 

`login as` 填上ubuntu的user和password

`Enter` 完成远程访问



### 传输文件

 指定文件上传|下载的位置 `cd` 或者 `lcd`

 查看本地路径与服务器路径 `lpwd`与`pwd` 

下载 `get  -r`  路径 + 文件名或者文件夹（文件夹需要加r）

上传 `put  -r`  路径 + 文件名或者文件夹（文件夹需要加r)

 **注意：** 下载文件时，需要注意本地目录应当为putty的工作目录，不能随便更改，否则容易出现：`unable to open file`的错误。 



> xshell个人版和xftp听说比较比较好用，在实际应用中比较方便 ，以后可以尝试使用

###  查看当前linux版本

 `lsb_release -a`

