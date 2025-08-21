#include "SaveManager.hpp"

SaveManager::SaveManager(Game & game) : game(game){}

void SaveManager::saveGame(const std::string & filename)
{
    std::ofstream file(filename) ;
    if(!file.is_open()) return ; 

    file << "# players info\n" ; 
    file << "player1: " << game.getPlayer1().name  << ',' << game.getPlayer1().hero->GetName() << '\n';
    file << "player2: " << game.getPlayer2().name << ',' << game.getPlayer2().hero->GetName()  << '\n';

    file << "\n# Hero\n" ;
    for(const auto h : game.get_turnManager().get_heroes()){
        file << "hero: " << h->GetName() << '\n' ; 
        file << "location: " << h->GetCurrentLocation()->get_name() << '\n' ;
        file << "available perk: " ;
        for(const auto& p : h->GetAvailablePerkCards())
            file << p->get_name() << ',' ; 
        file << '\n';

        file << "played perk: " ;
        for(const auto& p : h->GetPlayedPerkCards())
            file << p->get_name() << ',' ;
        file << '\n';

        file << "items: " << '\n' ;  
        for( const auto& i : h->GetItems())
            file << i.getName() << ',' << i.color_to_string(i.getColor()) << ','
                << i.getStrength() << ',' << i.getLocationName() << ',' << i.get_TexturePath() << '\n';
        file << '\n' ;

    }
    file << "# turn info\n" ;
    file << "turn: " << game.get_turnManager().get_active_hero()->GetName() << '\n' ; 

    file << "\n# Monster\n" ; 
    file << "monster: " << game.get_dracula()->get_name() << '\n' ;
    file << "location: " << game.get_dracula()->get_location()->get_name()  << '\n' ;
    file << "monster: " << game.get_invisibleMan()->get_name() << '\n' ;
    file << "location: " << game.get_invisibleMan()->get_location()->get_name()  << '\n' ;

    file << "\n# locations:\n" ;
    for(const auto& loc : game.get_map().get_locations()){
        file << "location: " << loc->get_name() << '\n' ;
        file << "items: " ;
        for( const auto i : loc->get_items())
            file << i.getName() << ',' << i.color_to_string(i.getColor()) << ','
                << i.getStrength() << ',' << i.getLocationName() << ',' << i.get_TexturePath() << ';';

        file << '\n' ;
        file << "villagers: " ; 
        for( const auto vill : loc->get_villagers())
            file << vill->get_name() << ',' ; 
        file << '\n' ;
    }
    file << "coffins: " ;
    for(auto& pair : game.get_dracula()->get_coffins_map())
        file << (pair.second ? '1' : '0');
    file << '\n' ;

    file << "evidence: " ;
    for(auto & evi : game.get_invisibleMan()->get_evidence_locations())
        file << evi << ',' ; 
    file << '\n' ;

    file << "played monstercards:" ;
    for(auto& card : game.get_MonsterDeck().get_drawncardsName())
        file << card << ',' ;
    file << '\n' ;

    file << "terror level:" ;
    file << game.get_terror_level() << '\n' ;
    
    file.close();
}

