#include<stdio.h>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
/*
	二叉树的链式存储结构非常适合用递归的方式进行遍历
	不论是前中后序的遍历，递归实现的逻辑都非常清晰
	递归三要素：
	1.确定递归的参数和返回值
	2.确定中止条件
	3.确定单层递归逻辑
*/
struct TreeNode
{
	int val;
	TreeNode * left;
	TreeNode * right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};//二叉树节点数据结构的定义

//递归前序遍历(中序、后序仅需要做简单的语句顺序调整)
void frontTraverse(TreeNode * root, vector<int>& ans)
{
	if (root != nullptr)
		ans.push_back(root->val);
	frontTraverse(root->left, ans);
	frontTraverse(root->right, ans);
}

//迭代法前序遍历
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

//迭代法中序遍历与前序遍历存在区别，所以实现代码不会是简单的调整语句顺序
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

//后序遍历可通过调整前序的代码顺序reverse向量得到
//由于二叉树的后序遍历顺序是左右中，我们调整前序遍历的入栈顺序，将其顺序调整为中右左
//而出栈顺序与入栈相反，则为我们需要的左右中
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
	当然，也可以通过巧妙的添加空节点的方法，将三种迭代法遍历的代码赋予统一性
	使用这种方法编程，仅需要简单地调整几行代码位置即可完成三种遍历
	在此给出中序遍历的写法
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
			if (temp->right) stk.push(temp->right);//右
			stk.push(temp);//中
			stk.push(nullptr);
			if (temp->left) stk.push(temp->left);//左
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
	以上的几种遍历都属于深度优先遍历，顾名思义优先查询底层的叶子节点
	而除此之外还存在广度优先的遍历，也称为层序遍历，也就是优先将每一层的所有节点进行查询
	二叉树的层序遍历与queue的容器特性完美match，以下是借助queue做层序遍历的模板代码
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