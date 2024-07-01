#include "os_mem.h"

int main(){

    memory_manager_t mm;
    setup_memory_manager(&mm);

    mm.create(150,1); //expected: 1, passed
    mm.alloc(1); //expected: mem_handle_t(0,1), passed
    mm.alloc(2); //expected: mem_handle_t(1,2), passed
    mm.alloc(3); //expected: mem_handle_t(3,3), passed
    mm.print_blocks();
    mm.alloc(4); //expected: mem_handle_t(6,4), passed
    mm.alloc(100); //expected: mem_handle_t(10,100), passed
    mm.free(mem_handle_t(0,1)); //expected: 1, passed
    mm.free(mem_handle_t(1,2)); //expected: 1, passed
    mm.free(mem_handle_t(3,3)); //expected: 1, passed
    mm.alloc(20); //expected: mem_handle_t(110,20), passed
    mm.alloc(100); //expected: mem_handle_t(0,0), passed
    mm.alloc(1); //expected: mem_handle_t(130,1), passed
    mm.get_max_block_size(); //expected: 19, passed
    mm.get_free_space(); //expected: 25, passed
    mm.free(mem_handle_t(130, 1)); //expected: 1, passed
    mm.free(mem_handle_t(110,20)); //expected: 1, passed
    mm.free(mem_handle_t(6,4)); //expected: 1, passed
    mm.free(mem_handle_t(10,100)); //expected: 1, passed
    mm.free(mem_handle_t(0,1)); //expected: 0, passed
    mm.free(mem_handle_t(10,100)); //expected: 0, passed
    mm.alloc(20); //expected: mem_handle_t(0,20), passed
    mm.alloc(1); //expected: mem_handle_t(20,1), passed
    mm.get_max_block_size(); //expected: 129, passed
    mm.get_free_space(); //expected: 129, passed
    mm.print_blocks();
    mm.free(mem_handle_t(0,20)); //expected: 1, passed
    mm.free(mem_handle_t(20,1)); //expected: 1, passed
    mm.free(mem_handle_t(0,1)); //expected: 0, passed
    mm.get_max_block_size(); //expected: 150, passed
    mm.get_free_space(); //expected: 150, passed
    mm.print_blocks();
    mm.destroy(); //expected: 1, passed

    return 0;
}