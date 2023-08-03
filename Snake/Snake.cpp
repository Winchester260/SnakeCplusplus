#include <SFML\Graphics.hpp>
#include <time.h>

using namespace sf;

int n=20, m = 20;
int sizeOfGameField = 16;
int width = n * sizeOfGameField;
int height = m *sizeOfGameField;
 RenderWindow snake ;
int directionOfSnake,sizeOfSnake=4;
class Snake{
    int x;
    int y;
public:
    Snake(){
        x =0;
        y =0;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setX(int x){
        this->x = x;
    }
    void setY(int y){
        this->y = y;
    }
};

class Fruit{
    int x;
    int y;
public:
    Fruit(){
        x = width /2;
        y = height / 2;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void setX(int x){
        this->x = x;
    }
    void setY(int Y){
        this->y = Y;
    }
};

int gameover(){
    sf::RenderWindow window(sf::VideoMode(300, 200), "Game Over");

 
    Texture t1;
    t1.loadFromFile("images/gv.png");
 

    Sprite sprite1;
    sprite1.setTexture(t1);
    
    sprite1.setScale(0.6,0.65);
 
 

    while (window.isOpen())
    {
 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
            snake.close();
                window.close();
            }
        }

        window.clear();
        window.draw(sprite1);
        window.display();
    }

    return 0;
}

void tick(Snake *s, Fruit *f){
        for (int i=sizeOfSnake;i>0;--i)
     {
        
      s[i].setX(s[i-1].getX());
      s[i].setY(s[i-1].getY());
      }

    if(directionOfSnake == 0){
        s[0].setY(s[0].getY()+1);
    }
    if(directionOfSnake == 1){
        s[0].setX(s[0].getX()-1);
    }
        if(directionOfSnake == 2){
        s[0].setX(s[0].getX()+1);
    }
        if(directionOfSnake == 3){
        s[0].setY(s[0].getY()-1);
    }

    if ((s[0].getX()==f->getX()) && (s[0].getY()==f->getY())) 
     {sizeOfSnake++; 
     f->setX(rand()%n); 
     f->setY(rand()%m);}

    if (s[0].getX()>n) {
        gameover();
    }
  
    if (s[0].getX()<0){
gameover();
    }
    if (s[0].getY()>m) {
gameover();
    }  
    if (s[0].getY()<0){
gameover();
    }

    for (int i=1;i<sizeOfSnake;i++)
     if (s[0].getX()==s[i].getX() && s[0].getY()==s[i].getY())  sizeOfSnake=i;
        
}
int main(){

    Snake s1[100];

    Fruit f1;

    srand(time(0));

        Texture t1,t2,t3,t4;
    t1.loadFromFile("images/grass.png");
    t2.loadFromFile("images/snake.jpg");
    t3.loadFromFile("images/red.png");

    Sprite sprite1;
    sprite1.setTexture(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
 Event e;
     f1.setX(10);
    f1.setY(10); 

     Clock clock;
    float timer=0, delay=0.1;
       snake.create(VideoMode(width, height), "Snake Game by Winch!");
while (snake.isOpen())
    {
         float time = clock.getElapsedTime().asSeconds();
        clock.restart(); 
        timer+=time; 
 
       while (snake.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                snake.close();
        }

          if (Keyboard::isKeyPressed(Keyboard::Left) && directionOfSnake != 2) directionOfSnake=1;   
        if (Keyboard::isKeyPressed(Keyboard::Right) && directionOfSnake != 1) directionOfSnake=2;    
        if (Keyboard::isKeyPressed(Keyboard::Up) && directionOfSnake != 0) directionOfSnake=3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && directionOfSnake != 3) directionOfSnake=0;

        if(timer> delay){
            timer = 0; 
            tick(s1,&f1);
        }

        snake.clear();
                      
 
    for (int i=0; i<width; i++) 
      for (int j=0; j<height; j++) 
        { 
 sprite1.setPosition(i*sizeOfGameField,j*sizeOfGameField); 
 snake.draw(sprite1); 
            }

       for (int i=0;i<sizeOfSnake;i++)
        { 
            sprite2.setPosition(s1[i].getX()*sizeOfGameField, s1[i].getY()*sizeOfGameField);

            snake.draw(sprite2); 

        }
    sprite3.setPosition(f1.getX()*sizeOfGameField,f1.getY()*sizeOfGameField);
      snake.draw(sprite3);    
         snake.display();
    }
}