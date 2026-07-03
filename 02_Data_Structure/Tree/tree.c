#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/*图书管理系统（二叉搜索树实现）*/

// 创建节点
TreeNode *Tree_CreateNode(Book *book)
{
    TreeNode *newnode = malloc(sizeof(TreeNode));
    if(newnode == NULL)   return NULL;  // 申请失败

    newnode->book = *book;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

// 插入节点,插入的节点数据为*book
int Tree_IncertNode(TreeNode **root, Book *book)
{
    if(Tree_FindNode(*root, book->id) != NULL) return -1;      // 已存在该书
    
    TreeNode *newnode = Tree_CreateNode(book);
    if(newnode == NULL) return -2;  // 创建失败

    if(*root == NULL)   // 如果一个节点都没有
    {
        (*root) = newnode;
        return 0;
    }

    TreeNode *cur = *root;   // 用于定位当前位置
    TreeNode *curParent = cur;    // 定位当前位置的父节点，即在它下面插入
    
    while (cur != NULL)
    {
        curParent = cur;
        if(book->id < cur->book.id)    cur = cur->left;
        else    cur = cur->right;
    }

    // 插入
    if(book->id < curParent->book.id)   curParent->left = newnode;
    else    curParent->right = newnode;

    return 0;
}

// 根据id查找节点
TreeNode *Tree_FindNode(TreeNode *root, int id)
{
    if(root == NULL)    return NULL;    // 没找到

    if(root->book.id == id)
        return root;
    
    // 根据二叉搜索树，值小的会存在左边，值大的存右边
    if(id < root->book.id)     return Tree_FindNode(root->left, id);
    else    return Tree_FindNode(root->right, id);
}

// 寻找某一节点子树的最大或最小值,1找最小值，2找最大值
TreeNode *Tree_FindExtreme(TreeNode *root, int dir)
{
    if(dir == 1)
    {
        if(root->left == NULL)  return root;
        return Tree_FindExtreme(root->left, 1);
    }
    else if(dir == 2)
    {
        if(root->right == NULL)  return root;
        return Tree_FindExtreme(root->right, 2);
    }
    else
    {
        printf("no direction\n");
        return 0;
    }
        
}

// 根据id删除节点
int Tree_DeleteNode(TreeNode **root, int id)
{
    TreeNode *cur = *root;        // 待删节点
    TreeNode *curParent = NULL;    // 待删节点的父节点
    
    // 查找待删节点和其父节点
    while(cur != NULL && id != cur->book.id) 
    {
        curParent = cur;
        if(id < cur->book.id)     cur = cur->left;
        else if(id > cur->book.id)    cur = cur->right;
    } 
    if(cur == NULL)     return -1;  // 没找到

    if(cur->left == NULL && cur->right == NULL) // 待删节点为叶子
    {
        if(cur == *root)    // 删除的是根节点
            (*root) = NULL;
        else
        {
            if(curParent->left == cur)  curParent->left = NULL;
            else if(curParent->right == cur) curParent->right = NULL;
        }
        free(cur);
    }
    else if(cur->left != NULL && cur->right == NULL) // 待删节点只有左子树
    {
        if(cur == *root)    // 删除的是根节点
            (*root) = cur->left;
        else
        {
            if(curParent->left == cur)  curParent->left = cur->left;
            else if(curParent->right == cur)    curParent->right = cur->left;
        }
        free(cur);
    }
    else if(cur->left == NULL && cur->right != NULL) // 待删节点只有右子树
    {
        if(cur == *root)    // 删除的是根节点
            (*root) = cur->right;
        else
        {
            if(curParent->left == cur)  curParent->left = cur->right;
            else if(curParent->right == cur)    curParent->right = cur->right;
        }
        free(cur);
    }
    // 待删节点有左子树和右子树
    // 找到待删节点的直接前驱，把待删的节点的数据换成前驱的数据，删除前驱
    else if(cur->left != NULL && cur->right != NULL) 
    {
        TreeNode *prev = Tree_FindExtreme(cur->left, 2);   // 找到待删节点的直接前驱
        cur->book = prev->book;     // 修改待删节点的值

        // 前驱一定在左子树，递归删除它。不能传cur，因为它的id已经被改了
        Tree_DeleteNode(&cur->left, prev->book.id); 
    }

    return 0;

}

// 找到对应编号的节点并修改其中的内容
int Tree_ChangeNode(TreeNode *root, int id, float price)
{
    TreeNode *des = Tree_FindNode(root, id);
    if(des == NULL) return -1;  // 没找到

    des->book.price = price;
    return 0;
}

// 中序遍历，前序和后序改变顺序即可
void Tree_Travel(TreeNode *root)
{
    if(root == NULL)    return ;
    Tree_Travel(root->left);
    printf("%d\n", root->book.id);
    Tree_Travel(root->right);
}

// 树中节点总数
int Tree_CountNode(TreeNode *root)
{   
    if(root == NULL)    return 0; 
    int ln = Tree_CountNode(root->left);
    int rn = Tree_CountNode(root->right);
    return ln + rn +1;    
}

// 树高
int Tree_Height(TreeNode *root)
{
    if(root == NULL)    return 0;

    int lh = Tree_Height(root->left);
    int rh = Tree_Height(root->right);

    return (lh > rh ? lh : rh) + 1;     // 算上根节点
}

// 叶子数量
int Tree_CountLeaf(TreeNode *root)
{
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL)
        return 1;
    int ln = Tree_CountLeaf(root->left);
    int rn = Tree_CountLeaf(root->right);

    return ln + rn;
}

// 层序遍历
void Tree_BFSTravel(TreeNode *root)
{
    TreeNode tmp = *root;
    queue *qu = Queue_Init();
    Queue_In(qu, &tmp);  // 根节点入队

    while (!Queue_IsEmpty(qu))
    {
        Queue_Out(qu, &tmp);
        printf("%d\n", tmp.book.id);

        // 出队后把它的左右孩子入队
        if(tmp.left != NULL)
            Queue_In(qu, tmp.left);
        if(tmp.right != NULL)
            Queue_In(qu, tmp.right);
    }

    Queue_Destroy(qu);
}

// 销毁树
void Tree_DestroyTree(TreeNode **root)
{
    if(*root == NULL)   return ;

    Tree_DestroyTree(&(*root)->left);
    Tree_DestroyTree(&(*root)->right);
    free(*root);
}

/* 层序遍历用的队列 */
// 初始化队列
queue *Queue_Init()
{
    queue *que = malloc(sizeof(queue));
    if(que == NULL)
    {
        return NULL;
    }
    que->front = que->rear = 0;

    return que;
}

// 队列为空返回真
int Queue_IsEmpty(queue *qu)
{
    return qu->rear == qu->front;
}

// 队列为满返回真
int Queue_IsFull(queue *qu)
{
    return (qu->rear + 1) % QUE_MAXSIZE == qu->front;
}

// 入队
int Queue_In(queue *qu, TreeNode *tree)
{
    if(Queue_IsFull(qu))
        return -1;
    
    qu->rear = (qu->rear + 1) % QUE_MAXSIZE;
    qu->tree[qu->rear] = *tree;

    return 0;
}

// 出队
int Queue_Out(queue *qu, TreeNode *tree)
{
    if(Queue_IsEmpty(qu))
        return -1;
    
    qu->front = (qu->front + 1) % QUE_MAXSIZE;
    *tree = qu->tree[qu->front];

    return 0;
}

void Queue_Destroy(queue *qu)
{
    free(qu);
}