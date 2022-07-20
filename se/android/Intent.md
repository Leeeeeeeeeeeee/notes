Intent是一种运行时绑定（runtime binding)机制，它能在程序运行的过程中连接两个不同的组件。通过Intent，程序可以向Android表达某种请求或者意愿，Android会根据意愿的内容选择适当的组件来响应。

**组成：**

- component(组件)：目的组件
- action（动作）：用来表现意图的行动
- category（类别）：用来表现动作的类别，或范畴
- data（数据）：表示与动作要操纵的数据
- type（数据类型）：对于data范例的描写
- extras（扩展信息）：扩展信息
- Flags（标志位）：期望这个意图的运行模式

Android官方定义Intent 是用于通过描述某个"意图"对象中执行的简单操作（如“查看地图”或“拍摄照片”）来启动另一应用中的某个 Activity。 这种 Intent 称作"隐式"Intent，因为它并不指定要启动的应用组件，而是指定一项"操作"并提供执行该操作所需的一些数据。

当调用 startActivity() 或 startActivityForResult()并向其传递隐式 Intent 时，系统会将Intent解析为可处理该 Intent 的应用并启动其对应的 Activity。 如果有多个应用可处理 Intent，系统会为用户显示一个对话框，供其选择要使用的应用。

注意：如果设备上没有可接收隐式 Intent 的应用，应用将在调用 startActivity() 时崩溃。如需事先验证是否存在可接收 Intent 的应用，需要对 Intent对象调用 resolveActivity()。如果结果为非空，则至少有一个应用能够处理该 Intent，并且可以安全调用 startActivity()，如果结果为空，则不应使用该 Intent。如有可能，应停用调用该 Intent 的功能。

注意：隐式Intent与显式Intent的区别：隐式Intent不指定意图的主体。

**常见使用：**https://www.jianshu.com/p/ac6efbc45a3e

1.相机

2.打开特定设置屏幕

3.撰写带附件的短信/彩信Broadcast

**注册**

静态注册：broadcast receiver广播接收者的注册分静态注册（在AndroidManifest文件中进行配置）

![image-20220310172539667](F:/Notes/se/android/Android_files/image-20220310172759002.png)

![image-20220310172917650](F:/Notes/se/android/Android_files/image-20220310172917650.png)

动态注册：通过代码动态创建并以调用Context.registerReceiver()的方式注册至系统

![image-20220310173433554](F:/Notes/se/android/Android_files/image-20220310173433554.png)

![image-20220310173511770](F:/Notes/se/android/Android_files/image-20220310173511770.png)

新建广播接收器并注册广播

![image-20220315171629565](Android_files/image-20220315171629565.png)

发送广播

![image-20220315171840036](Android_files/image-20220315171840036.png)

在广播接收器中接受广播

![image-20220315171848965](Android_files/image-20220315171848965.png)

# PendingIntent

## 认识

PendingIntent是对Intent的封装，但它不是立刻执行某个行为，而是满足某些条件或触发某些事件后才执行指定的行为

A组件 创建了一个 PendingIntent 的对象然后传给 B组件，B 在执行这个 PendingIntent 的 send 时候，它里面的 Intent 会被发送出去，而接受到这个 Intent 的 C 组件会认为是 A 发的。

B以A的权限和身份发送了这个Intent

即：PendingIntent将某个动作的触发时机交给其他应用；让那个应用代表自己去执行那个动作（权限都给他）

我们的 Activity 如果设置了 exported = false，其他应用如果使用 Intent 就访问不到这个 Activity，但是使用 PendingIntent 是可以的。

## 获取

关于PendingIntent的实例获取一般有以下五种方法，分别对应Activity、Broadcast、Service

- `getActivity()` 从系统 取得一个用于启动一个Activity的PendingIntent对象.
- `getActivities()` 
- `getBroadcast()` 从系统取得一个用于向BroadcastReceiver的发送广播的PendingIntent对象.
- `getService()` 从系统取得一个 用于启动一个Service的PendingIntent对象.
- `getForegroundService()`

它们的参数都相同，都是四个：Context， requestCode, Intent, flags，分别对应上下文对象、请求码、请求意图用以指明启动类及数据传递、关键标志位。
前面三个参数共同标志一个行为的唯一性，而第四个参数flags：

**FLAG_CANCEL_CURRENT**：如果当前系统中已经存在一个相同的PendingIntent对象，那么就将先将已有的PendingIntent取消，然后重新生成一个PendingIntent对象。

**FLAG_NO_CREATE**：如果当前系统中不存在相同的PendingIntent对象，系统将不会创建该PendingIntent对象而是直接返回null，如果之前设置过，这次就能获取到。

**FLAG_ONE_SHOT**：该PendingIntent只作用一次。在该PendingIntent对象通过send()方法触发过后，PendingIntent将自动调用cancel()进行销毁，那么如果你再调用send()方法的话，系统将会返回一个SendIntentException。

**FLAG_UPDATE_CURRENT**：如果系统中有一个和你描述的PendingIntent对等的PendingInent，那么系统将使用该PendingIntent对象，但是会使用新的Intent来更新之前PendingIntent中的Intent对象数据，例如更新Intent中的Extras

备注：两个PendingIntent对等是指它们的operation一样, 且其它们的Intent的action, data, categories, components和flags都一样。但是它们的Intent的Extra可以不一样

## 使用场景

关于PendingIntent的使用场景主要用于闹钟、通知、桌面部件。

大体的原理是: A应用希望让B应用帮忙触发一个行为，这是跨应用的通信，需要 Android 系统作为中间人，这里的中间人就是 ActivityManager。 A应用创建建 PendingIntent，在创建 PendingIntent 的过程中，向 ActivityManager 注册了这个 PendingIntent，所以，即使A应用死了，当它再次苏醒时，只要提供相同的参数，还是可以获取到之前那个 PendingIntent 的。当 A 将 PendingIntent 调用系统 API 比如 AlarmManager.set()，实际是将权限给了B应用，这时候， B应用可以根据参数信息，来从 ActivityManager 获取到 A 设置的 PendingIntent

# 注意

## getIntent()

getIntent ()方法在Activity中使用，**获得启动当前活动时的Intent内容**。. 使用的时候要注意， 如果想每次启动Activity时使用此方法获得通过Intent传输的数据，要注意使用的启动模式。. 因为此时获得的Intent数据是在初始创建Activity时的赋值，如果使用standard启动模式则没有什么问题，但如果使用的是singleTask、singleTop等模式，若任务栈中（singleTask）或顶部（singleTop）存在该Activity，下次启动时则不会重新创建Activity（具体出入栈机制或四种启动模式详情请自行了解），所以此时获得的Intent仍为创建时的缓存数据。.