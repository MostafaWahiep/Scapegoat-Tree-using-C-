#pragma once

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template < typename T>
	class ScapegoatTree
	{
		public:

			/*operations in a Scapegoat is dependent on α coefficient with a domain starting
			  starting from[1/2, 1[ in our implementation we choose it be 2/3*/
			class Scapenode
			{
				public:
					T data;
				Scapenode *left, *right, *parent;
				Scapenode(): data(0), left(0), right(0), parent(0) {}

				Scapenode(T element): data(element), left(0), right(0), parent(0) {}
			};

		typedef Scapenode * NodePointer;
		public:
			ScapegoatTree();
			ScapegoatTree(const ScapegoatTree<T> &orig);
			//    ~ScapegoatTree();
			bool empty() const;
			bool remove(T value);
			void insert(T value);
			NodePointer search(T value) const;
			//return mysize of the whole tree
			int size() const;
			//display the values of the tree in ascending order
			void inorder() const;

		private:
			NodePointer root;
			int mysize;
			int q;	// overestimate of size -> q * a <= n <= q
			//return mysize of a subtree p
			int size(NodePointer p) const;
			void inorder(NodePointer p) const;
			bool remove(NodePointer p);
			NodePointer getsuccessor(NodePointer p);
			NodePointer search(NodePointer p, T value);
			inline double log3_2(int q) const;
			int insertwithdepth(NodePointer p);
			NodePointer buildbalanced(vector<NodePointer> &v);
			void putinarray(vector<NodePointer> &v, NodePointer p);
			void rebuild(NodePointer p);
	};

template < typename T>
	ScapegoatTree<T>::ScapegoatTree(): root(0), mysize(0), q(0) {}

template < typename T>
	ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &orig): mysize(orig.mysize), q(orig.q) {}

template < typename T>
	bool ScapegoatTree<T>::empty() const
	{
		return root == 0;
	}

template < typename T>
	bool ScapegoatTree<T>::remove(T value)
	{
		bool deleted = remove(search(root, value));
		if (deleted)
		{
			mysize--;
			if (mysize < (2.0 / 3 *q))
			{
				rebuild(root);
				q = mysize;
			}
		}

		return deleted;
	}

template < typename T>
	void ScapegoatTree<T>::insert(T value)
	{
		NodePointer p = new Scapenode(value);
		int depth = insertwithdepth(p);
		if (depth > log3_2(q))
		{
			p = p->parent;
			while (2* size(p->parent) >= 3* size(p))
				p = p->parent;
			p = p->parent;
			cout << "Scapegoat is " << p->data << endl;
			rebuild(p);
		}

		if (depth == -1)
		{
			cerr << "the inserted item is already existed\n";
		}

		cout << depth << endl;
	}

template < typename T>
	typename ScapegoatTree<T>::NodePointer ScapegoatTree<T>::search(T value) const
	{
		return search(root, value);
	}

template < typename T>
	int ScapegoatTree<T>::size() const
	{
		return mysize;
	}

template < typename T>
	void ScapegoatTree<T>::inorder() const
	{
		inorder(root);
	}

template < typename T>
	int ScapegoatTree<T>::size(NodePointer p) const
	{
		if (p == 0)
			return 0;
		return size(p->right) + size(p->left) + 1;
	}

template < typename T>
	void ScapegoatTree<T>::inorder(NodePointer p) const
	{
		if (p == 0)
			return;
		inorder(p->left);
		cout << p->data << " ";
		inorder(p->right);
	}

template < typename T>
	bool ScapegoatTree<T>::remove(NodePointer p)
	{
		//key doesnt exists
		if (p == 0)
		{
			return false;
		}

		// node has no downren
		if (p->left == 0 && p->right == 0)
		{
			if (p != root)
			{
				if (p->parent->left == p)
				{
					p->parent->left = 0;
				}
				else
				{
					p->parent->right = 0;
				}
			}
			else
			{
				root = nullptr;
			}

			delete p;
		}
		else if (p->left && p->right)
		{
			NodePointer successor = getsuccessor(p->right);
			// store successor value
			int val = successor->data;
			// delete the successor
			remove(successor);
			// copy value of the successor to the current node
			p->data = val;
		}
		else
		{
			NodePointer down;
			if (p->left)
				down = p->left;
			else
				down = p->right;
			if (p != root)
			{
				if (p == p->parent->left)
					p->parent->left = down;
				else
					p->parent->right = down;
			}
			else
			{
				root = down;
			}

			delete p;
		}
	}

template < typename T>
	typename ScapegoatTree<T>::NodePointer ScapegoatTree<T>::getsuccessor(NodePointer p)
	{
		while (p->left != nullptr)
		{
			p = p->left;
		}

		return p;
	}

template < typename T>
	inline double ScapegoatTree<T>::log3_2(int q) const
	{
		double
		const log2_3 = 2.4663034623;
		return log2_3* log(q);
	}

template < typename T>
	int ScapegoatTree<T>::insertwithdepth(NodePointer p)
	{
		NodePointer rt = root;
		if (rt == 0)
		{
			root = p;
			mysize++;
			q++;
			return 0;
		}

		bool flag = false;
		int depth = 0;
		do { 	if (p->data > rt->data)
			{
				if (rt->right == 0)
				{
					rt->right = p;
					p->parent = rt;
					flag = true;
				}
				else
					rt = rt->right;
			}
			else if (p->data < rt->data)
			{
				if (rt->left == 0)
				{
					rt->left = p;
					p->parent = rt;
					flag = true;
				}
				else
					rt = rt->left;
			}
			else
			{
				delete p;
				return -1;
			}

			depth++;
		} while (flag == 0);
		mysize++;
		q++;
		return depth;
	}

template < typename T>
	typename ScapegoatTree<T>::NodePointer ScapegoatTree<T>::search(NodePointer p, T value)
	{
		if (p == 0 || p->data == value)
			return p;
		if (p->data > value)
			return search(p->left, value);
		return search(p->right, value);
	}

template < typename T>
	typename ScapegoatTree<T>::NodePointer ScapegoatTree<T>::buildbalanced(vector<NodePointer> &v)
	{
		if (v.size() == 0)
			return 0;
		int center = v.size() / 2;
		NodePointer root = v[center];
		vector<NodePointer> l(v.begin(), v.begin() + center);
		root->left = buildbalanced(l);
		if (root->left != 0)
			root->left->parent = root;
		vector<NodePointer> r(v.begin() + center + 1, v.end());
		root->right = buildbalanced(r);
		if (root->right != 0)
			root->right->parent = root;
		return root;
	}

//inorder traversal to push back ascendingly so save the sorting time
template < typename T>
	void ScapegoatTree<T>::putinarray(vector<NodePointer> &v, NodePointer p)
	{
		if (p == 0)
			return;
		putinarray(v, p->left);
		v.push_back(p);
		putinarray(v, p->right);
	}

template < typename T>
	void ScapegoatTree<T>::rebuild(NodePointer p)
	{
		//int s = size(p);
		NodePointer up = p->parent;
		vector<NodePointer> v;
		putinarray(v, p);
		if (up == 0)
		{
			root = buildbalanced(v);
			root->parent = 0;
		}
		else if (up->left == p)
		{
			up->left = buildbalanced(v);
			up->left->parent = up;
		}
		else
		{
			up->right = buildbalanced(v);
			up->right->parent = up;
		}
	}
