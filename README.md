> 模块化机器人控制项目，第一台原型机名为赤星，希望可以在机器人大赛上获取名次

[toc]

## 最终目标
* 主要是人形但不限于人形的模块化机器人，方便的拆卸和组装
* 尺寸大小没有限制，先做缩略版，再做真人大小版
* 支持实时控制，这是着重需要实现的的功能
* 包含两个控制核心，头部为主要控制核心，胸部为副控制核心
* 支持自动运行和多种方式的手动控制，主要手动控制方式为AR方式，实时图像+现实增强+体感控制+键鼠控制

## 目录结构
* DOC 存放相关文档

* Source  存放源文件

* Tools 存放过程中使用的工具，一般是存放此部分使用的独有的工具，如果有共用的工具，该工具将存放至更高级别的目录

## 模块分类

### 核心模块
#### 数据处理模块

#### 控制模块
##### 手动控制

##### 自动控制

### 通讯模块
#### 指令传输
* 负责运动指令的传输，延迟做到最低
#### 数据传输

### 运动控制模块

## 调试模块


## 思考中的问题
* 最后的软件包是以Python还是C SDK的方式输出
* 主CPU使用树莓派，模块MCU使用ESP32
* 电磁干扰和复杂情况也需要考虑
* 希望可以突破业界的性能最高水平

#### 通信方式的选择
* 整体的控制似乎与穿越机的控制相似，远程控制，低延时，画面传输

###### 控制功能通信协议选择
* 中国人自己的高端运动控制网络总线——固高gLink协议簇 https://new.qq.com/rain/a/20221201A07CCB00
* EtherCAT，https://zhuanlan.zhihu.com/p/376024654
* 技术解读PROFINET、Ethernet/IP等7种主流工业以太网 https://zhuanlan.zhihu.com/p/148907119

## 工程整体思路

#### Demo模块1
* 参考ESP32与Rust的示例github工程 https://github.com/esp-rs/std-training
* 尽可能多的支持通信协议，做到最大的传速速度

## 关键问题解决思路

#### 图像实时无线的传输
* 模拟图传和数字图传 https://www.17fpv.com/338.html
* 矩阵式WIFI + 5G 保证画面质量和低延迟
* 先造个穿越机尝试解决这个问题

## 经验总结
* 查看过，波士顿的API创建的demo项目，发现只是开源了库，并且想要使用波士顿的库还要购买波士顿的硬件，波士顿的项目没有参考意义

## 参考链接
* [GVN系列高性能多轴网络运动控制卡](http://www.googoltech.com.cn/pro_view-92.html#:~:text=%E9%AB%98%E9%80%9FgLink-,%E6%BF%80%E5%85%89%E5%8A%A0%E5%B7%A5%E7%AD%89%E8%A1%8C%E4%B8%9A%E3%80%82)
* [工业4.0智能制造通信协议](https://blog.csdn.net/Yilingsi_M/article/details/128136233)