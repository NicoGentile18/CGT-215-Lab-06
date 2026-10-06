#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    string background = "images1/backgrounds/winter.png";
    string foreground = "images1/characters/yoda.png";

    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Background Image" << endl;
        return 1;
    }

    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Foreground Image" << endl;
        return 1;
    }

    Image backgroundImage = backgroundTex.copyToImage();
    Image foregroundImage = foregroundTex.copyToImage();

    Color greenScreen = foregroundImage.getPixel(0, 0);
    Vector2u sz = backgroundImage.getSize();

    for (unsigned int y = 0; y < sz.y; y++) {
        for (unsigned int x = 0; x < sz.x; x++) {
            Color pixel = foregroundImage.getPixel(x, y);

            if (pixel == greenScreen) {
                Color backgroundPixel = backgroundImage.getPixel(x, y);
                foregroundImage.setPixel(x, y, backgroundPixel);
            }
        }
    }

    RenderWindow window(VideoMode(sz.x, sz.y), "Lab 06 - Image Compositing");
    Texture tex1;
    tex1.loadFromImage(foregroundImage);
    Sprite sprite1;
    sprite1.setTexture(tex1);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite1);
        window.display();
    }

    return 0;
}
