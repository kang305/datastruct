#include<stdio.h>      // 包含标准输入输出库，用于 printf
#include<stdlib.h>     // 包含标准库，用于 malloc、free 等
#include "RBTree.h"    // 包含红黑树自定义头文件，定义了结构体和宏（如 RED, BLACK, KeyType 等）

// =================== 左旋操作 ===================
/* 将节点 x 进行左旋，更新左、右、父节点的指向关系
 *     px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           /  \
 *  lx   y                          x   ry
 *     /   \                      /  \
 *    ly   ry                    lx  ly
*/
static void leftRotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;          //记录 x 的右孩子 y（旋转后的新根）
    x->right = y->left;            //将 y 的左子树挂接到 x 的右子树上
    if (y->left) {                 //如果 y 的左子树存在（非空）
        y->left->parent = x;       //更新该左子树的父节点指针指向 x
    }
    y->parent = x->parent;         //将 y 的父节点设为 x 原来的父节点
    if (x->parent) {               //如果 x 不是根节点（父节点存在）
        if (x->parent->left == x) { //判断 x 是其父节点的左孩子还是右孩子
            x->parent->left = y;    //若是左孩子，则将父节点的左指针指向 y
        } else {
            x->parent->right = y;   //若是右孩子，则将父节点的右指针指向 y
        }
    } else {                        //否则 x 是原来的根节点
        tree->root = y;             //更新树的根节点为 y
    }
    y->left = x;                    //将 x 设为 y 的左孩子
    x->parent = y;                  //更新 x 的父节点为 y，完成左旋
}

// =================== 右旋操作 ===================
/* 将节点 y 进行右旋，更新左、右、父节点的指向关系
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 */
static void rightRotate(RBTree* tree, RBNode* y) {
    RBNode* x = y->left;           //记录 y 的左孩子 x（旋转后的新根）
    y->left = x->right;            //将 x 的右子树挂接到 y 的左子树上
    if (x->right) {                //如果 x 的右子树存在（非空）
        x->right->parent = y;      //更新该右子树的父节点指针指向 y
    }
    x->parent = y->parent;         //将 x 的父节点设为 y 原来的父节点
    if (y->parent) {               //如果 y 不是根节点
        if (y->parent->left == y) { //判断 y 是其父节点的左孩子还是右孩子
            y->parent->left = x;    //若是左孩子，则将父节点的左指针指向 x
        } else {
            y->parent->right = x;   //若是右孩子，则将父节点的右指针指向 x
        }
    } else {                        //否则 y 是原来的根节点
        tree->root = x;             //更新树的根节点为 x
    }
    x->right = y;                   //将 y 设为 x 的右孩子
    y->parent = x;                  //更新 y 的父节点为 x，完成右旋
}

// =================== 插入修正函数 ===================
/* 插入新节点后，修复可能违反的红黑树性质
 * node 是刚插入的红色节点，可能是导致“红-红”冲突的节点
 * 1. 如果父节点是黑色，直接结束（不会违反性质）
 * 2. 如果父节点是红色，则处理“红-红”冲突：
 *   2.1 叔叔节点是红色 -> 重新着色（父、叔变黑，祖父变红），并将祖父作为新当前节点向上继续检查
 *   2.2 叔叔节点是黑色或不存在 -> 根据结构分为 LL、RR、LR、RL 四种情况进行旋转和变色
 */
