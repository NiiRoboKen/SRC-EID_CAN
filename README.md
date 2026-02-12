# SRC-EID CAN Protocol

Sender-Receiver-Command Expected ID CAN Protocol

新居浜高専ロボット研究部内で使用するCANプロトコル上の通信プロトコル。

## ID(29bit)

```plaintext
|Sender ID(8bit)|Receiver ID(8bit)|Core command flag(1bit)|Command (12bit)|
```

パケットの拡張ID(29bit)内に受信,送信者ID 8bitずつと12bitのコマンドを含みます。

## Command(12bit)

### Core Command

プロトコル共通の核となるコマンドです。
Core Command Flagが有効(1)である場合Core Commandと認識されます。

|command|data|explain|
|-------|----|-------|
|BOOT|0x000|起動命令|
|BOOT_NOTICE|0x001|起動通知|
|POWEROFF|0x002|終了命令|
|POWEROFF_NOTICE|0x003|正常終了通知|
|ERROR|0x004|異常通知|
|GET_TYPE|0x005|型取得|

### Sub Command

ノードの型毎の独自コマンドです。
Core Command Flagが無効(0)の場合Sub Commandと認識されます。

0x000~0xFFFまでが使用可能です。

## Data(8byte)

以下"任意に拡張可能"とはプロトコルを使用するノードの型毎での独自実装が可能であることを示します。

### GREET(0x000)~REBOOT(0x004)

```plaintext
|(Empty)|
```

空データ。任意に拡張可能。

### GET_TYPE(0x005)

```plaintext
|Type(1byte)|(Empty)|
```

1byteのノードの型情報を含みます。残る7byteは任意に拡張可能です。

## Node type

現行で想定されているノードの型情報です。

|type|ID|explain|
|----|--|-------|
|GCBRawMotor|0x0|汎用基板を使用したDuty比制御のモータ|
|GCBSpeedControllableMotor|0x1|汎用基板を使用した速度制御モータ|
|GCBServo|0x2|汎用基板を使用した角度制御モータ|
|GCBRPMEncoder|0x3|汎用基板を使用した回転速度エンコーダ|
|GCBAngleEncoder|0x4|汎用基板を使用した角度エンコーダ|
