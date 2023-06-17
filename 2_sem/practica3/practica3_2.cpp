#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

const double PI = acos(-1);

class KinematicSolver
{
private:
    double k_alpha;
    double k_beta;
    double k_L1;
    double k_L2;

public:
    KinematicSolver(double L1, double L2) : k_L1(L1), k_L2(L2), k_alpha(0.0), k_beta(0.0) {}

    void Solve(double x, double y) 
    {
        double B = sqrt(x * x + y * y);     // B is distance between (0, 0) and (x, y)

        if (!(B < k_L1 + k_L2 && x > 0 && y > 0))       // in a triangle the sum of two sides is greater that the third side
            return;

        double angle1 = std::atan(y / x);       // angle between OX and B
        double angle2 = std::acos((k_L1 * k_L1 - k_L2 * k_L2 + B * B) / (2.0 * B * k_L1));      // angle between B and L1 - found via cos theorem

        k_alpha = angle1 - angle2;
        k_beta = PI - std::acos(
            (k_L1 * k_L1 + k_L2 * k_L2 - B * B) /
            (2 * k_L1 * k_L2));     //same cos theorem
    }

    double getL1() const
    {
        return k_L1;
    }

    double getL2() const
    {
        return k_L2;
    }

    double getAlpha() const
    {
        return k_alpha;
    }

    double getBeta() const
    {
        return k_beta;
    }
};

class Coordinates     // contains info on coordinates
{
private:
    float p_x;
    float p_y;

public:
    Coordinates(float x, float y) : p_x(x), p_y(y) { }

    float getX() const 
    {
        std::cout << p_x << " ";
        return p_x;
    }

    float getY() const 
    {
        std::cout << p_y << "\n";
        return p_y;
    }

    static Coordinates rotate(float cx, float cy, float angle, Coordinates coord)       //  static keyword - no matter how many objects of the class are created, there is only one copy of the static member
    {
        float s = sin(angle);
        float c = cos(angle);

        coord.p_x -= cx;
        coord.p_y -= cy;

        float xnew = coord.p_x * c - coord.p_y * s;
        float ynew = coord.p_x * s + coord.p_y * c;

        coord.p_x = xnew + cx;
        coord.p_y = ynew + cy;

        return coord;
    }
};

class Link      // how it looks and moves
{
private:
    sf::RectangleShape m_rectangleShape;
public:
    Link(float length, Coordinates position, float initialRotation) 
    {
        m_rectangleShape.setSize(sf::Vector2f(length, 10));
        m_rectangleShape.setOrigin(0, 0.5);
        m_rectangleShape.setPosition(position.getX(), position.getY());
        m_rectangleShape.setFillColor(sf::Color::Magenta);
        m_rectangleShape.rotate(initialRotation);
    }

    void move(Coordinates position) 
    {
        m_rectangleShape.setPosition(position.getX() - 5, position.getY() + 5);
    }

    void rotate(float angle) 
    {
        m_rectangleShape.setRotation(angle);
    }

    void draw(sf::RenderWindow& window) 
    {
        window.draw(m_rectangleShape);
    }
};

class Joint 
{
private:
    sf::CircleShape m_circle;
public:
    Joint() 
    {
        m_circle.setRadius(10);
        m_circle.setFillColor(sf::Color::Black);
        m_circle.setPointCount(100);
    }

    void move(Coordinates position) 
    {
        float radius = m_circle.getRadius();
        m_circle.setPosition(position.getX() - radius, position.getY() - radius);
    }

    void draw(sf::RenderWindow& window) 
    {
        window.draw(m_circle);
    }
};

double radiansToDegrees(double radians) 
{
    return radians * (180.0 / PI);
}


int main() 
{

    KinematicSolver kinematicSolver(300, 300);

    sf::RenderWindow Window(sf::VideoMode(600, 600), "Kinematics robot", sf::Style::Close);
    Window.setFramerateLimit(60);

    Link L1(kinematicSolver.getL1(), Coordinates(0.0, 600.0), 0.0);
    Link L2(kinematicSolver.getL2(), Coordinates(kinematicSolver.getL1(), 600.0), 0.0);

    Joint joint;

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        sf::Event event;
        while (Window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }

        if (!Window.isOpen()) 
            break;

        Window.clear(sf::Color::White);

        sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(Window);
        mouseLocalPosition.y = 600.0 - mouseLocalPosition.y;

        kinematicSolver.Solve(mouseLocalPosition.x, mouseLocalPosition.y);

        float alpha = kinematicSolver.getAlpha() * -1; // counter clock wise
        float beta = kinematicSolver.getBeta() * -1;

        L1.rotate(radiansToDegrees(alpha));

        Coordinates L2_position = Coordinates::rotate(0, 600.0, alpha, Coordinates(kinematicSolver.getL1(), 600.0));
        L2.move(L2_position);
        L2.rotate(radiansToDegrees(alpha + beta));

        L1.draw(Window);
        L2.draw(Window);

        joint.move(L2_position);
        joint.draw(Window);

        Window.display();
    }
}