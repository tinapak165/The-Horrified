#include "Perkcards.hpp"
#include <iostream>
#include <ctime>
using namespace std ; 

Perkcard::Perkcard(const string name , const string& tex): name(name) , texture(LoadTexture(tex.c_str())) {}

Perkcard::~Perkcard(){ UnloadTexture(texture) ;}

string Perkcard::get_name() const {return name ;}
Texture2D Perkcard::get_texture() const { return texture ;}

void Perkcard::DrawInfoPanel(){
    Rectangle infoPanel = {285.0f, 150.0f, 390.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(RAYWHITE, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);
}
bool Perkcard::handleShouldClose()
{
    if (shouldClose) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 1.5f) {
            return true; 
        }
        return false; 
    }  
    return false ;
}

void Perkcard::set_ShouldClose(bool val){ shouldClose = val ; }
void Perkcard::Setmessage(std::string msg){ message = msg; }

void Perkcard::Drawmessage(int y, Color color){
    DrawText(message.c_str(), 300, y, 17, color);
}

void Perkcard::Drawtexture(){
    Rectangle cardRect = {90.0f, 155.0f, 190.0f, 300.0f};
    Texture2D tex = get_texture();
    DrawTexturePro( tex, {0, 0, (float)tex.width, (float)tex.height}, cardRect, {0, 0}, 0.0f, WHITE);
}

std::string Perkcard::type(std::string input){
    int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125) 
                input += (char)key;
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty()) 
            input.pop_back();    
    return input ;  
}

Hurrycard::Hurrycard( const vector<Hero*>& heroes, GameMap &map): Perkcard("Hurry" , "../Assets/Perk_Cards/Hurry.png") , heroes(heroes) , map(map) {}

void Hurrycard::play(Hero*){

    if(currentHeroIndex == 2)
        done = true ; 
    
    Hero* hero = heroes[currentHeroIndex] ;
    Location* currentLoc = hero->GetCurrentLocation() ; 

    if(typing){
        chosenPlace = type(chosenPlace);

        if(IsKeyPressed(KEY_ENTER)){
            chosenLocation = map.get_location_by_name(chosenPlace) ; 
            if(chosenLocation && currentLoc->findNeighbor(chosenPlace)){
                Finished = true ;
                typing = false ;
            }else{
                Setmessage("invalid location or not a neighbor!") ;
                chosenPlace.clear() ; 
                typing = true ; 
            }
        }
    }
    if(Finished){
        hero->MoveTo(chosenLocation) ; 
        Setmessage(hero->GetName() + " moved to " + chosenPlace) ;
        moveStep++ ; 

        if(moveStep == 2){
            moveStep = 0 ;
            currentHeroIndex++ ; 

            if(currentHeroIndex >= heroes.size())
                done = true ; 
        }
        Reset();
    }     
}

void Hurrycard::draw() {
    if (done) return;

    Drawtexture();
    DrawInfoPanel();

    Hero* hero = heroes[currentHeroIndex];

    int y = 200 ;

    DrawText(("Hero: " + hero->GetName()).c_str(), 300, y, 22, DARKBLUE);
    y += 40;

    DrawText("Enter a neighboring location name:", 300, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), 300, y, 24, BLUE);
    y += 40;
    Drawmessage(y , RED);
}

bool Hurrycard::isDone() const{ return done ; }

void Hurrycard::Reset(){
    typing = true;
    Finished = false;
    chosenLocation = nullptr;
    chosenPlace.clear(); 
}

Repelcard::Repelcard(Dracula * d ,InvisibleMan * i, GameMap & map): Perkcard("Repel" , "../Assets/Perk_Cards/Repel.png") , dracula(d) , invisibleman(i) , map(map){}

void Repelcard::play(Hero*){

    Monster* monsters[2] = {dracula , invisibleman} ; 

    if(currentMonsterIndex == 2)
        done = true ; 
    
    Monster* monster = monsters[currentMonsterIndex] ;

    if(typing){

        chosenPlace = type(chosenPlace);

        if(IsKeyPressed(KEY_ENTER)){
            chosenLocation = map.get_location_by_name(chosenPlace) ; 
            if(chosenLocation){
                Finished = true ;
                typing = false ;
            }else{
                Setmessage("invalid location!") ;
                chosenPlace.clear() ; 
                typing = true ; 
            }
        }
    }
    if(Finished && chosenLocation){
        monster->set_location(chosenLocation) ; 
        Setmessage(monster->get_name() + " moved to " + chosenPlace) ;

        moveStep++ ; 

        if(moveStep == 2){
            moveStep = 0 ;
            currentMonsterIndex++ ; 

            if(currentMonsterIndex == 2)
                done = true ;    
        }
        Reset();
    }
}

