#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <random>


int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void reload(std::vector<sf::CircleShape>& circle){
    for(auto & i : circle){
        i.setPosition(static_cast<float>(rand_uns(-50000, 50000)), static_cast<float>(rand_uns(-50000, 50000)));
    }
}

void viewMap(float time, sf::View& view){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.move(time * view.getSize().x / 1000, 0);//скроллим карту вправо
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.move(0, time * view.getSize().y / 1000);//скроллим карту вниз
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.move(-time * view.getSize().x / 1000, 0);//скроллим карту влево
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.move(0, -time * view.getSize().y / 1000);//скроллим карту вправо
    }
}


int main() {

    sf::Clock clock;
    float time;

    float alfa = 100;

    sf::RenderWindow window(sf::VideoMode(1920, 900), "Task", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::Event ev;
    sf::View view;
    view.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));


    std::vector<sf::CircleShape> circle;

    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        sf::CircleShape A;
        A.setRadius(50);
        A.setFillColor(sf::Color(rand_uns(50, 255), rand_uns(50, 255), rand_uns(50, 255)));
        A.setPosition(static_cast<float>(rand_uns(0, 1920)), static_cast<float>(rand_uns(0, 900)));
        circle.push_back(A);
    }


    while(window.isOpen()) {

        while (window.pollEvent(ev)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                reload(circle);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                alfa += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                alfa -= 10;
                if(alfa == 0)
                    alfa = 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                alfa += 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                alfa -= 1;
                if(alfa == 0)
                    alfa = 1;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                int a;
                std::cin >> a;

                circle.clear();

                for(int i = 0; i < a; i++){
                    sf::CircleShape A;
                    A.setRadius(50);
                    A.setFillColor(sf::Color(rand_uns(50, 255), rand_uns(50, 255), rand_uns(50, 255)));
                    A.setPosition(static_cast<float>(rand_uns(0, 1920)), static_cast<float>(rand_uns(0, 900)));
                    circle.push_back(A);
                }
            }

            if (ev.type == sf::Event::MouseWheelScrolled)
            {
                if (ev.mouseWheelScroll.delta < 0)
                    view.zoom(1.1f);
                else if (ev.mouseWheelScroll.delta > 0)
                    view.zoom(0.9f);
            }
        }


        for(int i = 0; i < circle.size(); i++){
            if(i == circle.size() - 1){
                circle[i].move((circle[0].getPosition().x - circle[i].getPosition().x) / alfa, (circle[0].getPosition().y - circle[i].getPosition().y) / alfa);
            } else{
                circle[i].move((circle[i + 1].getPosition().x - circle[i].getPosition().x) / alfa, (circle[i + 1].getPosition().y - circle[i].getPosition().y) / alfa);
            }
        }


        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        viewMap(time, view);

        window.clear(sf::Color(0, 0, 0));

        for(const auto & i : circle){
            window.draw(i);
        }
        window.setView(view);
        window.display();
    }
    return 0;
}
