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

![image-20220310172539667](Android_files/image-20220310172759002.png)

![image-20220310172917650](Android_files/image-20220310172917650.png)

动态注册：通过代码动态创建并以调用Context.registerReceiver()的方式注册至系统

![image-20220310173433554](Android_files/image-20220310173433554.png)

![image-20220310173511770](Android_files/image-20220310173511770.png)

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

# 七大属性

## ComponentName

指定了ComponentName属性的Intent已经明确了它将要启动哪个组件，因此这种Intent被称为显式Intent，没有指定ComponentName属性的Intent被称为隐式Intent。隐式Intent没有明确要启动哪个组件，应用会根据Intent指定的规则去启动符合条件的组件。
```java
Intent intent = new Intent();
ComponentName cName = new ComponentName(MainActivity.this,NextActivity.class);
intent.setComponent(cName);
startActivity(intent);
 
//实际上，以上的写法都被简化为以下写法：
Intent intent = new Intent(MainActivity.this,NextActivity.class);
        startActivity(intent);
 
//也就是说，平时我们最常用的Intent页面跳转的写法就调用的是显式Intent。
 
 
此外，ComponentName属性可以实现一个app跳转到另一个app。
 
Intent intent = new Intent();
   ComponentName cName = new ComponentName(
"com.steven.testasyncloader.sqlitedata","com.steven.testasyncloader.sqlitedata.MainActivity");
//其中两个参数的含义：第一个是要跳转到的app的包名，第二个参数是该包中的要跳转到app的页面的class
   intent.setComponent(cName);
   startActivity(intent);
```

## Action

Action作为标识符，代表一个Intent，当一个Activity需要外部协助处理时，就会发出一个Intent，如果一个程序能完成相应功能，只要在intent-filter加上这个这个intent就可以了。

通常，Action、Category属性结合使用，定义这两个属性都是在配置文件的<intent-filter>节点中。Intent通过定义Action属性（其实就是一段自定义的字符串），这样就可以把Intent与具体的某个Activity分离，实现了解耦。否则，每次跳转，都要写成类似new Intent(MainActivity.this,NextActivity.class)这样的形式，也就是说必须将要跳转的目标Activity的名字写出来，这样的编码其实是“硬编码”，并没有实现松耦合。调用Intent对象的setAction()方法实现页面跳转虽然略微复杂（需要在AndroidManifest.xml文件中配置），但是实现了解耦。

常用的Action属性常量：

- ACTION_MAIN：（android.intent.action.MAIN）Android程序入口//每个Android应用必须且只能包含一个此类型的Action声明。【如果设置多个，则哪个在前，执行哪个。】
- ACTION_VIEW： （android.intent.action.VIEW） 显示指定数据。
- ACTION_EDIT： （android.intent.action.EDIT） 编辑指定数据。      
- ACTION_DIAL： （android.intent.action.DIAL） 显示拨号面板。      
- ACTION_CALL： （android.intent.action.CALL） 直接呼叫Data中所带的号码。      
- ACTION_ANSWER： （android.intent.action.ANSWER） 接听来电。      
- ACTION_SEND： （android.intent.action.SEND） 向其他人发送数据（例如：彩信/email）。      
- ACTION_SENDTO：  （android.intent.action.SENDTO） 向其他人发送短信。      
- ACTION_SEARCH： （android.intent.action.SEARCH） 执行搜索。      
- ACTION_GET_CONTENT： （android.intent.action.GET_CONTENT） 让用户选择数据，并返回所选数据。

Intent利用Action属性中的ACTION_GET_CONTENT获取返回值：

