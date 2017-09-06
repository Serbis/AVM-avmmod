#include "../includes/mem.h"


int8_t heap[HEAP_SIZE];

typedef struct {
    int32_t start;
    int32_t size;
} Block;

Node *fbt = NULL;
int32_t pCount = 0; //Количество выданных укахателей

void xmem_init() {
    Block *b0 = (Block*) malloc(sizeof(Block));
    b0->start = 0;
    b0->size = HEAP_SIZE;

    LIST_Shift(&fbt, (int) b0);
}

//int32_t btSize = 1;
//int32_t bt[1][3];

void *xmalloc (uint32_t __size) {
    //printf("-------------------------------------\n");
    //printf("Starting allocate size %d.\n", __size);

    int32_t btSize = LIST_Length(fbt); //Размер списка блоков

    for (int i = 0; i < btSize; i++) {
        Block *block = (Block*) LIST_Get(fbt, i);

        if (block->size >= __size + 8) {
            int32_t *pos = (int32_t*) &heap[block->start]; //Запись относительной позиции указателя внутри хипа
            *pos = block->start;

            int32_t *s = (int32_t*) &heap[block->start + 4]; //Запись размера указателя в начало блока
            *s = __size;

            void * ptr = &heap[block->start + 8];
            block->start = block->start + __size + 8;
            block->size = block->size - (__size + 8);
            if (block-> size == 0)
                LIST_Remove(&fbt, i);

            pCount++;
            return ptr;
        }
    }

    return NULL;
}

void xfree (void *__ptr) {
    int32_t bs = *((int *) (((int) __ptr) - 4)); //Размер указатьеля
    int32_t bp = *((int *) (((int) __ptr) - 8)); //Относительная позиция указатедя внутри хипа


    //Попытаться найти смежых соседей слева и справа от предполагаемого блока
    int32_t btSize = LIST_Length(fbt); //Размер списка блоков
    int32_t leftAdjIndex = -1; //Индекс смеждного блока с левой стороны
    int32_t rightAdjIndex = -1; //Иедекс смежного блока с правой стороны
    for (int i = 0; i < btSize; i++) {
        Block *block = (Block *) LIST_Get(fbt, i);
        if (block->start + block->size == bp) {
            leftAdjIndex = i;
        }
        if(block->start == bp + bs + 8) {
            rightAdjIndex = i;
        }
    }

    if (leftAdjIndex >= 0 && rightAdjIndex >= 0) { //Если есть левый смежный и правый смежный +
        Block *leftBlock = (Block *) LIST_Get(fbt, leftAdjIndex); //Увеличить размер левого смежного до резмеров правого семежного, а последний удалить
        Block *rightBlock = (Block *) LIST_Get(fbt, rightAdjIndex);
        leftBlock->size = rightBlock->size + leftBlock ->size + bs + 8;
        LIST_Remove(&fbt, rightAdjIndex);
    } else if (leftAdjIndex >= 0 && rightAdjIndex == -1) { //Если естьтолько левый смежный +
        Block *leftBlock = (Block *) LIST_Get(fbt, leftAdjIndex); //Увеличить размер левого смежного блока до размеров предполагаемого блока
        leftBlock->size = leftBlock->size + bs + 8;
    } else if (leftAdjIndex == -1 && rightAdjIndex >= 0) { //Если есть только правый смежный
        Block *rightBlock = (Block *) LIST_Get(fbt, rightAdjIndex); //Увеличить размер правого блока до уровня предполагаемого блока
        rightBlock->start = bp;
        rightBlock->size = rightBlock->size + bs;
    } else { //Если смежных блоков нет +
        Block *newBlock = (Block*) malloc(sizeof(Block)); //Создать новый блок
        newBlock->start = bp;
        newBlock->size = bs + 8;
        LIST_Shift(&fbt, (int) newBlock);
    }

    pCount--;
}

/**
 * Выводит hex дамп хипа
 */
void xdump() {
    uint8_t c = 0;
    for (int i = 0; i < HEAP_SIZE; i++) {
        printf("%02X ", (uint8_t) heap[i]);
        c++;
        if (c > 24) {
            c = 0;
            printf("\n");
        }
    }
    printf("\n");
}

/**
 * Выводит матрицу свободных/занятых байтов
 */
void xmap() {
    int32_t btSize = LIST_Length(fbt); //Размер списка блоков
    uint8_t c = 0;

    for (int i = 0; i < HEAP_SIZE; i++) {
        uint8_t free = 0;
        for (int j = 0; j < btSize; j++) {
            Block *block = (Block*) LIST_Get(fbt, j);
            if (i >= block->start && i < block->start + block->size) {
                free = 1;
                break;
            }
        }
        if (free == 0)
            printf("XX ");
        else
            printf("OO ");

        c++;
        if (c > 24) {
            c = 0;
            printf("\n");
        }
    }

    printf("\n");
}

/**
 * Выводит дамп свободных блоков
 */
void xbmap() {
    int32_t btSize = LIST_Length(fbt); //Размер списка блоков
    for (int i = 0; i < btSize; i++) {
        Block *block = (Block*) LIST_Get(fbt, i);
        printf("%d-%d:%d\n", block->start, block->start + block->size, block->size);
    }

}

/**
 * Возвращает объем свободной мапяти внутри хипа
 */
int32_t xfreeMem() {
    int32_t btSize = LIST_Length(fbt); //Размер списка блоков
    int32_t size = 0;

    for (int i = 0; i < btSize; i++) {
        Block *block = (Block*) LIST_Get(fbt, i);
        size += block->size;
    }

    return size;
}

/**
 * Возвращает размер таблицы блоков
 */
int32_t xtableSize() {
    int32_t btSize = LIST_Length(fbt); //Размер списка блоков

    return (btSize * 8) + (btSize * 8); // (Количетсво элеметров в таблице * размер структуры Block) + (Количетсво элеметров в таблице * размер структуры Node)
}

/**
 * Возвращает размер метаиннформации внутри хипа
 * (метки относитльеного адреса и размера указетеля)
 */
int32_t xmetaSize() {
    return pCount * 8; //Количество выданных указтелей * размер метаблока
}
