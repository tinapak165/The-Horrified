#ifndef VILLAGER_HPP
#define VILLAGER_HPP
#include <iostream>
#include <vector>
class villager{

    private:
        const std::string name ; 
        std::string safePlace ;
        std::string currentLocation ; 
        static std::vector<villager*> vil ; 
    public:
        static std::vector<villager*>& all() ; 
        villager(const std::string , std::string) ; 
        bool in_the_safePlace() const ; 
        void set_currentLocation(std::string) ; 
        std::string get_currentLocation() ; 
        std::string get_name() ; 
        std::string get_safeplace() ; 
        void set_safeplace(std::string) ; 
        //void DisplayVillagers() ; 
        void MoveTo(std::string , std::string) ; 
};

#endif