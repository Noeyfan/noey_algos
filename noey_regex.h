#ifndef _NOEY_REGEX_H
#define _NOEY_REGEX_H

#include <vector>

namespace noey
{
  using std::vector;

  struct pool
    {
      size_t size;
      char* _pool;
      char* p;

      pool(size_t _s): _pool((char*)malloc(_s)), p(_pool) { }
      ~pool() { free((void*)_pool); }

      void* allocate(size_t s) {
	  char* head = p;
	  p += s;
	  return (void*)head;
      }
    };

  struct _state
    {
      _state(int _c, _state* _out1, _state* _out2)
	: c(_c), out1(_out1), out2(_out2)
	{ }

      int c;
      _state* out1;
      _state* out2;
    };

  struct _frag
    {
      _state* start;
      vector<_state**> out;

      _frag() = default;
      _frag(_state* _s, vector<_state**> _o)
	: start(_s), out(_o) { }
    };

  void concat(vector<_state**>& ss, _state* s) {
      for (auto& sp : ss) {
	  *sp = s;
      }
  }

  template<typename T, typename Alloc, typename... Args>
    T* New(Alloc* alloc, Args... args) {
      return ::new((T*)alloc->allocate(sizeof(T))) T(args...);
    }

  _state*
    build_nfa(const char* postfix, pool* m_pool)
      {
	const char* p;
	_frag stack[1000], *stackp, e1, e2, e;
	_state* s;

#define push_in(s) *stackp++ = s
#define pop_out() *--stackp;

	stackp = stack;

	for (p = postfix; *p; p++) {
	    switch(*p) {
	      case '*':
		e1 = pop_out();
		s = New<_state>(m_pool, 256, e1.start, nullptr);
		concat(e1.out, s);
		push_in(_frag(s, vector<_state**>{&(s->out2)}));
		break;
	      case '|':
		e2 = pop_out();
		e1 = pop_out();
		s = New<_state>(m_pool, 256, e1.start, e2.start);
		e1.out.insert(e1.out.end(), e2.out.begin(), e2.out.end());
		push_in(_frag(s, e1.out));
		break;
	      case '.':
		e2 = pop_out();
		e1 = pop_out();
		concat(e1.out, e2.start);
		// if (!e1.out[0]) std::cerr << "boom";
		push_in(_frag(e1.start, e2.out));
		break;
	      default:
		s = New<_state>(m_pool, *p, nullptr, nullptr);
		push_in(_frag(s, vector<_state**>{&(s->out1)}));
		break;
	    }
	}

	e1 = pop_out();
	_state* matching = New<_state>(m_pool, 257, nullptr, nullptr);
	concat(e1.out, matching);
	return e1.start;
      }

  bool
    match(const char* s, const _state* nfa)
      {
	if (nfa->c == 257) return true;
	if (nfa->c == 256) return match(s, nfa->out1) || match(s, nfa->out2);
	if (nfa->c == (int)*s) {
	    return match(s+1, nfa->out1);
	}
	return false;
      }
}

#endif
