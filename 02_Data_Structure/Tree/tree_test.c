#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main()
{
    TreeNode *tree_book = NULL;
    Book initial_Books[5] = {{1004,"rtos",34.34},{1001,"linux",34.1},{1007,"communication",66.78},{1002,"stm32",83.4},{1006,"OS",12.45}};
    Book tmpBook;
    int op;

    for(int i = 0; i < sizeof(initial_Books)/sizeof(*initial_Books); i++)
    {
        int res = Tree_IncertNode(&tree_book, &initial_Books[i]);
        if(res == -1)  printf("Book Already Exists!\n");
        else if(res == -2) printf("Memory error\n");
    }

    while (1)
    {
        printf("\nPlease Enter Operate:\n");
        printf("Exit 0, Incert 1, Find 2, Delete 3, ChangePrice 4, Travel 5, Statistic 6, BFS 7\n");
        scanf("%d",&op);

        if(op == 0) break;

        switch (op)
        {
            case 1:     // 插入
            {
                printf("Enter Book Information:\n");
                scanf("%d %s %f",&tmpBook.id, tmpBook.name, &tmpBook.price);

                int res = Tree_IncertNode(&tree_book, &tmpBook);
                if(res == -1)  printf("Book Already Exists!\n");
                else if(res == -2) printf("Memory error\n");
                break;
            }  
            case 2:     //查找
            {
                printf("Enter New Book ID:\n");
                scanf("%d",&tmpBook.id);

                TreeNode *tmpnode = Tree_FindNode(tree_book, tmpBook.id);
                if(tmpnode == NULL) printf("can not find\n");
                else
                {
                    tmpBook = tmpnode->book;
                    printf("%d %s %.2f\n", tmpBook.id, tmpBook.name, tmpBook.price);
                }
                break;
            }
            case 3:     //删除
            {
                printf("Enter Delete Book ID:\n");
                scanf("%d",&tmpBook.id);

                int res = Tree_DeleteNode(&tree_book, tmpBook.id);
                if(res == -1)   printf("can not find this book\n");
                break;
            }
            case 4:     // 修改价格
            {
                printf("Enter Book ID and Price:\n");
                scanf("%d %f",&tmpBook.id, &tmpBook.price);

                int res = Tree_ChangeNode(tree_book, tmpBook.id, tmpBook.price);
                if(res == -1)   printf("can not find this book\n");
                break;
            }
            case 5:     // 按顺序遍历输出
            {
                Tree_Travel(tree_book);
                break;
            }
            case 6:     // 统计
            {
                printf("Book Number : %d\nTree Height : %d\nLeaf Number : %d\n", Tree_CountNode(tree_book), Tree_Height(tree_book), Tree_CountLeaf(tree_book));
                break;
            }
            case 7:     // 层序遍历
            {
                Tree_BFSTravel(tree_book);
                break;
            }
            default: 
                printf("invalid operate\n");   
                break;
        }
    }
    
    Tree_DestroyTree(&tree_book);
    

    return 0;
}
