>抓帧看log进行分析太累，每次都要先将帧内容一个一个的按格式排好，写一个自动格式化处理帧log的脚本

## 使用方法
* 1.修改目录下 LogTidyConfig.json
	* key为修改前的内容，value为修改后的内容
	* 支持空格回车，回车用"\n"
* 2.将需要整理格式的Log文件放入 ./Log 文件夹下
* 3.运行AutoTidyLog.py