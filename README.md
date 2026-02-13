# SRC-EID CAN Protocol

Sender-Receiver-Command Expected ID CAN Protocol

新居浜高専ロボット研究部内で使用するCANプロトコル上の通信プロトコル。

## ID(29bit)

```plaintext
|Sender ID(8bit)|Receiver ID(8bit)|Command (13bit)|
```

パケットの拡張ID(29bit)内に受信,送信者ID 8bitずつと13bitのコマンドを含みます。

## Command(13bit)

### Core Command

プロトコル共通のコマンドです。
13bitのコマンドのうち0x1000以降はCore Command用の予約領域となります。

|command|data|explain|
|-------|----|-------|
|BOOT|0x1000|起動命令|
|BOOT_NOTICE|0x1001|起動通知|
|POWEROFF|0x1002|終了命令|
|POWEROFF_NOTICE|0x1003|正常終了通知|
|ERROR|0x1004|異常通知|
|PING|0x1005|疎通確認|
|PONG|0x1006|疎通応答|

### Sub Command

ノードの型毎の独自コマンドです。
0x0000~0x0FFFまでが使用可能です。

## Payload(8byte)

以下"任意に拡張可能"とはプロトコルを使用するノードの型毎での独自実装が可能であることを示します。

### BOOT(0x000)~POWEROFF_NOTICE(0x003), PING(0x005), PONG(0x006)

```plaintext
|(Empty)|
```

空データ。任意に拡張可能。

### ERROR(0x004)

```plaintext
|Error code(1byte)|(Empty)|
```

1byteのエラーコードを含みます。残る7byteは任意に拡張可能です。
