#include "ch19.h"

using namespace std;

namespace ch19
{
	template <typename T, typename A>
		void m_vector<T, A>::reserve (int new_space)
	{
		//if (new_space <= this -> space)
		if (new_space < 0)
			return;	
		if (new_space == 0)
		{
			for (int i = 0; i < this -> sz; ++i)
				this -> alloc.destroy (this -> elem + i);
			this -> alloc.deallocate (this -> elem, this -> space);
			this -> elem = nullptr;
			this -> sz = this -> space = 0;
			return;
		}

		vector_base<T, A> 
			b (this -> alloc, new_space);
		uninitialized_copy (this -> elem, & this -> elem [this -> sz], b.elem);
		b.sz = this -> sz;
		for (int i = 0; i < this -> sz; ++i)
			this -> alloc.destroy (& this -> elem[i]);
		swap <vector_base <T, A>> (* this, b);
	}
	
	template <typename T, typename A>
		void m_vector<T, A>::resize (int new_size, T val)
	{		
		if (new_size < 0)
			return;
		reserve (new_size);
		for (int i = this -> sz; i < new_size; ++i)
			this -> alloc.construct (& this -> elem [i], val);
		for (int i = new_size; i < this -> sz; ++i)
			this -> alloc.destroy (& this -> elem [i]);
		this -> sz = new_size;
	}
	
	template <typename T, typename A>
		void m_vector<T, A>::push_back (T val)
	{
		if (this -> space == 0)
			reserve (8);		
		else
			if (this -> space == this -> sz)
				reserve (2 * this -> space);
		this -> alloc.construct (& this -> elem [this -> sz], val);
		++(this -> sz);
	}

//	----------------------------------------------------------
	
	// unit testing still not introduced - going for this ersatz
	int test_no {0};

	template <typename T>
		void printing (m_vector<T> & v)
	{
		cout
			<< "\nsz : " << v.size() <<",\tspace : " << v.capacity() << '\n';
	}
	template <typename U>
		void testing (string name, U expected, U given)
	{		
		if (given != expected)
		cout
			<< name << "\tfailed\n";
	}

//	----------------------------------------------------------

