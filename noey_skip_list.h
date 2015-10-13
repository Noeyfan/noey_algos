#ifndef NOEY_SKIP_LIST
#define NOEY_SKIP_LIST

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

namespace noey
{
  using std::vector;
  using std::less;
  using std::shared_ptr;
  using std::make_shared;

  template <typename _Tp, typename _Comp, int _MaxLevel>
    class __skip_list;

  template <typename _Tp, int _MaxLevel>
    class __skip_list_node
    {
      using node = __skip_list_node<_Tp, _MaxLevel>;

    public:
      explicit __skip_list_node(_Tp __t)
      : _M_data(__t), _M_forward(_MaxLevel) { }

      ~__skip_list_node() = default;

    private:
      _Tp _M_data;
      vector<shared_ptr<node>> _M_forward;

      template <typename _A, typename _B, int _C>
      friend class __skip_list;
    };

  template <typename _Tp, typename _Comp = less<_Tp>, int _MaxLevel = 16>
    class __skip_list
    {
      using node = __skip_list_node<_Tp, _MaxLevel>;

    public:
      __skip_list(_Tp __min, _Tp __max)
      : _M_max(__max), _M_min(__min), _M_cur_max_level(0),
      _M_head(new node(__min)), _M_tail(new node(__max))
      {
	for (int i = 0; i < _MaxLevel; ++i) {
	  _M_head->_M_forward[i] = _M_tail;
	}
      }

      void
      insert(_Tp __t)
      {
	auto* cur_ptr = _M_head.get();
	vector<node*> update(_MaxLevel);
	for (int level = _M_cur_max_level; level >= 0; --level) {
	  while(_Comp()(cur_ptr->_M_forward[level]->_M_data, __t)) {
	    cur_ptr = cur_ptr->_M_forward[level].get();
	  }
	  update[level] = cur_ptr;
	}
	// if already exist, simply  add to next
	int new_level = _M_flip_coin();
	if (new_level > _M_cur_max_level) {
	  for (int level = _M_cur_max_level + 1; level <= new_level; ++level) {
	    update[level] = _M_head.get();
	  }
	  _M_cur_max_level = new_level;
	}
	auto ins = make_shared<node>(__t);
	for (int level = 0; level <= new_level; ++level) {
	  ins->_M_forward[level] = update[level]->_M_forward[level];
	  update[level]->_M_forward[level] = ins;
	}
      }

      void erase(_Tp __t) {
	auto* cur_ptr = _M_head.get();
	vector<node*> update(_MaxLevel);
	for (int level = _M_cur_max_level; level >= 0; --level) {
	  while(_Comp()(cur_ptr->_M_forward[level]->_M_data, __t)) {
	    cur_ptr = cur_ptr->_M_forward[level].get();
	  }
	  update[level] = cur_ptr;
	}
	cur_ptr = cur_ptr->_M_forward[0].get();
	if (cur_ptr->_M_data != __t) return;

	// erase
	for (int level = 0; level <= _M_cur_max_level; ++level) {
	  if (update[level]->_M_forward[level].get() != cur_ptr) break;
	  update[level]->_M_forward[level] = cur_ptr->_M_forward[level];
	}

	while(_M_cur_max_level > 0 &&
	      _M_head->_M_forward[_M_cur_max_level] == _M_tail) {
	  _M_cur_max_level--;
	}
      }

      bool find(_Tp __t) {
	auto* cur_ptr = _M_head.get();
	vector<node*> update(_MaxLevel);
	for (int level = _M_cur_max_level; level >= 0; --level) {
	  while(_Comp()(cur_ptr->_M_forward[level]->_M_data, __t)) {
	    cur_ptr = cur_ptr->_M_forward[level].get();
	  }
	  update[level] = cur_ptr;
	}
	cur_ptr = cur_ptr->_M_forward[0].get();
	return cur_ptr->_M_data == __t;
      }

      bool empty()
      { return _M_head->_M_forward[0] == _M_tail;}

    private:
      int _M_flip_coin()
      { return rand() % _MaxLevel; }

      _Tp _M_max, _M_min;
      int _M_cur_max_level;
      shared_ptr<node> _M_head;
      shared_ptr<node> _M_tail;
    };
}
#endif  //NOEY_SKIP_LIST
