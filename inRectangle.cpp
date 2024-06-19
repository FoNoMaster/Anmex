#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>


class object{
public:
    sf::CircleShape a;
    float mass, vx, vy;
};


int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void reload(std::vector<object>& circle){
    for(auto & i : circle){
        i.a.setPosition(static_cast<float>(rand_uns(50, 1900)), static_cast<float>(rand_uns(50, 900)));
        i.vx = static_cast<float>(rand_uns(-5, 5));
        i.vy = static_cast<float>(rand_uns(-5, 5));
//        i.vx = 0;
//        i.vy = 0;
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

    float mv = 0;

    sf::Clock clock;
    float time;

    float alfa = 1, betta = 1;

    sf::RenderWindow window(sf::VideoMode(1920, 900), "popopopopo", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::Event ev;
    sf::View view;
    view.reset(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));



    std::vector<object> circle;
    std::vector<object> tmp_vector;

    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        object A;
        A.a.setRadius(50);
        A.a.setFillColor(sf::Color(rand_uns(50, 255), rand_uns(50, 255), rand_uns(50, 255)));
        A.a.setPosition(static_cast<float>(rand_uns(0, 1920)), static_cast<float>(rand_uns(0, 900)));
        A.a.setOrigin(A.a.getRadius(), A.a.getRadius());
        A.vx = static_cast<float>(rand_uns(-50, 50)) / 10;
        A.vy = static_cast<float>(rand_uns(-50, 50)) / 10;
        A.mass = 1;

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
                circle[0].vy += -5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                circle[0].vy += 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                circle[0].vx += 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                circle[0].vx += -5;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                int a;
                std::cin >> a;

                circle.clear();

                for(int i = 0; i < a; i++){
                    object A;
                    A.mass = static_cast<float>(rand_uns(1, 20));
                    A.a.setRadius(std::sqrt(A.mass * 500));
                    A.a.setFillColor(sf::Color(rand_uns(50, 255), rand_uns(50, 255), rand_uns(50, 255)));
                    A.a.setPosition(static_cast<float>(rand_uns(-1000, 1000)), static_cast<float>(rand_uns(-1000, 1000)));
                    A.a.setOrigin(A.a.getRadius(), A.a.getRadius());
                    A.vx = static_cast<float>(rand_uns(-5, 5));
                    A.vy = static_cast<float>(rand_uns(-5, 5));

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

        float w, dx, dy, r2;
        float v1, v2, dr1r2, v1x, v2x, v1y, v2y, D, m1, m2, sin, cos, a, b, c, g, ctg, ctg2;
        std::vector<int> deletable_index;
        for(int i = 0; i < circle.size(); i++){

            circle[i].vy += 0;

            if(circle[i].a.getPosition().x + circle[i].a.getRadius() > 1920){
                circle[i].a.setPosition(1920 - circle[i].a.getRadius(), circle[i].a.getPosition().y);
                circle[i].vx *= -1.00;
            }
            if(circle[i].a.getPosition().y + circle[i].a.getRadius() > 1080){
                circle[i].a.setPosition(circle[i].a.getPosition().x, 1080 - circle[i].a.getRadius());
                circle[i].vy *= -1.00;
            }
            if(circle[i].a.getPosition().x - circle[i].a.getRadius() < 0){
                circle[i].a.setPosition(circle[i].a.getRadius(), circle[i].a.getPosition().y);
                circle[i].vx *= -1.00;
            }
            if(circle[i].a.getPosition().y - circle[i].a.getRadius() < 0){
                circle[i].a.setPosition(circle[i].a.getPosition().x, circle[i].a.getRadius());
                circle[i].vy *= -1.00;
            }

            for(int j = 0; j < circle.size(); j++){
                if(i != j){
                    dx = circle[j].a.getPosition().x - circle[i].a.getPosition().x;
                    dy = circle[j].a.getPosition().y - circle[i].a.getPosition().y;
                    r2 = dx * dx + dy * dy;
                    m1 = circle[i].mass;
                    m2 = circle[j].mass;
//                    w = 10 * m2 / (1 * r2);
//                    circle[i].vx += dx / std::sqrt(r2) * w;
//                    circle[i].vy += dy / std::sqrt(r2) * w;


                    if(i < j) {
                        if (std::sqrt(r2) < circle[i].a.getRadius() + circle[j].a.getRadius()) {
                            sin = (circle[j].a.getPosition().y - circle[i].a.getPosition().y) / (circle[i].a.getRadius() + circle[j].a.getRadius());
                            cos = (circle[j].a.getPosition().x - circle[i].a.getPosition().x) / (circle[i].a.getRadius() + circle[j].a.getRadius());


                            if(circle[j].a.getPosition().y - circle[i].a.getPosition().y != 0) {
                                ctg = -(circle[j].a.getPosition().x - circle[i].a.getPosition().x) /
                                      (circle[j].a.getPosition().y - circle[i].a.getPosition().y);
                            } else
                                ctg = -9999999;

                            ctg2 = ctg * ctg;

                            v1x = circle[i].vx;
                            v1y = circle[i].vy;
                            v2x = circle[j].vx;
                            v2y = circle[j].vy;
                            v1 = std::sqrt(v1x * v1x + v1y * v1y);
                            v2 = std::sqrt(v2x * v2x + v2y * v2y);

                            g = m2 / m1;
                            a = g * ctg2 + g + ctg2 + 1;
                            b = 2 * (v1x * ctg - g * ctg2 * v2y - g * v2y - v1y - v2x * ctg - v2y * ctg2);
                            c = v1x * v1x / g - 2 * v1x * v2y * ctg + g * v2y * v2y * ctg2 + g * v2y * v2y + 2 * v2y * v1y + v1y * v1y / g + v2x * v2x + 2 * v2x * v2y * ctg +
                                v2y * v2y * ctg2 - v1 * v1 / g - v2 * v2;
                            D = b * b - 4 * a * c;

                            if(circle[i].a.getPosition().y > circle[j].a.getPosition().y){
                                circle[j].vy = ((-b - std::sqrt(D)) / (2 * a)) * betta;
                            } else{
                                circle[j].vy = ((-b + std::sqrt(D)) / (2 * a)) * betta;
                            }

                            circle[i].vy = (m2 * (v2y - circle[j].vy) + m1 * v1y) / m1;
                            circle[i].vx = (v1x + v1y * ctg - ctg * circle[i].vy);
                            circle[j].vx = (v2x + v2y * ctg - ctg * circle[j].vy);

                        }
                    }
                }
            }
        }

        for(int i = 0; i < circle.size(); i++){
            int count = 0;
            for(int j : deletable_index){
                if(j == i)
                    count = 1;
            }
            if(count == 0){
                tmp_vector.push_back(circle[i]);
            }
        }
        circle = tmp_vector;
        tmp_vector.clear();
        deletable_index.clear();


        for(auto & i : circle){
            i.a.move(i.vx, i.vy);
        }

        mv = 0;
        for(auto & i : circle){
            mv += i.mass * (i.vx * i.vx + i.vy * i.vy);
        }
        std::cout << mv << std::endl;


        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 1000;
        viewMap(time, view);

        window.clear(sf::Color(0, 0, 0));

        for(const auto & i : circle){
            window.draw(i.a);
        }
        window.setView(view);
        window.display();
    }
    return 0;
}
