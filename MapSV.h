#include "Map.h"
#include <vector>

class MapSV: public Map{

	private:
	
		std::vector<std::pair<std::string, int>> v;
		int tam;
		
	public:
		
		MapSV();
		
		int bs(std::string k);
		
		void insert(std::pair<std::string,int> p);
		int at(std::string k);
		void erase(std::string k);
		int size();
		bool empty();
};
