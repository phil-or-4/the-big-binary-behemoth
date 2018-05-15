/*
Author: Phillip Sopt,   
Description: The program was designed to test our skills with binary search trees. In specific we were
supposed to create 5 functions, to_vector(), get_ith(), num_geq(), num_leq(), num_range() and ensure that they 
were correct and satisfied the required runtime requirements.

We were also require to balance the tree if ever it was to break the balance rule of 1/3 --- 2/3. So the difference
of two subtree was not to greater than 1/3 of the number of nodes in the tree. We did this to ensure that insert(), remove()
and lookup() was O(logn). I wrote bst_balance to take care of the balancing, it would trigger if insert or remove cause a balancing
violation.

*/
#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class bst {

public:
	struct bst_node {
		T      val;
		int count;		//store the number of nodes in subtree including the root
		int lcount;		//store the number of nodes in the left
		int rcount;		//store the number of nodes in the right
		bst_node *left;
		bst_node *right;

		bst_node(const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int lnum = 0, int rnum = 0, int tnum = 0)
			: val{ _val }, left{ l }, right{ r }, lcount{ lnum }, rcount{ rnum }, count{ tnum }
		{
		}
	};

	// constructor:  initializes an empty tree
	bst()
	{
		root = nullptr;
	}

private:
	// helper function which recursively deallocates nodes
	//   in a tree.
	static void delete_nodes(bst_node *r)
	{
		if (r == nullptr) return;
		delete_nodes(r->left);
		delete_nodes(r->right);
		delete r;
	}

public:
	// destructor
	~bst()
	{
		delete_nodes(root);
	}

private:

	//these are used for the size balancing
	static int max(int num1, int num2) {
		return (num1 > num2) ? num1 : num2;
	}
	static int min(int num1, int num2) {
		return (num1 < num2) ? num1 : num2;
	}
	/**
	* function:  insert()
	* desc:      recursive helper function inserting x into
	*            binary search tree rooted  at r.
	*
	* returns:   pointer to root of tree after insertion.
	*
	* notes:     if x is already in tree, no modifications are made.
	*/
	static bst_node * _insert(bst_node *r, T & x, bool &success, bst_node** violator)
	{
		if (r == nullptr)
		{
			success = true;
			return new bst_node(x, nullptr, nullptr, 0, 0, 1);		//make the count 1 but r and l 0
		}
		if (r->val == x)
		{
			success = false;
			return r;
		}
		if (x < r->val)
		{
			r->left = _insert(r->left, x, success, violator);
			if (success) r->lcount += 1;				//if the insert worked then count++
			r->count = 1 + r->lcount + r->rcount;		//recalculate total
			if (max(r->lcount, r->rcount) > 2 * min(r->lcount, r->rcount) + 1) *violator = r; //check the size balance condition on this node
			return r;
		}
		else
		{
			r->right = _insert(r->right, x, success, violator);
			if (success) r->rcount += 1;				//if the insert worked then count++
			r->count = 1 + r->lcount + r->rcount;		//recalculate total
			if (max(r->lcount, r->rcount) > 2 * min(r->lcount, r->rcount) + 1) *violator = r;//check the size balance condition on this node
			return r;
		}
	}

public:
	/**
	* function:  insert
	* desc:      inserts x into BST given by t.  Note that
	*            a BST stores a SET -- no duplicates.  Thus,
	*            if x is already in t when call made, no
	*            modifications to tree result.
	*
	* note:      helper function does most of the work.
	*
	*/
	//TODO add & back to insert
	bool insert(T &x)
	{
		bst_node* violator = nullptr;
		bool success;
		root = _insert(root, x, success, &violator);
		if (violator != nullptr) bst_balance(violator);
		return success;
	}

	/*
	fuction:	bst_balance
	desc:		if the check in insert or remove trigger, (max(left,right) <= 2*min(left,right)+1 condidtion)
				then we'll have to rebalance that tree at the node that triggered
				this event. We must retain a 2/3 to 1/3 balance to ensure we get good runtimes
				for insert, lookup, remove, etc...
	*/
	static void bst_balance(bst_node *(&r)) {
		vector<bst_node*> vec = vector<bst_node*>();
		populate_balance_vector(vec, r);				//store all the values to rebalance in a vector
		_my_from_vec(vec, 0, vec.size() - 1, r);			//now use that vector to rebalance the nodes
	}

