#ifndef DATASTRUCT2_COMMON_H
#define DATASTRUCT2_COMMON_H

typedef struct {//边集数组
    int begin;//边的起点编号(顶点1)
    int end;  //边的终点编号(顶点2)
    int weight;//边的权值
}EdgeSet;
#endif //DATASTRUCT2_COMMON_H