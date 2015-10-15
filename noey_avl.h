#ifndef NOEY_AVL
#define NOEY_AVL

#include <vector>
#include <ostream>
#include <algorithm>

#define NODE_MAX 1000
// Set max node to benefit the pool implementation

namespace noey
{
  using std::vector;
  using std::less;
  using std::max;
  using std::cout;

  template <typename _Tp>
    struct __avl_node
    {
      int _M_h;
      _Tp _M_data;
      __avl_node* _M_left, *_M_right;

      __avl_node() = default;

      __avl_node(_Tp __t)
      : _M_h(1), _M_data(__t), _M_left(nullptr), _M_right(nullptr)
      {}

      inline int
      operator -(__avl_node<_Tp>* const __r)
      { return this->_M_h - __r->_M_h; }

    };

  template <typename _Tp, typename _Comp = less<_Tp>>
    class __avl_tree
    {
    public:
      using node_type = __avl_node<_Tp>;

      __avl_tree(_Tp __init) : __pool_top(0), _M_pool(NODE_MAX)
      { _M_root = _M_allocate(__init); }

      void
      insert(_Tp __t)
      { _M_root = insert_imp(_M_root, __t); }

      void
      print()
      { _M_dfs(_M_root); }

    protected:
      void
      _M_dfs(node_type* __root)
      {
	if (!__root) return;
	cout << __root->_M_data << " ";
	_M_dfs(__root->_M_left);
	_M_dfs(__root->_M_right);
      }

      int
      _M_height(node_type* __n)
      { return __n ? __n->_M_h : 0; }

      node_type*
      _M_rotate_right(node_type* __y)
      {
	node_type* __x = __y->_M_left;
	node_type* __x_left = __x->_M_left;

	__x->_M_right = __y;
	__y->_M_left = __x_left;

	// update height
	__x->_M_h = max(_M_height(__x->_M_left),
			_M_height(__x->_M_right)) + 1;

	__y->_M_h = max(_M_height(__y->_M_left),
			_M_height(__y->_M_right)) + 1;

	return __x;
      }

      node_type*
      _M_rotate_left(node_type* __x)
      {
	node_type* __y = __x->_M_right;
	node_type* __y_left = __y->_M_left;

	__y->_M_left = __x;
	__x->_M_right = __y_left;

	// update height
	__x->_M_h = max(_M_height(__x->_M_left),
			_M_height(__x->_M_right)) + 1;

	__y->_M_h = max(_M_height(__y->_M_left),
			_M_height(__y->_M_right)) + 1;

	return __y;
      }

      node_type*
      insert_imp(node_type* __root, _Tp __t)
      {
	if (!__root) return _M_allocate(__t);

	if (_Comp()(__t, __root->_M_data))
	  __root->_M_left = insert_imp(__root->_M_left, __t);
	else
	  __root->_M_right = insert_imp(__root->_M_right, __t);

	__root->_M_h = max(_M_height(__root->_M_left),
			   _M_height(__root->_M_right)) + 1;

	int __bal = _M_check_blance(__root);

	// LL
	if (__bal > 1 && __t < __root->_M_left->_M_data)
	  return _M_rotate_right(__root);

	// RR
	if (__bal < -1 && __t > __root->_M_right->_M_data)
	  return _M_rotate_left(__root);

	// LR
	if (__bal > 1 && __t > __root->_M_left->_M_data)
	  {
	    __root->_M_left = _M_rotate_left(__root->_M_left);
	    return _M_rotate_right(__root);
	  }

	// RL
	if (__bal < -1 && __t < __root->_M_right->_M_data)
	  {
	    __root->_M_right = _M_rotate_right(__root->_M_right);
	    return _M_rotate_left(__root);
	  }

	return __root;
      }

      node_type*
      _M_allocate(_Tp __t)
      {
	_M_pool[__pool_top++] = node_type(__t);
	return &_M_pool[__pool_top - 1];
      }

      int _M_check_blance(node_type* __n)
      { return __n ? _M_height(__n->_M_left) - _M_height(__n->_M_right) : 0; }

    private:
      int __pool_top;
      node_type* _M_root;
      vector<node_type> _M_pool;
    };
}

#endif  //NOEY_AVL
