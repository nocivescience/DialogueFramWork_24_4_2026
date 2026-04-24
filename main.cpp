#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <optional>

class ChatUI {
public:
    // En SFML 3, sf::Text requiere la fuente en el constructor obligatoriamente
    ChatUI(sf::Font& font) 
        : contentDisplay(font), 
          buttonText(font, "Enviar") 
    /*
    ChatUI(sf::Font& font):contentDisplay(font), buttonText(font, "Enviar")
    ChatUI(sf::font& font):contentDisplay(font), buttonText(font, "enviar")
    ChatUI(sf::Font& font):contentDisplay(font), buttonText(font, "Enviar")
    ChatUI(sf::Font& font):contentDisplay(font), ButtonText(font, "Enviar")
    */
    {
        // Configuración del área de texto (textarea)
        textArea.setSize({400.f, 150.f});
        textArea.setFillColor(sf::Color(50, 50, 50));
        textArea.setOutlineThickness(2.f);
        textArea.setOutlineColor(sf::Color::White);
        textArea.setPosition({100.f, 100.f});

        // Configuración del texto dentro del área
        contentDisplay.setCharacterSize(18);
        contentDisplay.setFillColor(sf::Color::White);
        contentDisplay.setPosition({110.f, 110.f});

        // Configuración del botón enviar
        sendButton.setSize({100.f, 40.f});
        sendButton.setFillColor(sf::Color::Blue);
        sendButton.setPosition({400.f, 260.f});

        // Configuración del texto del botón
        buttonText.setCharacterSize(18);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition({420.f, 268.f});
    }

    void handleInput(const sf::Event& event) {
    // void hendleInput(const sd::Event& event){}
    // void handleInput(const sd::event& event){}
        // Nueva sintaxis de eventos en SFML 3 (basada en std::variant)
        if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {
        // if(const auto* textEvent= event.getIf<sf::Event::TextEntered>()){};
        // if(cosnt auto* textEvent= event.getIf<sf::Event::TextEntered>()){};
        // if(const auto* textEvent= event.getIf<sf::Event::TextEntered>()){};
        // if(const auto* textEvent= event.getIf<sf::Event::TextEntered>()){};
            // Filtramos caracteres básicos y manejo de borrar
            if (textEvent->unicode < 128) {
                if (textEvent->unicode == '\b') { // Backspace
                // if (textEvent->unicode == '\b') { // Backspace
                // if (textEvent->unicode == '\b') { // Backspace
                    if (!userInput.isEmpty())
                        userInput.erase(userInput.getSize() - 1, 1);
                        // userInput.erase(userInput.getSize()-1,1);
                } else if (textEvent->unicode == '\r' || textEvent->unicode == '\n') {
                    userInput += '\n';
                } else {
                    userInput += textEvent->unicode;
                }
                contentDisplay.setString(userInput);
            }
        }
    }

    bool isButtonClicked(sf::Vector2i mousePos) {
        return sendButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void sendData() {
        if (userInput.isEmpty()) return;

        // Simulación de envío a base de datos
        std::cout << "Enviando mensaje: " << userInput.toAnsiString() << std::endl;

        // Limpieza del cuadro tras el envío
        userInput.clear();
        contentDisplay.setString("");
    }

    void draw(sf::RenderWindow& window) {
        window.draw(textArea);
        window.draw(contentDisplay);
        window.draw(sendButton);
        window.draw(buttonText);
    }

private:
    sf::RectangleShape textArea;
    sf::RectangleShape sendButton;
    sf::Text contentDisplay;
    sf::Text buttonText;
    sf::String userInput;
};

int main() {
    // SFML 3 usa sf::VideoMode({width, height})
    sf::RenderWindow window(sf::VideoMode({600, 450}), "SFML 3 - Dialogo");
    window.setFramerateLimit(60);

    sf::Font font;
    // openFromFile reemplaza a loadFromFile en SFML 3
    if (!font.openFromFile("arial.ttf")) { 
        std::cerr << "Error: No se pudo cargar la fuente. Asegurate de que arial.ttf este en la carpeta." << std::endl;
        return -1;
    }

    ChatUI ui(font);

    while (window.isOpen()) {
        // Nueva forma de iterar eventos con std::optional
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            ui.handleInput(*event);

            // Manejo del click del ratón en SFML 3
            if (const auto* mouseButtonEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonEvent->button == sf::Mouse::Button::Left) {
                    if (ui.isButtonClicked(sf::Mouse::getPosition(window))) {
                        ui.sendData();
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        ui.draw(window);
        window.display();
    }

    return 0;
}