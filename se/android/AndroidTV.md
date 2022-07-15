# 开发入门

## UI设计

- TV的观看距离较远，建议限制TV屏幕上的文字和阅读量
- 确保界面具有清晰的两轴导航路径以供上下左右四个方向的移动操作使用
- 应用必须清楚地指明聚焦的对象，这样用户就很容易看出他们可以执行的操作。使用缩放、阴影亮度 、不透明度、动画来帮助用户看出聚焦的对象。

## 声明 TV Activity

目标平台为 TV 设备的应用必须在其清单中声明 TV 启动器 Activity。它使用 CATEGORY_LEANBACK_LAUNCHER intent 过滤器来执行此操作。此过滤器可将您的应用标识为支持 TV 平台，并让 Google Play 将其识别为 TV 应用。

```java
    <application
      android:banner="@drawable/banner" >
      ...
      <activity
        android:name="com.example.android.MainActivity"
        android:label="@string/app_name" >

        <intent-filter>
          <action android:name="android.intent.action.MAIN" />
          <category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>
      </activity>

      <activity
        android:name="com.example.android.TvActivity"
        android:label="@string/app_name"
        android:theme="@style/Theme.Leanback">

        <intent-filter>
          <action android:name="android.intent.action.MAIN" />
          <category android:name="android.intent.category.LEANBACK_LAUNCHER" />
        </intent-filter>

      </activity>
    </application>
```

注意：如果您不在应用中包含 CATEGORY_LEANBACK_LAUNCHER intent 过滤器，那么用户在 TV 设备上运行 Google Play 时将看不到您的应用。此外，如果您的应用没有此过滤器，那么当您使用开发者工具将其加载到 TV 设备上时，该应用不会出现在 TV 界面中。

## 声明Leanback支持

声明您的应用使用 Android TV 所要求的 Leanback 界面。如果您要开发一款在移动设备（手机、穿戴式设备、平板电脑等）以及 Android TV 上都可运行的应用，请将 required 属性值设为 false。如果您将 required 属性值设为 true，您的应用将只能在使用 Leanback 界面的设备上运行。

```java
    <manifest>
        <uses-feature android:name="android.software.leanback"
            android:required="false" />
        ...
    </manifest>
```

## 将触摸屏声明为非必备条件

目标平台为 TV 设备的应用不依赖于触摸屏进行输入。为明确这一点，您的 TV 应用的清单必须声明 android.hardware.touchscreen 功能为非必备功能。此设置会将您的应用标识为能够在 TV 设备上工作，这也是您的应用在 Google Play 中被视为 TV 应用的必要条件。以下代码示例展示了如何添加此清单声明：

```java
 <manifest>
        <uses-feature android:name="android.hardware.touchscreen"
                  android:required="false" />
        ...
</manifest>
```

注意：您必须在应用清单中声明触摸屏并非必要条件（如本示例代码中所示），否则您的应用将不会出现在 TV 设备上的 Google Play 中。

## 提供主屏幕横幅

如果应用包含 Leanback 启动器 intent 过滤器，那么它必须针对每种本地化语言提供一张主屏幕横幅图片。横幅是显示在主屏幕的应用和游戏行中的应用启动点。如需向您的应用添加横幅，请在清单中描述横幅，如下所示：

```java
    <application
        ...
        android:banner="@drawable/banner" >

        ...
    </application>
    
```

您可以将 android:banner 属性与 <application> 标记一起使用，为所有应用 Activity 提供默认横幅，也可以将其与 <activity> 标记一起使用，为特定 Activity 提供横幅。

横幅应该是 xhdpi 资源，尺寸为 320 x 180 像素。文本必须包含在图片中。如果您的应用支持多种语言，对于带文本的横幅，您必须针对支持的每种语言提供单独的版本。

*大概类似于logo吧。。。

## 更改启动器颜色

当 TV 应用启动时，系统会显示动画，就像一个不断膨胀的实心圆。要自定义此动画的颜色，请将 TV 应用或 Activity 的 android:colorPrimary 属性设为特定颜色。此外，还应将另外两个过渡重叠属性设为 true，如主题背景资源 XML 文件中的以下代码段所示：

```java
    <resources>
        <style ... >
          <item name="android:colorPrimary">@color/primary</item>
          <item name="android:windowAllowReturnTransitionOverlap">true</item>
          <item name="android:windowAllowEnterTransitionOverlap">true</item>
        </style>
    </resources>
    
```

# 添加 TV 库

Jetpack 包含用于 TV 应用的 androidx 软件包库。这些库为 TV 设备提供了 API 和界面微件。

- androidx.leanback.app
- androidx.leanback.database
- androidx.leanback.graphics
- androidx.leanback.media
- androidx.leanback.preference
- androidx.leanback.system
- androidx.leanback.widget
- androidx.leanback.widget.picker

# 代理设置

C:\Users\5109U25854\.gradle的gradle.properties文件下

systemProp.http.proxyHost=137.153.66.14

systemProp.http.proxyPort=10080

systemProp.https.proxyHost=137.153.66.14

systemProp.https.proxyPort=10080

# 确认App是否运行在TV设备下

UiModeManager.getCurrentModeType()

```java
public static final String TAG = "DeviceTypeRuntimeCheck";
UiModeManager uiModeManager = (UiModeManager)getSystemService(UI_MODE_SERVICE);
if(uiModeManager.getCurrentModeType()==Configuration.UI_MODE_TYPE_TELEVISION){
    Log.d(TAG,"Running on a TV Device")
}else{
    Log.d(TAG,"Running on a non-TV Device")
}
```

