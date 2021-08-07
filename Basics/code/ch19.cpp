#include "ch19.h"

using namespace std;

namespace ch19
{
	template <typename T, typename A>
		void m_vector<T, A>::reserve (int new_space)
	{
		if (new_space <= this -> space)
			return;
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


	void test_01()
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
			auto a = []() -> m_vector<int>
			{
				m_vector<int> temp {-1};
				return temp;
				 //return m_vector<int>(); //doesn't call the copy/move constr !!!
			};
			m_vector<int> v {a()};
			
			testing ("move constr: size", v.size(), 1);
			testing ("move constr: space", v.capacity(), 1);
			testing ("move constr: elem", v[0], -1);
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

	void test_02()
	{
		if (true)
		{
			m_vector<int> v;
			v.reserve (1);
			testing ("empty constr + 1 : size", v.size(), 0);
			testing ("empty constr + 1 : space", v.capacity(), 1);
			testing ("empty constr + 1 : *", int (v.addr()!= nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v;
			v.reserve (0);
			testing ("empty constr + 0 : size", v.size(), 0);
			testing ("empty constr + 0 : space", v.capacity(), 0);
			testing ("empty constr + 0 : *", int (v.addr()== nullptr), 1);
			++test_no;
		}

		if (true)
		{
			m_vector<int> v {-1};
			v.reserve (0);
			testing ("empty constr -1 : size", v.size(), 1);
			testing ("empty constr -1 : space", v.capacity(), 1);
			++test_no;
		}
	}

	void main()
	{		
		//test_01(); // basic functioning

		test_02(); // reserve

		cout << "all tests done (" << test_no << ")\n";
	}
}