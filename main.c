//#inc3ude "libs/avm/includes/avm.h"
#include "libs/avm/includes/mem.h"

int main(int argc, char** argv)
{
    xmem_init();

    printf("Free memory: %d\n", xfreeMem());
    printf("===============================\n");

    int32_t *x0 = (int32_t*) xmalloc(4);
    *x0 = 0x11111111;

    printf("Free memory: %d\n", xfreeMem());
    printf("===============================\n");
    int32_t *x1 = (int32_t*) xmalloc(4);
    *x1 = 0x22222222;

    printf("Free memory: %d\n", xfreeMem());
    printf("===============================\n");
    int32_t *x2 = (int32_t*) xmalloc(4);
    *x2 = 0x33333333;

    char *str = (char*) xmalloc(5);
    str[0] = 'a';
    str[1] = 'a';
    str[2] = 'a';
    str[3] = 'a';
    str[4] = 'a';

    printf("===============================\n");


    //*str = 0x11111111;

    //char *str = (char*) xmalloc(10);
    //str[1] = 'b';
    printf("--------------------------- 1\n");

    xdump();
    xmap();
    xbmap();
    printf("Free memory: %d\n", xfreeMem());
    printf("Table size: %d\n", xtableSize());
    printf("Meta size: %d\n", xmetaSize());
    printf("Total service info size: %d\n", xtableSize() + xmetaSize());


    printf("--------------------------- 2\n");

    xfree (x0);
    xdump();
    xmap();
    xbmap();
    printf("Free memory: %d\n", xfreeMem());
    printf("Table size: %d\n", xtableSize());
    printf("Meta size: %d\n", xmetaSize());
    printf("Total service info size: %d\n", xtableSize() + xmetaSize());


    printf("--------------------------- 3\n");


    xfree (x1);
    xdump();
    xmap();
    xbmap();
    printf("Free memory: %d\n", xfreeMem());
    printf("Table size: %d\n", xtableSize());
    printf("Meta size: %d\n", xmetaSize());
    printf("Total service info size: %d\n", xtableSize() + xmetaSize());


    printf("--------------------------- 4\n");

    xfree (x2);
    xdump();
    xmap();
    xbmap();
    printf("Free memory: %d\n", xfreeMem());
    printf("Table size: %d\n", xtableSize());
    printf("Meta size: %d\n", xmetaSize());
    printf("Total service info size: %d\n", xtableSize() + xmetaSize());

    printf("--------------------------- 4\n");

    xfree (str);
    xdump();
    xmap();
    xbmap();
    printf("Free memory: %d\n", xfreeMem());
    printf("Table size: %d\n", xtableSize());
    printf("Meta size: %d\n", xmetaSize());
    printf("Total service info size: %d\n", xtableSize() + xmetaSize());

    //xfree (x1);
    //xfree (x2);
    //xfree (str);
    //xmalloc(4);
    //xmalloc(4);
    //AVM_Run("/home/serbis/tmp/fft.avmb", "bbb");

    return 0;
}

