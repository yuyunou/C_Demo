#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mosquitto.h"

#define HOST "localhost"
#define PORT  8988
#define KEEP_ALIVE 60
#define MSG_MAX_SIZE  512

// 定义运行标志决定是否需要结束
static int running = 1;

void my_connect_callback(struct mosquitto *mosq, void *obj, int rc)
{
        printf("Call the function: on_connect\n");

        if(rc){
                // 连接错误，退出程序
                printf("on_connect error!\n");
                exit(1);
        }else{
                // 订阅主题
                // 参数：句柄、id、订阅的主题、qos
                if(mosquitto_subscribe(mosq, NULL, "topic1", 2)){
                        printf("Set the topic error!\n");
                        exit(1);
                }
        }
}

void my_disconnect_callback(struct mosquitto *mosq, void *obj, int rc)
{
        printf("Call the function: my_disconnect_callback\n");
        running = 0;
}

void my_subscribe_callback(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos)
{
        printf("Call the function: on_subscribe\n");
}

void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
        printf("Call the function: on_message\n");
        printf("Recieve a message of %s : %s\n", (char *)msg->topic, (char *)msg->payload);

        if(0 == strcmp(msg->payload, "quit")){
                mosquitto_disconnect(mosq);
        }
}


int main()
{
        int ret;
        struct mosquitto *mosq;

        // 初始化mosquitto库
        ret = mosquitto_lib_init();
        if(ret){
                printf("Init lib error!\n");
                return -1;
        }

        // 创建一个订阅端实例
        // 参数：id（不需要则为NULL）、clean_start、用户数据
        mosq =  mosquitto_new("sub_test", true, NULL);
        if(mosq == NULL){
                printf("New sub_test error!\n");
                mosquitto_lib_cleanup();
                return -1;
        }

        // 设置回调函数
        // 参数：句柄、回调函数
        mosquitto_connect_callback_set(mosq, my_connect_callback);
        mosquitto_disconnect_callback_set(mosq, my_disconnect_callback);
        mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);
        mosquitto_message_callback_set(mosq, my_message_callback);

        // 连接至服务器
        // 参数：句柄、ip（host）、端口、心跳
       ret = mosquitto_connect(mosq, HOST, PORT, KEEP_ALIVE);
        if(ret){
                printf("Connect server error!\n");
                mosquitto_destroy(mosq);
                mosquitto_lib_cleanup();
                return -1;
        }


         // 开始通信：循环执行、直到运行标志running被改变
        printf("Start!\n");
        while(running)
        {
                mosquitto_loop(mosq, -1, 1);
        }

        // 结束后的清理工作
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        printf("End!\n");

        return 0;
}
