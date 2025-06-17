#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>
using namespace std;
using namespace sf;
//adha chalta wa 2 player...
const int M = 25;
const int N = 40;

int grid[M][N] = {0};
int ts = 18; //tile size

struct ScoreEntry {
    int score;
    int time;  // Time in seconds
};


struct Enemy
{   
    float x, y;
    float dx, dy;
    
    bool isCircular;
    float angle;
    float centerX, centerY;
    float radius;
    
    Enemy()
    {   
        x = y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
        
        isCircular = false;
        angle = 0.0;
        centerX = x;
        centerY = y;
        radius = 85.0f;
        
    }

   void move(float speedMultiplier)
{
    if (isCircular) {
        angle += 0.03f * speedMultiplier;

        x = centerX + radius * cos(angle);
        y = centerY + radius * sin(angle);

        // Prevent going outside the grid
        if (x < ts) x = ts;
        if (x > (N - 2) * ts) x = (N - 2) * ts;
        if (y < ts) y = ts;
        if (y > (M - 2) * ts) y = (M - 2) * ts;
    } 
    else {
        x += dx * speedMultiplier;
        if (grid[int(y)/ts][int(x)/ts] == 1) {
            dx = -dx;
            x += dx * speedMultiplier;
        }

        y += dy * speedMultiplier;
        if (grid[int(y)/ts][int(x)/ts] == 1) {
            dy = -dy;
            y += dy * speedMultiplier;
        }
    }
}

};


void drop(int y,int x)
{
  if (grid[y][x]==0) grid[y][x]=-1;
  if (grid[y-1][x]==0) drop(y-1,x);
  if (grid[y+1][x]==0) drop(y+1,x);
  if (grid[y][x-1]==0) drop(y,x-1);
  if (grid[y][x+1]==0) drop(y,x+1);
}

void resetGrid() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1; // border
            else
                grid[i][j] = 0; // empty
        }
    }
}


int showMenu() {
    RenderWindow menuWindow(VideoMode(600, 400), "Xonix Menu");
      Texture backgroundText;
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/1.jpg")) {
        cout << "Failed to load background image!" << endl;
        }
    Sprite background(backgroundText);
    menuWindow.setFramerateLimit(60);

    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return 3; // Exit if font missing
    }

    const int menuTitles = 3;
    Text menu[menuTitles];
    string options[menuTitles] = {"Single Player", "Two Player", "Exit"};
    int selected = 0;

    for (int i = 0; i < menuTitles; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setPosition(150, 100 + i * 60);
    }

    while (menuWindow.isOpen()) {
        Event e;
        while (menuWindow.pollEvent(e)) {
            if (e.type == Event::Closed)
                menuWindow.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up)
                    selected = (selected - 1 + menuTitles) % menuTitles;
                if (e.key.code == Keyboard::Down)
                    selected = (selected + 1) % menuTitles;
                if (e.key.code == Keyboard::Enter) {
                    menuWindow.close();
                    return selected + 1; // 1 = Single, 2 = Two player, 3 = Exit
                }
            }
        }

        // Draw
        menuWindow.draw(background);
       
        for (int i = 0; i < menuTitles; i++) {
            menu[i].setFillColor(i == selected ? Color::Yellow : Color::White);
            menuWindow.draw(menu[i]);
        }
        menuWindow.display();
    }

    return 3; // Default to Exit if window closed
}

int showMenu1() {
    RenderWindow menuWindow(VideoMode(600, 400), "Xonix Menu");
    Texture backgroundText;
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/3.jpg")) {
        cout << "Failed to load background image!" << endl;
        }
    Sprite background(backgroundText);
    menuWindow.setFramerateLimit(60);

    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return 3; // Exit if font missing
    }

    const int menuTitles = 3;
    Text menu[menuTitles];
    string options[menuTitles] = {"Start Game", "Select Level", "Scoreboard"};
    int selected = 0;

    for (int i = 0; i < menuTitles; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setPosition(150, 100 + i * 60);
    }

    while (menuWindow.isOpen()) {
        Event e;
        while (menuWindow.pollEvent(e)) {
            if (e.type == Event::Closed)
                menuWindow.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up)
                    selected = (selected - 1 + menuTitles) % menuTitles;
                if (e.key.code == Keyboard::Down)
                    selected = (selected + 1) % menuTitles;
                if (e.key.code == Keyboard::Enter) {
                    menuWindow.close();
                    return selected + 1; // 1 = easy lvl, 2 = mid lvl, 3 = hard lvl, 4 = continious mode , 5 = scoreboard
                }
            }
        }

        // Draw
        menuWindow.draw(background);
        
        for (int i = 0; i < menuTitles; i++) {
            menu[i].setFillColor(i == selected ? Color::Yellow : Color::White);
            menuWindow.draw(menu[i]);
        }
        menuWindow.display();
    }

    return 3; // Default to Exit if window closed
}


