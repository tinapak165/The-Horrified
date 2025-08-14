#include "Button.hpp"

ClickableText::ClickableText(const std::string& txt, Vector2 pos, int size, Color col)
    : text(txt), position(pos), fontSize(size), color(col) {
    int width = MeasureText(text.c_str(), fontSize);
    bounds = { pos.x, pos.y, (float)width, (float)fontSize };
}
void ClickableText::Draw() {
    DrawText(text.c_str(), position.x, position.y, fontSize, color);
    if (CheckCollisionPointRec(GetMousePosition(), bounds)) 
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, RED);
}

bool ClickableText::isClicked() const {
    return  IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), bounds);
}

std::string ClickableText::get_text(){ return text;}

Button::Button(const std::string& path, Vector2 position , float scale) : scale(scale) {
    texture = LoadTexture(path.c_str());

    bounds = {position.x, position.y, 
            (float)texture.width*scale, (float)texture.height*scale};
}

void Button::Draw() {
       
      //  DrawTexture(texture, static_cast<int>(bounds.x),static_cast<int>(bounds.y), WHITE);
    DrawTextureEx(texture, (Vector2){bounds.x, bounds.y}, 0.0f, scale, WHITE); //with scale
    if (CheckCollisionPointRec(GetMousePosition(), bounds)) {
        DrawRectangleLinesEx(bounds, 2.0f, RED);
    }
}    

bool Button::isPressed()const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), bounds);
}

Vector2 Button::GetPosition() const{
return {bounds.x, bounds.y} ; 
}

Vector2 Button::GetSize() const{
return {bounds.width, bounds.height}; 
}

Rectangle Button::GetBounds() const{
 return bounds;
}

void Button::DrawWithFade(){
    Color fadeColor = WHITE ; 
    fadeColor.a = static_cast<unsigned char> (100) ;
    DrawTextureEx(texture , {bounds.x , bounds.y} , 0.0f , scale , fadeColor) ;
}

// Button::~Button()
// {
//     UnloadTexture(texture);
// }
