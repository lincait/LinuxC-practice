#ifndef TREE_H__
#define TREE_H__

#define QUE_MAXSIZE  10

typedef struct Book
{
    int id;         // 书编号
    char name[50];  // 书名
    float price;    // 书价格
}Book;

typedef struct TreeNode
{
    Book book;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

// 用于层序遍历的队列
typedef struct sqqueue
{
    TreeNode tree[QUE_MAXSIZE];    
    int front;
    int rear;
}queue;

TreeNode *Tree_CreateNode(Book *book);
int Tree_IncertNode(TreeNode **root, Book *book);
TreeNode *Tree_FindNode(TreeNode *root, int id);
TreeNode *Tree_FindExtreme(TreeNode *root, int dir);
int Tree_DeleteNode(TreeNode **root, int id);
int Tree_ChangeNode(TreeNode *root, int id, float price);
void Tree_Travel(TreeNode *root);
int Tree_CountNode(TreeNode *root);
int Tree_Height(TreeNode *root);
int Tree_CountLeaf(TreeNode *root);
void Tree_BFSTravel(TreeNode *root);
void Tree_DestroyTree(TreeNode **root);
queue *Queue_Init();
int Queue_IsEmpty(queue *qu);
int Queue_IsFull(queue *qu);
int Queue_In(queue *qu, TreeNode *tree);
int Queue_Out(queue *qu, TreeNode *tree);
void Queue_Destroy(queue *qu);

#endif