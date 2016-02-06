#include <stdint.h>
#include <rcp/rdp.h>

void run_dpc(const void * list, uint32_t len) {
    uint32_t end = (uint32_t)list+len;
    __builtin_memcpy((void*)DPC_START, &list, 4);
    __builtin_memcpy((void*)DPC_END, &end, 4);
    //*DPC_START = (uint32_t)list;
    //*DPC_END = (uint32_t)list + len;
}