void SaveManager::loadGame(const std::string & filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) 
        std::cerr << "Could not open " << filename << '\n';

    std::string line;
    Hero* currentHero = nullptr;
    Location* currentLocation = nullptr;

    while(getline(file , line)){

        if(line.empty() || line[0] == '#') continue;

        if(line.find("player1:" , 0) == 0){
            std::string data = line.substr(9) ; 
            std::stringstream ss(data) ;
            std::string playername , heroname ;
            getline(ss, playername, ',');
            getline(ss, heroname, ',');

            Hero* h = game.get_turnManager().find_hero_by_name(heroname);
            if(!h) {
                h = game.create_hero_by_name(heroname) ;
                game.get_turnManager().add_hero(h);
            }
            game.setPlayer1(playername , h);
        }

        else if(line.find("player2:" , 0) == 0){
            std::string data = line.substr(9) ; 
            std::stringstream ss(data) ;
            std::string playername , heroname ;
            getline(ss, playername, ',');
            getline(ss, heroname, ',');

            Hero* hero = game.get_turnManager().find_hero_by_name(heroname);
            if(!hero) {
                hero = game.create_hero_by_name(heroname) ;
                game.get_turnManager().add_hero(hero);
            }
            game.setPlayer2(playername , hero);
        }
        else if(line.find("hero:" , 0) == 0){
            std::string name = line.substr(6); 
            currentHero = game.get_turnManager().find_hero_by_name(name);

            if(!currentHero){
                currentHero = game.create_hero_by_name(name);
                if(currentHero)
                    game.get_turnManager().add_hero(currentHero);  
            }
        }
        else if(line.find("location: " , 0) == 0 && currentHero){
            std::string name = line.substr(10) ; 
            Location* loc = game.get_map().get_location_by_name(name) ;
            currentHero->SetCurrentLocation(loc) ;
        }
        else if(line.find("available perk:" , 0) == 0 && currentHero){
            std::string perkLine = line.substr(16) ;
            std::stringstream ss(perkLine) ;
            std::string perk ; 
            while(getline(ss , perk , ',')){
                if(!perk.empty()){
                    auto card = game.find_perk_by_name(perk) ;
                    if(card)
                        currentHero->AddAvailablePerk(std::move(card)) ;
                }
            }
        }
        else if(line.find("played perk:" , 0) == 0 && currentHero){
            std::string perkLine = line.substr(13) ;
            std::stringstream ss(perkLine) ;
            std::string perk ; 
            while(getline(ss , perk , ',')){
                if(!perk.empty()){
                    auto card = game.find_perk_by_name(perk) ;
                    if(card)
                        currentHero->addPlayedCards(std::move(card)) ;
                }
            }
        }
        else if(line.find("items:" , 0 ) == 0 && currentHero){
            while(getline(file , line) && !line.empty()){
                std::stringstream itemStream(line);
                std::string name , colorStr , strengthStr , LocName , texture ;
                if(!getline(itemStream, name, ',')) continue;
                if(!getline(itemStream, colorStr, ',')) continue;
                if(!getline(itemStream, strengthStr, ',')) continue;
                if(!getline(itemStream, LocName, ',')) continue;
                if(!getline(itemStream, texture, ',')) continue;

                ItemColor color = game.string_to_color(colorStr);
                int strength = stoi(strengthStr);
                Item item(name , color , strength , LocName , texture);
                item.loadTexture() ;

                currentHero->addItems(item);
            }
            currentHero = nullptr ;
        }
        else if(line.find("turn:" , 0) == 0){
            std::string active_name = line.substr(6) ;
            game.get_turnManager().set_active_hero(active_name) ;
        }
        else if(line.find("monster:" , 0) == 0) {
            std::string monstername = line.substr(9); 
            getline(file , line); 
            if(line.find("location: " , 0 ) == 0){
                std::string locname = line.substr(10);
                Location* loc = game.get_map().get_location_by_name(locname);

                if(monstername == "Dracula") game.get_dracula()->set_location(loc ? loc : nullptr); 
                else if(monstername == "InvisibleMan") game.get_invisibleMan()->set_location(loc ? loc : nullptr); 
            
            }
        }
        else if(line.find("location: " , 0) == 0){
            std::string locname = line.substr(10) ;
            currentLocation = game.get_map().get_location_by_name(locname) ; 
        }
        else if(line.find("items:", 0) == 0 && currentLocation){
            std::string itemstr = line.substr(6);
            if(!itemstr.empty() && itemstr[0] == ' ')
                itemstr = itemstr.substr(1);

            if(itemstr.empty())
                continue;

            std::stringstream ss(itemstr);
            std::string itemData;

            while(getline(ss, itemData, ';')){
                if(itemData.empty()) continue;

                std::stringstream itemStream(itemData);
                std::string name , colorStr , strengthStr , Locname , texture ;

                if(!getline(itemStream, name, ','))  continue; 
                if(!getline(itemStream, colorStr, ',')) continue;
                if(!getline(itemStream, strengthStr, ',')) continue;
                if(!getline(itemStream, Locname, ',')) continue;
                if(!getline(itemStream, texture, ',')) continue;

                ItemColor color = game.string_to_color(colorStr);
                int strength = stoi(strengthStr);
                Item item(name, color, strength, Locname, texture);
                item.loadTexture() ;
                currentLocation->add_item(item);
            }
        }
        else if(line.find("villagers:" , 0) == 0 && currentLocation){
            std::string villagerStr = line.substr(11) ; 
            std::stringstream ss(villagerStr) ; 
            std::string villName ; 
            while (getline(ss, villName, ',')) {
                if (villName.empty()) continue;

                Villager* vill = Villager::find_villager_by_name(villName);
                if(!vill) 
                    game.create_villager(villName , currentLocation) ;
                if(vill) 
                    currentLocation->add_villager(vill) ;   
            }
        }
        else if(line.find("coffins:" , 0) == 0){
            std::string flags = line.substr(9);
            std::vector<std::string> locs = {"Cave", "Dungeon", "Crypt", "Graveyard"};
            for (size_t i = 0; i < flags.size() && i < locs.size(); ++i) {
                if (flags[i] == '1') 
                  game.get_dracula()->destroy_coffin_at(locs[i]);    
            }
        }
        else if(line.find("evidence:" , 0) == 0){
            std::string loc = line.substr(10) ; 
            std::stringstream ss(loc) ;
            std::string evi ;
            while(getline(ss , evi , ',')){
                if(!evi.empty())
                    auto itemlocation = game.get_invisibleMan()->add_evidence(evi) ;
            }
        }
        else if(line.find("played monstercards:" , 0) == 0){
            std::string name = line.substr(20) ; 
            std::stringstream ss(name) ;
            std::string card ;
            while(getline(ss , card , ',')){
                if(!card.empty()){
                    game.get_MonsterDeck().removeCardByName(card) ;
                }
            }
        }
        else if(line.find("terror level:" , 0) == 0){
            int level = std::stoi(line.substr(13)) ; 
            game.set_terror_level(level) ;
        }

    }
    file.close() ;
}

std::string SaveManager::generateNextFile()
{
    int index = 1 ; 
    while(true){
        std::string filename = "save" + std::to_string(index) + ".txt" ;
        std::ifstream file(filename) ;
        if(!file.good()){
            return filename ; 
        }
        index++ ;
    }
}

std::vector<std::string> SaveManager::getFiles()
{
    std::vector<std::string> files ;
    std::ifstream file("save_list.txt") ; 
    std::string line ; 
    while(std::getline(file , line)){
        if(!line.empty())
            files.push_back(line) ;
    }
    return files ;
}

void SaveManager::registerSaveFiles(const std::string & filename)
{
    std::ofstream file("save_list.txt" , std::ios::app) ;
    if(file.is_open())
        file << filename << '\n' ;
}
