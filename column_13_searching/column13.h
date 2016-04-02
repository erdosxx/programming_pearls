#ifndef PROGRAMMING_PEARLS_COLUMN13_H
#define PROGRAMMING_PEARLS_COLUMN13_H

#include <iostream>
#include <set>
using namespace std;


class IntSetSTL {
private:
	set<int> S;

public:
	IntSetSTL(int maxelements, int maxval) {}

	int size() {
        return S.size();
    }

	void insert(int t) {
        S.insert(t);
    }

	void report(int *v) {
		int j = 0;
		set<int>::iterator i;

		for (i = S.begin(); i != S.end(); ++i)
			v[j++] = *i;
	}
};

class IntSetBitVec {
private:
    // int = 4 byte = 4*8 bit = 32 bit
	enum { BIT_PER_INT_TYPE = 32, SHIFT = 5, MASK = 0b111111 };
	int *x, _size, _maxval;
    //                          i/32               i%32
	void set(int i)  {        x[i>>SHIFT] |=  (1<<(i & MASK)); }
	void clr(int i)  {        x[i>>SHIFT] &= ~(1<<(i & MASK)); }
	int  test(int i) { return x[i>>SHIFT] &   (1<<(i & MASK)); }

public:
    // TODO: max_size is not used. Remove it.
	IntSetBitVec(int max_size, int maxval): _maxval(maxval), _size(0) {
		x = new int[1 + _maxval / BIT_PER_INT_TYPE];
		for (int i = 0; i < _maxval; i++)
			clr(i);
	}

	int size() {
        return _size;
    }

	void insert(int value) {
        if (test(value))
			return;
		set(value);
		_size++;
	}

	void report(int *v) {
        int j=0;
		for (int i = 0; i < _maxval; i++)
			if (test(i))
				v[j++] = i;
	}
};

class Integer_Set_Sorted_Array {
private:
    int* x;
	int size_x;

public:
	Integer_Set_Sorted_Array(int maxelements, int maxval): size_x(0) {
        x = new int[1 + maxelements];
		x[0] = maxval; /* sentinel at x[n] */
	}

	int size() {
        return size_x;
    }

	void insert(int value) {
        int position;

		for (position = 0; x[position] < value; position++)
			;

		if (x[position] == value)
			return;

		for (int j = size_x; j >= position; j--)
			x[j+1] = x[j];

		x[position] = value;
		size_x++;
	}

	void report(int *v) {
        for (int i = 0; i < size_x; i++)
			v[i] = x[i];
	}
};

class Integer_Set_Sorted_List {
private:
	int _size;

	struct node {
		int val;
		node *next;

		node(int i, node *p) {
            val = i;
            next = p;
        }
	};

	node *head, *sentinel;

	node *rinsert(node *p, int value) {
        if (p->val < value) {
			p->next = rinsert(p->next, value);
		} else if (p->val > value) {
			p = new node(value, p);
			_size++;
		}
		return p;
	}

public:
    // TODO: maxelements and maxcal are not used. Remove two variables.
	Integer_Set_Sorted_List(int maxelements, int maxval) {
        sentinel = new node(maxval, NULL);
        head = sentinel;
		_size = 0;
	}

	int size() {
        return _size;
    }

	void insert_recursive(int value) {
        head = rinsert(head, value);
    }

	void insert_non_recursive(int value) {
        node *p;

		if (head->val == value)
			return;

		if (head->val > value) {
			head = new node(value, head);
			_size++;
			return;
		}

		for (p = head; p->next->val < value; p = p->next)
			;

		if (p->next->val == value)
			return;

		p->next = new node(value, p->next);
		_size++;
	}

	void insert_non_recursive_with_pointer(int value) {
        node **p;

		for (p = &head; (*p)->val < value; p = &((*p)->next))
			;

		if ((*p)->val == value)
			return;

		*p = new node(value, *p);
		_size++;
	}

	void report(int *v) {
        int j = 0;
		for (node *p = head; p != sentinel; p = p->next)
			v[j++] = p->val;
	}
};

class Integer_Set_Sorted_list_with_allocator {
private:
	int _size;

	struct node {
		int val;
		node *next;
	};

	node *head, *sentinel, *freenode;

public:
	Integer_Set_Sorted_list_with_allocator(int max_size, int maxval) {
        sentinel = new node;
		sentinel->val = maxval;
        head = sentinel;

		freenode = new node[max_size];
		_size = 0;
	}

	int size() {
        return _size;
    }

	void insert(int value) {
        node **p;
		for (p = &head; (*p)->val < value; p = &((*p)->next))
			;
		if ((*p)->val == value)
			return;
		freenode->val = value;
		freenode->next = *p;
		*p = freenode++;
		_size++;
	}

	void report(int *v) {
        int j = 0;
		for (node *p = head; p != sentinel; p = p->next)
			v[j++] = p->val;
	}
};

class IntSetBST {
private:
	int size_BST;
    int *report_ary, size_report_ary;

	struct node {
		int val;
		node *left, *right;

		node(int value) {
            val = value;
            left = right = NULL;
        }
	};

	node *root;

