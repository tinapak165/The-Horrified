#include "perkcards.hpp"
#include <iostream>
#include <ctime>
using namespace std ; 

Perkcard::Perkcard(const string name , const string& tex): name(name) , texture(LoadTexture(tex.c_str())) {}

Perkcard::~Perkcard(){ UnloadTexture(texture) ;}

string Perkcard::get_name() const {return name ;}
Texture2D Perkcard::get_texture() const { return texture ;}

Hurrycard::Hurrycard( const vector<Hero*>& heroes, GameMap &map): Perkcard("Hurry" , "../Assets/Perk_Cards/Hurry.png") , heroes(heroes) , map(map) {}

void Hurrycard::play(Hero*){

    if(currentHeroIndex == 2){
        done = true ; 
        return ;
    }

    Hero* hero = heroes[currentHeroIndex] ;
    Location* currentLoc = hero->GetCurrentLocation() ; 

    if(typing){
        int key = GetCharPressed() ;
        while(key>0){
            if(key >= 32 && key <= 125){
                chosenPlace += (char)key ; 
            }
            key = GetCharPressed() ; 
        }
        if(IsKeyPressed(KEY_BACKSPACE) && !chosenPlace.empty()){
            chosenPlace.pop_back() ; 
        }
        if(IsKeyPressed(KEY_ENTER)){
            chosenLocation = map.get_location_by_name(chosenPlace) ; 
            if(chosenLocation && currentLoc->findNeighbor(chosenPlace)){
                validInput = true ; 
                Finished = true ;
                typing = false ;
            }else{
                message = "invalid location or not a neighbor!" ;
                chosenPlace.clear() ; 
                typing = true ; 
            }
        }
    }
    if(Finished && validInput && chosenLocation){
        hero->MoveTo(chosenLocation) ; 
        message = hero->GetName() + " moved to " + chosenPlace ;
        moveStep++ ; 

        if(moveStep == 2){
            moveStep = 0 ;
            currentHeroIndex++ ; 

            if(currentHeroIndex >= heroes.size()){
                done = true ; // همه هیروها حرکت کردند
                return ;
            }
        }

        // ریست برای هیرو بعدی
        typing = true;
        validInput = false;
        Finished = false;
        chosenLocation = nullptr;
        chosenPlace.clear();
    }     
}

void Hurrycard::draw() {
    if (done || currentHeroIndex >= heroes.size()) return;

    // بک‌گراند اصلی کارت
    Rectangle cardRect = {120.0f, 200.0f, 200.0f, 300.0f};
    Texture2D tex = get_texture();
    DrawTexturePro(
        tex,
        {0, 0, (float)tex.width, (float)tex.height},
        cardRect,
        {0, 0},
        0.0f,
        WHITE
    );

    // پنل اطلاعات کارت کنار تصویر
    Rectangle infoPanel = {340.0f, 200.0f, 480.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(RAYWHITE, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);

    Hero* hero = heroes[currentHeroIndex];

    // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    DrawText(("Hero: " + hero->GetName()).c_str(), x, y, 22, DARKBLUE);
    y += 40;

    DrawText("Enter a neighboring location name:", x, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), x, y, 24, BLUE);
    y += 40;

    if (!message.empty()) {
        DrawText(message.c_str(), x, y, 18, MAROON);
    }
}



bool Hurrycard::isDone() const{
    return done ;
}

Repelcard::Repelcard(Dracula * d ,InvisibleMan * i, GameMap & map): Perkcard("Repel" , "../Assets/Perk_Cards/Repel.png") , dracula(d) , invisibleman(i) , map(map){}

void Repelcard::play(Hero*){

    cout << "[Playing Repel - perk card] -> Move each monster by two spaces.\n";
    cout << "where do you want to move the invisible man for the first move? " ; 
    string firstplace ; cin >> firstplace ;
    Location* IfirstnewLoc = map.get_location_by_name(firstplace) ;  
    if(IfirstnewLoc){
        invisibleman->set_location(IfirstnewLoc) ;
        cout << "InvisibleMan moved to " << IfirstnewLoc->get_name() << '\n' ; 
 
    }
    else{
        cerr << "could not find the place!\n" ;
    }
    cout << "where do you want to move the invisible man for the second move? " ;
    string secondplace ; cin >> secondplace ;
    Location* IsecondnewLoc = map.get_location_by_name(secondplace) ;  
    if(IsecondnewLoc){
        invisibleman->set_location(IsecondnewLoc) ;
        cout << "InvisibleMan moved to " << IsecondnewLoc->get_name() << '\n' ; 

    }
    else{
        cerr << "could not find the place!\n" ;
    }
    cout << "where do you want to move the dracula for the first move? " ; 
    string Dfirstplace ; cin >> Dfirstplace ;
    Location* DfirstLec = map.get_location_by_name(Dfirstplace) ;  
    if(DfirstLec){
        dracula->set_location(DfirstLec) ; 
        cout << "Dracula moved to " << DfirstLec->get_name() << '\n' ; 

    }
    else{
        cerr << "could not find the place!\n" ;
    }
    cout << "where do you want to move the dracula for the second move? " ;
    string Dsecondplace ; cin >> Dsecondplace ;
    Location* DsecondLoc = map.get_location_by_name(Dsecondplace) ;  
    if(DsecondLoc){
        dracula->set_location(DsecondLoc) ; 
        cout << "dracula moved to " << Dsecondplace << '\n' ; 
    }
    else
        cerr << "could not find the place!\n" ;
            
}

