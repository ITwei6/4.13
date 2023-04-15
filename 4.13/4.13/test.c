#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef char STDataType;
typedef struct BinaryTreeroot
{
	struct BinaryTreeroot* left;
	struct BinaryTreeroot* right;
	STDataType data;

}BTroot;

BTroot* CreatBinaryTree(char*a,int *pi)//创建二叉树
{
	if (a[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	//如果不是#那就是字母，如果是字母那就要为它分配节点
	BTroot* root = (BTroot*)malloc(sizeof(BTroot));
	if (root == NULL)
	{
		perror("malloc");
	}
	//将字母塞到节点里
	root->data = a[*pi];
	(*pi)++;
	//创建完节点后就要为左孩子和右孩子创建节点
	root->left=CreatBinaryTree(a, pi);
	root->right= CreatBinaryTree(a, pi);
	return root;
}
void DestroyBinaryTree(BTroot* root)//销毁二叉树
{
	if (root == NULL)
	{
		return;
	}
	//销毁二叉树  先销毁左子树-右子树-根
	DestroyBinaryTree(root->left);
	DestroyBinaryTree(root->right);
	free(root);
}
void BinaryTreePrevOrder(BTroot* root)//二叉树前序遍历
{
	
	if (root == NULL)
	{
		printf("#");
		return;
		}
			
		printf("%c", root->data);
		BinaryTreePrevOrder(root->left);
		BinaryTreePrevOrder(root->right);
}
void BinaryTreeInOrder(BTroot* root)//二叉树中序遍历
{
	if (root == NULL)
	{
		printf("#");
		return;
	}
	BinaryTreePrevOrder(root->left);
	printf("%c", root->data);
	BinaryTreePrevOrder(root->right);
}

void BinaryTreePostOrder(BTroot* root)//二叉树后序遍历
{
	if (root == NULL)
	{
		printf("#");
		return;
	}
	BinaryTreePrevOrder(root->left);
	BinaryTreePrevOrder(root->right);
	printf("%c", root->data);
}
int BinaryTreeSize(BTroot* root)//二叉树节点的个数
{
	if (root == NULL)
	{
		return 0;
	}
	return BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}
int BinaryTreeHeight(BTroot* root)//二叉树的高度
{
	if (root == NULL)
		return 0;

	int leftheight = BinaryTreeHeight(root->left);
	int rightheight= BinaryTreeHeight(root->right);
	return leftheight > rightheight ? leftheight + 1 : rightheight + 1;
}

int BinaryTreeLevelKSize(BTroot* root,int k)//二叉树第K层节点的个数
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}
BTroot* BinaryTreeFind(BTroot* root, STDataType x)//二叉树查找值为x的节点
{
	if (root == NULL)
		return NULL;
	if (root->data == x)
		return root;
	BTroot* leftx = BinaryTreeFind(root->left, x);
	if (leftx->data == x)
		return leftx;
	BTroot*rightx= BinaryTreeFind(root->right, x);
	if (rightx->data == x)
		return rightx;
	return NULL;

}

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
int  main()
{
	char arr[] = "ABD##E#H##CF##G##";
	int i = 0;
	BTroot *root=CreatBinaryTree(arr,&i);
	BinaryTreePrevOrder(root);
	printf("\n");
	printf("二叉树的高度：%d\n", BinaryTreeHeight(root));
	printf("二叉树节点的个数：%d\n", BinaryTreeSize(root));
	printf("二叉树第2层节点的个数：%d\n", BinaryTreeLevelKSize(root, 2));
	printf("查找二叉树中值为B的节点: %p", BinaryTreeFind(root, 'B'));
	return 0;
}