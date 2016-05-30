#include <stddef.h>
#include <rcp/rdp.h>

/* Assumes that the caller has already made the necessary checks against the
 * DP_STATUS register.
 */
void run_dpc(const void *list, size_t len) {
   const void *end = list + len;
    __builtin_memcpy((void*)DPC_START, &list, 4);
    __builtin_memcpy((void*)DPC_END, &end, 4);
    //*DPC_START = (uint32_t)list;
    //*DPC_END = end;
}
