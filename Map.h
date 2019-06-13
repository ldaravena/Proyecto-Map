#ifndef MAP_ADT
#define MAP_ADT

#include <string>
#include <utility>
#include <limits>

class Map{

    public:

        virtual void insert(std::pair<std::string,int>) = 0;
		virtual int at(std::string) = 0;
        virtual void erase(std::string) = 0;
		virtual int size() = 0;
		virtual bool empty() = 0;
};

#endif
