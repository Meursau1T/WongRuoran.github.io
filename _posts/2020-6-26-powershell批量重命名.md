---
layout: post
title:  "powershell批量重命名"
date:   2020-6-26 0:0:01
categories: [Powershell]
---

下载高清动画后，因为需要外挂字幕，所以要重命名动画名称，使其与字幕名称一致，方便播放器识别。动画原名如下：
```
[ANK-Raws] 進撃の巨人3 01 (BDrip 1920x1080 HEVC-YUV420P10 FLAC).mkv
```

思路是用正则表达式提取文件名中的数字部分，然后用其替代文件名。代码如下：

```
Get-ChildItem . *.mkv | ForEach-Object -Process {if($_.name -match '\s\d\d\s'){Rename-Item $_.FullName -NewName ($Matches.Item(0) + '.mkv') }}
```
`Get-ChildItem`实质上就是`ls`，列出当前文件夹内所有`mkv`文件，然后通过管道`|`传递给`ForEach-Object`，该函数的参数`Process`后跟要运行的代码，当`$_.name -match '\s\d\d\s'`为真，也就是匹配到夹在两个空格之间的两个数字后，将文件名用`Rename-Item`重命名为刚刚匹配到的数字，该数字储存在`$Matches`中，可以通过`Item()`方法调用，最后加上后缀即可。