static void insertFixUp(RBTree *tree, RBNode *node) {
    RBNode *parent, *grandparent;  // 声明父节点、祖父节点指针
    RBNode *uncle;                 // 声明叔叔节点指针
    RBNode *tmp;                   // 临时指针，用于 LR/RL 型中交换父子角色

    parent = node->parent;         // 获取当前节点的父节点
    // 循环条件：父节点存在且为红色（即发生了红-红冲突）
    while (parent && parent->color == RED) {
        grandparent = parent->parent;  // 祖父节点一定存在（父为红色，根必须为黑）
        // 根据父节点是祖父的左孩子还是右孩子，确定叔叔节点位置
        if (parent == grandparent->left) {
            uncle = grandparent->right;   // 叔叔节点在另一侧
        } else {
            uncle = grandparent->left;
        }

        // 情况1：叔叔节点存在且为红色 -> 重新着色
        if (uncle && uncle->color == RED) {
            uncle->color = BLACK;         // 叔叔染黑
            parent->color = BLACK;        // 父亲染黑
            grandparent->color = RED;     // 祖父染红
            node = grandparent;           // 将祖父作为新的待调整节点
            parent = node->parent;        // 更新父指针
            continue;                     // 继续向上检查（可能祖父变为红色后与它的父节点冲突）
        }

        // 情况2/3/4：叔叔为黑色或不存在，需要进行旋转并变色
        // 父节点是祖父的左孩子（L）
        if (grandparent->left == parent) {
            if (parent->right == node) {   // LR型：插入节点是父的右孩子
                leftRotate(tree, parent);   // 先对父节点左旋，变为 LL 型
                tmp = parent;               // 交换 parent 和 node 的指向，使 parent 重新指向原来的 node
                parent = node;
                node = tmp;                 // 现在 node 变成了之前的 parent（即新插入节点依然在下方）
            }
            // 现在统一处理 LL 型
            rightRotate(tree, grandparent); // 对祖父右旋
            grandparent->color = RED;       // 祖父（旋转后成为子节点）染红
            parent->color = BLACK;          // 父节点（旋转后成为局部根）染黑
        }
        //父节点是祖父的右孩子(R)
        else {
            if (parent->left == node) {    // RL型：插入节点是父的左孩子
                rightRotate(tree, parent);  // 先对父节点右旋，变为 RR 型
                tmp = parent;               // 交换 parent 和 node 指向
                parent = node;
                node = tmp;
            }
            // 现在统一处理 RR 型
            leftRotate(tree, grandparent);  // 对祖父左旋
            grandparent->color = RED;       // 祖父染红
            parent->color = BLACK;          // 父节点染黑
        }
    }
    // 循环结束后，确保整棵树的根节点一定是黑色
    tree->root->color = BLACK;
}

// =================== 创建新节点 ===================
static RBNode* createRBNode(KeyType key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode)); // 动态分配节点内存
    node->key = key;                // 设置键值
    node->color = RED;              // 新节点默认颜色为红色（插入规则）
    node->left = node->right = node->parent = NULL; // 左右子节点和父节点初始化为 NULL
    return node;                    // 返回新节点指针
}

// =================== 插入函数 ===================
void insertRBTree(RBTree *tree, KeyType key) {
    // 1. 创建一个红色节点
    RBNode *node = createRBNode(key);
    // 2. 根据二叉搜索树的规则找到插入位置
    RBNode *cur = tree->root;       // 当前遍历节点
    RBNode *prev = NULL;            // 记录父节点
    while (cur) {                   // 循环直到 cur 为空（找到叶子位置）
        prev = cur;                 // 更新父节点
        if (key < cur->key) {       // 待插入关键字小于当前节点键值
            cur = cur->left;        // 进入左子树
        } else if (key > cur->key) { // 大于当前键值
            cur = cur->right;       // 进入右子树
        } else {                    // 键值相等，不允许重复插入
            printf("Key %d have exist!\n", key);
            free(node);             // 释放刚创建的节点内存
            return;                 // 直接返回
        }
    }
    // 3. 将新节点挂接到父节点下方
    node->parent = prev;            // 设置新节点的父节点
    if (prev) {                     // 如果树非空（prev 不为 NULL）
        if (key < prev->key)        // 根据键值大小决定插入为左孩子还是右孩子
            prev->left = node;
        else
            prev->right = node;
    } else {                        // 如果树为空，新节点就是根节点
        tree->root = node;
    }
    // 4. 调用修复函数，调整可能违反的红黑树性质
    insertFixUp(tree, node);
}

// =================== 创建红黑树 ===================
RBTree * createRBTree() {
    RBTree *tree = malloc(sizeof(RBTree)); // 分配树结构体内存
    tree->count = 0;                       // 初始节点计数为 0
    tree->root = NULL;                     // 根节点初始为空
    return tree;                           // 返回树指针
}


//node: 当前节点 key: 父节点的键值，dir: 方向（0表示根，-1左孩子，1右孩子）
void printRBTree(const RBNode *node, int key, int dir) {
    if (node) {
        if (dir == 0) {
            printf("%2d[B] is root\n", node->key);
        } else {
            printf("%2d[%c] is %2d's %s\n", node->key,
                    node->color == RED ? 'R' : 'B', key,
                    (dir == 1) ? "right child" : "left child");
        }
        //递归打印
        printRBTree(node->left, node->key, -1);
        printRBTree(node->right, node->key, 1);
    }
}

// =================== 查找节点 ===================
RBNode *searchRBNode(const RBTree *tree, KeyType key) {
    RBNode *node = tree->root;  // 从根节点开始查找
    while (node) {              // 循环直到节点为空
        if (key < node->key)    // 小于当前节点键值，去左子树找
            node = node->left;
        else if (key > node->key) // 大于当前节点键值，去右子树找
            node = node->right;
        else {
            //相等，找到目标节点，直接返回
            return node;
        }
    }
    return NULL; //未找到，返回 NULL
}



