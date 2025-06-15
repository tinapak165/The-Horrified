#ifndef VILLAGER_HPP
#define VILLAGER_HPP
#include <iostream>
#include <vector>
class villager{
    
    private:
        const std::string name ; 
        std::string safePlace ;

    public:
        villager(const std::string , std::string) ; 
        villager() ;
        std::string get_name() ; 
        std::string get_safeplace() ; 
        void set_safeplace(std::string) ; 
        //void DisplayVillagers() ; 
        void MoveTo(std::string , std::string) ; 
};

#endif