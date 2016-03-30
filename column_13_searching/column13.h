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
	enum { BIT_PER_INT_TYPE = 32, SHIFT = 5, MASK = 0b111111 };
	int _size, _maxval, *x;
	void set(int i)  {        x[i>>SHIFT] |=  (1<<(i & MASK)); }
	void clr(int i)  {        x[i>>SHIFT] &= ~(1<<(i & MASK)); }
	int  test(int i) { return x[i>>SHIFT] &   (1<<(i & MASK)); }

public:
	IntSetBitVec(int maxelements, int maxval): _maxval(maxval), _size(0) {
		x = new int[1 + _maxval / BIT_PER_INT_TYPE];
		for (int i = 0; i < _maxval; i++)
			clr(i);
	}

	int size() {
        return _size;
    }

	void insert(int t) {
        if (test(t))
			return;
		set(t);
		_size++;
	}

	void report(int *v) {
        int j=0;
		for (int i = 0; i < _maxval; i++)
			if (test(i))
				v[j++] = i;
	}
};

class IntSetArr {
private:
	int _size, *x;
public:
	IntSetArr(int maxelements, int maxval) {
        x = new int[1 + maxelements];
		_size =0;
		x[0] = maxval; /* sentinel at x[n] */
	}

	int size() {
        return _size;
    }

	void insert(int t) {
        int i;

		for (i = 0; x[i] < t; i++)
			;

		if (x[i] == t)
			return;

		for (int j = _size; j >= i; j--)
			x[j+1] = x[j];

		x[i] = t;
		_size++;
	}

	void report(int *v) {
        for (int i = 0; i < _size; i++)
			v[i] = x[i];
	}
};

class IntSetList {
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
	IntSetList(int maxelements, int maxval) {
        sentinel = head = new node(maxval, 0);
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

class IntSetList_with_allocator {
private:
	int _size;

	struct node {
		int val;
		node *next;
	};

	node *head, *sentinel, *freenode;

public:
	IntSetList_with_allocator(int maxelements, int maxval) {
        sentinel = head = new node;
		sentinel->val = maxval;
		freenode = new node[maxelements];
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
	int _size, *v, size_v;

	struct node {
		int val;
		node *left, *right;

		node(int v) {
            val = v;
            left = right = 0;
        }
	};

	node *root;

	node *rinsert(node *p, int value) {
        if (p == 0) {
			p = new node(value);
			_size++;
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
		v[size_v++] = p->val;
        inorder_traverse(p->right);
	}

public:
	IntSetBST(int maxelements, int maxval): root(0), _size(0) {}

	int size() {
        return _size;
    }

	void insert(int value) {
        root = rinsert(root, value);
    }

	void report(int *x) {
        v = x;
        size_v = 0;
        inorder_traverse(root);
    }
};

class IntSetBST_with_allocator {
private:
	int _size, *v, size_v;

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
			_size++;
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
		v[size_v++] = p->val;
        inorder_traverse(p->right);
	}

public:
	IntSetBST_with_allocator(int maxelements, int maxval) {
        root = sentinel = new node;  // 0 if using insert1
		_size = 0;
		freenode = new node[maxelements];
	}

	int size() {
        return _size;
    }

	void insert1(int value) {
        root = rinsert(root, value);
    }

	void insert(int value) {
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
			_size++;
		}
	}

	void report(int *x) {
        v = x;
        size_v = 0;
        inorder_traverse(root);
    }
};

class IntSetBins {
private:
	int _size, _maxval;
    const int _maxelements;

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
	IntSetBins(int maxelements, int maxval): _maxelements(maxelements) {
		_maxval = maxval;

		bin = new node*[_maxelements];
		sentinel = new node(_maxval, 0);

		for (int i = 0; i < _maxelements; i++)
			bin[i] = sentinel;
		_size = 0;
	}

	int size() {
        return _size;
    }

	void insert(int value) {
        int i = value / (1 + _maxval / _maxelements);  // CHECK !
		bin[i] = rinsert(bin[i], value);
	}

	void report(int *v) {
        int j = 0;

		for (int i = 0; i < _maxelements; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};

class IntSetBins_with_allocator {
private:
	int _size, _maxval;
    const int _maxelements;

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
	IntSetBins_with_allocator(int maxelements, int maxval): _maxelements(maxelements) {
		_maxval = maxval;

		freenode = new node[maxelements];
		bin = new node*[_maxelements];

		sentinel = new node;
		sentinel->val = _maxval;

		for (int i = 0; i < _maxelements; i++)
			bin[i] = sentinel;
		_size = 0;
	}

	int size() {
        return _size;
    }

	void insert_recursive(int value) {
        int i = value / (1 + _maxval / _maxelements);
		bin[i] = rinsert(bin[i], value);
	}

	void insert(int value) {
        node **p;
		int i = value / (1 + _maxval / _maxelements);

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
		for (int i = 0; i < _maxelements; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};

#endif //PROGRAMMING_PEARLS_COLUMN13_H
