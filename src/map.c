#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "uthash.h"
//#include <unistd.h>

#define MAP_MALLOC(a) (malloc(a))

typedef struct _map_node
{
    uint32_t id;
    uint32_t x;
    uint32_t y;
    UT_hash_handle hh;
}MAP_NODE;


typedef struct _MAP_CTRL
{
    MAP_NODE *map_node;
}MAP_CTRL;

static MAP_CTRL map_ctrl;


int32_t map_find_node(uint32_t id,  MAP_NODE *out)
{
    HASH_FIND(hh, map_ctrl.map_node, &id, sizeof(uint32_t), out);
    if (out)
    {
        printf("##NODE [%d %d %d] \n", out->id, out->x, out->y);  
        return 0;
    }

    printf("%s FAILED!\n", __FUNCTION__);
    
    return 1;
}


int32_t map_add_node(uint32_t id, uint32_t x, uint32_t y)
{
    MAP_NODE *p_map_node = NULL;
    MAP_NODE *out = NULL;
    p_map_node = MAP_MALLOC(sizeof(MAP_NODE));
    if (p_map_node)
    {  
        HASH_FIND(hh,  map_ctrl.map_node, &id, sizeof(uint32_t), out);
        if (!out)
        {
            p_map_node->id = id;
            p_map_node->x = x;
            p_map_node->y = y;
            //HASH_FIND(hh, map_ctrl.map_node,);
            HASH_ADD(hh, map_ctrl.map_node, id, sizeof(uint32_t), p_map_node);
            return 0;
        }
        else 
        {
            printf("## MAP NODE[%d] ADD FAILED!\n", out->id);
        }

    }
    
    return 1;
}

void map_print()
{
    MAP_NODE *el = NULL;
    MAP_NODE *tmp = NULL;

    printf("## MAP NODE COUNT %d\n", HASH_COUNT(map_ctrl.map_node));

    HASH_ITER(hh, map_ctrl.map_node, el, tmp)
    {
        printf("## ID %u - [%u, %u]\n", el->id, el->x, el->y);
    }
}


void map_clear()
{
    HASH_CLEAR(hh, map_ctrl.map_node);
}



void nop_fun(uint32_t val)
{

    uint32_t key_id = 0;
    while (1)
    {
        if (key_id > val)
        {

            break;
        }
        key_id++;  
        //printf("##key_id %d %d\n", key_id, val);
    }

}

int main()
{
    int32_t ret = 0;
    int cnt = 10;
    MAP_NODE *out = NULL;
    while (cnt--)
    {
        map_add_node(cnt, 2000, 1000);
    }

    //map_add_node(5, 2000, 1000);
    //map_print(); 

    ret = map_find_node(5, out);
    if (0 == ret && out)
    {
         printf("##NODE [%d %d %d] \n", out->id, out->x, out->y);  
    }

    //map_clear();
    //map_print(); 












    clock_t start, end;
    double t_comsume = 0;
    uint32_t key = 999999;
    //clock函数的时间精度是毫秒
    start = clock();

    nop_fun(999999);
    //HASH_FIND(hh, map_ctrl.map_node, &key, sizeof(uint32_t), out);
    //usleep(100 * 1000);
    end = clock();
    t_comsume = (end - start);
    //printf("## %f %d %d\n",  t_comsume, CLOCKS_PER_SEC, out->x);
    printf("##consume time %f  %f\n", t_comsume, t_comsume / CLOCKS_PER_SEC);


    struct timeval tv1;
    struct timeval tv2;
    //gettimeofday微秒精度
    //gettimeofday(&tv1,NULL);
    //nop_fun(99999);
    //gettimeofday(&tv2,NULL);
    //printf("###consume time %lf  %lf\n", tv1.tv_sec - tv2.tv_sec, tv1.tv_usec - tv2.tv_usec);
 
    return 0;
}