private:
	/*
	* Recursive  helper function _my_from_vec, used by
	* balance_bst. The function must return a sub-tree that is
	* perfectly balanced, given a sorted array of bst_node*'s.
	*/
	static bst_node* _my_from_vec(const std::vector<bst_node*> &a, int low, int hi, bst_node*(&root))
	{
		int m;

		if (hi < low) return nullptr;
		m = (low + hi) / 2;
		root = a[m];		//set the root to point to the bst_node in the vec
		root->count = 0;
		root->lcount = 0;
		root->rcount = 0;
		root->left = _my_from_vec(a, low, m - 1, root->left);
		root->right = _my_from_vec(a, m + 1, hi, root->right);
		if (root->right != nullptr)	root->rcount += root->right->count;		//if there's a right node we have to tally it's count to rcount
		if (root->left != nullptr) root->lcount += root->left->count;		//if there's a left node we have to tally it's count to lcount
		root->count = 1 + root->rcount + root->lcount;						//recalculate total
		return root;
	}

	//modified to return a node pointing to the root
	static bst_node * from_sorted_vec(const std::vector<bst_node*> &a, int n)
	{
		return _from_vec(a, 0, n - 1);
	}

	//helper func for bst_balance, helps make a sorted array
	static void populate_balance_vector(vector<bst_node*> &V, bst_node *(&r)) {
		if (r == nullptr) return;
		populate_balance_vector(V, r->left);
		V.push_back(r);
		populate_balance_vector(V, r->right);
	}

public:
	/**
	* function:  contains()
	* desc:      returns true or false depending on whether x is an
	*            element of BST (calling object)
	*
	*/
	bool contains(const T & x)
	{
		bst_node *p = root;

		while (p != nullptr)
		{

			if (p->val == x)
				return true;
			if (x < p->val)
			{
				p = p->left;
			}
			else
				p = p->right;
		}
		return false;
	}

	//TODO change to private
private:
	// returns pointer to node containing
	//   smallest value in tree rooted at r
	static bst_node * _min_node(bst_node *r)
	{
		if (r == nullptr)
			return nullptr; // should never happen!
		while (r->left != nullptr)
			r = r->left;
		return r;
	}

	// returns pointer to node containing
	//   smallest value in tree rooted at r
	static bst_node * _max_node(bst_node *r)
	{
		if (r == nullptr)
			return nullptr; // should never happen!
		while (r->right != nullptr)
			r = r->right;
		return r;
	}

	// recursive helper function for node removal
	//   returns root of resulting tree after removal.
	static bst_node * _remove(bst_node *r, T & x, bool &success, bst_node** violator)
	{
		bst_node *tmp;
		bool sanity;

		if (r == nullptr)
		{
			success = false;
			return nullptr;
		}
		if (r->val == x)
		{
			success = true;

			if (r->left == nullptr)
			{
				tmp = r->right;
				delete r;
				return tmp;
			}
			if (r->right == nullptr)
			{
				tmp = r->left;
				delete r;
				return tmp;
			}
			// if we get here, r has two children
			r->val = _min_node(r->right)->val;
			r->right = _remove(r->right, r->val, sanity, violator);
			if (!sanity)
				std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
			r->rcount -= 1;							//modify the rcount b/c we remove a node in the right
			r->count = 1 + r->rcount + r->lcount;	//recalculate total
			if (max(r->lcount, r->rcount) > 2 * min(r->lcount, r->rcount) + 1) *violator = r;//check the size balance condition on this node
			return r;
		}
		if (x < r->val)
		{
			r->left = _remove(r->left, x, success, violator);
			if (success) r->lcount -= 1;			//modify the lcount b/c we remove a node in the left
			r->count = 1 + r->rcount + r->lcount;	//recalculate total
		}
		else
		{
			r->right = _remove(r->right, x, success, violator);
			if (success) r->rcount -= 1;			//modify the rcount b/c we remove a node in the right
			r->count = 1 + r->rcount + r->lcount;	//recalculate total
		}
		if (max(r->lcount, r->rcount) > 2 * min(r->lcount, r->rcount) + 1) *violator = r;//check the size balance condition on this node
		return r;
	}

