#include "perkcards.hpp"
#include <iostream>
#include <ctime>
using namespace std ; 

Perkcard::Perkcard(string name): name(name){}

string Perkcard::get_name() const {return name ;}

Hurrycard::Hurrycard(Hero * Mayor, Hero * Arch, GameMap &map): Perkcard("Hurry") , mayor(Mayor) , arch(Arch) , map(map) {}

void Hurrycard::play(Hero*){

    cout << "[Playing Hurry - perk card] -> Move each hero by two spaces.\n" ;
    string firstMove , secondMove ; 
    cout << "Mayor..where do you want to move first? " ;
    cin >> firstMove ; 
    Location* currentLoc = mayor->GetCurrentLocation() ; 
    Location* firstMoveLoc = map.get_location_by_name(firstMove);
    if(currentLoc->findNeighbor(firstMove))
        mayor->MoveTo(firstMoveLoc) ;        
    else{
        cerr << "what you have chosen is not a neighboring place!!\n" ;
    } 
    cout << "Mayor..what is your second place to move? " ;
    cin >> secondMove ;
    Location* secondMoveLoc = map.get_location_by_name(secondMove);
    if(currentLoc->findNeighbor(secondMove)) 
        mayor->MoveTo(secondMoveLoc) ;        
    else{
        cerr << "what you have chosen is not a neighboring place!!\n" ;
    }  
    cout << "--------------\n" ;
    string AfirstMove , AsecondMove ; 
    cout << "Archaeologist..where do you want to move first? " ;
    cin >> AfirstMove ; 
    Location* AcurrentLoc = arch->GetCurrentLocation() ; 
    Location* AfirstMoveLoc = map.get_location_by_name(AfirstMove);
    if(AcurrentLoc->findNeighbor(AfirstMove))
        arch->MoveTo(AfirstMoveLoc) ;        
    else{
        cerr << "what you have chosen is not a neighboring place!!\n" ;
    } 
    cout << "Archaeologist..what is your second place to move? " ;
    cin >> AsecondMove ;
    Location* AsecondMoveLoc = map.get_location_by_name(AsecondMove);
    if(AcurrentLoc->findNeighbor(AsecondMove)) 
        arch->MoveTo(AsecondMoveLoc) ;        
    else{
        cerr << "what you have chosen is not a neighboring place!!\n" ;
    }      
}

// Repelcard::Repelcard(Dracula * d ,InvisibleMan * i, GameMap & map): Perkcard("Repel") , dracula(d) , invisibleman(i) , map(map){}

// void Repelcard::play(Hero*){

//     cout << "[Playing Repel - perk card] -> Move each monster by two spaces.\n";
//     cout << "where do you want to move the invisible man for the first move? " ; 
//     string firstplace ; cin >> firstplace ;
//     Location* IfirstnewLoc = map.get_location_by_name(firstplace) ;  
//     if(IfirstnewLoc){
//       //  invisibleman.set_location(IfirstnewLoc) ; 
//                 cout << "invisible man moved to " << firstplace << '\n' ; 
//             }
//             else{
//                 cerr << "could not find the place!\n" ;
//             }
//             cout << "where do you want to move the invisible man for the second move? " ;
//             string secondplace ; cin >> secondplace ;
//             Location* IsecondnewLoc = map.get_location_by_name(secondplace) ;  
//             if(IsecondnewLoc){
//            //     invisibleman.set_location(IsecondnewLoc) ; 
//                 cout << "invisible man moved to " << secondplace << '\n' ; 
//             }
//             else{
//                 cerr << "could not find the place!\n" ;
//             }
//             cout << "where do you want to move the dracula for the first move? " ; 
//             string Dfirstplace ; cin >> Dfirstplace ;
//             Location* DfirstLec = map.get_location_by_name(Dfirstplace) ;  
//             if(DfirstLec){
//            //     dracula->set_location(DfirstLec) ; 
//                 cout << "dracula moved to " << Dfirstplace << '\n' ; 
//             }
//             else{
//                 cerr << "could not find the place!\n" ;
//             }
//             cout << "where do you want to move the dracula for the second move? " ;
//             string Dsecondplace ; cin >> Dsecondplace ;
//             Location* DsecondLoc = map.get_location_by_name(Dsecondplace) ;  
//             if(DsecondLoc){
//           //      dracula->set_location(DsecondLoc) ; 
//                 cout << "dracula moved to " << Dsecondplace << '\n' ; 
//             }
//             else
//                 cerr << "could not find the place!\n" ;
            