```java
//选择图片 requestCode 返回的标识
Intent intent = new Intent();
intent.setAction(Intent. ACTION_GET_CONTENT );
intent.setType( "image/*" );
Intent wrapperIntent = Intent.createChooser(intent, null);
startActivityForResult(wrapperIntent, requestCode);  
 
 
//添加音频
Intent intent = new Intent();
intent.setAction(Intent. ACTION_GET_CONTENT );
intent.setType( "video/*" );
Intent wrapperIntent = Intent.createChooser(intent, null);
startActivityForResult(wrapperIntent, requestCode);  
 
 
//视频
Intent intent = new Intent();
intent.setAction(Intent. ACTION_GET_CONTENT );
intent.setType( "video/*" );
Intent wrapperIntent = Intent.createChooser(intent, null);
startActivityForResult(wrapperIntent, requestCode);  
 
 
//录音
Intent intent = new Intent();
intent.setAction(Intent. ACTION_GET_CONTENT );
intent.setType( "audio/amr" );
intent.setClassName("com.android.soundrecorder","com.android.soundrecorder.SoundRecorder");
startActivityForResult(intent, requestCode);  
```

## Category

Category表示Intent的种类，从android上启动Activity有多种方式，比如 程序列表、桌面图标、点击Home激活的桌面等等，Category则用来标识这些Activity的图标会出现在哪些启动的上下文环境里。

Category属性为Action增加额外的附加类别信息。CATEGORY_LAUNCHER意味着在加载程序的时候Acticity出现在最上面，而CATEGORY_HOME表示页面跳转到HOME界面。

实现页面跳转到HOME界面的代码：

```java
Intent intent = new Intent();
intent.setAction(Intent.ACTION_MAIN);
intent.addCategory(Intent.CATEGOTY_HOME);
startActivity(intent);
```

常用Category属性常量

- CATEGORY_DEFAULT： （android.intent.category.DEFAULT） Android系统中默认的执行方式，按照普通Activity的执行方式执行。      
- CATEGORY_HOME： （android.intent.category.HOME） 设置该组件为Home Activity。    
- CATEGORY_PREFERENCE： （android.intent.category.PREFERENCE） 设置该组件为Preference。      
- CATEGORY_LAUNCHER： （android.intent.category.LAUNCHER） 设置该组件为在当前应用程序启动器中优先级最高的Activity，通常与入口ACTION_MAIN配合使用。     
- CATEGORY_BROWSABLE： （android.intent.category.BROWSABLE） 设置该组件可以使用浏览器启动。

## Data

Data属性通常用于向Action属性提供操作的数据。Data属性的值是个Uri对象。

Uri的格式如下：scheme://host:port/path

系统内置的几个Data属性常量：

- tel://：号码数据格式，后跟电话号码。      
- mailto://：邮件数据格式，后跟邮件收件人地址。      
- smsto://：短息数据格式，后跟短信接收号码。    
- content://：内容数据格式，后跟需要读取的内容。      
- file://：文件数据格式，后跟文件路径。      
- market://search?q=pname:pkgname：市场数据格式，在Google Market里搜索包名为pkgname的应用。      
- geo://latitude, longitude：经纬数据格式，在地图上显示经纬度所指定的位置。

Intent利用Action属性和Data属性启动Android系统内置组件的代码：

1. 拨打电话

```java
Intent intent=new Intent();
intent.setAction(Intent.ACTION_CALL);  
//intent.setAction("android.intent.action.CALL");  //以下各项皆如此，都有两种写法。
intent.setData(Uri.parse("tel:1320010001"));
startActivity(intent);
 
//调用拨号面板：
Intent intent=new Intent();
intent.setAction(Intent.ACTION_DIAL);
intent.setData(Uri.parse("tel:1320010001"));
startActivity(intent);
 
//调用拨号面板：
Intent intent=new Intent();
intent.setAction(Intent.ACTION_VIEW);
intent.setData(Uri.parse("tel:1320010001"));
startActivity(intent);
```

2. 利用Uri打开浏览器、打开地图等

```java
Uri uri = Uri.parse("http://www.google.com"); //浏览器
Uri uri=Uri.parse("geo:39.899533,116.036476"); //打开地图定位
Intent intent = new Intent();
intent.setAction(Intent.ACTION_VIEW);
intent.setData(uri);
startActivity(intent);
```