public:
	//TODO put the ampersand back
	bool remove(T &x)
	{
		bst_node* violator = nullptr;
		bool success;
		root = _remove(root, x, success, &violator);
		if (violator != nullptr) bst_balance(violator); //balance
		return success;
	}

private:
	// recursive helper function to compute size of tree rooted at r
	static int _size(bst_node *r)
	{
		if (r == nullptr) return 0;
		return _size(r->left) + _size(r->right) + 1;
	}

public:
	int size()
	{
		return _size(root);
	}

private:
	static int _height(bst_node *r)
	{
		int l_h, r_h;

		if (r == nullptr) return -1;
		l_h = _height(r->left);
		r_h = _height(r->right);
		return 1 + (l_h > r_h ? l_h : r_h);
	}

public:
	int height()
	{
		return _height(root);
	}

	bool min(T & answer)
	{
		if (root == nullptr)
		{
			return false;
		}
		answer = _min_node(root)->val;
		return true;
	}

	T max()
	{
		return _max_node(root)->val;
	}

	/******************************************
	*
	* "stubs" for assigned TODO functions below
	*
	*****************************************/

	// TODO
	/* Function: to_vector
	Description : creates a vector and populates it with the
	elements of the tree (in-order) and returns the vector
	as a pointer
	Runtime: O(n) where n is the number of elements in the tree.
	*/
	std::vector<T> * to_vector()
	{
		vector<T> *res = new vector<T>();
		//check if there's no root
		if (to_vector_helper(res, root) == nullptr)
		{
			delete res;		//bail and delete the memory we allocated for vec
			return nullptr;	//YOU GET NOTHING, GOOD DAY SIR! -Willy Wonka
		}
		else
		{
			return res;
		}
	}

private:
	//helper function to to_vector, takes
	vector<T> * to_vector_helper(vector<T> *V, bst_node *node)
	{
		//base case
		if (node == nullptr) return nullptr;

		to_vector_helper(V, node->left);	//traverse to the left
		V->push_back(node->val);				//insert the val in the vector
		to_vector_helper(V, node->right);	//traverse to the right
		return V;
	}

public:
	/* TODO
	* Function:  get_ith
	* Description:  determines the ith smallest element in t and
	*    "passes it back" to the caller via the reference parameter x.
	*    i ranges from 1..n where n is the number of elements in the
	*    tree.
	*
	*    If i is outside this range, false is returned.
	*    Otherwise, true is returned (indicating "success").
	*
	* Runtime:  O(h) where h is the tree height
	*/
	bool get_ith(int i, T &x)
	{
		if (root == nullptr)return false;
		//bounds check
		if (i < 1 || i > root->count) return false;
		_get_ith(root, i, x);
		return true;
	}

private:
	//helper function for get_ith
	void _get_ith(bst_node* r, int i, T &x) {

		if (r == nullptr) return;

		//the root is the ith smallest
		if (r->lcount + 1 == i) {
			x = r->val;
			return;
		}
		//the ith is in the right side
		else if (r->lcount < i) {
			//move the pointer to the right & reeval i to offset it with the count in left
			_get_ith(r->right, i - (r->lcount + 1), x);
		}
		//iths is in left side
		else {
			_get_ith(r->left, i, x);
		}
	}

public:
	bool get_ith_SLOW(int i, T &x)
	{
		int n = size();
		int sofar = 0;

		if (i < 1 || i > n)
			return false;

		_get_ith_SLOW(root, i, x, sofar);
		return true;
	}

	/* TODO
	* Function:  num_geq
	* Description:  returns the number of elements in tree which are
	*       greater than or equal to x.
	*
	* Runtime:  O(h) where h is the tree height
	*/
	int num_geq(const T & x)
	{
		return _num_geq(root, x);
	}

