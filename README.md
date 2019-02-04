# Tencent_emotionsm_fixer
修复被企鹅在/sdcard/tencent/mobileQQ/emotionsm./xxx/× 下被破坏的gif文件的文件头。

设a.out为本二进制程序
执行命令： ./a.out 被破坏的gif文件路径 
输出结果： Fixed_GIF：??=>+.gif
PS：如果修复成功，将自动加上.gif扩展名

扩展用法（利用find搜索文件并调用本程序进行gif修正，仅限linux，win请自便）：
find 搜索相关文件 -exec ./a.out {} \;

得到的gif是非常规的，导致一些程序识别异常，可以使用Image Converter软件进行修复
添加图片源文件->转换格式为gif->开始转换
