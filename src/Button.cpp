#include "Button.hpp"

ClickableText::ClickableText(const std::string& txt, Vector2 pos, int size, Color col)
    : text(txt), position(pos), fontSize(size), color(col) {
    int width = MeasureText(text.c_str(), fontSize);
    bounds = { pos.x, pos.y, (float)width, (float)fontSize };
}
void ClickableText::Draw(Vector2 mousePos) {
    DrawText(text.c_str(), position.x, position.y, fontSize, color);
    if (CheckCollisionPointRec(mousePos, bounds)) {
        DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, RED);
    }
}

bool ClickableText::isClicked(Vector2 mousePos, bool click) const {
    return click && CheckCollisionPointRec(mousePos, bounds);
}

Button::Button(const std::string& path, Vector2 position , float scale) : scale(scale) {
    texture = LoadTexture(path.c_str());

    bounds = {position.x, position.y, 
            (float)texture.width*scale, (float)texture.height*scale};
}

void Button::Draw(Vector2 mousePos) {
       
      //  DrawTexture(texture, static_cast<int>(bounds.x),static_cast<int>(bounds.y), WHITE);
    DrawTextureEx(texture, (Vector2){bounds.x, bounds.y}, 0.0f, scale, WHITE); //with scale
    if (CheckCollisionPointRec(mousePos, bounds)) {
        DrawRectangleLinesEx(bounds, 2.0f, RED);
    }
}    

bool Button::isPressed(Vector2 mousePos, bool click)const {
    return click && CheckCollisionPointRec(mousePos, bounds);
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

void Button::DrawWithFade(Vector2 mousepos, float alpha){
    Color fadeColor = WHITE ; 
    fadeColor.a = static_cast<unsigned char> (alpha) ;
    DrawTextureEx(texture , {bounds.x , bounds.y} , 0.0f , scale , fadeColor) ;
}

// Button::~Button()
// {
//     UnloadTexture(texture);
// }
