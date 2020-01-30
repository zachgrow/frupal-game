#ifndef FRUPALGAME_SRC_TILE_HPP_INCLUDED
#define FRUPALGAME_SRC_TILE_HPP_INCLUDED

class Tile
{
public:
    virtual void display() = 0;
    virtual char getChar() = 0;
};
class Grass : public Tile
{
private:
    char c;
    int r, g, b;
    bool status;

public:
    void display();
    Grass();
    Grass(char c, int r, int g, int b);
    ~Grass();
    char getChar();
    class Water : public Tile
    {
    private:
        char c;
        int r, g, b;
        bool status;

    public:
        void display();
        Water();
        Water(char c, int r, int g, int b);
        ~Water();
        char getChar();
    };
    struct Tree : public Tile
    {
    private:
        char c;
        int r, g, b;
        bool status;

    public:
        void display();
        Tree();
        Tree(char c, int r, int g, int b);
        char getChar();
    };

    struct Obstacle : Tile
    {
    public:
        virtual void display();
        virtual void getAction();
        virtual void afterAction();
    };
    struct Boulder : public Obstacle
    {
    private:
        char c;
        int r, g, b;
        bool status;

    public:
        void display();
        Boulder();
        Boulder(char c, int r, int g, int b);
        char getChar();
        void getAction();
        void afterAction();
    };
#endif // FRUPALGAME_SRC_TILE_HPP_INCLUDED
