[toc]

# STM32F103C8T6

* 芯片有48个引脚，引脚图如下

![](.\image\STM32F103C8T6IOimage.png)

## 程序的下载

**需要对BOOT有一定了解**

![img](.\image\BOOT.png)

* Main Flash Memory

  STM32的内置**Flash**，在JTAG或SWD模式下载程序时，就下载到主闪存存储器，

* System Memory

  从系统存储器启动，这种模式启动的程序功能是由厂家设置的。一般来说，这种启动方式用的比较少。系统存储器是芯片内部一块特定的区域，STM32在出厂时，由ST在这个区域内部预置了一段BootLoader， 也就是我们常说的ISP程序， 这是一块**ROM**，出厂后无法修改。一般来说，我们选用这种启动模式时，是为了从串口下载程序，因为在厂家提供的BootLoader中，提供了串口下载程序的固件，可以通过这个BootLoader将程序下载到系统的Flash中。但是这个下载方式需要以下步骤：
  **Step1:**将BOOT0设置为1，BOOT1设置为0，然后按下复位键，这样才能从系统存储器启动BootLoader
  **Step2:**最后在BootLoader的帮助下，通过串口下载程序到Flash中
  **Step3:**程序下载完成后，又有需要将BOOT0设置为GND，手动复位，这样，STM32才可以从Flash中启动可以看到， 利用串口下载程序还是比较的麻烦， 需要跳帽跳来跳去的，非常的不注重用户体验。

* Embedded Memory

  内置**SRAM**，既然是SRAM，自然也就没有程序存储的能力了，这个模式一般用于程序调试。假如我只修改了代码中一个小小的地方，然后就需要重新擦除整个Flash，比较的费时，可以考虑从这个模式启动代码（也就是STM32的内存中），用于快速的程序调试，等程序调试完成后，在将程序下载到SRAM中。

程序下载可使用三种方式

1. ISP串口下载

   使用USB-TTL接PA9(TX)、PA10(RX)。

   In-SystemPrograming，烧录的时候需要配合BOOT0(跳1)和BOOT1接地(跳0)来实现，使用FLyMcu烧录，开始编程后需要按复位键启动BootLoader，烧录完成后将BOOT0跳0，即可启动Flash中的程序。

2. SWD下载

   使用STLink接PA13、PA14

3. JTAG下载

   使用JLink接PA13、PA14、PA15、PB3、PB4

# 步进电机的驱动

## DM860H

https://zhuanlan.zhihu.com/p/210507128

https://blog.csdn.net/weixin_41883890/article/details/111184974

https://blog.csdn.net/tang2010up/article/details/109355020 	