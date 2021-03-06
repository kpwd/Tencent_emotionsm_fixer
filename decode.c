/*
QQ原创表情解析 for android 
处理/tencent/mobileQQ/.emotionsm/{number}/{md5}(无扩展名) 这种文件，将它变成表情

设a.out为本二进制程序
执行命令： ./a.out 被破坏的gif文件路径 
输出结果： Fixed_GIF：??=>+.gif
PS：如果修复成功，将自动加上.gif扩展名，文件将可以正常使用

扩展用法（利用find搜索文件并调用本程序进行gif修正，仅限linux，win请自便）：
find 搜索相关文件 -exec ./a.out {} \;

程序核心原理：
将文件头为
0x47,0x48,0x46,0x39,0x39,0x60,0x2c,0x00,0x2c,0x00
的文件，替换为
0x47,0x49,0x46,0x38,0x39,0x61,0x2c,0x01,0x2c,0x01
*/
#include <stdio.h>
#include <string.h>
int main(int argc,char* arg[]){
	if(argc<1){
		return -1;
	}
	unsigned int i=0;
	char filename[1024]={0x00};
	char now_head[]={0x47,0x48,0x46,0x39,0x39,0x60,0x2c,0x00,0x2c,0x00,0x00};//0x47,0x48,0x46,0x39,0x39,0x60,0x2c,0x00,0x2c,0x00 为被腾讯污染的文件头
	char read_head[11]={0x00};
	FILE* f=fopen(arg[1],"rw+");
	if(f){
		//判断文件是否为被污染的文件头
		if(fread(read_head,sizeof(char),10,f)==10 && strcmp(read_head,now_head)==0){
			now_head[1]=0x49;now_head[3]=0x38;now_head[5]=0x61;now_head[7]=0x01;now_head[9]=0x01;//修正GIF文件头
			if(-1 == (fseek(f,0L, SEEK_SET))){
				printf("seek error\n");
			}else{
				//覆盖错误的文件头为正确的文件头。
				fwrite(now_head,sizeof(char),10,f);
				fflush(f);
				fclose(f);

				//修改文件名,增加.gif
				i=strlen(arg[1]);
				memcpy(filename,arg[1],i);
				filename[i]='.';filename[i+1]='g';filename[i+2]='i';filename[i+3]='f';
				rename(arg[1],filename);

				printf("Fixed_GIF：%s=>+.gif\n",arg[1]);
				return 0;
			}
		}else{
			printf("Wrong GIF：%s\n",arg[1]);
		}
		fclose(f);
	}else
	printf("No GIF：%s\n",arg[1]);
	return -1;
}
