Linux 查找文件相关命令 

https://blog.csdn.net/m0_37568814/article/details/82753281

```linux
find / -name DirName
```

添加环境变量

https://www.cnblogs.com/yaoqingzhuan/p/10889718.html

**当前用户永久添加环境变量：**

编辑.bashrc文件 vim ~/.bashrc  **<<---- 通过这种方式，在关闭xshell后，添加的环境变量仍然生效**

文件末尾添加：export PATH="/usr/local/nginx/sbin/:$PATH"

source ~/.bashrc

 

为Linux服务器安装GUI(在阿里云轻量应用服务器上无效)

https://phoenixnap.com/kb/how-to-install-a-gui-on-ubuntu



为Linux服务器（Ubuntu20.04）安装GUI（VNC）

https://help.aliyun.com/document_detail/59330.html?spm=5176.10695662.1996646101.searchclickresult.3a642366PdbbzL

root@iZt4n2r37at459efgntordZ:~# vncserver

You will require a password to access your desktops.

Password:
Verify:

New 'iZt4n2r37at459efgntordZ:1 (root)' desktop is iZt4n2r37at459efgntordZ:1

Creating default startup script /root/.vnc/xstartup
Starting applications specified in /root/.vnc/xstartup
Log file is /root/.vnc/iZt4n2r37at459efgntordZ:1.log

```text
git remote add origin ssh://git@remote-server/repo-<wbr< a="">>path-on-server..git
```
