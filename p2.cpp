#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>

class ChatUI {
    public:
    ChatUI(sf::Font font)
    : contentDisplay(font),
      buttonText(font, "Enviar")
}

int main() {
    if(!font.openFile("arial.ttf")){
        std::cerr << "Error estúpido" << std::endl;
        return -1;
    }
}