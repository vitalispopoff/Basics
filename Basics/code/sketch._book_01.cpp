

#include <string>


namespace sketch_book_1
{
	using namespace std;

	struct my_node
	{
		string
			key,
			value;
		my_node
			& left,
			& rite,
			& branch;

		my_node (
			string k, 
			string v, 
			my_node l, 
			my_node r, 
			my_node b
		) :
			key {k},
			value {v},
			left {l},
			rite {r},
			branch {b}
		{}





	}
	





}