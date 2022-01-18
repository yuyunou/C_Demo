#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#define mm_size (50 * 1024 * 1024)
CURL *curl;
CURLcode res;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
   return fwrite(ptr, size, nmemb, (FILE*)stream); 
}

int my_progress_func(char *progress_data,  
                     double t, /* dltotal */  
                     double d, /* dlnow */  
                     double ultotal,  
                     double ulnow)  
{  
  printf("%s  (%g %%)\n", progress_data,  d*100.0/t);  
  return 0;  
}  

int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	CURL *easy_handle = (CURL *)(clientp);
	char timeFormat[9] = "Unknow";
 
	// Defaults to bytes/second
	double speed;
	char unit = "B";
 
	curl_easy_getinfo(easy_handle, CURLINFO_SPEED_DOWNLOAD, &speed); // curl_get_info必须在curl_easy_perform之后调用
 
	if (speed != 0)
	{
		// Time remaining
		//double leftTime = (downloadFileLength - dlnow - resumeByte) / speed;
		//int hours = leftTime / 3600;
		//int minutes = (leftTime - hours * 3600) / 60;
		//int seconds = leftTime - hours * 3600 - minutes * 60;
 
#ifdef _WIN32
		//sprintf_s(timeFormat, 9, "%02d:%02d:%02d", hours, minutes, seconds);
#else
		//sprintf(timeFormat, "%02d:%02d:%02d", hours, minutes, seconds);
#endif
	}
 
	if (speed > 1024 * 1024 * 1024)
	{
		unit = "G";
		speed /= 1024 * 1024 * 1024;
        printf("speed:%.2f G\n", speed);
	}
	else if (speed > 1024 * 1024)
	{
		unit = "M";
		speed /= 1024 * 1024;
         printf("speed:%.2f M\n", speed);
	}
	else if (speed > 1024)
	{
		unit = "kB";
		speed /= 1024;
        printf("speed:%.2f kb\n", speed);
	}
    else
    {

        printf("speed:%.2f b\n", speed);
    }
 
	
 
	if (dltotal != 0)
	{
		//double progress = (dlnow + resumeByte) / downloadFileLength * 100;
		//printf("\t%.2f%%\tRemaing time:%s\n", progress, timeFormat);
	}
 
	return 0;
}

char *down_file(char *filename)
{
    //static char str[10000000];
    double speed = 0;
    char *progress_data = "* "; 

    FILE* fp = fopen("video.mp4","ab+");
    if(fp == NULL) //文件打开错误，进行下一个文件的下载
    {
        return NULL;
    }

    //curl_easy_setopt(curl, CURLOPT_URL, "http://vjs.zencdn.net/v/oceans.mp4"); //设置下载地址
    curl_easy_setopt(curl, CURLOPT_URL, " http://www.82bt.com/rlink.php?ref=3705652");
   
    //curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);//设置超时时间
   
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//设置写数据的函数
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);//设置写数据的变量

    /*显示下载进度*/
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);  
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);  
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, progress_data);  
    /*获取下载速度*/
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);

    res = curl_easy_perform(curl);//执行下载
   
    printf("res %d\n", res);
    fclose(fp);
    //str[9999999] = '/0';
    if(CURLE_OK != res) return NULL;//判断是否下载成功

    return NULL;
}

int main()
{
    char url[200];
    curl = curl_easy_init();//对curl进行初始化
    char *result;
    while(fgets(url, 200, stdin))
    {
        result = down_file(url);
        if (result)
        {
            puts("Get success!");
        } 
        else 
        {
            puts("Get Error!");
        }

        printf("/nPlease Input a url:");
    }

    curl_easy_cleanup(curl);//释放curl资源

    return 0;
}