/*
设a.out为本二进制程序
执行命令： ./a.out 被破坏的gif文件路径 
输出结果： Fixed_GIF：??=>+.gif
PS：如果修复成功，将自动加上.gif扩展名

扩展用法（利用find搜索文件并调用本程序进行gif修正，仅限linux，win请自便）：
find 搜索相关文件 -exec ./a.out {} \;

得到的gif是非常规的，导致一些程序识别异常，可以使用Image Converter软件进行修复
添加图片源文件->转换格式为gif->开始转换

*/
#include <stdio.h>
#include <string.h>
int main(int argc,char* arg[]){
	if(argc<1){
		return -1;
	}
	unsigned int i=0;
	char filename[1024]={0x00};
	char now_head[]={0x47,0x48,0x46,0x39,0x39,0x60,0x00};//0x47,0x48,0x46,0x39,0x39,0x60为被腾讯污染的文件头
	char read_head[7]={0x00};
	FILE* f=fopen(arg[1],"rw+");
	if(f){
		//判断文件是否为被污染的文件头
		if(fread(read_head,sizeof(char),6,f)==6 && strcmp(read_head,now_head)==0){
			now_head[1]=0x49;now_head[3]=0x38;now_head[5]=0x61;//修正GIF文件头
			if(-1 == (fseek(f,0L, SEEK_SET))){
				printf("seek error\n");
			}else{
				//覆盖错误的文件头为正确的文件头。
				fwrite(now_head,sizeof(char),6,f);
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