	void test_min()
	{
		if (true)
		{
			m_vector<int> v;
			testing ("empty constr: size", v.size(), 0);
			testing ("empty constr: space", v.capacity(), 0);
			++test_no;
		}
		
		if (true)
		{
			m_vector<int> v (1, -1);
			testing ("expl constr: size", v.size(), 1);
			testing ("expl constr: space", v.capacity(), 1);
			testing ("expl constr: elem", v[0], -1);
			++test_no;
		}
		
		if (true)
		{
			m_vector<int> v {-1};
			testing ("init constr: size", v.size(), 1);
			testing ("init constr: space", v.capacity(), 1);
			testing ("init constr: elem", v[0], -1);
			++test_no;
		}
		
		if (true)
		{
			m_vector<int> 
				u {-1},
				v {u};
			testing ("copy constr: size", v.size(), 1);
			testing ("copy constr: space", v.capacity(), 1);
			testing ("copy constr: elem", v[0], -1);
			++test_no;
		}
		
		if (true)
		{	
			void * temp_ptr = nullptr;
			auto a = [&]() -> m_vector<int>
			{
				m_vector<int> temp {-1};
				temp_ptr = (void *) temp.addr();
				return temp;
			};
			m_vector<int> v {a()};
			
			testing ("move constr: size", v.size(), 1);
			testing ("move constr: space", v.capacity(), 1);
			testing ("move constr: elem", v[0], -1);
			testing ("move constr: *", (int) temp_ptr, (int) v.addr());
			++test_no;
		}
		
		if (true)
		{
			m_vector<int>
				v = m_vector<int> {-1};
			testing ("= oper: size", v.size(), 1);
			testing ("= oper: space", v.capacity(), 1);
			testing ("= oper: elem", v[0], -1);
			++test_no;
		}
		
		if (true)
		{
			m_vector<int> 
				u {-1},
				v = u;
			testing ("= copy oper: size", u.size(), v.size());
			testing ("= copy oper: space", u.capacity(), v.capacity());
			testing ("= copy oper: elem", u[0], v[0]);
			++test_no;
		}
		
		if (true)
		{
			void 
				* ptr = nullptr;
			auto a = [&]() -> m_vector<int>
			{
				m_vector<int> temp {-1};
				ptr = (void *)temp.addr();
				return temp;
			};
			m_vector<int>
				v = a();
			testing ("= move oper: size", v.size(), 1);
			testing ("= move oper: space", v.capacity(), 1);
			testing ("= move oper: elem", v[0], -1);			
			testing ("= move oper: *", (int) ptr, (int) v.addr());
			++test_no;
		}
		
		if (true)
		{
			m_vector<int>
				v(0);
			v.reserve (4);
			testing ("reserve: size", v.size(), 0);
			testing ("reserve: space", v.capacity(), 4);
			++test_no;
		}
		
		if (true)
		{
			m_vector<int>
				v {-1};
			v.resize(2);
			testing ("resize: size", v.size(), 2);
			testing ("resize: space", v.capacity(), 2);
			testing ("resize: elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v(0);
			v.push_back (-1);
			testing ("push_back", v.size(), 1);
			testing ("push_back", v.capacity(), 8);
			testing ("push_back", v[0], -1);
			++test_no;
		}
	}

	void test_reserve()
	{
		if (true)
		{
			m_vector<int> v;
			v.reserve (1);
			testing ("reserve : empty, 1 : size", v.size(), 0);
			testing ("reserve : empty, 1 : space", v.capacity(), 1);
			testing ("reserve : empty, 1 : *", int (v.addr()!= nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v;
			v.reserve (0);
			testing ("reserve : empty, 0 : size", v.size(), 0);
			testing ("reserve : empty, 0 : space", v.capacity(), 0);
			testing ("reserve : empty, 0 : *", int (v.addr()== nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v {-1};
			v.reserve (0);
			testing ("reserve : init, 0 : size", v.size(), 0);
			testing ("reserve : init, 0 : space", v.capacity(), 0);
			testing ("reserve : init, 0 : *", int (v.addr() == nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v {-1};
			v.reserve (2);
			testing ("reserve : init, 2 : size", v.size(), 1);
			testing ("reserve : init, 2 : space", v.capacity(), 2);
			testing ("reserve : init, 2 : elem", v[0], -1);
			++test_no;
		}
	}

	void test_resize()
	{
		if (true)
		{
			m_vector<int> v;
			v.resize (0);
			testing ("resize : empty,0 : size", v.size(), 0);
			testing ("resize : empty,0 : space", v.capacity(), 0);
			testing ("resize : empty,0 : *", int (v.addr() == nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v;
			v.resize (-1);
			testing ("empty constr ,-1 : size", v.size(), 0);
			testing ("empty constr ,-1 : space", v.capacity(), 0);
			testing ("empty constr ,-1 : *", int (v.addr() == nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v;
			v.resize (1);
			testing ("empty constr, 1 : size", v.size(), 1);
			testing ("empty constr, 1 : space", v.capacity(), 1);
			testing ("empty constr, 1 : *", int (v.addr() != nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v {-1, -2};
			v.resize (1);
			testing ("init constr 2, 1 : size", v.size(), 1);
			testing ("init constr 2, 1 : space", v.capacity(), 1);
			testing ("init constr 2, 1 : elem", v[0], -1);
			++test_no;
		}

		if (false)
		{
			m_vector<int> v {-1};
			v.resize (0);
			testing ("resize : init, 0 : size", v.size(), 0);
			testing ("resize : init, 0 : space", v.capacity(), 0);
			testing ("resize : init, 0 : *", int (v.addr() == nullptr), 1);
			++test_no;
		}
	}

	void main()
	{		
		//test_min(); // basic functioning

		test_reserve();

		test_resize();

		cout << "\nAll tests done (" << test_no << ").\n";
	}
}

namespace ch19_try_this
{
	template <typename T, typename A>
		m_vector <T, A> & m_vector <T, A>::operator = (const m_vector & v)
	{
		if (this == & v)
			return * this;
		if (space < v.sz)
		{
			elem = alloc.allocate (v.sz);
			space = v.sz;
		}
		sz = v.sz;
		copy (v.elem.get(), v.elem.get() + sz, elem.get());
		return * this;
	}

	template <typename T, typename A>
		m_vector <T, A> & m_vector <T, A>::operator = (m_vector && v) noexcept
	{
		sz = v.sz;
		space = v.space;
		elem.reset(v.elem);
		v.sz = v.space = 0;
		return * this;
	}

	template <typename T, typename A>
		void m_vector <T, A>::reserve (int new_space)
	{
		if (new_space <= space)
			return;
		unique_ptr<T> p {alloc.allocate (new_space)};
		copy (elem.get(), elem.get() + sz, p.get());
		elem.reset (p.release());
		
		space = new_space;
	}

	template <typename T, typename A>
		void m_vector <T, A>::resize (int new_size, T val)
	{
		if (new_size < 0)
			return;
		reserve (new_size);
		for (int i = sz; i < new_size; ++i)
			alloc.construct (& elem.get() [i], val);
		for (int i = new_size; i < sz; ++i)
			alloc.destroy (& elem.get() [i]);
		sz = new_size;
	}

	template <typename T, typename A>
		void m_vector <T, A>::push_back (T val)
	{
		if (space == 0)
			reserve (8);
		else 
			if (space == sz)
				reserve (space * 2);
		alloc.construct (& elem.get() [sz], val);
		++sz;
	}

//	----------------------------------------------------------
	
	int test_no {0};

	template <typename T>
		void printing (m_vector <T> & v)
	{
		cout
			<< "\nsz : " << v.size() <<",\tspace : " << v.capacity() << '\n';
	}
	template <typename U>
		void testing (string name, U expected, U given)
	{		
		if (given != expected)
		cout
			<< name << "\tfailed\n";
	}

//	----------------------------------------------------------	

	void test_min()
	{
		if (true)
		{
			m_vector <int> v;
			testing ("empty : size", v.size(), 0);
			testing ("empty : space", v.capacity(), 8);
			++test_no;
		}

		if (true)
		{
			m_vector <int> v (1, -1);
			testing ("expl : size", v.size(), 1);
			testing ("expl : space", v.capacity(), 1);
			testing ("expl : elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			m_vector <int> v {-1, -2};
			testing ("init : size", v.size(), 2);
			testing ("init : space", v.capacity(), 2);
			testing ("init : elem", v [0], -1);
			testing ("init : elem", v [1], -2);
			++test_no;
		}
	
		if (true)
		{
			m_vector <int> 
				u {-1},
				v {u};
			testing ("copy : size", v.size(), 1);
			testing ("copy : space", v.capacity(), 1);
			testing ("copy : elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			void * temp_ptr = nullptr;
			auto a = [&]() -> m_vector <int>
			{
				m_vector <int> temp {-1};
				temp_ptr = (void *) temp.addr();
				return temp;
			};
			m_vector <int> v {a()};

			testing ("move : size", v.size(), 1);
			testing ("move : space", v.capacity(), 1);
			testing ("move : *", (int) temp_ptr, (int) v.addr());
			++test_no;
		}

		if (true)
		{
			m_vector <int>
				v = m_vector <int> {-1};
			testing ("= : size", v.size(), 1);
			testing ("= : space", v.capacity(), 1);
			testing ("= : elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			m_vector <int>
				u {-1},
				v = u;
			testing ("= copy: size", u.size(), v.size());
			testing ("= copy: space", u.capacity(), v.capacity());
			testing ("= copy: elem", u[0], v[0]);
			++test_no;
		}

		if (true)
		{
			void * ptr = nullptr;
			auto a = [&]() -> m_vector <int>
			{
				m_vector <int> temp {-1};
				ptr = (void *) temp.addr();
				return temp;
			};
			m_vector <int>
				v = a();
			testing ("= move: size", v.size(), 1);
			testing ("= move: space", v.capacity(), 1);
			testing ("= move: *", (int) ptr, (int) v.addr());
			++test_no;
		}
	}

	void test_reserve()
	{
		if (true)
		{
			m_vector <int> v;
			v.reserve (1);
			testing ("reserve : empty, 1: size", v.size(), 0);
			testing ("reserve : empty, 1: space", v.capacity(), 8);
			testing ("reserve : empty, 1: *", int (v.addr() != nullptr), 1);
			++test_no;
		}
	}

	void test_resize()
	{
		if (true)
		{
			m_vector <int> v;
				v.resize(0);
			testing ("resize : init, 0 : size", v.size(), 0);
			testing ("resize : init, 0 : space", v.capacity(), 8);
			testing ("resize : init, 0 : *", int (v.addr() != nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector <int> v;
			v.resize(1);
			testing ("resize : init, 1 : size", v.size(), 1);
			testing ("resize : init, 1 : space", v.capacity(), 8);
			testing ("resize : init, 1 : elem", v[0], 0);
			++test_no;
		}
				
		if (true)
		{
			m_vector <int> v;
			v.resize(1, -1);
			testing ("resize : init, 1 : size", v.size(), 1);
			testing ("resize : init, 1 : space", v.capacity(), 8);
			testing ("resize : init, 1 : elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			m_vector <int> v {-1, -2};
			v.resize (1);
			testing ("resize : init 2, 1 : size", v.size(), 1);
			testing ("resize : init 2, 1 : space", v.capacity(), 2);
			testing ("resize : init 2, 1 : elem", v[0], -1);
			++test_no;	
		}
	}

	void test_push_back()
	{
		if (true)
		{
			m_vector <int> v;
			v.push_back (-1);
			testing ("push_back, empty : size", v.size(), 1);
			testing ("push_back, empty : space", v.capacity(), 8);
			testing ("push_back, empty : elem", v[0], -1);
			++test_no;
		}

		if (true)
		{
			m_vector <int> v (8);
			void * ptr = (void *) v.addr();
			v.push_back (-1);
			testing ("push_back, expl, 8 : size", v.size(), 9);
			testing ("push_back, expl, 8 : space", v.capacity(), 16);
			testing ("push_back, expl, 8 : elem", v[8], -1);
			testing ("push_back, expl, 8 : *", int (ptr !=  (void *) v.addr()), 1);
			++test_no;
		}
	}

	void main()
	{
		test_min();
		test_reserve();
		test_resize();
		test_push_back();

		cout << "\nAll tests done (" << test_no << ").\n";		
	}
}