private:
	//recursive helper for num_geq
	int _num_geq(bst_node * r, const T & x) {

		if (r == nullptr) return 0;										//return 0 if it's a null node
		if (r->val >= x) return 1 + r->rcount + _num_geq(r->left, x);	//if the node is >= x then tally 1 + rcount then go left
		else return _num_geq(r->right, x);								//if the node is < x go right
	}

public:
	/*
	* function:     num_geq_SLOW
	* description:  same functionality as num_geq but sloooow (linear time)
	*
	*/
	int num_geq_SLOW(const T & x)
	{
		return _num_geq_SLOW(root, x);
	}

	/* TODO
	* Function:  num_leq
	* Description:  returns the number of elements in tree which are less
	*      than or equal to x.
	*
	* Runtime:  O(h) where h is the tree height
	*
	**/
	int num_leq(const T &x)
	{
		return _num_leq(root, x);
	}

private:
	//recursive helper for num_leq
	int _num_leq(bst_node * r, const T & x) {

		if (r == nullptr) return 0;										//return 0 if it's a null node
		if (r->val <= x) return 1 + r->lcount + _num_leq(r->right, x);	//if the node is <= x then tally 1 + lcount then go right
		else return _num_leq(r->left, x);								//if the node is > x go left
	}

public:
	/*
	* function:     num_leq_SLOW
	* description:  same functionality as num_leq but sloooow (linear time)
	*
	*/
	int num_leq_SLOW(const T & x)
	{
		return _num_leq_SLOW(root, x);
	}

	/* TODO
	* Function:  num_range
	* Description:  returns the number of elements in tree which are
	*       between min and max (inclusive).
	*
	* Runtime:  O(h) where h is the tree height
	*
	**/
	int num_range(const T & min, const T & max)
	{
		if (root == nullptr) return 0;			//if root is null drop it
		if (min > max) return 0;				//if user is silly drop it
		int numTotal = root->count;				//get the total number of nodes
		int gTotal = num_gq(max);				//get the set to the right of the range
		int lTotal = num_lq(min);				//get the set to the left of the range
		return numTotal - (gTotal + lTotal);	//return the middle portion
	}

private:
	//num_lq and num_gq get the numbers less then or greater then the min and max respectivaly
	int num_lq(const T &x)
	{
		return _num_lq(root, x);
	}
	int _num_lq(bst_node * r, const T & x) {

		if (r == nullptr) return 0;									//return 0 if it's a null node
		if (r->val < x) return 1 + r->lcount + _num_lq(r->right, x);	//if the node is < x then tally 1 + lcount then go right
		else return _num_lq(r->left, x);								//if the node is > x go left
	}

	int num_gq(const T & x)
	{
		return _num_gq(root, x);
	}
	int _num_gq(bst_node * r, const T & x) {

		if (r == nullptr) return 0;									//return 0 if it's a null node
		if (r->val > x) return 1 + r->rcount + _num_gq(r->left, x);	//if the node is > x then tally 1 + rcount then go left
		else return _num_gq(r->right, x);							//if the node is < x go right
	}

public:
	/*
	* function:     num_range_SLOW
	* description:  same functionality as num_range but sloooow (linear time)
	*
	*/
	int num_range_SLOW(const T & min, const T & max)
	{
		return _num_range_SLOW(root, min, max);
	}

private:
	static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar)
	{
		if (t == nullptr)
			return;
		_get_ith_SLOW(t->left, i, x, sofar);

		if (sofar == i)
			return;
		sofar++;
		if (sofar == i)
		{
			x = t->val;
			return;
		}
		_get_ith_SLOW(t->right, i, x, sofar);
	}

	static int _num_geq_SLOW(bst_node * t, const T & x)
	{
		int total;

		if (t == nullptr) return 0;
		total = _num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

		if (t->val >= x)
			total++;
		return total;
	}

	static int _num_leq_SLOW(bst_node *t, const T &x)
	{
		int total;

		if (t == nullptr) return 0;
		total = _num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

		if (t->val <= x)
			total++;
		return total;
	}

	static int _num_range_SLOW(bst_node *t, const T &min, const T &max)
	{
		int total;

		if (t == nullptr) return 0;
		total = _num_range_SLOW(t->left, min, max) +
			_num_range_SLOW(t->right, min, max);

		if (t->val >= min && t->val <= max)
			total++;
		return total;
	}

