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

BTroot* CreatBinaryTree(char*a,int *pi)//����������
{
	if (a[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	//�������#�Ǿ�����ĸ���������ĸ�Ǿ�ҪΪ������ڵ�
	BTroot* root = (BTroot*)malloc(sizeof(BTroot));
	if (root == NULL)
	{
		perror("malloc");
	}
	//����ĸ�����ڵ���
	root->data = a[*pi];
	(*pi)++;
	//������ڵ���ҪΪ���Ӻ��Һ��Ӵ����ڵ�
	root->left=CreatBinaryTree(a, pi);
	root->right= CreatBinaryTree(a, pi);
	return root;
}
void DestroyBinaryTree(BTroot* root)//���ٶ�����
{
	if (root == NULL)
	{
		return;
	}
	//���ٶ�����  ������������-������-��
	DestroyBinaryTree(root->left);
	DestroyBinaryTree(root->right);
	free(root);
}
void BinaryTreePrevOrder(BTroot* root)//������ǰ�����
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
void BinaryTreeInOrder(BTroot* root)//�������������
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

void BinaryTreePostOrder(BTroot* root)//�������������
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
int BinaryTreeSize(BTroot* root)//�������ڵ�ĸ���
{
	if (root == NULL)
	{
		return 0;
	}
	return BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}
int BinaryTreeHeight(BTroot* root)//�������ĸ߶�
{
	if (root == NULL)
		return 0;

	int leftheight = BinaryTreeHeight(root->left);
	int rightheight= BinaryTreeHeight(root->right);
	return leftheight > rightheight ? leftheight + 1 : rightheight + 1;
}

int BinaryTreeLevelKSize(BTroot* root,int k)//��������K��ڵ�ĸ���
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}
BTroot* BinaryTreeFind(BTroot* root, STDataType x)//����������ֵΪx�Ľڵ�
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

// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
int  main()
{
	char arr[] = "ABD##E#H##CF##G##";
	int i = 0;
	BTroot *root=CreatBinaryTree(arr,&i);
	BinaryTreePrevOrder(root);
	printf("\n");
	printf("�������ĸ߶ȣ�%d\n", BinaryTreeHeight(root));
	printf("�������ڵ�ĸ�����%d\n", BinaryTreeSize(root));
	printf("��������2��ڵ�ĸ�����%d\n", BinaryTreeLevelKSize(root, 2));
	printf("���Ҷ�������ֵΪB�Ľڵ�: %p", BinaryTreeFind(root, 'B'));
	return 0;
}