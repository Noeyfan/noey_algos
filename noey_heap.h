#ifndef NOEY_HEAP_CC
#define NOEY_HEAP_CC

#include <functional>
#include <vector>
#include <iostream>
#include <cassert>

namespace noey
{
  using std::swap;
  using std::greater;
  using std::vector;

  // BINARY_HEAP
  template <typename _Tp, typename _Comp>
    class __heap
    {
    public:
      __heap(_Tp* __rhs, size_t __size)
      : _M_data(__rhs, __rhs + __size)
      { __heapfy(); }

      __heap(vector<_Tp>& __rhs)
      : _M_data(__rhs)
      { __heapfy(); }

      __heap(__heap& __rhs)
      : _M_data(__rhs.data())
      { __heapfy(); }

      _Tp& top()
      {
	assert(!_M_data.empty());
	return _M_data[0];
      }

      void pop()
      {
	assert(!_M_data.empty());
	swap(_M_data[0], _M_data[_M_data.size() - 1]);
	_M_data.pop_back();
	__bubble_down(0);
      }

      bool empty()
      { return _M_data.empty(); }

      auto& data()
      { return _M_data; }

    private:
      // move item up to the right pos
      void __bubble_up(size_t __idx, _Comp __comp)
      {
	if (__idx == 0) return;

	size_t __parent_idx = (__idx - 1) >> 2;

	if (__comp(_M_data[__idx], _M_data[__parent_idx]))
	{
	    swap(_M_data[__idx], _M_data[__parent_idx]);
	    __bubble_up(__parent_idx);
	}
      }

      // move down up to the right pos
      void __bubble_down(size_t __idx, _Comp __comp = _Comp())
      {
	size_t __len = _M_data.size(),
	       __left_child_idx = __idx * 2 + 1,
	       __right_child_idx = __idx * 2 + 2,
	       __min_idx = __idx;

	if (__left_child_idx >= __len)
	  return;

	if (!__comp(_M_data[__idx], _M_data[__left_child_idx]))
	  __min_idx = __left_child_idx;

	if (__right_child_idx < __len &&
	    !__comp(_M_data[__min_idx], _M_data[__right_child_idx]))
	  __min_idx = __right_child_idx;

	if (__min_idx != __idx)
	  {
	    swap(_M_data[__min_idx], _M_data[__idx]);
	    __bubble_down(__min_idx, __comp);
	  }
      }

      // heapfy
      void __heapfy()
      {
	// O(n)
	for(int __i = _M_data.size() - 1; __i >= 0; __i--)
	  __bubble_down(__i);
      }

      vector<_Tp> _M_data;
    };
}
#endif
