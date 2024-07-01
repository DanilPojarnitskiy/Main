#include "os_mem.h"
#include "stdlib.h"

char *Mem = NULL;
mem_handle_t *blocks = NULL;
int SIZE = 0;

int create(int size, int num_pages);
int destroy();
mem_handle_t alloc(int block_size);
int free(mem_handle_t h);
int get_max_block_size();
int get_free_space();
void print_blocks();

int compare(const void *a, const void *b){
    const mem_handle_t *m1 = (const mem_handle_t *)a;
    const mem_handle_t *m2 = (const mem_handle_t *)b;
    return m1->addr - m2->addr;
}

mem_handle_t get_max_block(){
    mem_handle_t max_block = mem_handle_t(0, 0);
    for (int i = 0; i < SIZE; ++i){
        if (Mem[i] == 0){
            int curMax = 0;
            for (int j = i; j < SIZE; ++j){
                if (Mem[j] == 1){
                    i = j;
                    break;
                }
                curMax++;
            }
            if (curMax > max_block.size){
                max_block.size = curMax;
                max_block.addr = i;
            }
        }
    }
    return max_block;
}

void alloc_mem(int addr, int size, int flag){
    for (int i = addr; i < addr + size; ++i){
        Mem[i] = flag;
    }
}

int create(int size, int num_pages){
    if (Mem == NULL && blocks == NULL){
        Mem = (char *)calloc(size, sizeof(char));
        blocks = (mem_handle_t *)malloc(sizeof(mem_handle_t) * size);
        for (int i = 0; i < size; ++i){
            blocks[i].addr = 0;
            blocks[i].size = 0;
        }
        SIZE = size;
        return 1;
    }
    return 0;
}

int destroy(){
    if (Mem != NULL && blocks != NULL){
        free(Mem);
        free(blocks);
        Mem = NULL;
        blocks = NULL;
        return 1;
    }
    return 0;
}

mem_handle_t alloc(int block_size){
    mem_handle_t max_block = get_max_block();
    if (block_size <= max_block.size){
        alloc_mem(max_block.addr, block_size, 1);
        for (int j = 0; j < SIZE; ++j){
            if (blocks[j].addr == 0 && blocks[j].size == 0){
                blocks[j].addr = max_block.addr;
                blocks[j].size = block_size;
                return blocks[j];
            }
        }
    }
    return mem_handle_t(0, 0);
}

int free(mem_handle_t h){
    for (int i = 0; i < SIZE; ++i){
        if (blocks[i] == h){
            alloc_mem(h.addr, h.size, 0);
            blocks[i].addr = 0;
            blocks[i].size = 0;
            return 1;
        }
    }
    return 0;
}

int get_max_block_size(){
    return get_max_block().size;
}

int get_free_space(){
    int count = 0;
    for (int i = 0; i < SIZE; ++i){
        if (Mem[i] == 0){
            count++;
        }
    }
    return count;
}

void print_blocks(){
    int size = 0;
    for (int i = 0; i < SIZE; ++i){
        if (blocks[i].size > 0){
            size++;
        }
    }
    mem_handle_t* tmp = (mem_handle_t*)malloc(sizeof(mem_handle_t) * size);
    int j = 0;
    for (int i = 0; i < SIZE; ++i){
        if (blocks[i].size > 0){
            tmp[j] = blocks[i];
            j++;
        }
    }

    qsort(tmp, size, sizeof(mem_handle_t), compare);
    for (int i = 0; i < size; i++){
        printf("%d %d\n", tmp[i].addr, tmp[i].size);
    }
    free(tmp);
}

void setup_memory_manager(memory_manager_t *mm){
    mm->create = create;
    mm->destroy = destroy;
    mm->alloc = alloc;
    mm->free = free;
    mm->get_max_block_size = get_max_block_size;
    mm->get_free_space = get_free_space;
    mm->print_blocks = print_blocks;
}
