# Context

Context分为ActivityContext和ApplicationContext两种。ActivityContext通过getContext()方法获得当前正在活动的Activity上下文；ApplicationContext通过getApplicationContext()方法获得，是全局的、共享的。

Application Context用于：

- 加载资源
- 开启\绑定\关闭\解绑服务
- 发送广播\注册广播接收器

Activity Context用于：

- 加载资源
- 视图膨胀(layout inflation)
- 启动Activity
- 展示对话框\弹出Toast
- 开启\绑定\关闭\解绑服务
- 发送广播\注册广播接收器

一边能使用Application Context的场景尽量使用Application Context，只能使用Activity Context的场景一般是与UI相关的。

getBaseContext()是 ContextWrapper中的方法，返回由构造函数指定或setBaseContext()设置的上下文。



# PackageManager

功能

- 安装，卸载应用 
- 查询permission相关信息 
- 查询Application相关信息(application，activity，receiver，service，provider及相应属性等） 
- 查询已安装应用 
- 增加，删除permission 
- 清除用户数据、缓存，代码段等 