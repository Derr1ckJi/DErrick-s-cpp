#include<stdio.h>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
/*
	����������ʽ�洢�ṹ�ǳ��ʺ��õݹ�ķ�ʽ���б���
	������ǰ�к���ı������ݹ�ʵ�ֵ��߼����ǳ�����
	�ݹ���Ҫ�أ�
	1.ȷ���ݹ�Ĳ����ͷ���ֵ
	2.ȷ����ֹ����
	3.ȷ������ݹ��߼�
*/
struct TreeNode
{
	int val;
	TreeNode * left;
	TreeNode * right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};//�������ڵ����ݽṹ�Ķ���

//�ݹ�ǰ�����(���򡢺������Ҫ���򵥵����˳�����)
void frontTraverse(TreeNode * root, vector<int>& ans)
{
	if (root != nullptr)
		ans.push_back(root->val);
	frontTraverse(root->left, ans);
	frontTraverse(root->right, ans);
}

//������ǰ�����
vector<int> frontIterate(TreeNode * root)
{
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<TreeNode*> stk;
	TreeNode * temp = nullptr;
	stk.push(root);
	while (!stk.empty())
	{
		temp = stk.top();
		ans.push_back(temp->val);
		stk.pop();
		if (temp->right) stk.push(temp->right);
		if (temp->left) stk.push(temp->left);
	}
	return ans;
}

//���������������ǰ�����������������ʵ�ִ��벻���Ǽ򵥵ĵ������˳��
vector<int> midIterate(TreeNode * root)
{
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<TreeNode*> stk;
	TreeNode * temp = root;
	while (temp!=nullptr || !stk.empty())
	{
		if (temp != nullptr)
		{
			stk.push(temp);
			temp = temp->left;
		}
		else
		{
			temp = stk.top();
			stk.pop();
			ans.push_back(temp->val);
			temp = temp->right;
		}
	}
	return ans;
}

//���������ͨ������ǰ��Ĵ���˳��reverse�����õ�
//���ڶ������ĺ������˳���������У����ǵ���ǰ���������ջ˳�򣬽���˳�����Ϊ������
//����ջ˳������ջ�෴����Ϊ������Ҫ��������
vector<int> backIterate(TreeNode * root)
{
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<TreeNode*> stk;
	TreeNode * temp = nullptr;
	stk.push(root);
	while (!stk.empty())
	{
		temp = stk.top();
		stk.pop();
		ans.push_back(temp->val);
		if (temp->left) stk.push(temp->left);
		if (temp->right) stk.push(temp->right);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

/*
	��Ȼ��Ҳ����ͨ���������ӿսڵ�ķ����������ֵ����������Ĵ��븳��ͳһ��
	ʹ�����ַ�����̣�����Ҫ�򵥵ص������д���λ�ü���������ֱ���
	�ڴ˸������������д��
*/
vector<int> midIterate2(TreeNode* root)
{
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<TreeNode*> stk;
	TreeNode * temp = nullptr;
	stk.push(root);
	while (!stk.empty())
	{
		temp = stk.top();
		if (temp != nullptr)
		{
			stk.pop();
			if (temp->right) stk.push(temp->right);//��
			stk.push(temp);//��
			stk.push(nullptr);
			if (temp->left) stk.push(temp->left);//��
		}
		else
		{
			stk.pop();
			temp = stk.top();
			stk.pop();
			ans.push_back(temp->val);
		}
	}
	return ans;
}

/*
	���ϵļ��ֱ���������������ȱ���������˼�����Ȳ�ѯ�ײ��Ҷ�ӽڵ�
	������֮�⻹���ڹ�����ȵı�����Ҳ��Ϊ���������Ҳ�������Ƚ�ÿһ������нڵ���в�ѯ
	�������Ĳ��������queue��������������match�������ǽ���queue�����������ģ�����
*/
vector<vector<int>> levelOrder(TreeNode* root)
{
	vector<vector<int>> ans;
	if (root == nullptr) return ans;
	queue<TreeNode*> que;
	que.push(root);
	TreeNode * temp = nullptr;
	while (!que.empty())
	{
		int n = que.size();
		vector<int> thislevel;
		for (int i = 0; i < n; i++)
		{
			temp = que.front();
			que.pop();
			thislevel.push_back(temp->val);
			if (temp->left) que.push(temp->left);
			if (temp->right) que.push(temp->right);
		}
		ans.push_back(thislevel);
	}
	return ans;
}