int showMenu2() {
    RenderWindow menuWindow(VideoMode(600, 400), "Xonix Menu");
    Texture backgroundText;
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/4.jpg")) {
        cout << "Failed to load background image!" << endl;
        }
    Sprite background(backgroundText);
    menuWindow.setFramerateLimit(60);

    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return 3; // Exit if font missing
    }

    const int menuTitles = 4;
    Text menu[menuTitles];
    string options[menuTitles] = {"Easy Level", "Mid Level", "Hard Level","Continious mode"};
    int selected = 0;

    for (int i = 0; i < menuTitles; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setPosition(150, 100 + i * 60);
    }

    while (menuWindow.isOpen()) {
        Event e;
        while (menuWindow.pollEvent(e)) {
            if (e.type == Event::Closed)
                menuWindow.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up)
                    selected = (selected - 1 + menuTitles) % menuTitles;
                if (e.key.code == Keyboard::Down)
                    selected = (selected + 1) % menuTitles;
                if (e.key.code == Keyboard::Enter) {
                    menuWindow.close();
                    return selected + 1; // 1 = easy lvl, 2 = mid lvl, 3 = hard lvl, 4 = continious mode , 5 = scoreboard
                }
            }
        }

         // Draw
        menuWindow.draw(background);
        for (int i = 0; i < menuTitles; i++) {
            menu[i].setFillColor(i == selected ? Color::Yellow : Color::White);
            menuWindow.draw(menu[i]);
        }
        menuWindow.display();
    }

    return 3; // Default to Exit if window closed
}



int showEndMenu() {
    RenderWindow endWindow(VideoMode(600, 400), "Game Over");
    Texture backgroundText;
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/2.jpg")) {
        cout << "Failed to load background image!" << endl;
        }
    Sprite background(backgroundText);
    endWindow.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return 3;
    }

    const int menuTitles = 3;
    Text menu[menuTitles];
    string options[menuTitles] = {"Retry", "Main Menu", "Exit"};
    int selected = 0;

    for (int i = 0; i < menuTitles; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setPosition(150, 120 + i * 60);
    }

    while (endWindow.isOpen()) {
        Event e;
        while (endWindow.pollEvent(e)) {
            if (e.type == Event::Closed)
                endWindow.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up)
                    selected = (selected - 1 + menuTitles) % menuTitles;
                if (e.key.code == Keyboard::Down)
                    selected = (selected + 1) % menuTitles;
                if (e.key.code == Keyboard::Enter) {
                    endWindow.close();
                    return selected + 1; // 1 = Retry, 2 = Main Menu, 3 = Exit
                }
            }
        }

        // Draw
        endWindow.draw(background);
        for (int i = 0; i < menuTitles; i++) {
            menu[i].setFillColor(i == selected ? Color::Red : Color::White);
            endWindow.draw(menu[i]);
        }
        endWindow.display();
    }
    
    return 3; // default to Exit
}

int showPauseMenu() {
    RenderWindow endWindow(VideoMode(600, 400), "Pause Menu");
    Texture backgroundText;
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/2.jpg")) {
        cout << "Failed to load background image!" << endl;
        }
    Sprite background(backgroundText);
    endWindow.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return 3;
    }

    const int menuTitles = 3;
    Text menu[menuTitles];
    string options[menuTitles] = {"Continue", "End Menu", "Exit"};
    int selected = 0;

    for (int i = 0; i < menuTitles; i++) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(40);
        menu[i].setPosition(150, 120 + i * 60);
    }

    while (endWindow.isOpen()) {
        Event e;
        while (endWindow.pollEvent(e)) {
            if (e.type == Event::Closed)
                endWindow.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up)
                    selected = (selected - 1 + menuTitles) % menuTitles;
                if (e.key.code == Keyboard::Down)
                    selected = (selected + 1) % menuTitles;
                if (e.key.code == Keyboard::Enter) {
                    endWindow.close();
                    return selected + 1; // 1 = Retry, 2 = Main Menu, 3 = Exit
                }
            }
        }

       // Draw
        endWindow.draw(background);
        
        for (int i = 0; i < menuTitles; i++) {
            menu[i].setFillColor(i == selected ? Color::Red : Color::White);
            endWindow.draw(menu[i]);
        }
        endWindow.display();
    }
    
    return 3; // default to Exit
}