## Type

Type属性用于指定Data所指定的Uri对应的MIME类型。MIME只要符合“abc/xyz”这样的字符串格式即可。

Intent利用Action、Data和Type属性启动Android系统内置组件的代码（播放视频）：

```java
Intent intent = new Intent();
Uri uri = Uri.parse("file:///sdcard/media.mp4");
intent.setAction(Intent.ACTION_VIEW);
intent.setDataAndType(uri, "video/*");
startActivity(intent);
```

## Extra

Extras保存需要传递的额外数据。

1. 通过intent.putExtra(键, 值)的形式在多个Activity之间进行数据交换
2. 系统内置的几个Extra常量：

- EXTRA_BCC：存放邮件密送人地址的字符串数组。      
- EXTRA_CC：存放邮件抄送人地址的字符串数组。      
- EXTRA_EMAIL：存放邮件地址的字符串数组。      
- EXTRA_SUBJECT：存放邮件主题字符串。      
- EXTRA_TEXT：存放邮件内容。      
- EXTRA_KEY_EVENT：以KeyEvent对象方式存放触发Intent的按键。      
- EXTRA_PHONE_NUMBER：存放调用ACTION_CALL时的电话号码。

Intent利用Action、Data和Type、Extra属性启动Android系统内置组件的代码（调用发送短信的程序）：

```java
Intent  intent  = new Intent();
intent.setAction(Intent.ACTION_VIEW);
intent.setType("vnd.android-dir/mms-sms");
intent.putExtra("sms_body", "信息内容...");
startActivity(intent);
 
//发送短信息
Uri uri = Uri.parse("smsto:13200100001");
Intent  intent  = new Intent();
intent.setAction(Intent.  ACTION_SENDTO );
intent.setData(uri);
intent.putExtra("sms_body", "信息内容...");
startActivity( intent );
 
//发送彩信,设备会提示选择合适的程序发送
Uri uri = Uri.parse("content://media/external/images/media/23"); //设备中的资源（图像或其他资源）
Intent intent = new Intent();
intent.setAction(Intent.  ACTION_SEND );
intent.setType("image/png");
intent.putExtra("sms_body", "内容");
intent.putExtra(Intent.EXTRA_STREAM, uri);
startActivity(it);
```

发送Email：

```java
Intent intent=new Intent();
intent.setAction(Intent.  ACTION_SEND );
String[] tos={"android1@163.com"};
String[] ccs={"you@yahoo.com"};
intent.putExtra(Intent.EXTRA_EMAIL, tos);
intent.putExtra(Intent.EXTRA_CC, ccs);
intent.putExtra(Intent.EXTRA_TEXT, "The email body text");
intent.putExtra(Intent.EXTRA_SUBJECT, "The email subject text");
intent.setType("message/rfc822");
startActivity(Intent.createChooser(intent, "Choose Email Client"));
 
Intent intent = new Intent(Intent.ACTION_SEND);
String[] tos = { "mobileservice@ablesky.com" };
intent.putExtra(Intent.EXTRA_EMAIL, tos);
intent.putExtra(Intent.EXTRA_TEXT, getPhoneParameter());
intent.putExtra(Intent.EXTRA_SUBJECT, "Android日志");
intent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(cacheDir));
intent.setType("message/rfc882");
intent.setType("plain/text");
Intent.createChooser(intent, "请选择邮件发送软件");
startActivity(intent);  

intent.setAction(android.provider.Settings.ACTION_SETTINGS);
```

## Flags

Intent可调用addFlags()方法来为Intent添加控制标记

- FLAG_ACTIVITY_CLEAR_TOP:（效果同Activity  LaunchMode的singleTask）
  如果在栈中已经有该Activity的实例，就重用该实例。重用时，会让该实例回到栈顶，因此在它上面的实例将会被移除栈。如果栈中不存在该实例，将会创建新的实例放入栈中。
