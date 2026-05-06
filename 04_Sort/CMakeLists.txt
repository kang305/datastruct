add_executable(01_InsertSort 01_InsertSort/main.c
        ./sortHelper.c ./sortHelper.h
        01_InsertSort/insertSort.c
        01_InsertSort/insertSort.h)

add_executable(02_SwapSort 02_SwapSort/main.c
        02_SwapSort/bubbleSort.c 02_SwapSort/bubbleSort.h
        ./sortHelper.c ./sortHelper.h
        02_SwapSort/quickSort.c
        02_SwapSort/quickSort.h
)

add_executable(03_HeapSort 03_HeapSort/main.c
03_HeapSort/heapSort.c 03_HeapSort/heapSort.h
        03_HeapSort/miniHeap.c 03_HeapSort/miniHeap.h
        ./sortHelper.c ./sortHelper.h
)
add_executable(04_MergeSort 04_MergeSort/main.c 04_MergeSort/mergeSort.c 04_MergeSort/mergeSort.h
        ./sortHelper.c ./sortHelper.h
)