/*void resetGame(
    int &x, int &y, int &dx, int &dy,
    int &score, int &power_ups, int &next_power_up_score,
    int &bonus_counter, int &bonus_multiplier, int &bonus_threshold,
    int &move_count, bool &is_building,
    bool &freeze_active, sf::Clock &freeze_clock,
    bool &Game
) {
    // Reset player position and direction
    x = 0; y = 0;
    dx = 0; dy = 0;

    // Reset score and power-up logic
    score = 0;
    power_ups = 0;
    next_power_up_score = 50;

    // Reset bonus logic
    bonus_counter = 0;
    bonus_multiplier = 1;
    bonus_threshold = 10;

    // Reset movement and building state
    move_count = 0;
    is_building = false;

    // Reset freeze state
    freeze_active = false;
    freeze_clock.restart();

    // Reset game state
    Game = true;

    // Reset grid
    resetGrid();

    // Restore border tiles
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;
}*/


  void playSinglePlayer_mid(){
  
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 4;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

void playSinglePlayer_easy(){
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 2;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

void playSinglePlayer_hard(){
   int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 6;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

  void playSinglePlayer_continious(){
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  srand(time(0));
  resetGrid();
  float enemySpeed = 1.0;

    RenderWindow window(VideoMode(N*ts, M*ts), "Continious mode!!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
    //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed
    

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 2;
    Enemy a[50];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;
   Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    int Totalseconds = 0;
    
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
       //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
           moveText.setString("Moves: " + to_string(move_count));
           scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           

}
        
        //Adding 2 enemies after every 20s in order to increase the difficulty time by time.
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
          if (enemyCount < 50)
            {
              enemySpeed+=0.2;
              enemyCount+=2;
              lastIncreaseTime = Totalseconds;
            }
          }
          
          if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}


        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
             if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape)
{
    bool isPaused = true;
    pauseClock.restart();
    int pauseChoice = showPauseMenu();

    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
  if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }
}
}

        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

         if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }


       for (int i = 0; i < enemyCount; i++)
       a[i].move(enemySpeed); // Use your speed variable here

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }

        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
      
      window.draw(timeText);
       window.draw(moveText);
       window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       
       }
};

  void playTwoPlayer_mid(){
  
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 4;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

void playTwoPlayer_easy(){
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 2;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

void playTwoPlayer_hard(){
   int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  
  float enemySpeed=1.0;
  
  
  srand(time(0));
  resetGrid(); 

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
     //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 6;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;      // Measures total game session time
    Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    float Totalseconds=0.0;

    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         int Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
         moveText.setString("Moves: " + to_string(move_count));
         scoreText.setString("Score: " + to_string(score));
         powerUpText.setString("Power-Ups: " + to_string(power_ups));
         bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           
         }
         //increasing speed every 20 s
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
              enemySpeed+=0.2;
              lastIncreaseTime = Totalseconds;
            
          }
          
         if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}  
          

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
            if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape){
             
                bool isPaused = true;
                pauseClock.restart();
                int pauseChoice = showPauseMenu();
  
  
    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
   if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }

}
}
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (!Game) continue;

        if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }
        for (int i=0;i<enemyCount;i++) a[i].move(enemySpeed); 

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
       window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       }
};

  void playTwoPlayer_continious(){
  int score = 0;
  int bonus_counter = 0;
  int bonus_threshold = 10;
  int bonus_multiplier = 1;
  int power_ups = 0;
  int move_count=0;
  bool is_building=false;
  bool freeze_active = false;
  Clock freeze_clock;
  const float freeze_duration = 3.0f;
  int captured_this_move = 0;
  int next_power_up_score = 50;
  srand(time(0));
  resetGrid();
  float enemySpeed = 1.0;

    RenderWindow window(VideoMode(N*ts, M*ts), "Continious mode!!");
    window.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
    //Font used to display the time counter....
    Font font;
   if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return ;
    }
    
    //printing the text in order to display the time on the top left corner...
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10); // top-left corner
    
    Text moveText;
    moveText.setFont(font);
    moveText.setCharacterSize(20);
    moveText.setFillColor(Color::White);
    moveText.setPosition(10, 40); 
    
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 70);
 
   Text powerUpText;
   powerUpText.setFont(font);
   powerUpText.setCharacterSize(20);
   powerUpText.setFillColor(Color::White);
   powerUpText.setPosition(10, 100);
   
   Text bonusText;
   bonusText.setFont(font);
   bonusText.setCharacterSize(20);
   bonusText.setFillColor(Color::White);
   bonusText.setPosition(10, 130); // Adjust as needed
    

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100,100);
    sEnemy.setOrigin(20,20);

    int enemyCount = 2;
    Enemy a[50];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    int x2 = N - 1, y2 = M - 1, dx2 = 0, dy2 = 0;
    bool is_building2 = false;
    int captured_this_move2 = 0;

    float timer=0, delay=0.07; 
    Clock clock;
    Clock Time;
   Clock pauseClock;            // Measures how long the game is paused
    float totalPausedTime = 0.0; // Cumulative paused time
    bool isPaused = false;       // Track pause state
    int Totalseconds = 0;
    
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
      if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
       //our new timer function in order to calculate the total time of the game.
        //ispaused logic in order to handle the timer when pause menu is opened.
          if (!isPaused) {
         Totalseconds = (Time.getElapsedTime().asSeconds() - totalPausedTime );
         timeText.setString("Time: " + to_string(Totalseconds) + " s");
           moveText.setString("Moves: " + to_string(move_count));
           scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
           

}
        
        //Adding 2 enemies after every 20s in order to increase the difficulty time by time.
        
        static int lastIncreaseTime = 0;
        if (Totalseconds - lastIncreaseTime >= 20)
         {
          if (enemyCount < 50)
            {
              enemySpeed+=0.2;
              enemyCount+=2;
              lastIncreaseTime = Totalseconds;
            }
          }
          
          if (Totalseconds >= 30) {
    for (int i = 0; i < enemyCount; i++) {
        if (!a[i].isCircular) {
            a[i].isCircular = true;
            a[i].angle = 0;
            a[i].centerX = a[i].x;
            a[i].centerY = a[i].y;
        }
    }
}


        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
               
             if (e.type == Event::KeyPressed){
             if (e.key.code == Keyboard::Escape)
{
    bool isPaused = true;
    pauseClock.restart();
    int pauseChoice = showPauseMenu();

    if (pauseChoice == 1)
    {   
        isPaused = false;
        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
        // Continue — do nothing
    }
    else if (pauseChoice == 2)
    {
                   return;
                   }
    else if (pauseChoice == 3)
    {
       
        exit(0); // Exit game entirely
    }
}
  if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                }
}
}

        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
        if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
        if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
        if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
        if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }

        
        if (!Game) continue;

         if (timer > delay) {
                x += dx;
                y += dy;

                // Boundary checking
                x = max(0, min(N-1, x));
                y = max(0, min(M-1, y));

                if (grid[y][x] == 2) Game = false;
                
                if (grid[y][x] == 0) {
                    if (!is_building) {
                        move_count++;
                        is_building = true;
                        captured_this_move = 0;
                    }
                    grid[y][x] = 2;
                    captured_this_move++;
                }
                 // Player 2
    x2 += dx2; y2 += dy2;
    x2 = max(0, min(N-1, x2));
    y2 = max(0, min(M-1, y2));
    if (grid[y2][x2] == 2) Game = false;
    if (grid[y2][x2] == 0) {
        if (!is_building2) {
            move_count++;
            is_building2 = true;
            captured_this_move2 = 0;
        }
        grid[y2][x2] = 2;
        captured_this_move2++;
    }

                timer = 0;
            }
            // Enemy movement
            if (freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                    freeze_active = false;
            } else {
                for (int i = 0; i < enemyCount; i++) 
                    a[i].move(enemySpeed);
            }


       for (int i = 0; i < enemyCount; i++)
       a[i].move(enemySpeed); // Use your speed variable here

       //collision and scoring
        if (grid[y][x] == 1) {
                dx = dy = 0;
                
                if (is_building && captured_this_move > 0) {
                    int points = captured_this_move;
                    
                    if (captured_this_move > bonus_threshold) {
                        bonus_counter++;
                        if (bonus_counter >= 5) bonus_multiplier = 4;
                        else if (bonus_counter >= 3) bonus_multiplier = 2;
                        points *= bonus_multiplier;
                    }
                    
                    score += points;
                    
                    while (score >= next_power_up_score) {
                        power_ups++;
                        next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                    }
                    
                    captured_this_move = 0;
                    is_building = false;
                }

                // Update grid
                for (int i = 0; i < enemyCount; i++)
                    drop(a[i].y/ts, a[i].x/ts);

                for (int i = 0; i < M; i++)
                    for (int j = 0; j < N; j++)
                        grid[i][j] = (grid[i][j] == -1) ? 0 : 1;
            }
            
            

        for (int i=0;i<enemyCount;i++)
           if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;

      /////////draw//////////
      window.clear();

      for (int i=0;i<M;i++)
        for (int j=0;j<N;j++)
         {
            if (grid[i][j]==0) continue;
            if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
            if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
            sTile.setPosition(j*ts,i*ts);
            window.draw(sTile);
         }

      sTile.setTextureRect(IntRect(36,0,ts,ts));
      sTile.setPosition(x*ts,y*ts);
      window.draw(sTile);

      sEnemy.rotate(10);
      for (int i=0;i<enemyCount;i++)
       {
        sEnemy.setPosition(a[i].x,a[i].y);
        window.draw(sEnemy);
       }

      if (!Game) window.draw(sGameover);
      
      window.draw(timeText);
       window.draw(moveText);
       window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
       window.display();
       
       }
};