void Repelcard::draw()
{
}

bool Repelcard::isDone() const
{
    return false;
}

LateintotheNightCARD::LateintotheNightCARD(): Perkcard("Late into the Night" , "../Assets/Perk_Cards/LateIntoTheNight.png") {}

void LateintotheNightCARD::play(Hero* hero){
    cout << "[Playing Late into the Night - perk card] -> You can have 2 more actions.\n" ;
    hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
    cout << hero->GetName() << " actions changed to " << hero->GetRemainingActions() << '\n' ; 
}

void LateintotheNightCARD::draw()
{
}

bool LateintotheNightCARD::isDone() const
{
    return false;
}

BreakofDawnCARD::BreakofDawnCARD(ItemPool p , GameMap& m) : Perkcard("Break of Dawn" , "../Assets/Perk_Cards/BreakOfDawn.png") , pool(p) , map(m){}

void BreakofDawnCARD::play(Hero*){
    cout << "[Playing Break of Dawn - perk card] -> The next monster phase is skipped. Take 2 items out of the bag and place them in their location.\n";
    vector<Item> PoolItems = pool.draw_random_items(2) ;
    for( auto i : PoolItems){
        Location* Loc = map.get_location_by_name(i.getLocationName());
        if(Loc){
       //     Loc->add_item(i , i.getTexture()) ;
            cout << "Item " << i.getName() << " placed in location " << i.getLocationName() << "\n";
        }
    }
}

void BreakofDawnCARD::draw()
{
}

bool BreakofDawnCARD::isDone() const
{
    return false;
}

void OverstockCard::draw()
{
}

bool OverstockCard::isDone() const
{
    return false;
}

OverstockCard::OverstockCard(vector<Hero *> heroes, ItemPool p, GameMap &m) : Perkcard("Overstock", "../Assets/Perk_Cards/Overstock.png"), heroes(heroes), pool(p), map(m) {}

void OverstockCard::play(Hero*){

    Hero* h1 = heroes[0] ;
    Hero* h2 = heroes[1] ;

    cout << "[Playing Overstock - perk card] -> Each player should take one item out of the item bag and place it in their location.\n" ;
    vector<Item> PoolItems = pool.draw_random_items(2) ;
    if(PoolItems.size() < 2) cerr << "not enough items drawn from the pool !\n" ;

    Location* LocFirst = map.get_location_by_name(PoolItems[0].getLocationName());
    if(LocFirst){
        LocFirst->add_item(PoolItems[0]) ; 
        cout << h1->GetName() << " placed " << PoolItems[0].getName() << " in the location " << PoolItems[0].getLocationName() << '\n' ;
    }
    Location* LocSecond = map.get_location_by_name(PoolItems[1].getLocationName());
    if(LocSecond){
        LocSecond->add_item(PoolItems[1]) ; 
        cout << "Archaeologist placed " << PoolItems[1].getName() << " in the location " << PoolItems[1].getLocationName() << '\n' ;
    }     
 
}

VisitfromtheDetectiveCARD::VisitfromtheDetectiveCARD(InvisibleMan * i , GameMap & map): Perkcard("Visit from the Detective" , "../Assets/Perk_Cards/VisitFromTheDetective.png") ,invisibleman(i) , map(map){}

void VisitfromtheDetectiveCARD::play(Hero*){
        if (!invisibleman) {
        cerr << "Error: InvisibleMan is not initialized!\n";
        return;
    }
    cout << "Current location: " << invisibleman->get_location()->get_name() << endl;
    cout << "[Playing Visit from the Detective - perk card] -> Place the invisible man at a location of the player's choice on the game screen.\n" ; 
    cout << "where do you want to move the invisible man? " ; 
    string place ; cin >> place ;
    Location* newLoc = map.get_location_by_name(place) ;  
    if(newLoc){
        invisibleman->set_location(newLoc); 
        cout << "InvisibleMan moved to " << newLoc->get_name() << '\n' ; 

    }
    else{
        cerr << "could not find the place!\n" ;
    }
}

void VisitfromtheDetectiveCARD::draw()
{
}

bool VisitfromtheDetectiveCARD::isDone() const
{
    return false;
}

PerkDeck::PerkDeck(){}

void PerkDeck::addCard(unique_ptr<Perkcard> card){
    cards.push_back(move(card)) ; 
}
unique_ptr<Perkcard> PerkDeck::drawcard() {

    if (cards.empty()) 
        throw runtime_error("Deck is empty!");
    
    //srand(time(0)); 
    int index = rand() % cards.size() ; 
    auto chosen_card = move(cards[index]);

    cards.erase(cards.begin() + index);

    return chosen_card;
}