	node *rinsert(node *p, int value) {
        if (p == NULL) {
			p = new node(value);
			size_BST++;
		} else if (value < p->val) {
			p->left = rinsert(p->left, value);
		} else if (value > p->val) {
			p->right = rinsert(p->right, value);
		} // do nothing if p->val == t
		return p;
	}

	void inorder_traverse(node *p) {
        if (p == 0)
			return;
        inorder_traverse(p->left);
		report_ary[size_report_ary++] = p->val;
        inorder_traverse(p->right);
	}

public:
    // TODO: remove maxelements and maxval
	IntSetBST(int maxelements, int maxval): root(0), size_BST(0) {}

	int size() {
        return size_BST;
    }

	void insert(int value) {
        root = rinsert(root, value);
    }

	void report(int *x) {
        report_ary = x;
        size_report_ary = 0;
        inorder_traverse(root);
    }
};

class IntSetBST_with_allocator {
private:
	int size_BST;
    int *report_ary, size_report_ary;

	struct node {
		int val;
		node *left, *right;
	};

	node *root, *freenode, *sentinel;

	node *rinsert(node *p, int value) {
        if (p == sentinel) {
			p = freenode++;
			p->val = value;
			p->left = p->right = sentinel;
			size_BST++;
		} else if (value < p->val) {
			p->left = rinsert(p->left, value);
		} else if (value > p->val) {
			p->right = rinsert(p->right, value);
		} // do nothing if p->val == t
		return p;
	}

	void inorder_traverse(node *p) {
        if (p == sentinel)
			return;
        inorder_traverse(p->left);
		report_ary[size_report_ary++] = p->val;
        inorder_traverse(p->right);
	}

public:
    // TODO: remove maxval
	IntSetBST_with_allocator(int maxelements, int maxval) {
        sentinel = new node;
        root = sentinel;
		size_BST = 0;
		freenode = new node[maxelements];
	}

	int size() {
        return size_BST;
    }

	void insert_recursive(int value) {
        root = rinsert(root, value);
    }

	void insert_non_recursive(int value) {
        sentinel->val = value;
		node **p = &root;

		while ((*p)->val != value)
			if (value < (*p)->val)
				p = &((*p)->left);
			else
				p = &((*p)->right);

		if (*p == sentinel) {
			*p = freenode++;
			(*p)->val = value;
			(*p)->left = (*p)->right = sentinel;
			size_BST++;
		}
	}

	void report(int *x) {
        report_ary = x;
        size_report_ary = 0;
        inorder_traverse(root);
    }
};

class Integer_Set_with_Hash_Bins {
private:
	int _size, _maxval;
    const int _max_size;

	struct node {
		int val;
		node *next;
		node(int v, node *p) {
            val = v;
            next = p;
        }
	};

	node **bin, *sentinel;

	node *rinsert(node *p, int value) {
        if (p->val < value) {
			p->next = rinsert(p->next, value);
		} else if (p->val > value) {
			p = new node(value, p);
			_size++;
		}
		return p;
	}

public:
	Integer_Set_with_Hash_Bins(int max_size, int maxval):
            _max_size(max_size), _maxval(maxval), _size(0) {
		bin = new node*[_max_size];
		sentinel = new node(_maxval, 0);

		for (int i = 0; i < _max_size; i++)
			bin[i] = sentinel;
	}

	int size() {
        return _size;
    }

	void insert(int value) {
        int i = value / (1 + _maxval / _max_size);  // CHECK !
		bin[i] = rinsert(bin[i], value);
	}

	void report(int *v) {
        int j = 0;

		for (int i = 0; i < _max_size; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};

class Integer_Set_with_Hash_Bins_with_allocator {
private:
	int _size, _maxval;
    const int _max_size;

	struct node {
		int val;
		node *next;
	};

	node **bin, *sentinel, *freenode;

	node *rinsert(node *p, int value) {
        if (p->val < value) {
			p->next = rinsert(p->next, value);
		} else if (p->val > value) {
			freenode->val = value;
			freenode->next = p;
			p = freenode++;
			_size++;
		}
		return p;
	}

public:
	Integer_Set_with_Hash_Bins_with_allocator(int maxelements, int maxval):
            _max_size(maxelements), _maxval(maxval), _size(0) {
		freenode = new node[maxelements];
		bin = new node*[_max_size];

		sentinel = new node;
		sentinel->val = _maxval;

		for (int i = 0; i < _max_size; i++)
			bin[i] = sentinel;
	}

	int size() {
        return _size;
    }

	void insert_recursive(int value) {
        int i = value / (1 + _maxval / _max_size);
		bin[i] = rinsert(bin[i], value);
	}

	void insert_non_recursive(int value) {
        node **p;
		int i = value / (1 + _maxval / _max_size);

		for (p = &bin[i]; (*p)->val < value; p = &((*p)->next))
			;

		if ((*p)->val == value)
			return;

		freenode->val = value;
		freenode->next = *p;
		*p = freenode++;
		_size++;
	}

	void report(int *v) {
        int j = 0;
		for (int i = 0; i < _max_size; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};

#endif //PROGRAMMING_PEARLS_COLUMN13_H