int main()
{
    while (true) {
    //Returning first choice from the menu function in order to handle single player and two player option in switch
        int choice = showMenu();  // Start menu

        switch (choice) {
        
           case 1: {
   //Returning second choice from the menu1 function in order to handle start game , select lvl and scoreboard option in switch
           int choice1 = showMenu1(); // Optional intermediate menu
           
          switch (choice1) {
              
              case 1: {
              bool playing = true;

                while (playing) {
                    playSinglePlayer_mid(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
            
            case 2:{
    //Returning third choice from the menu2 function in order to handle the difficulties leveln switch
                int choice2 = showMenu2(); // Optional intermediate menu
                
                switch (choice2) {
            
                case 1: {
             
                bool playing = true;

                while (playing) {
                    playSinglePlayer_easy(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 2: {
            
                bool playing = true;

                while (playing) {
                    playSinglePlayer_mid(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 3: {
              
                bool playing = true;

                while (playing) {
                    playSinglePlayer_hard(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 4: {
               bool playing = true;

                while (playing) {
                    playSinglePlayer_continious(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                }
                break;
                 }
                
                case 3: {
                cout<<"Score board under construction...."<<endl;
                }
                break;
               
            }
            }
            break;
            
            

            case 2:{
            //Returning second choice from the menu1 function in order to handle start game , select lvl and scoreboard option in switch
           int choice1 = showMenu1(); // Optional intermediate menu
           
          switch (choice1) {
              
              case 1: {
              bool playing = true;

                while (playing) {
                    playTwoPlayer_mid(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
            
            case 2:{
    //Returning third choice from the menu2 function in order to handle the difficulties leveln switch
                int choice2 = showMenu2(); // Optional intermediate menu
                
                switch (choice2) {
            
                case 1: {
             
                bool playing = true;

                while (playing) {
                    playTwoPlayer_easy(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 2: {
            
                bool playing = true;

                while (playing) {
                    playTwoPlayer_mid(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 3: {
              
                bool playing = true;

                while (playing) {
                    playTwoPlayer_hard(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                break;
                
                case 4: {
               bool playing = true;

                while (playing) {
                    playTwoPlayer_continious(); // Play the game

                    int endChoice = showEndMenu(); // End game menu
                    if (endChoice == 1) continue;         // Retry
                    else if (endChoice == 2) playing = false; // Back to main menu
                    else if (endChoice == 3) return 0;     // Exit
                }
                }
                }
                break;
                 }
                
                case 3: {
                cout<<"Score board under construction...."<<endl;
                }
                break;
               
          }  
            }
            break;
              

            case 3:
                cout << "Exiting the game. Goodbye!\n";
                return 0;
        }
    }


    return 0;
}
