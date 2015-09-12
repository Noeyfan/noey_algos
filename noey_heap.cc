#ifndef NOEY_HEAP_CC
#define NOEY_HEAP_CC

#include <functional>
#include <vector>
#include <cassert>

namespace noey
{
  // MIN_HEAP
  template <typename _Tp, typename _Comp = std::greater<_Tp>>
    class __min_heap
    {
    public:
      __min_heap(_Tp* __rhs, size_t __size)
      : _M_data(__rhs, __rhs + __size)
      { __heapfy(); }

      __min_heap(std::vector<_Tp>& __rhs)
      : _M_data(__rhs)
      { __heapfy(); }

      _Tp front()
      {
	assert(!_M_data.empty());
	return _M_data[0];
      }

      void pop()
      {
	assert(!_M_data.empty());
	std::swap(_M_data[0], _M_data[_M_data.size() - 1]);
	_M_data.pop_back();
	__bubble_down(0);
      }

    private:
      // move item up to the right pos
      void __bubble_up(size_t __idx, _Comp __comp)
      {
	if (__idx == 0) return;

	size_t __parent_idx = (__idx - 1) >> 2;

	if (__comp(_M_data[__idx], _M_data[__parent_idx]))
	{
	    std::swap(_M_data[__idx], _M_data[__parent_idx]);
	    __bubble_up(__parent_idx);
	}
      }

      // move down up to the right pos
      void __bubble_down(size_t __idx, _Comp __comp)
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
	    std::swap(_M_data[__min_idx], _M_data[__idx]);
	    __bubble_down(__min_idx, __idx);
	  }
      }

      // heapfy
      void __heapfy()
      {
	// O(n)
	for(int __i = _M_data.size() - 1; __i >= 0; __i++)
	  __bubble_down(__i);
      }

      std::vector<_Tp> _M_data;
    };
}
#endif
