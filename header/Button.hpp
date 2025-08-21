#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>
#include <iostream>

class ClickableText {
private:
    std::string text;
    Vector2 position;
    int fontSize;
    Color color;
    Rectangle bounds;

public:
    ClickableText(const std::string&, Vector2, int, Color);
    void Draw();
    bool isClicked() const;
    std::string get_text() ;
};

class Button {
    private:
        Texture2D texture ; 
        Rectangle bounds;
        float scale ; 

    public:
        Button(const std::string& path, Vector2 position, float scale = 0.15f);
        void Draw();
        bool isPressed()const;
        Vector2 GetPosition() const ;
        Vector2 GetSize() const ;
        Rectangle GetBounds() const ;
        void DrawWithFade() ; 
};

struct TextBox {
    Rectangle rect;
    std::string text;
    bool active;
    enum InputType {ANY, NUMBERS_ONLY, LETTERS_ONLY } inputType;
    TextBox(): rect({0,0,0,0}), text(""), active(false), inputType(ANY) {} ;

    TextBox(Rectangle r, InputType type = ANY) : 
        rect(r), text(""), active(false), inputType(type) {}
};
#endif