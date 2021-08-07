#include "ch19.h"

//#include <iostream>

using namespace std;

namespace ch19
{
	template <typename T, typename A>
		m_vector<T, A> & m_vector<T, A>::operator = (const m_vector & v)
	{
		if (this == & v)
			return * this;
		if (space < v.sz)
		{
			delete [] elem;
			elem = alloc.allocate (v.sz);
			space = v.sz;
		}
		sz = v.sz;			
		copy (v.elem, v.elem + sz, elem);
		return * this;
	}
	
	template <typename T, typename A>
		m_vector<T, A> & m_vector<T, A>::operator = (m_vector && v) noexcept (true)
	{
		if (true)
			delete [] elem;
		else
		{
			alloc.destroy (space, elem);
			alloc.deallocate (elem);
		}

		sz = v.sz;
		space = v.space;
		elem = v.elem;
		v.elem = nullptr;
		v.sz = v.space = 0;
		return * this;
	}
	
	template <typename T, typename A>
		void m_vector<T, A>::reserve (int new_space)
	{
		if (new_space <= space)
			return;
		T * p = alloc.allocate(new_space);

		for (int i = 0; i < sz; ++i)
		{
			alloc.construct(& p [i], elem [i]);
			alloc.destroy (& elem[i]);
		}
		alloc.deallocate (elem, space);
		elem = p;
		space = new_space;
	}
	
	template <typename T, typename A>
		void m_vector<T, A>::resize (int new_size, T val)
	{		
		if (new_size < 0)
			return;

		reserve (new_size);
			for (int i = sz; i < new_size; ++i)
				alloc.construct (&elem [i], val);
			for (int i = new_size; i < sz; ++i)
				alloc.destroy (&elem [i]);
			sz = new_size;
	}
	
	template <typename T, typename A>
		void m_vector<T, A>::push_back (T val)
	{
		if (space == 0)
			reserve (8);		
		/// is 'else' redundant?: if space==0 reserve(8) returns sz==0 && space==8
		/// but if space!=0 then and only then space?=sz is to be checked
		else
			if (space == sz)
				reserve (space * 2);
		alloc.construct (& elem [sz], val);
		++sz;
	}

//	----------------------------------------------------------
	
	// unit testing still not introduced - going for this ersatz
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
			testing ("empty constr: space", v.capacity(), 8);
		}
		if (true)
		{
			m_vector<int> v (1, -1);
			testing ("expl constr: size", v.size(), 1);
			testing ("expl constr: space", v.capacity(), 1);
			testing ("expl constr: elem", v[0], -1);
		}
		if (true)
		{
			m_vector<int> v {-1};
			testing ("init constr: size", v.size(), 1);
			testing ("init constr: space", v.capacity(), 1);
			testing ("init constr: elem", v[0], -1);
		}
		if (true)
		{
			m_vector<int> 
				u {-1},
				v {u};
			testing ("copy constr: size", v.size(), 1);
			testing ("copy constr: space", v.capacity(), 1);
			testing ("copy constr: elem", v[0], -1);
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
		}
		if (true)
		{
			m_vector<int>
				v = m_vector<int> {-1};
			testing ("= oper: size", v.size(), 1);
			testing ("= oper: space", v.capacity(), 1);
			testing ("= oper: elem", v[0], -1);
		}
		if (true)
		{
			m_vector<int> 
				u {-1},
				v = u;
			testing ("= copy oper: size", u.size(), v.size());
			testing ("= copy oper: space", u.capacity(), v.capacity());
			testing ("= copy oper: elem", u[0], v[0]);
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
		}
		if (true)
		{
			m_vector<int>
				v(0);
			v.reserve (4);
			testing ("reserve: size", v.size(), 0);
			testing ("reserve: space", v.capacity(), 4);
		}
		if (true)
		{
			m_vector<int>
				v {-1};
			v.resize(2);

			testing ("resize: size", v.size(), 2);
			testing ("resize: space", v.capacity(), 2);
			testing ("resize: elem", v[0], -1);
		}
		if (false)
		{
			auto skrt = [](const auto & v)	// 'auto' XD
			{
				for (int i = 0; i < v.size(); ++i)
					cout
						<< v[i] << ", ";
				cout << '\n';
			};

			m_vector <double>
				a {0, 1, 2, 3},
				b;

			skrt(a);
		
			a.push_back(-1);

			skrt(a);

			a.resize (b.capacity());

			a.reserve (16);

			skrt(a);
	
			a.resize (-1);

			a.resize (4);

			skrt (a);
		}
		cout << "all tests done\n";
	}

	void main()
	{
		test_01();
		//test();
	}
}