// }

LateintotheNightCARD::LateintotheNightCARD(): Perkcard("Late into the Night") {}

void LateintotheNightCARD::play(Hero* hero){
    cout << "[Playing Late into the Night - perk card] -> You can have 2 more actions.\n" ;
    hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
    cout << hero->GetName() << " actions changed to " << hero->GetRemainingActions() << '\n' ; 
}

BreakofDawnCARD::BreakofDawnCARD(ItemPool p , GameMap& m) : Perkcard("Break of Dawn") , pool(p) , map(m){}

void BreakofDawnCARD::play(Hero*){
    cout << "[Playing Break of Dawn - perk card] -> The next monster phase is skipped. Take 2 items out of the bag and place them in their location.\n";
    vector<Item> PoolItems = pool.draw_random_items(2) ;
    for(const auto i : PoolItems){
        Location* Loc = map.get_location_by_name(i.getLocationName());
        if(Loc){
            Loc->add_item(i) ;
            cout << "Item " << i.getName() << " placed in location " << i.getLocationName() << "\n";
        }
    }
}

OverstockCard::OverstockCard(ItemPool p , GameMap & m) : Perkcard("Overstock") , pool(p) , map(m){}

void OverstockCard::play(Hero*){

    cout << "[Playing Overstock - perk card] -> Each player should take one item out of the item bag and place it in their location.\n" ;
    vector<Item> PoolItems = pool.draw_random_items(2) ;
    if(PoolItems.size() < 2) cerr << "not enough items drawn from the pool !\n" ;
        Location* LocFirst = map.get_location_by_name(PoolItems[0].getLocationName());
        if(LocFirst){
            LocFirst->add_item(PoolItems[0]) ; 
            cout << "Mayor placed " << PoolItems[0].getName() << " in the location " << PoolItems[0].getLocationName() << '\n' ;
        }
        Location* LocSecond = map.get_location_by_name(PoolItems[1].getLocationName());
        if(LocSecond){
            LocSecond->add_item(PoolItems[1]) ; 
            cout << "Archaeologist placed " << PoolItems[1].getName() << " in the location " << PoolItems[1].getLocationName() << '\n' ;
        }  
}

VisitfromtheDetectiveCARD::VisitfromtheDetectiveCARD(InvisibleMan * i , GameMap & map): Perkcard("Visit from the Detective") ,invisibleman(i) , map(map){}

void VisitfromtheDetectiveCARD::play(Hero*){
    cout << "[Playing Visit from the Detective - perk card] -> Place the invisible man at a location of the player's choice on the game screen.\n" ; 
    cout << "where do you want to move the invisible man? " ; 
    string place ; cin >> place ;
    Location* newLoc = map.get_location_by_name(place) ;  
    if(newLoc){
        invisibleman->set_location(newLoc) ; 
        cout << "invisible man moved to " << place << '\n' ; 
    }
    else{
        cerr << "could not find the place!\n" ;
    }
}

PerkDeck::PerkDeck(){}

void PerkDeck::addCard(unique_ptr<Perkcard> card){
    cards.push_back(move(card)) ; 
}
unique_ptr<Perkcard> PerkDeck::drawcard() {

    if (cards.empty()) 
        throw runtime_error("Deck is empty!");
    
    srand(time(0)); 
    int index = rand() % cards.size();
    auto chosen_card = move(cards[index]);

    cards.erase(cards.begin() + index);

    return chosen_card;
}