- FLAG_ACTIVITY_SINGLE_TOP:（效果同Activity  LaunchMode的singleTop）
  如果在任务的栈顶正好存在该Activity的实例， 就重用该实例，而不会创建新的Activity对象。
- FLAG_ACTIVITY_NEW_TASK: （效果类似Activity  LaunchMode的singleInstance）
- FLAG_ACTIVITY_MULTIPLE_TASK
- FLAG_ACTIVITY_BROUGHT_TO_FRONT
- FLAG_ACTIVITY_RESET_TASK_IF_NEEDED

示例代码：

```java
Intent intent = new Intent(this, MainActivity.class);
//将Activity栈中处于MainActivity主页面之上的Activity都弹出。
intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
startActivity(intent);
```

如果依次启动了四个Activity：A、B、C、D。
在D Activity里，跳到B Activity，同时希望D 和 C 都finish掉，可以在startActivity(intent)里的intent里添加flags标记，如下所示：

```java
Intent intent = new Intent(this, B.class);   
intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);  
startActivity(intent);
```

这样启动B Activity的同时，就会把D、C都finished掉。
如果B Activity的launchMode是默认的“standard”，则B Activity会首先finished掉旧的B页面，再启动一个新的Activity B。  如果不想重新再创建一个新的B Activity，而是重用之前的B Activity，可以将B Activity的launchMode设置为“singleTask”。【特别需要注意的是：在部分手机中，如三星手机。即便是singleTask也会产生新的页面，而不是重用之前的页面。】

# IntentFilter

## 定义

IntentFilter翻译成中文就是“意图过滤器”，主要用来过滤隐式意图。当用户进行一项操作的时候，Android系统会根据配置的 “意图过滤器” 来寻找可以响应该操作的组件，服务。

例如：当用户点击PDF文件的时候，Android系统就会通过设定好的意图过滤器，进行匹配测试。找到能够打开PDF文件的APP程序。

## 原理

Android系统会根据我们配置的Intent Filter（意图过滤器），来进行匹配测试。匹配的时候，只会考虑三个方面：动作、数据（URI以及数据类型）和类别。也就是说Android系统会进行“动作测试”，“数据测试”，“类别测试”，来寻找可以响应隐式意图的组件或服务。

另外，当对其他App程序开放组件和服务的时候也需要配置Intent Filter（意图过滤器），一个Activity可以配置多个<intent-filter>。

### 动作测试

对应<intent-filter>中的<action/>标签；

- 如果<intent-filter>标签中有多个<action/>，那么Intent请求的Action，只要匹配其中的一条<action/>就可以通过了这条<intent-filter>的动作测试。

- 如果<intent-filter>中没有包含任何<action/>，那么无论什么Intent请求都无法和这条<intent-filter>匹配。

- 如果Intent请求中没有设定Action(动作)，那么这个Intent请求就将顺利地通过<intent-filter>的动作测试（前提是<intent-filter>中必须包含有<action/>，否则与第二条冲突）。

### 类别测试

对应<intent-filter>中的<category />标签；

- Intent中的类别必须全部匹配<intent-filter>中的<category />，但是<intent-filter>中多余的<category />将不会导致匹配失败。

例如：Intent中有3个类别，而意图过滤器中定义了5个，如果Intent中的3个类别都与过滤器中的匹配，那么过滤器中的另外2个，将不会导致类别测试失败。

# 注意

## getIntent()

getIntent ()方法在Activity中使用，**获得启动当前活动时的Intent内容**。. 使用的时候要注意， 如果想每次启动Activity时使用此方法获得通过Intent传输的数据，要注意使用的启动模式。. 因为此时获得的Intent数据是在初始创建Activity时的赋值，如果使用standard启动模式则没有什么问题，但如果使用的是singleTask、singleTop等模式，若任务栈中（singleTask）或顶部（singleTop）存在该Activity，下次启动时则不会重新创建Activity（具体出入栈机制或四种启动模式详情请自行了解），所以此时获得的Intent仍为创建时的缓存数据。.