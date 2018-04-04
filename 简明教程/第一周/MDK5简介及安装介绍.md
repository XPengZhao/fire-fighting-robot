# MDK5 简介及安装

## 1. MDK 5简介

MDK 源自德国的 KEIL 公司，是 RealView MDK 的简称。在全球 MDK 被超过 10 万的嵌入式开发工程师使用。本项目采用的是：MDK5.14，该版本使用 uVision5 IDE 集成开发环境，是目前针对 ARM 处理器，尤其是 Cortex M 内核处理器的最佳开发工具。

### 1.1 MDK5 兼容性

MDK5 向后兼容 MDK4 和 MDK3 等，以前的项目同样可以在 MDK5 上进行开发(但是头文件方面得全部自己添加!!!)， MDK5 同时加强了针对 Cortex-M 微控制器开发的支持，并且对传统的开发模式和界面进行升级。

### 1.2 MDK5 组成

MDK5 由两个部分组成：MDK Core 和 Software Packs。其中， Software Packs 可以独立于工具链进行新芯片支持和中间库的升级。
MDK Core 分成四个部分：

- uVision IDE with Editor（编辑器）
- ARM C/C++ Compiler（编译器）
- Pack Installer（包安装器）
- uVision Debugger with Trace（调试跟踪器）。

uVision IDE 从 MDK4.7 版本开始就加入了代码提示功能和语法动态检测等实用功能，相对于以往的 IDE 改进很大。

MDK5 中，MDK Core 是一个独立的安装包，它并不包含器件支持和设备驱动等组件，但是一般都会包括 CMSIS 组件，大小 350M 左右，相对于 MDK4.70A 的 500 多 M，瘦身不少，MDK5 安装包可以在：[keil 官网] 下载到。而器件支持、设备驱动、CMSIS 等组件，则可以点击 MDK5 的 Build Toolbar 的最后一个图标调出 Pack Installer，来进行各种组件的安装。也可以在 <http://www.keil.com/dd2/pack>  这个地址下载，然后进行安装。

在 MDK5 安装完成后，要让 MDK5 支持 STM32F103 的开发，我们还需要安装 STM32F1的器件支持包：Keil.STM32F1xx_DFP.1.0.5.pack（STM32F1 的器件包）。

引自<www.openedv.com>

## 2. MDK5 安装

打开 mdk514.exe,进行安装。MDK安装比较简单，基本只要一路按 next 即可。

### 2.1 安装路径

**安装路径最好直接是D盘**，新建MDK5.14文件夹下。如下图所示。

![路径]()

### 2.2 设置信息

安装 MDK5 时会让你填写一些简单的信息，这些信息无关紧要，随便设置即可，如下图。

>注意！**安装路径不要包含中文名字！**

![设置信息]

### 2.3 Tools by ARM

安装软件可能会提示安装总线控制器，选择**安装**即可

![总线控制器](https://github.com/a-sleepy-cat/image-host/raw/master/fire-fighting-robot/%E7%AE%80%E6%98%8E%E6%95%99%E7%A8%8B/4.PNG)

### 2.4 Pack Installer

安装完成之后，点击 Finish, 之后，MDK 会自动弹出 Pack Installer 界面。

![安装成功](https://github.com/a-sleepy-cat/image-host/raw/master/fire-fighting-robot/%E7%AE%80%E6%98%8E%E6%95%99%E7%A8%8B/Image_005.jpg)
![包安装器](Image_006.jpg)

[keil 官网]: <http://www.keil.com/demo/eval/arm.htm> "http://www.keil.com/demo/eval/arm.htm"
