#include "LocationOverview.hpp"
#include <iostream>
#include <iomanip>
using namespace std ; 

void locationOverview::display(){
    //Item i ;
    //Monster m ; 
    //Villager v ; 
    cout << "------------------Location Overview------------------\n"; 
    cout << left << "| " << setw(13) << "Location" << setw(13) << "Item" << setw(13) << "Monsters" << setw(13) << "Villagers   |\n" ;
    cout << "-------------------------------------------------------\n" ; 

    cout << left << "| " << setw(13) << "Docks" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Camp" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Inn" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Mansion" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Abbey" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Museum" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Theatre" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Graveyard" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Barn" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Shop" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Precint" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Institute" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Laboratory" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "| " << setw(13) << "Tower" << setw(13) << ((i.is_there_an_item()) ? (i.name_item + "(" + i.tedad_Item + ")") : "-") << setw(13) 
         << ((m.is_there_monsters()) ? m.name_monster : "-") << setw(13)
         << ((v.is_there_villager()) ?( m.name_villager + "(" + i.safe_place + ")") : "-") << "|\n" ; 

    cout << left << "|" << setw(15) << "|\n"; 
    cout << left << "| Key Locations:" << setw(14) << "|\n"; 
    cout << "| [" << last_place_coffin << "] coffins smashed: " << tedad_broken_coffins << "/4" << setw(10) << "|\n" ; 
    cout << "| [" << last_place_cevidence << "] Evidence collected: " << tedad_collected_evidence << "/5" << setw(14) << "|\n" ; 

    cout << "--------------------------------------------------------------\n" ; 


}   


int main(){
    locationOverview l ; 
    l.display() ; 
}

/*
places:
Docks
Camp
INN
Mansion
Abbey
Museum
Theatre
Graveyard
Barn
Shop
Precint
Institute
Laboratory
Tower
*/
