如需实现语音交互应用 (VIA)，您需要完成以下步骤：

1. 创建 VIA 框架。
2. （可选）实现首次设置/登录流程。
3. （可选）实现“设置”屏幕。
4. 在清单文件中声明必需的权限。
5. 实现语音控制面板界面。
6. 实现语音识别（必须包含 RecognitionService API 实现）。
7. 实现语音内容（可以选择性地实现 TextToSpeech API）。
8. 实现命令执行。请参阅执行命令，了解这方面的内容。

# 创建 VIA 框架

## 清单

当应用清单中包含以下内容时，该应用会被检测为具有语音交互功能。

`AndroidManifest.xml`

```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.myvoicecontrol">
    ...

  <application ... >
    <service android:name=".MyInteractionService"
        android:label="@string/app_name"
        android:permission="android.permission.BIND_VOICE_INTERACTION"
        android:process=":interactor">
      <meta-data
          android:name="android.voice_interaction"
          android:resource="@xml/interaction_service" />
      <intent-filter>
        <action android:name=
          "android.service.voice.VoiceInteractionService" />
      </intent-filter>
    </service>
  </application>
</manifest>
```

在此示例中：

- VIA 必须公开一项用于扩展 `VoiceInteractionService` 的服务，并为 `VoiceInteractionService.SERVICE_INTERFACE ("android.service.voice.VoiceInteractionService")` 操作提供 intent 过滤器。
- 此服务必须拥有 `BIND_VOICE_INTERACTION` 系统签名权限。
- 此服务应具有包含以下代码的 `android.voice_interaction` 元数据文件：

`res/xml/interaction_service.xml`

```java
<voice-interaction-service
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:sessionService=
      "com.example.MyInteractionSessionService"
    android:recognitionService=
      "com.example.MyRecognitionService"
    android:settingsActivity=
      "com.example.MySettingsActivity"
    android:supportsAssist="true"
    android:supportsLaunchVoiceAssistFromKeyguard="true"
    android:supportsLocalInteraction="true" />
```

如需详细了解各字段，请参阅 `R.styleable#VoiceInteractionService`。鉴于所有的 VIA 也都属于语音识别器服务，您还必须在清单中添加以下代码：

`AndroidManifest.xml`

```xml
<manifest ...>
  <uses-permission android:name="android.permission.RECORD_AUDIO"/>
  <application ...>
    ...
    <service android:name=".RecognitionService" ...>
      <intent-filter>
        <action android:name="android.speech.RecognitionService" />
        <category android:name="android.intent.category.DEFAULT" />
      </intent-filter>
      <meta-data
        android:name="android.speech"
        android:resource="@xml/recognition_service" />
    </service>
  </application>
</manifest>
```

语音识别服务还需要具有以下元数据：

`res/xml/recognition_service.xml`

```xml
<recognition-service
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:settingsActivity="com.example.MyRecognizerSettingsActivity" />
```