private:
	static void indent(int m)
	{
		int i;
		for (i = 0; i < m; i++)
			std::cout << "-";
	}

	static void _inorder(bst_node *r)
	{
		if (r == nullptr) return;
		_inorder(r->left);
		std::cout << "[ " << r->val << " ]\n";
		_inorder(r->right);
	}

	static void _preorder(bst_node *r, int margin)
	{
		if (r == nullptr)
		{
			indent(margin);
			std::cout << " nullptr \n";
		}
		else
		{
			indent(margin);
			std::cout << "[ " << r->val << " ]\n";
			_preorder(r->left, margin + 3);
			_preorder(r->right, margin + 3);
		}
	}

	/*
	* TODO:
	* Complete the (recursive) helper function for the post-order traversal.
	* Remember: the indentation needs to be proportional to the height of the node!
	*/
	static void _postorder(bst_node *r, int margin)
	{
		if (r == nullptr)
		{
			indent(margin);
			std::cout << " nullptr \n";
		}
		else
		{
			indent(margin);
			_postorder(r->left, margin + 3);
			_postorder(r->right, margin + 3);
			std::cout << "[ " << r->val << " ]\n";
		}
	}

public:
	void inorder()
	{
		std::cout << "\n======== BEGIN INORDER ============\n";
		_inorder(root);
		std::cout << "\n========  END INORDER  ============\n";
	}

	void preorder()
	{
		std::cout << "\n======== BEGIN PREORDER ============\n";
		_preorder(root, 0);
		std::cout << "\n========  END PREORDER  ============\n";
	}

	// indentation is proportional to depth of node being printed
	//   depth is #hops from root.
	void postorder()
	{
		std::cout << "\n======== BEGIN POSTORDER ============\n";
		_postorder(root, 0);
		std::cout << "\n========  END POSTORDER  ============\n";
	}

private:
	/*
	* Recursive  helper function _from_vec, used by
	* bst_from_sorted_arr(...). The function must return a sub-tree that is
	* perfectly balanced, given a sorted array of elements a.
	*/
	static bst_node * _from_vec(const std::vector<T> &a, int low, int hi)
	{
		int m;
		bst_node *root;

		if (hi < low) return nullptr;
		m = (low + hi) / 2;
		root = new bst_node(a[m]);
		root->left = _from_vec(a, low, m - 1);
		root->right = _from_vec(a, m + 1, hi);
		if (root->right != nullptr)	root->rcount += root->right->count;
		if (root->left != nullptr) root->lcount += root->left->count;
		root->count = 1 + root->rcount + root->lcount; //recalculate total
		return root;
	}

public:
	static bst * from_sorted_vec(const std::vector<T> &a, int n)
	{

		bst * t = new bst();
		t->root = _from_vec(a, 0, n - 1);
		return t;
	}

	// TODO:  num_leaves
	//   Hint:  feel free to write a helper function!!
	int num_leaves()
	{
		return _num_leaves(root);
	}

private:
	int _num_leaves(bst_node * r) 
	{
		if (r == nullptr) return 0;
		if (r->left == nullptr && r->right == nullptr) return 1;
		return _num_leaves(r->left) + _num_leaves(r->right);
	}

public:
	// TODO:  num_at_level
	// description:  returns the number of nodes at specified level
	//   in tree.
	// note:  the root is at level 0.
	// Hint:  recursive helper function?
	int num_at_level(int level)
	{
		return _num_at_levels(root, level);
	}

private:
	int _num_at_levels(bst_node* r,int level)
	{
		if (r == nullptr) return 0;
		if (level == 0) return 1;
		return _num_at_levels(r->left, level - 1) + _num_at_levels(r->right, level - 1);
	}

	//TODO change to private
private:
	bst_node *root;
}; // end class bst

#endif