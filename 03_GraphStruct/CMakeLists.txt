add_executable(01_MatrixGraph 01_MatrixGraph/main.c 01_MatrixGraph/matrixGraph.c 01_MatrixGraph/matrixGraph.h)
add_executable(02_AdjacencyList 02_AdjacencyList/main.c 02_AdjacencyList/adjacencyList.c 02_AdjacencyList/adjacencyList.h)
add_executable(03_CrossLinkGraph 03_CrossLinkedGraph/main.c 03_CrossLinkedGraph/crossLinkGraph.c 03_CrossLinkedGraph/crossLinkGraph.h)
add_executable(04_adjacencyMultiList 04_AdjacenyMultiList/main.c 04_AdjacenyMultiList/adjacencyMultiList.c 04_AdjacenyMultiList/adjacencyMultiList.h)

add_executable(05_MiniTree 05_MinTree/main.c 05_MinTree/Kruskal.c
        05_MinTree/Kruskal.h 01_MatrixGraph/matrixGraph.h
        01_MatrixGraph/matrixGraph.c
        05_MinTree/common.h 05_MinTree/Prim.c 05_MinTree/Prim.h)

add_executable(06_ShortPath 06_ShortPath/main.c 06_ShortPath/DijkstraShortPath.c 06_ShortPath/DijkstraShortPath.h
        01_MatrixGraph/matrixGraph.c 01_MatrixGraph/matrixGraph.h)

add_executable(07_TopologicalSort 07_TopologicalSort/main.c 07_TopologicalSort/topologicalSort.c 07_TopologicalSort/topologicalSort.h
        02_AdjacencyList/adjacencyList.h 02_AdjacencyList/adjacencyList.c)

add_executable(08_KeyPath 08_KeyPath/main.c
        08_KeyPath/keyPath.c
        08_KeyPath/keyPath.h
02_AdjacencyList/adjacencyList.c 02_AdjacencyList/adjacencyList.h)