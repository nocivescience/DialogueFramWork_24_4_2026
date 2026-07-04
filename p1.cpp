#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>

class ChatUI{
    sf::Text contentDisplay;
    sf::Text buttonText;
    public:
        ChatUI(sf::Font& font):contentDisplay(font), buttonText(font, "Enviar"){
            contentDisplay.setString("holaSFML 3");
        }
        friend std::ostream& operator<<(std::ostream& os, const ChatUI& ui) {
        // Convertimos el sf::String de SFML a un std::string estándar
        os << ui.contentDisplay.getString().toAnsiString();
        return os;
    }

};
int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}), "Ventana re pulenta");
    sf::Font font;

    ChatUI chat(font);
    const float entrega = 2;

    while (window.isOpen()){
        while (const std::optional event= window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            std::cout<< entrega << chat << std::endl;
        }
    }
    return 0;
}