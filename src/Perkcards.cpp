#include "Perkcards.hpp"
#include <iostream>
#include <ctime>
using namespace std ; 

Perkcard::Perkcard(const string name , const string& tex): name(name) , texture(LoadTexture(tex.c_str())) {}

Perkcard::~Perkcard(){ UnloadTexture(texture) ;}

string Perkcard::get_name() const {return name ;}
Texture2D Perkcard::get_texture() const { return texture ;}

Hurrycard::Hurrycard( const vector<Hero*>& heroes, GameMap &map): Perkcard("Hurry" , "../Assets/Perk_Cards/Hurry.png") , heroes(heroes) , map(map) {}

void Hurrycard::play(Hero*){

    if (showingMessage) {
        if (GetTime() - messageStartTime >= 1.5) {
            showingMessage = false;
            typing = true;  // دوباره اجازه تایپ بده
        }
        return; // هنوز صبر کن
    }

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
                typing = false ; 
                showingMessage = true ; 
                messageStartTime = GetTime() ; 
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


bool Hurrycard::isDone() const{ return done ; }

Repelcard::Repelcard(Dracula * d ,InvisibleMan * i, GameMap & map): Perkcard("Repel" , "../Assets/Perk_Cards/Repel.png") , dracula(d) , invisibleman(i) , map(map){}


void Repelcard::play(Hero*){

    if (showingMessage) {
        if (GetTime() - messageStartTime >= 1.5) {
            showingMessage = false;
            typing = true;
            message.clear()  ;
        }
        return;
    }

    Monster* monsters[2] = {dracula , invisibleman} ; 

    if(currentMonsterIndex == 2){
        done = true ; 
        return ;
    }

    Monster* monster = monsters[currentMonsterIndex] ;

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
            if(chosenLocation){
                validInput = true ; 
                Finished = true ;
                typing = false ;
            }else{
                message = "invalid location!" ;
                chosenPlace.clear() ; 
                typing = false ; 
                showingMessage = true ; 
                messageStartTime = GetTime() ;
            }
        }
    }
    if(Finished && validInput && chosenLocation){
        monster->set_location(chosenLocation) ; 
        message = monster->get_name() + " moved to " + chosenPlace ;
        showingMessage = true ; 
        messageStartTime = GetTime() ; 
        moveStep++ ; 

        if(moveStep == 2){
            moveStep = 0 ;
            currentMonsterIndex++ ; 

            if(currentMonsterIndex == 2){
                done = true ; 
                return ;
            }
        }

        typing = true;
        validInput = false;
        Finished = false;
        chosenLocation = nullptr;
        chosenPlace.clear();
    }
}


void Repelcard::draw(){

    if (done || currentMonsterIndex == 2) return;

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

    Monster* monsters[2] = {dracula , invisibleman} ; 
    Monster* monster = monsters[currentMonsterIndex] ;

    // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    DrawText(("Monster: " + monster->get_name()).c_str(), x, y, 22, DARKBLUE);
    y += 40;

    DrawText("Enter any location name:", x, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), x, y, 24, BLUE);
    y += 40;

    if (!message.empty()) {
        DrawText(message.c_str(), x, y, 18, MAROON);
    }
}

bool Repelcard::isDone() const{ return done; }

LateintotheNightCARD::LateintotheNightCARD(): Perkcard("Late into the Night" , "../Assets/Perk_Cards/LateIntoTheNight.png") {}

void LateintotheNightCARD::play(Hero* hero){
    if(done)return ;

    hero->SetRemainingActions(hero->GetRemainingActions() + 2) ;
    message = hero->GetName() + " actions changed to " + to_string(hero->GetRemainingActions()) ;

    messageVisible = true ;
    messageTimer = GetTime() ;
    done = true ; 
 
}

