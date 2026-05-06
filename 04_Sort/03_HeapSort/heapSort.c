
#include "heapSort.h"


void MiniHeapSort(SortTable *table) {
    MiniHeap *heap = createMiniHeap(table->length);
    for (int i = 0; i < table->length; ++i) {
        m_inserMiniHeap(heap, table->data[i].key);
    }
    for (int i = 0; i < table->length; ++i) {
        table->data[i].key = m_extractMiniHeap(heap);
    }
    releaseMiniHeap(heap);
}