// =================== 删除修正函数 ===================
static void deleteFixUp(RBTree *tree, RBNode *x, RBNode *parent) {
    RBNode *w;  // 兄弟节点
    // 当x不是根节点，并且x为黑色（或为NULL叶子视为黑色）时循环
    while (tree->root != x && (x == NULL || x->color == BLACK)) {
        if (parent->left == x) {    // x是父节点的左孩子
            w = parent->right;      // 兄弟 w 是父的右孩子
            // 情况1：兄弟 w 是红色
            if (w->color == RED) {
                w->color = BLACK;               // 兄弟染黑
                parent->color = RED;            // 父节点染红
                leftRotate(tree, parent);       // 对父节点左旋
                w = parent->right;              // 更新兄弟 w（旋转后新的兄弟）
            }
            // 情况2：兄弟 w 的两个孩子都是黑色（或为NULL视为黑）
            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;                 // 将兄弟染红
                x = parent;                     // 将父节点作为新的 x 继续向上调整
                parent = x->parent;             // 更新 parent 指针
            } else {
                // 情况3：兄弟 w 是黑色，且 w 的右孩子为黑色，左孩子为红色（即异向红）
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK; // 红色左孩子染黑（安全性检查）
                    w->color = RED;                     // w 染红
                    rightRotate(tree, w);               // 对 w 右旋
                    w = parent->right;                  // 更新兄弟 w
                }
                // 情况4：兄弟 w 是黑色，且 w 的右孩子为红色（同向红，或经过情况3转换后）
                w->color = parent->color;   // 兄弟颜色继承父节点颜色
                parent->color = BLACK;      // 父节点染黑
                if (w->right) w->right->color = BLACK; // 红色右孩子染黑（保证黑色数量）
                leftRotate(tree, parent);   // 对父节点左旋
                x = tree->root;             // 设置 x 为根，准备退出循环
                break;
            }


        } else {   // 对称情况：x 是父节点的右孩子
            w = parent->left;               // 兄弟 w 是父的左孩子
            if (w->color == RED) {          // 情况1：兄弟红
                w->color = BLACK;
                parent->color = RED;
                rightRotate(tree, parent);  // 对父节点右旋
                w = parent->left;           // 更新兄弟
            }
            // 情况2：兄弟的两个孩子都是黑色
            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = parent;
                parent = x->parent;
            } else {
                // 情况3：兄弟黑，左孩子黑，右孩子红（异向红）
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = parent->left;
                }
                // 情况4：兄弟黑，左孩子红（同向红）
                w->color = parent->color;
                parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rightRotate(tree, parent);
                x = tree->root;
                break;
            }
        }
    }
    if (x) x->color = BLACK; // 如果x非空，确保其为黑色（弥补可能缺少的黑色）
}

// =================== 删除节点内部函数 ===================
/* 从红黑树中删除指定节点node */
static void deleteRBNode(RBTree* tree, RBNode *node) {
    RBNode *y; // 真正要删除的节点
    RBNode *x; // y的孩子节点，用于替换y的位置

    // 1. 确定实际要摘掉的节点y
    if (node->left == NULL || node->right == NULL) {
        y=node;   //如果node至多有一个孩子，直接删除node
    } else {
        //有两个孩子，找node的中序后继节点（右子树的最左节点）
        y = node->right;
        while (y->left != NULL) {
            y = y->left;
        }
    }

    // 2. 确定y的孩子x(用于接替y的位置)
    if (y->left!=NULL) {//node至多有一个孩子
        x = y->left;
    } else {
        x = y->right;
    }

    // 3. 将x与y的父节点连接，把y摘除
    if (x != NULL) {
        x->parent = y->parent;   // 设置x的父节点
    }
    if (y->parent == NULL) {     //y是根节点
        tree->root = x;          //根直接变成 x
    } else if (y->parent->left == y) { //y是父的左孩子
        y->parent->left = x;
    } else {                     //y是父的右孩子
        y->parent->right = x;
    }
    // 4. 如果y是后继节点,右子树最左（即不是要删除的原始 node），将y的键值复制给 node
    if (y!=node) {
        node->key = y->key;      //将node变为y,删除原位置的y
    }

    // 5. 如果被删除节点y是黑色(黑高不相等)，需要调用修正函数恢复红黑树性质
    if (y->color == BLACK) {
        RBNode *parent = y->parent; // 记录 y 原来的父节点（注意 y 可能已被摘除，parent 可能已变化）
        deleteFixUp(tree, x, parent);
    }

    // 6. 释放被删除节点的内存
    free(y);
}


// =================== 对外删除接口 ===================
void deleteRBTree(RBTree *tree, KeyType key) {
    RBNode *node = searchRBNode(tree, key); // 先查找待删除节点
    if (node) {                             // 如果找到
        deleteRBNode(tree, node);           // 调用内部删除函数
    }
}