---
layout: post
title:  "windows与linux下回车的差异"
categories: [Linux]
---
windows下，回车是\r\n,对应ascii码为1310。

linux下，回车是\n，对应ascii码为10。

如果在刷OJ读入字符串时发现无论如何回车部分都有问题，可以试试加特殊判定，把字符串末尾可能存在的\r替换为\0。