void Repelcard::draw(){

    if (done) return;

    Drawtexture();
    DrawInfoPanel();

    Monster* monsters[2] = {dracula , invisibleman} ; 
    Monster* monster = monsters[currentMonsterIndex] ;

    int y = 200;

    DrawText(("Monster: " + monster->get_name()).c_str(), 300, y, 22, DARKBLUE);
    y += 40;

    DrawText("Enter any location name:", 300, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), 300, y, 24, BLUE);
    y += 40;

    Drawmessage(y , RED);
}

bool Repelcard::isDone() const{ return done; }

void Repelcard::Reset(){
    typing = true;
    Finished = false;
    chosenLocation = nullptr;
    chosenPlace.clear();
}

LateintotheNightCARD::LateintotheNightCARD(): Perkcard("Late into the Night" , "../Assets/Perk_Cards/LateIntoTheNight.png") {}

void LateintotheNightCARD::play(Hero* hero){

    if(done)return ;

    hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
    Setmessage(hero->GetName() + " actions changed to " + to_string(hero->GetRemainingActions())) ;

    set_ShouldClose(true);
    messageVisible = true ;
    done = true ; 
}

void LateintotheNightCARD::draw(){

    if(handleShouldClose()) {
        messageVisible = false;
        return;
    }

    Drawtexture();
    DrawInfoPanel();
    Drawmessage(220 , RED);     
}

bool LateintotheNightCARD::isDone() const { return done && !messageVisible ; }

BreakofDawnCARD::BreakofDawnCARD(ItemPool& p , GameMap& m) : Perkcard("Break of Dawn" , "../Assets/Perk_Cards/BreakOfDawn.png") , pool(p) , map(m){}

void BreakofDawnCARD::play(Hero*){

    if(done)return ;

    vector<Item> PoolItems = pool.draw_random_items(2) ;
    
    for( auto &i : PoolItems){
        i.loadTexture() ;
        Location* Loc = map.get_location_by_name(i.getLocationName());
        if(Loc){
            Loc->add_item(i) ;
            Setmessage("Item " + i.getName() + " placed in location " + i.getLocationName()) ;
        }
    }

    set_ShouldClose(true);
    messageVisible = true ;
    done = true ; 
}

void BreakofDawnCARD::draw(){

    if(handleShouldClose()) {
        messageVisible = false;
        return;
    }

    Drawtexture();
    DrawInfoPanel();
    Drawmessage(220 , RED);    
}

bool BreakofDawnCARD::isDone() const{ return done && !messageVisible; }

OverstockCard::OverstockCard(ItemPool& p, GameMap &m) : Perkcard("Overstock", "../Assets/Perk_Cards/Overstock.png"),  pool(p), map(m) {}

void OverstockCard::play(Hero*){

    if(done) return ;
    
    auto PoolItems = pool.draw_random_items(2);

    for (auto &i : PoolItems) {
        i.loadTexture();
        Location* Loc = map.get_location_by_name(i.getLocationName());
        if (Loc) {
            Loc->add_item(i);
            Setmessage(" placed " + i.getName() + " in location " + i.getLocationName());
        }
    }  

    set_ShouldClose(true);
    messageVisible = true ;
    done = true ; 
}

void OverstockCard::draw(){

    if(handleShouldClose()) {
        messageVisible = false;
        return;
    }
    Drawtexture();
    DrawInfoPanel();
    Drawmessage(220 , RED); 
}
bool OverstockCard::isDone()const { return done && !messageVisible ;}

VisitfromtheDetectiveCARD::VisitfromtheDetectiveCARD(InvisibleMan* i , GameMap & map): Perkcard("Visit from the Detective" , "../Assets/Perk_Cards/VisitFromTheDetective.png") ,invisibleman(i) , map(map){}

void VisitfromtheDetectiveCARD::play(Hero*){

    if(typing){

        chosenPlace = type(chosenPlace);

        if(IsKeyPressed(KEY_ENTER)){
            Location* chosenLocation = map.get_location_by_name(chosenPlace) ; 
            if(chosenLocation){
                invisibleman->set_location(chosenLocation) ; 
                typing = false;
                done = true;
            }else{
                Setmessage("invalid location!") ;
                typing = true;
                chosenPlace.clear();
            }
        }
    }
}

void VisitfromtheDetectiveCARD::draw(){

    if (done) return;

    Drawtexture();
    DrawInfoPanel();

    int y = 200;

    DrawText("Enter any location name:", 300, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), 300, y, 24, BLUE);
    y += 40;

    Drawmessage(y , RED);
}

bool VisitfromtheDetectiveCARD::isDone() const{ return done; }

PerkDeck::PerkDeck(){}

void PerkDeck::addCard(unique_ptr<Perkcard> card){
    cards.push_back(move(card)) ; 
}
unique_ptr<Perkcard> PerkDeck::drawcard() {

    if (cards.empty()) 
        cout << "out of perk\n";
    
    srand(time(0)); 
    int index = rand() % cards.size() ; 
    auto chosen_card = move(cards[index]);

    cards.erase(cards.begin() + index);
    if(chosen_card)
        return chosen_card;
    return nullptr;
}