void LateintotheNightCARD::draw(){
        // اگه پیام قراره نشون داده نشه، هیچی نکش
    if (!messageVisible) return;

        // اگه زمانش گذشته، پیام رو پاک کن
    if ((GetTime() - messageTimer >= messageDuration)) {
        messageVisible = false;
        message.clear();
        return;
    }
        // بک‌گراند اصلی کارت
    Rectangle cardRect = {120.0f, 200.0f, 200.0f, 300.0f};
    Texture2D tex = get_texture();
    DrawTexturePro( tex, {0, 0, (float)tex.width, (float)tex.height}, cardRect, {0, 0},  0.0f, WHITE );

    // پنل اطلاعات کارت کنار تصویر
    Rectangle infoPanel = {340.0f, 200.0f, 480.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(RAYWHITE, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);
      // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    if (!message.empty()) 
        DrawText(message.c_str(), x, y, 18, MAROON);
        
}

bool LateintotheNightCARD::isDone() const { return done && !messageVisible; }

BreakofDawnCARD::BreakofDawnCARD(ItemPool& p , GameMap& m) : Perkcard("Break of Dawn" , "../Assets/Perk_Cards/BreakOfDawn.png") , pool(p) , map(m){}

void BreakofDawnCARD::play(Hero*){

    if(done)return ;

    vector<Item> PoolItems = pool.draw_random_items(2) ;
    
    for( auto &i : PoolItems){
        i.loadTexture() ;
        Location* Loc = map.get_location_by_name(i.getLocationName());
        if(Loc){
            Loc->add_item(i) ;
            message.push_back("Item " + i.getName() + " placed in location " + i.getLocationName());
        }
    }

    messageVisible = true ;
    messageTimer = GetTime() ;
    done = true ; 
}

void BreakofDawnCARD::draw(){
    // اگه پیام قراره نشون داده نشه، هیچی نکش
    if (!messageVisible) return;

        // اگه زمانش گذشته، پیام رو پاک کن
    if ((GetTime() - messageTimer >= messageDuration)) {
        messageVisible = false;
        message.clear();
        return;
    }
        // بک‌گراند اصلی کارت
    Rectangle cardRect = {120.0f, 200.0f, 200.0f, 300.0f};
    Texture2D tex = get_texture();
    DrawTexturePro( tex, {0, 0, (float)tex.width, (float)tex.height}, cardRect, {0, 0},  0.0f, WHITE );

    // پنل اطلاعات کارت کنار تصویر
    Rectangle infoPanel = {340.0f, 200.0f, 480.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(RAYWHITE, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);
      // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    if(!message.empty()){
        for (const auto& msg : message) {
                DrawText(msg.c_str(), x, y, 18, MAROON);
                y += 30; // فاصله بین پیام‌ها
            }          
    }
     
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
            message.push_back(" placed " + i.getName() + " in location " + i.getLocationName());
        }
    }  
    messageVisible = true ;
    messageTimer = GetTime() ;
    done = true ; 
}

void OverstockCard::draw(){

    if (!messageVisible) return;

    if ((GetTime() - messageTimer >= messageDuration)) {
        messageVisible = false;
        message.clear();
        return;
    }
        // بک‌گراند اصلی کارت
    Rectangle cardRect = {120.0f, 200.0f, 200.0f, 300.0f};
    Texture2D tex = get_texture();
    DrawTexturePro( tex, {0, 0, (float)tex.width, (float)tex.height}, cardRect, {0, 0},  0.0f, WHITE );

    // پنل اطلاعات کارت کنار تصویر
    Rectangle infoPanel = {340.0f, 200.0f, 480.0f, 300.0f};
    DrawRectangleRec(infoPanel, Fade(RAYWHITE, 0.94f));
    DrawRectangleLinesEx(infoPanel, 2, GRAY);
      // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    if(!message.empty()){
        for (const auto& msg : message) {
                DrawText(msg.c_str(), x, y, 18, MAROON);
                y += 30; // فاصله بین پیام‌ها
            }          
    }

}
bool OverstockCard::isDone()const { return done && !messageVisible ;}

VisitfromtheDetectiveCARD::VisitfromtheDetectiveCARD(InvisibleMan* i , GameMap & map): Perkcard("Visit from the Detective" , "../Assets/Perk_Cards/VisitFromTheDetective.png") ,invisibleman(i) , map(map){}

void VisitfromtheDetectiveCARD::play(Hero*){

    if(done) return ;

    // مرحله نمایش پیام (چه خطا، چه موفقیت)
    if (showingMessage) {
        if (GetTime() - messageStartTime >= 1.5) {
            showingMessage = false;
            message.clear();

            // اگه پیام موفقیت بود، کارتم کامل شده
            if (!typing && Finished && validInput) {
                done = true;
            } else {
                typing = true; // برای خطا، دوباره اجازه تایپ بده
            }
        }
        return;
    }

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
            if(chosenLocation){
                invisibleman->set_location(chosenLocation) ; 
                message = "invisible man moved to " + chosenPlace ;
                messageStartTime = GetTime() ;
                showingMessage = true;
                typing = false;
                Finished = true;
                validInput = true;


            }else{
                message = "invalid location!" ;
                messageStartTime = GetTime();
                showingMessage = true;
                typing = false;
                chosenPlace.clear();
                validInput = false;
                Finished = false;
            }
        }
    }
}

void VisitfromtheDetectiveCARD::draw(){

    if (done) return;

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

    // اطلاعات کارت
    int x = (int)infoPanel.x + 20;
    int y = (int)infoPanel.y + 20;

    DrawText("Enter any location name:", x, y, 18, DARKGRAY);
    y += 30;

    DrawText(("> " + chosenPlace).c_str(), x, y, 24, BLUE);
    y += 40;

    if (!message.empty()) {
        DrawText(message.c_str(), x, y, 18, MAROON);
    }
}

bool VisitfromtheDetectiveCARD::isDone() const{ return done; }

PerkDeck::PerkDeck(){}

void PerkDeck::addCard(unique_ptr<Perkcard> card){
    cards.push_back(move(card)) ; 
}
unique_ptr<Perkcard> PerkDeck::drawcard() {

    if (cards.empty()) 
        throw runtime_error("Deck is empty!");
    
    srand(time(0)); 
    int index = rand() % cards.size() ; 
    auto chosen_card = move(cards[index]);

    cards.erase(cards.begin() + index);

    return chosen_card;
}