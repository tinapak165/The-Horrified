
#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "Location.hpp"
#include <vector>
#include <memory>

class GameMap {
private:
    std::vector<std::unique_ptr<Location>> locations;

public:
    void build_map(); 
    // Location* find_location_by_name(const std::string& name);
     const std::vector<std::unique_ptr<Location>>& get_locations() const;  
    // چرا std::unique_ptr<Location> استفاده شده؟
    // چون Location قراره حاوی اشاره‌گرهایی به Hero*، Monster* و غیره باشه، استفاده از smart pointer مثل unique_ptr باعث می‌شه:
    
    // مدیریت حافظه به‌صورت اتوماتیک باشه.
    
    // از مشکلات memory leak جلوگیری بشه.
    
    // همچنان بتونی از ارجاع و اشاره‌گر برای رفت‌و‌برگشت بین لوکیشن‌ها استفاده کنی
};

#endif
