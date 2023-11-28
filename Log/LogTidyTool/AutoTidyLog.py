
import json
import re
import os

LogTidyConfigFile = "LogTidyConfig.json"
LogPath = "./Log"

if __name__ == "__main__":

    with open(LogTidyConfigFile,'r') as f:
        LogTidyConfigFileItemList = json.load(f)
        f.close()

    print("============== The following is the Log Tidy information =============")
    for key, value in LogTidyConfigFileItemList.items():
        print(key + " ==> " + value )

    LogFiles = os.listdir(LogPath)  #读取Log路径下所有的文件
    for LogFile in LogFiles:    #遍历文件夹
        if not os.path.isdir(LogFile):  #判断是否是文件夹，不是文件夹才进行处理
            print("============== Tidy Log file " + LogFile + " ==============")
            with open(LogPath+"/"+LogFile,"r") as f:    #打开文件，读模式
                LogFileLines = f.readlines()    #读取该文件所有行
                f.close()
            with open(LogPath+"/"+LogFile,"w+") as f:   #打开文件，写模式
                for itemLine in LogFileLines:   #按行来进行替换处理
                    currnetline = itemLine
                    for key, value  in LogTidyConfigFileItemList.items():   #遍历配置文件中需要替换的内容
                        if (key in currnetline):    #如果找到了需要替换的内容
                            currnetline = re.sub(key, value, currnetline)   #替换行字符串
                    f.writelines(currnetline)   #写入字符创
                    print("[ " + itemLine + " ] ==> [ " +currnetline + " ]")
                f.close()   #关闭文件

    print("============== Log tidy end ==============")
    input()
