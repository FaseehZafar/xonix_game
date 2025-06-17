#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <cmath>
#include <fstream>
using namespace std;
using namespace sf;

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
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/9.png")) {
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
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/9.png")) {
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
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/9.png")) {
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
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/9.png")) {
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
      if (!backgroundText.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/images/9.png")) {
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
void saveScore(int score, int time)
 {
    ofstream outfile("scoreboard.txt", ios::app);
    if (outfile.is_open())
    {
        outfile << score << " " << time << endl;
        outfile.close();
    }
 }

int getTopScores(int scores[], int times[], int maxScores) {
    ifstream infile("scoreboard.txt");
    int count = 0;
    while (infile >> scores[count] >> times[count]) {
        count++;
        if (count >= maxScores) break; // Stop if full
    }
    infile.close();

    // Sort in descending order by score
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i] < scores[j]) {
                swap(scores[i], scores[j]);
                swap(times[i], times[j]);
            }
        }
    }

    return count;  // Actual number of scores read
}
int showScoreboard(RenderWindow& window) {
    Font font;
    font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf");

    Text title("Top 5 Scores", font, 40);
    title.setPosition(200, 50);

    int scores[100]={0};
    int times[100]={0}; // Enough for many entries
    int total= getTopScores(scores, times, 100);

    Text lines[5];
    int showCount = total < 5 ? total : 5;
    for (int i = 0; i < showCount; ++i) {
        lines[i].setFont(font);
        lines[i].setCharacterSize(30);
        lines[i].setString("Score: " + to_string(scores[i]) + "  Time: " + to_string(times[i]) + "s");
        lines[i].setPosition(200, 120 + i * 50);
    }

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed ||
                (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)) {
                return -1;
            }
        }

        window.clear(Color::Black);
        window.draw(title);
        for (int i = 0; i < showCount; ++i)
            window.draw(lines[i]);
        window.display();
    }

    return -1;
}




void playSinglePlayer_mid() {
   bool scoreSaved=false;
    int score = 0;
    int bonus_counter = 0;
    int bonus_threshold = 10;
    int bonus_multiplier = 1;
    int power_ups = 0;
    int move_count = 0;
    bool is_building = false;
    bool freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;
    int captured_this_move = 0;
    int next_power_up_score = 50;
   
    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
     Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false; // Track if game over sound has played
   
    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
   
    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }
   
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10);
   
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
    bonusText.setPosition(10, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    int enemyCount = 4;
    Enemy a[10];
    float enemySpeeds[10];
    int movementType[10]; // 0 = linear, 1 = circular, 2 = sinusoidal

    // Initialize enemies
    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f; // Speeds between 0.8 and 1.6
        a[i].x = (N/2 + i * 2) * ts; // Spread enemies
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0; // All start linear
    }

    bool Game = true;
    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;
    Clock Time;
    Clock pauseClock;
    float totalPausedTime = 0.0;
    bool isPaused = false;
    float Totalseconds = 0.0;

    // Set boundary walls
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M-1 || j == N-1) grid[i][j] = 1;

    bool movementAssigned = false;
    static float lastIncreaseTime = 0.0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
       
        if (!isPaused) {
            Totalseconds = Time.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText.setString("Moves: " + to_string(move_count));
            scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
        }
       
        // Increase speed every 20 seconds
        if (Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f; // Increased to 0.5 for noticeable effect
            }
            lastIncreaseTime += 20; // Increment by 20 for precise intervals
        }

        // Assign movement types after 30 seconds
        if (Totalseconds >= 30 && !movementAssigned) {
            movementType[0] = 0; // Linear
            movementType[1] = 0; // Linear
            movementType[2] = 1; // Circular
            movementType[3] = 2; // Sinusoidal
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
           
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                    powerUpSound.play();
                }
            }
        }
       
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx = -1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Right)) {dx = 1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx = 0; dy = -1;}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx = 0; dy = 1;}
       
        if (!Game) continue;

         if (timer > delay) {
            x += dx;
            y += dy;
            // Boundary checking
            if (x < 0) x = 0;
            else if (x > N - 1) x = N - 1;
            if (y < 0) y = 0;
            else if (y > M - 1) y = M - 1;
            if (grid[y][x] == 2) Game = false;
            if (grid[y][x] == 0) {
                if (!is_building) {
                    move_count++;
                    is_building = true;
                    captured_this_move = 0;
                }
                grid[y][x] = 2;
                captured_this_move++;
                // Update score continuously: 1 point per tile captured
                score += 1;
                // Check for power-up thresholds
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                }
            }
            timer = 0;
        }
       
        // Enemy movement
        if (freeze_active) {
            if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                freeze_active = false;
        } else {
            for (int i = 0; i < enemyCount; i++) {
                // Bounds checking to prevent segmentation faults
                int gridX = int(a[i].x / ts);
                int gridY = int(a[i].y / ts);
                if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    a[i].dx = -a[i].dx;
                    a[i].dy = -a[i].dy;
                    continue;
                }

                if (movementType[i] == 0) {
                    // Linear motion using Enemy::move
                    a[i].isCircular = false;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 1) {
                    // Circular motion using Enemy::move
                    a[i].isCircular = true;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 2) {
                    // Sinusoidal motion
                    a[i].isCircular = false;
                    a[i].x += a[i].dx * enemySpeeds[i] * time;
                    a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                    a[i].angle += 0.05f * enemySpeeds[i];
                    gridX = int(a[i].x / ts);
                    gridY = int(a[i].y / ts);
                    if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                        a[i].dx = -a[i].dx;
                        a[i].x += a[i].dx * enemySpeeds[i] * time;
                    }
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                }
            }
        }
       
        for (int i = 0; i < enemyCount; i++) {
            int gridX = int(a[i].x / ts);
            int gridY = int(a[i].y / ts);
            if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 2)
                Game = false;
        }

           //collision and scoring
    if (grid[y][x] == 1) {
        dx = dy = 0;
        if (is_building && captured_this_move > 0) {
            // Apply bonus multiplier if captured tiles meet/exceed threshold
            int current_threshold = (bonus_counter >= 3) ? 5 : 10;
            if (captured_this_move >= current_threshold) {
               
                bonus_counter++;
                 bonusSound.play();
                int bonus_points = captured_this_move; // Base bonus points
                // Apply multiplier based on total bonus occurrences
                if (bonus_counter >= 5) {
                    bonus_points *= 3; // Additional ×4 - 1 = ×3 points (since 1 point already added per tile)

                } else {
                    bonus_points *= 1; // Additional ×2 - 1 = ×1 points (since 1 point already added per tile)

                }
                score += bonus_points;
                captureSound.play();
                // Check for power-up thresholds again after bonus
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;

               }
            }
            // Reset building state and captured tiles

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
     
        // Set background color based on power-up status
        if (freeze_active) {
            window.clear(Color::White); // White when power-up is active
        } else {
            window.clear(Color::Black); // Default black
        }
         for (int i=0;i<enemyCount;i++)
     if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;
      //calling savescore function to save score
    if (!Game && !scoreSaved) {
    int finalTime = Time.getElapsedTime().asSeconds() - totalPausedTime;
    saveScore(score, finalTime);
    cout << "Score saved: " << score << ", Time: " << finalTime << endl; // Debug message
    scoreSaved = true;
}

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x*ts, y*ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            if (!gameOverSoundPlayed) {
                gameOverSound.play();
                gameOverSoundPlayed = true;
            }
            window.draw(sGameover);
        }
        window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
        window.display();
    }
};

void playSinglePlayer_easy() {
   bool scoreSaved=false;
    int score = 0;
    int bonus_counter = 0;
    int bonus_threshold = 10;
    int bonus_multiplier = 1;
    int power_ups = 0;
    int move_count = 0;
    bool is_building = false;
    bool freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;
    int captured_this_move = 0;
    int next_power_up_score = 50;
   
    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
     Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false; // Track if game over sound has played
   
    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
   
    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }
   
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10);
   
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
    bonusText.setPosition(10, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    int enemyCount = 2;
    Enemy a[10];
    float enemySpeeds[10];
    int movementType[10]; // 0 = linear, 1 = circular, 2 = sinusoidal

    // Initialize enemies
    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f; // Speeds between 0.8 and 1.6
        a[i].x = (N/2 + i * 2) * ts; // Spread enemies
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0; // All start linear
    }

    bool Game = true;
    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;
    Clock Time;
    Clock pauseClock;
    float totalPausedTime = 0.0;
    bool isPaused = false;
    float Totalseconds = 0.0;

    // Set boundary walls
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M-1 || j == N-1) grid[i][j] = 1;

    bool movementAssigned = false;
    static float lastIncreaseTime = 0.0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
       
        if (!isPaused) {
            Totalseconds = Time.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText.setString("Moves: " + to_string(move_count));
            scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
        }
       
        // Increase speed every 20 seconds
        if (Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f; // Increased to 0.5 for noticeable effect
            }
            lastIncreaseTime += 20; // Increment by 20 for precise intervals
        }

        // Assign movement types after 30 seconds
        if (Totalseconds >= 30 && !movementAssigned) {
            movementType[0] = 0; // Linear
            movementType[1] = 0; // Linear
            movementType[2] = 1; // Circular
            movementType[3] = 2; // Sinusoidal
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
           
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                    powerUpSound.play();
                }
            }
        }
       
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx = -1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Right)) {dx = 1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx = 0; dy = -1;}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx = 0; dy = 1;}
       
        if (!Game) continue;

         if (timer > delay) {
            x += dx;
            y += dy;
            // Boundary checking
            if (x < 0) x = 0;
            else if (x > N - 1) x = N - 1;
            if (y < 0) y = 0;
            else if (y > M - 1) y = M - 1;
            if (grid[y][x] == 2) Game = false;
            if (grid[y][x] == 0) {
                if (!is_building) {
                    move_count++;
                    is_building = true;
                    captured_this_move = 0;
                }
                grid[y][x] = 2;
                captured_this_move++;
                // Update score continuously: 1 point per tile captured
                score += 1;
                // Check for power-up thresholds
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                }
            }
            timer = 0;
        }
       
        // Enemy movement
        if (freeze_active) {
            if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                freeze_active = false;
        } else {
            for (int i = 0; i < enemyCount; i++) {
                // Bounds checking to prevent segmentation faults
                int gridX = int(a[i].x / ts);
                int gridY = int(a[i].y / ts);
                if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    a[i].dx = -a[i].dx;
                    a[i].dy = -a[i].dy;
                    continue;
                }

                if (movementType[i] == 0) {
                    // Linear motion using Enemy::move
                    a[i].isCircular = false;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 1) {
                    // Circular motion using Enemy::move
                    a[i].isCircular = true;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 2) {
                    // Sinusoidal motion
                    a[i].isCircular = false;
                    a[i].x += a[i].dx * enemySpeeds[i] * time;
                    a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                    a[i].angle += 0.05f * enemySpeeds[i];
                    gridX = int(a[i].x / ts);
                    gridY = int(a[i].y / ts);
                    if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                        a[i].dx = -a[i].dx;
                        a[i].x += a[i].dx * enemySpeeds[i] * time;
                    }
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                }
            }
        }
       
        for (int i = 0; i < enemyCount; i++) {
            int gridX = int(a[i].x / ts);
            int gridY = int(a[i].y / ts);
            if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 2)
                Game = false;
        }

           //collision and scoring
    if (grid[y][x] == 1) {
        dx = dy = 0;
        if (is_building && captured_this_move > 0) {
            // Apply bonus multiplier if captured tiles meet/exceed threshold
            int current_threshold = (bonus_counter >= 3) ? 5 : 10;
            if (captured_this_move >= current_threshold) {
               
                bonus_counter++;
                 bonusSound.play();
                int bonus_points = captured_this_move; // Base bonus points
                // Apply multiplier based on total bonus occurrences
                if (bonus_counter >= 5) {
                    bonus_points *= 3; // Additional ×4 - 1 = ×3 points (since 1 point already added per tile)

                } else {
                    bonus_points *= 1; // Additional ×2 - 1 = ×1 points (since 1 point already added per tile)

                }
                score += bonus_points;
                captureSound.play();
                // Check for power-up thresholds again after bonus
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;

               }
            }
            // Reset building state and captured tiles

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
     
        // Set background color based on power-up status
        if (freeze_active) {
            window.clear(Color::White); // White when power-up is active
        } else {
            window.clear(Color::Black); // Default black
        }
         for (int i=0;i<enemyCount;i++)
     if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;
      //calling savescore function to save score
    if (!Game && !scoreSaved) {
    int finalTime = Time.getElapsedTime().asSeconds() - totalPausedTime;
    saveScore(score, finalTime);
    cout << "Score saved: " << score << ", Time: " << finalTime << endl; // Debug message
    scoreSaved = true;
}

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x*ts, y*ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            if (!gameOverSoundPlayed) {
                gameOverSound.play();
                gameOverSoundPlayed = true;
            }
            window.draw(sGameover);
        }
        window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
        window.display();
    }
};

void playSinglePlayer_hard() {
   bool scoreSaved=false;
    int score = 0;
    int bonus_counter = 0;
    int bonus_threshold = 10;
    int bonus_multiplier = 1;
    int power_ups = 0;
    int move_count = 0;
    bool is_building = false;
    bool freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;
    int captured_this_move = 0;
    int next_power_up_score = 50;
   
    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
     Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false; // Track if game over sound has played
   
    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
   
    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }
   
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10);
   
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
    bonusText.setPosition(10, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    int enemyCount = 6;
    Enemy a[10];
    float enemySpeeds[10];
    int movementType[10]; // 0 = linear, 1 = circular, 2 = sinusoidal

    // Initialize enemies
    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f; // Speeds between 0.8 and 1.6
        a[i].x = (N/2 + i * 2) * ts; // Spread enemies
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0; // All start linear
    }

    bool Game = true;
    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;
    Clock Time;
    Clock pauseClock;
    float totalPausedTime = 0.0;
    bool isPaused = false;
    float Totalseconds = 0.0;

    // Set boundary walls
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M-1 || j == N-1) grid[i][j] = 1;

    bool movementAssigned = false;
    static float lastIncreaseTime = 0.0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
       
        if (!isPaused) {
            Totalseconds = Time.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText.setString("Moves: " + to_string(move_count));
            scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
        }
       
        // Increase speed every 20 seconds
        if (Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f; // Increased to 0.5 for noticeable effect
            }
            lastIncreaseTime += 20; // Increment by 20 for precise intervals
        }

        // Assign movement types after 30 seconds
        if (Totalseconds >= 30 && !movementAssigned) {
            movementType[0] = 0; // Linear
            movementType[1] = 0; // Linear
            movementType[2] = 1; // Circular
            movementType[3] = 2; // Sinusoidal
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
           
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                    powerUpSound.play();
                }
            }
        }
       
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx = -1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Right)) {dx = 1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx = 0; dy = -1;}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx = 0; dy = 1;}
       
        if (!Game) continue;

         if (timer > delay) {
            x += dx;
            y += dy;
            // Boundary checking
            if (x < 0) x = 0;
            else if (x > N - 1) x = N - 1;
            if (y < 0) y = 0;
            else if (y > M - 1) y = M - 1;
            if (grid[y][x] == 2) Game = false;
            if (grid[y][x] == 0) {
                if (!is_building) {
                    move_count++;
                    is_building = true;
                    captured_this_move = 0;
                }
                grid[y][x] = 2;
                captured_this_move++;
                // Update score continuously: 1 point per tile captured
                score += 1;
                // Check for power-up thresholds
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                }
            }
            timer = 0;
        }
       
        // Enemy movement
        if (freeze_active) {
            if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                freeze_active = false;
        } else {
            for (int i = 0; i < enemyCount; i++) {
                // Bounds checking to prevent segmentation faults
                int gridX = int(a[i].x / ts);
                int gridY = int(a[i].y / ts);
                if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    a[i].dx = -a[i].dx;
                    a[i].dy = -a[i].dy;
                    continue;
                }

                if (movementType[i] == 0) {
                    // Linear motion using Enemy::move
                    a[i].isCircular = false;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 1) {
                    // Circular motion using Enemy::move
                    a[i].isCircular = true;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 2) {
                    // Sinusoidal motion
                    a[i].isCircular = false;
                    a[i].x += a[i].dx * enemySpeeds[i] * time;
                    a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                    a[i].angle += 0.05f * enemySpeeds[i];
                    gridX = int(a[i].x / ts);
                    gridY = int(a[i].y / ts);
                    if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                        a[i].dx = -a[i].dx;
                        a[i].x += a[i].dx * enemySpeeds[i] * time;
                    }
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                }
            }
        }
       
        for (int i = 0; i < enemyCount; i++) {
            int gridX = int(a[i].x / ts);
            int gridY = int(a[i].y / ts);
            if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 2)
                Game = false;
        }

           //collision and scoring
    if (grid[y][x] == 1) {
        dx = dy = 0;
        if (is_building && captured_this_move > 0) {
            // Apply bonus multiplier if captured tiles meet/exceed threshold
            int current_threshold = (bonus_counter >= 3) ? 5 : 10;
            if (captured_this_move >= current_threshold) {
               
                bonus_counter++;
                 bonusSound.play();
                int bonus_points = captured_this_move; // Base bonus points
                // Apply multiplier based on total bonus occurrences
                if (bonus_counter >= 5) {
                    bonus_points *= 3; // Additional ×4 - 1 = ×3 points (since 1 point already added per tile)

                } else {
                    bonus_points *= 1; // Additional ×2 - 1 = ×1 points (since 1 point already added per tile)

                }
                score += bonus_points;
                captureSound.play();
                // Check for power-up thresholds again after bonus
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;

               }
            }
            // Reset building state and captured tiles

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
     
        // Set background color based on power-up status
        if (freeze_active) {
            window.clear(Color::White); // White when power-up is active
        } else {
            window.clear(Color::Black); // Default black
        }
         for (int i=0;i<enemyCount;i++)
     if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;
      //calling savescore function to save score
    if (!Game && !scoreSaved) {
    int finalTime = Time.getElapsedTime().asSeconds() - totalPausedTime;
    saveScore(score, finalTime);
    cout << "Score saved: " << score << ", Time: " << finalTime << endl; // Debug message
    scoreSaved = true;
}

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x*ts, y*ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            if (!gameOverSoundPlayed) {
                gameOverSound.play();
                gameOverSoundPlayed = true;
            }
            window.draw(sGameover);
        }
        window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
        window.display();
    }
};

 void playSinglePlayer_continious() {
   bool scoreSaved=false;
    int score = 0;
    int bonus_counter = 0;
    int bonus_threshold = 10;
    int bonus_multiplier = 1;
    int power_ups = 0;
    int move_count = 0;
    bool is_building = false;
    bool freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;
    int captured_this_move = 0;
    int next_power_up_score = 50;
   
    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
     Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false; // Track if game over sound has played
   
    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Medium Level!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");
   
    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }
   
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(10, 10);
   
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
    bonusText.setPosition(10, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    int enemyCount = 2;
    Enemy a[10];
    float enemySpeeds[10];
    int movementType[10]; // 0 = linear, 1 = circular, 2 = sinusoidal

    // Initialize enemies
    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f; // Speeds between 0.8 and 1.6
        a[i].x = (N/2 + i * 2) * ts; // Spread enemies
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0; // All start linear
    }

    bool Game = true;
    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;
    Clock Time;
    Clock pauseClock;
    float totalPausedTime = 0.0;
    bool isPaused = false;
    float Totalseconds = 0.0;

    // Set boundary walls
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M-1 || j == N-1) grid[i][j] = 1;

    bool movementAssigned = false;
    static float lastIncreaseTime = 0.0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
       
        if (!isPaused) {
            Totalseconds = Time.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText.setString("Moves: " + to_string(move_count));
            scoreText.setString("Score: " + to_string(score));
            powerUpText.setString("Power-Ups: " + to_string(power_ups));
            bonusText.setString("Bonus x" + to_string(bonus_multiplier) + " (" + to_string(bonus_counter) + " bonuses)");
        }
       
        // Increase speed every 20 seconds
        if (Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f; // Increased to 0.5 for noticeable effect
                enemyCount+=2;
            }
           
            lastIncreaseTime += 20; // Increment by 20 for precise intervals
        }

        // Assign movement types after 30 seconds
        if (Totalseconds >= 30 && !movementAssigned) {
            movementType[0] = 0; // Linear
            movementType[1] = 0; // Linear
            movementType[2] = 1; // Circular
            movementType[3] = 2; // Sinusoidal
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
           
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (e.key.code == Keyboard::Space && power_ups > 0 && !freeze_active) {
                    freeze_active = true;
                    freeze_clock.restart();
                    power_ups--;
                    powerUpSound.play();
                }
            }
        }
       
        if (Keyboard::isKeyPressed(Keyboard::Left)) {dx = -1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Right)) {dx = 1; dy = 0;}
        if (Keyboard::isKeyPressed(Keyboard::Up)) {dx = 0; dy = -1;}
        if (Keyboard::isKeyPressed(Keyboard::Down)) {dx = 0; dy = 1;}
       
        if (!Game) continue;

         if (timer > delay) {
            x += dx;
            y += dy;
            // Boundary checking
            if (x < 0) x = 0;
            else if (x > N - 1) x = N - 1;
            if (y < 0) y = 0;
            else if (y > M - 1) y = M - 1;
            if (grid[y][x] == 2) Game = false;
            if (grid[y][x] == 0) {
                if (!is_building) {
                    move_count++;
                    is_building = true;
                    captured_this_move = 0;
                }
                grid[y][x] = 2;
                captured_this_move++;
                // Update score continuously: 1 point per tile captured
                score += 1;
                // Check for power-up thresholds
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;
                }
            }
            timer = 0;
        }
       
        // Enemy movement
        if (freeze_active) {
            if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration)
                freeze_active = false;
        } else {
            for (int i = 0; i < enemyCount; i++) {
                // Bounds checking to prevent segmentation faults
                int gridX = int(a[i].x / ts);
                int gridY = int(a[i].y / ts);
                if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    a[i].dx = -a[i].dx;
                    a[i].dy = -a[i].dy;
                    continue;
                }

                if (movementType[i] == 0) {
                    // Linear motion using Enemy::move
                    a[i].isCircular = false;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 1) {
                    // Circular motion using Enemy::move
                    a[i].isCircular = true;
                    a[i].move(enemySpeeds[i]);
                } else if (movementType[i] == 2) {
                    // Sinusoidal motion
                    a[i].isCircular = false;
                    a[i].x += a[i].dx * enemySpeeds[i] * time;
                    a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                    a[i].angle += 0.05f * enemySpeeds[i];
                    gridX = int(a[i].x / ts);
                    gridY = int(a[i].y / ts);
                    if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                        a[i].dx = -a[i].dx;
                        a[i].x += a[i].dx * enemySpeeds[i] * time;
                    }
                    // Clamp x to [ts, (N-2)*ts]
                    if (a[i].x < ts) a[i].x = ts;
                    else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                    // Clamp y to [ts, (M-2)*ts]
                    if (a[i].y < ts) a[i].y = ts;
                    else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                }
            }
        }
       
        for (int i = 0; i < enemyCount; i++) {
            int gridX = int(a[i].x / ts);
            int gridY = int(a[i].y / ts);
            if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 2)
                Game = false;
        }

           //collision and scoring
    if (grid[y][x] == 1) {
        dx = dy = 0;
        if (is_building && captured_this_move > 0) {
            // Apply bonus multiplier if captured tiles meet/exceed threshold
            int current_threshold = (bonus_counter >= 3) ? 5 : 10;
            if (captured_this_move >= current_threshold) {
               
                bonus_counter++;
                 bonusSound.play();
                int bonus_points = captured_this_move; // Base bonus points
                // Apply multiplier based on total bonus occurrences
                if (bonus_counter >= 5) {
                    bonus_points *= 3; // Additional ×4 - 1 = ×3 points (since 1 point already added per tile)

                } else {
                    bonus_points *= 1; // Additional ×2 - 1 = ×1 points (since 1 point already added per tile)

                }
                score += bonus_points;
                captureSound.play();
                // Check for power-up thresholds again after bonus
                while (score >= next_power_up_score) {
                    power_ups++;
                    next_power_up_score = (next_power_up_score == 50) ? 70 : next_power_up_score + 30;

               }
            }
            // Reset building state and captured tiles

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
     
        // Set background color based on power-up status
        if (freeze_active) {
            window.clear(Color::White); // White when power-up is active
        } else {
            window.clear(Color::Black); // Default black
        }
         for (int i=0;i<enemyCount;i++)
     if (grid[int(a[i].y)/ts][int(a[i].x)/ts] == 2) Game = false;
      //calling savescore function to save score
    if (!Game && !scoreSaved) {
    int finalTime = Time.getElapsedTime().asSeconds() - totalPausedTime;
    saveScore(score, finalTime);
    cout << "Score saved: " << score << ", Time: " << finalTime << endl; // Debug message
    scoreSaved = true;
}

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x*ts, y*ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            if (!gameOverSoundPlayed) {
                gameOverSound.play();
                gameOverSoundPlayed = true;
            }
            window.draw(sGameover);
        }
        window.draw(timeText);
        window.draw(moveText);
        window.draw(scoreText);
        window.draw(powerUpText);
        window.draw(bonusText);
        window.display();
    }
};
void playTwoPlayer_mid() {
    

    // Enemy variables
    int enemyCount = 4; // Fixed at 4 for Mid
    bool scoreSaved = false;

    // Player 1 variables
    int score1 = 0, move_count1 = 0, power_ups1 = 0;
    int bonus_multiplier1 = 1, bonus_counter1 = 0;
    int captured_this_move1 = 0;
    bool is_building1 = false;
    int next_power_up_score1 = 50;
    bool player1_alive = true;
    int minRow1 = M-1, maxRow1 = 0, minCol1 = N-1, maxCol1 = 0;

    // Player 2 variables
    int score2 = 0, move_count2 = 0, power_ups2 = 0;
    int bonus_multiplier2 = 1, bonus_counter2 = 0;
    int captured_this_move2 = 0;
    bool is_building2 = false;
    int next_power_up_score2 = 50;
    bool player2_alive = true;
    int minRow2 = M-1, maxRow2 = 0, minCol2 = N-1, maxCol2 = 0;

    int bonus_threshold = 10;
    bool p1_freeze_active = false;
    bool p2_freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;

    Enemy a[50];
    float enemySpeeds[50];
    int movementType[50];
    bool movementAssigned = false;

    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
    Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false;

    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Mid Mode!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    Text timeText;
    timeText.setFont(font); timeText.setCharacterSize(25); timeText.setFillColor(Color::Red); timeText.setPosition(300, 20);
    Text moveText1;
    moveText1.setFont(font); moveText1.setCharacterSize(20); moveText1.setFillColor(Color::White); moveText1.setPosition(10, 40);
    Text scoreText1;
    scoreText1.setFont(font); scoreText1.setCharacterSize(20); scoreText1.setFillColor(Color::White); scoreText1.setPosition(10, 70);
    Text powerUpText1;
    powerUpText1.setFont(font); powerUpText1.setCharacterSize(20); powerUpText1.setFillColor(Color::White); powerUpText1.setPosition(10, 100);
    Text bonusText1;
    bonusText1.setFont(font); bonusText1.setCharacterSize(20); bonusText1.setFillColor(Color::White); bonusText1.setPosition(10, 130);
    Text moveText2;
    moveText2.setFont(font); moveText2.setCharacterSize(20); moveText2.setFillColor(Color::White); moveText2.setPosition(N*ts - 200, 40);
    Text scoreText2;
    scoreText2.setFont(font); scoreText2.setCharacterSize(20); scoreText2.setFillColor(Color::White); scoreText2.setPosition(N*ts - 200, 70);
    Text powerUpText2;
    powerUpText2.setFont(font); powerUpText2.setCharacterSize(20); powerUpText2.setFillColor(Color::White); powerUpText2.setPosition(N*ts - 200, 100);
    Text bonusText2;
    bonusText2.setFont(font); bonusText2.setCharacterSize(20); bonusText2.setFillColor(Color::White); bonusText2.setPosition(N*ts - 200, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f;
        a[i].x = (N/2 + i * 2) * ts;
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0;
    }

    bool Game = true;
    int x1 = 0, y1 = 0, dx1 = 0, dy1 = 0;
    int x2 = N - 1, y2 = M - 1, dx2 = 0, dy2 = 0;
    float timer = 0, delay = 0.07f;
    Clock clock;
    Clock gameClock;
    Clock pauseClock;
    float totalPausedTime = 0.0f;
    bool isPaused = false;
    float Totalseconds = 0.0f;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    int q_r[M*N];
    int q_c[M*N];
    bool visited[M][N];

    static float lastIncreaseTime = 0.0f;

    while (window.isOpen()) {
        float time_elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time_elapsed;

        if (!isPaused && Game) {
            Totalseconds = gameClock.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText1.setString("P1 Moves: " + to_string(move_count1));
            scoreText1.setString("P1 Score: " + to_string(score1));
            powerUpText1.setString("P1 PowerUps: " + to_string(power_ups1));
            bonusText1.setString("P1 Bonus x" + to_string(bonus_multiplier1) + " (" + to_string(bonus_counter1) + ")");
            moveText2.setString("P2 Moves: " + to_string(move_count2));
            scoreText2.setString("P2 Score: " + to_string(score2));
            powerUpText2.setString("P2 PowerUps: " + to_string(power_ups2));
            bonusText2.setString("P2 Bonus x" + to_string(bonus_multiplier2) + " (" + to_string(bonus_counter2) + ")");
        }

        if (!isPaused && Game && Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f;
            }
            lastIncreaseTime += 20;
        }

        if (!isPaused && Game && Totalseconds >= 30 && !movementAssigned) {
            for (int i = 0; i < enemyCount; i++) {
                if (i == 0 || i == 1) movementType[i] = 0;
                else if (i == 2) movementType[i] = 1;
                else if (i == 3) movementType[i] = 2;
                else {
                    int mod = i % 4;
                    movementType[i] = (mod == 0 || mod == 1) ? 0 : (mod == 2 ? 1 : 2);
                }
            }
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (!isPaused && Game) {
                    if (e.key.code == Keyboard::Space && power_ups1 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p1_freeze_active = true;
                        freeze_clock.restart();
                        power_ups1--;
                        powerUpSound.play();
                    }
                    if (e.key.code == Keyboard::Enter && power_ups2 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p2_freeze_active = true;
                        freeze_clock.restart();
                        power_ups2--;
                        powerUpSound.play();
                    }
                }
            }
        }
       
        if (isPaused || !Game) {
            // Skip game logic updates but continue drawing
        } else {
            if (player1_alive && !p2_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::Left)) { dx1 = -1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Right)) { dx1 = 1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Up)) { dx1 = 0; dy1 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::Down)) { dx1 = 0; dy1 = 1; }
            } else {
                dx1 = 0; dy1 = 0;
            }

            if (player2_alive && !p1_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }
            } else {
                dx2 = 0; dy2 = 0;
            }

            if (timer > delay) {
                if (player1_alive) {
                    int next_x1 = x1 + dx1;
                    int next_y1 = y1 + dy1;

                    if (next_x1 < 0) next_x1 = 0; else if (next_x1 >= N) next_x1 = N - 1;
                    if (next_y1 < 0) next_y1 = 0; else if (next_y1 >= M) next_y1 = M - 1;
                   
                    x1 = next_x1; y1 = next_y1;

                    if (is_building1) {
                        if (y1 < minRow1) minRow1 = y1; if (y1 > maxRow1) maxRow1 = y1;
                        if (x1 < minCol1) minCol1 = x1; if (x1 > maxCol1) maxCol1 = x1;
                    }

                    if (grid[y1][x1] == 2 || grid[y1][x1] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player1_alive = false; dx1=0; dy1=0;
                    } else if (grid[y1][x1] == 0) {
                        if (!is_building1) {
                            move_count1++; is_building1 = true; captured_this_move1 = 0;
                            minRow1 = y1; maxRow1 = y1; minCol1 = x1; maxCol1 = x1;
                        }
                        grid[y1][x1] = 2; captured_this_move1++;
                    }
                }

                if (player2_alive) {
                    int next_x2 = x2 + dx2;
                    int next_y2 = y2 + dy2;

                    if (next_x2 < 0) next_x2 = 0; else if (next_x2 >= N) next_x2 = N - 1;
                    if (next_y2 < 0) next_y2 = 0; else if (next_y2 >= M) next_y2 = M - 1;

                    x2 = next_x2; y2 = next_y2;

                    if (is_building2) {
                        if (y2 < minRow2) minRow2 = y2; if (y2 > maxRow2) maxRow2 = y2;
                        if (x2 < minCol2) minCol2 = x2; if (x2 > maxCol2) maxCol2 = x2;
                    }
                    if (grid[y2][x2] == 2 || grid[y2][x2] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player2_alive = false; dx2=0; dy2=0;
                    } else if (grid[y2][x2] == 0) {
                        if (!is_building2) {
                            move_count2++; is_building2 = true; captured_this_move2 = 0;
                            minRow2 = y2; maxRow2 = y2; minCol2 = x2; maxCol2 = x2;
                        }
                        grid[y2][x2] = 3; captured_this_move2++;
                    }
                }
                timer = 0;
            }

            if (p1_freeze_active || p2_freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration) {
                    p1_freeze_active = false;
                    p2_freeze_active = false;
                }
            } else {
                for (int i = 0; i < enemyCount; i++) {
                    int gridX = int(a[i].x / ts);
                    int gridY = int(a[i].y / ts);
                    if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                        a[i].dx = -a[i].dx;
                        a[i].dy = -a[i].dy;
                        continue;
                    }

                    if (movementType[i] == 0) {
                        a[i].isCircular = false;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 1) {
                        a[i].isCircular = true;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 2) {
                        a[i].isCircular = false;
                        a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                        a[i].angle += 0.05f * enemySpeeds[i];
                        gridX = int(a[i].x / ts);
                        gridY = int(a[i].y / ts);
                        if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                            a[i].dx = -a[i].dx;
                            a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        }
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    }
                }
            }

            // Player 1 Capture & Scoring Logic
            if (player1_alive && grid[y1][x1] == 1 && is_building1 && captured_this_move1 > 0) {
                dx1 = 0; dy1 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 2) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move1; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player1_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter1 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter1 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier1 = 4;
                        } else {
                            bonus_multiplier1 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter1++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier1 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier1;
                    score1 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P1 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier1
                         << ", Bonus Counter: " << bonus_counter1 << ", Points Added: " << points_to_add << endl;

                    while (score1 >= next_power_up_score1) {
                        power_ups1++;
                        powerUpSound.play();
                        next_power_up_score1 = (next_power_up_score1 == 50) ? 70 : next_power_up_score1 + 30;
                    }
                }
                captured_this_move1 = 0; is_building1 = false;
                minRow1 = M - 1; maxRow1 = 0; minCol1 = N - 1; maxCol1 = 0;
            }

            // Player 2 Capture & Scoring Logic
            if (player2_alive && grid[y2][x2] == 1 && is_building2 && captured_this_move2 > 0) {
                dx2 = 0; dy2 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 3) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move2; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player2_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter2 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter2 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier2 = 4;
                        } else {
                            bonus_multiplier2 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter2++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier2 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier2;
                    score2 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P2 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier2
                         << ", Bonus Counter: " << bonus_counter2 << ", Points Added: " << points_to_add << endl;

                    while (score2 >= next_power_up_score2) {
                        power_ups2++;
                        powerUpSound.play();
                        next_power_up_score2 = (next_power_up_score2 == 50) ? 70 : next_power_up_score2 + 30;
                    }
                }
                captured_this_move2 = 0; is_building2 = false;
                minRow2 = M - 1; maxRow2 = 0; minCol2 = N - 1; maxCol2 = 0;
            }

            for (int i = 0; i < enemyCount; i++) {
                int ex_grid = static_cast<int>(a[i].x) / ts;
                int ey_grid = static_cast<int>(a[i].y) / ts;
                if (ex_grid >= 0 && ex_grid < N && ey_grid >= 0 && ey_grid < M) {
                    if (grid[ey_grid][ex_grid] == 2 && player1_alive) {
                        player1_alive = false;
                        is_building1 = false;
                    }
                    if (grid[ey_grid][ex_grid] == 3 && player2_alive) {
                        player2_alive = false;
                        is_building2 = false;
                    }
                }
            }

            if (!player1_alive && !player2_alive) {
                Game = false;
                if (!gameOverSoundPlayed) {
                    gameOverSound.play();
                    gameOverSoundPlayed = true;
                }
            }
        }

        if (p1_freeze_active || p2_freeze_active) {
            window.clear(Color::White);
        } else {
            window.clear(Color::Black);
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(36, 0, ts, ts));
                if (grid[i][j] == 3) sTile.setTextureRect(IntRect(72, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }
        }

        if (player1_alive) {
            sTile.setTextureRect(IntRect(36, 0, ts, ts));
            sTile.setPosition(x1*ts, y1*ts);
            window.draw(sTile);
        }
        if (player2_alive) {
            sTile.setTextureRect(IntRect(72, 0, ts, ts));
            sTile.setPosition(x2*ts, y2*ts);
            window.draw(sTile);
        }

        if (Game) sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            window.draw(sGameover);
            string winner_str;
            if (score1 > score2) winner_str = "Player 1 Wins!";
            else if (score2 > score1) winner_str = "Player 2 Wins!";
            else winner_str = "Tie!";
           
            Text winnerText;
            winnerText.setFont(font);
            winnerText.setString(winner_str);
            winnerText.setCharacterSize(30);
            winnerText.setFillColor(Color::Yellow);
            FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            winnerText.setPosition(N*ts/2.0f, M*ts/2.0f + 20);
            window.draw(winnerText);
        }
       
        if (isPaused) {
            Text pauseText("PAUSED", font, 50);
            FloatRect textRect = pauseText.getLocalBounds();
            pauseText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            pauseText.setPosition(N*ts/2.0f, M*ts/2.0f - 50);
            pauseText.setFillColor(Color::Red);
            window.draw(pauseText);
        }

        window.draw(timeText); window.draw(moveText1); window.draw(scoreText1); window.draw(powerUpText1); window.draw(bonusText1);
        window.draw(moveText2); window.draw(scoreText2); window.draw(powerUpText2); window.draw(bonusText2);
        window.display();
    }
}


void playTwoPlayer_easy() {
    

    // Enemy variables
    int enemyCount = 2; // Fixed at 4 for Mid
    bool scoreSaved = false;

    // Player 1 variables
    int score1 = 0, move_count1 = 0, power_ups1 = 0;
    int bonus_multiplier1 = 1, bonus_counter1 = 0;
    int captured_this_move1 = 0;
    bool is_building1 = false;
    int next_power_up_score1 = 50;
    bool player1_alive = true;
    int minRow1 = M-1, maxRow1 = 0, minCol1 = N-1, maxCol1 = 0;

    // Player 2 variables
    int score2 = 0, move_count2 = 0, power_ups2 = 0;
    int bonus_multiplier2 = 1, bonus_counter2 = 0;
    int captured_this_move2 = 0;
    bool is_building2 = false;
    int next_power_up_score2 = 50;
    bool player2_alive = true;
    int minRow2 = M-1, maxRow2 = 0, minCol2 = N-1, maxCol2 = 0;

    int bonus_threshold = 10;
    bool p1_freeze_active = false;
    bool p2_freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;

    Enemy a[50];
    float enemySpeeds[50];
    int movementType[50];
    bool movementAssigned = false;

    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
    Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false;

    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Mid Mode!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    Text timeText;
    timeText.setFont(font); timeText.setCharacterSize(25); timeText.setFillColor(Color::Red); timeText.setPosition(300, 20);
    Text moveText1;
    moveText1.setFont(font); moveText1.setCharacterSize(20); moveText1.setFillColor(Color::White); moveText1.setPosition(10, 40);
    Text scoreText1;
    scoreText1.setFont(font); scoreText1.setCharacterSize(20); scoreText1.setFillColor(Color::White); scoreText1.setPosition(10, 70);
    Text powerUpText1;
    powerUpText1.setFont(font); powerUpText1.setCharacterSize(20); powerUpText1.setFillColor(Color::White); powerUpText1.setPosition(10, 100);
    Text bonusText1;
    bonusText1.setFont(font); bonusText1.setCharacterSize(20); bonusText1.setFillColor(Color::White); bonusText1.setPosition(10, 130);
    Text moveText2;
    moveText2.setFont(font); moveText2.setCharacterSize(20); moveText2.setFillColor(Color::White); moveText2.setPosition(N*ts - 200, 40);
    Text scoreText2;
    scoreText2.setFont(font); scoreText2.setCharacterSize(20); scoreText2.setFillColor(Color::White); scoreText2.setPosition(N*ts - 200, 70);
    Text powerUpText2;
    powerUpText2.setFont(font); powerUpText2.setCharacterSize(20); powerUpText2.setFillColor(Color::White); powerUpText2.setPosition(N*ts - 200, 100);
    Text bonusText2;
    bonusText2.setFont(font); bonusText2.setCharacterSize(20); bonusText2.setFillColor(Color::White); bonusText2.setPosition(N*ts - 200, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f;
        a[i].x = (N/2 + i * 2) * ts;
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0;
    }

    bool Game = true;
    int x1 = 0, y1 = 0, dx1 = 0, dy1 = 0;
    int x2 = N - 1, y2 = M - 1, dx2 = 0, dy2 = 0;
    float timer = 0, delay = 0.07f;
    Clock clock;
    Clock gameClock;
    Clock pauseClock;
    float totalPausedTime = 0.0f;
    bool isPaused = false;
    float Totalseconds = 0.0f;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    int q_r[M*N];
    int q_c[M*N];
    bool visited[M][N];

    static float lastIncreaseTime = 0.0f;

    while (window.isOpen()) {
        float time_elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time_elapsed;

        if (!isPaused && Game) {
            Totalseconds = gameClock.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText1.setString("P1 Moves: " + to_string(move_count1));
            scoreText1.setString("P1 Score: " + to_string(score1));
            powerUpText1.setString("P1 PowerUps: " + to_string(power_ups1));
            bonusText1.setString("P1 Bonus x" + to_string(bonus_multiplier1) + " (" + to_string(bonus_counter1) + ")");
            moveText2.setString("P2 Moves: " + to_string(move_count2));
            scoreText2.setString("P2 Score: " + to_string(score2));
            powerUpText2.setString("P2 PowerUps: " + to_string(power_ups2));
            bonusText2.setString("P2 Bonus x" + to_string(bonus_multiplier2) + " (" + to_string(bonus_counter2) + ")");
        }

        if (!isPaused && Game && Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f;
            }
            lastIncreaseTime += 20;
        }

        if (!isPaused && Game && Totalseconds >= 30 && !movementAssigned) {
            for (int i = 0; i < enemyCount; i++) {
                if (i == 0 || i == 1) movementType[i] = 0;
                else if (i == 2) movementType[i] = 1;
                else if (i == 3) movementType[i] = 2;
                else {
                    int mod = i % 4;
                    movementType[i] = (mod == 0 || mod == 1) ? 0 : (mod == 2 ? 1 : 2);
                }
            }
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (!isPaused && Game) {
                    if (e.key.code == Keyboard::Space && power_ups1 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p1_freeze_active = true;
                        freeze_clock.restart();
                        power_ups1--;
                        powerUpSound.play();
                    }
                    if (e.key.code == Keyboard::Enter && power_ups2 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p2_freeze_active = true;
                        freeze_clock.restart();
                        power_ups2--;
                        powerUpSound.play();
                    }
                }
            }
        }
       
        if (isPaused || !Game) {
            // Skip game logic updates but continue drawing
        } else {
            if (player1_alive && !p2_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::Left)) { dx1 = -1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Right)) { dx1 = 1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Up)) { dx1 = 0; dy1 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::Down)) { dx1 = 0; dy1 = 1; }
            } else {
                dx1 = 0; dy1 = 0;
            }

            if (player2_alive && !p1_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }
            } else {
                dx2 = 0; dy2 = 0;
            }

            if (timer > delay) {
                if (player1_alive) {
                    int next_x1 = x1 + dx1;
                    int next_y1 = y1 + dy1;

                    if (next_x1 < 0) next_x1 = 0; else if (next_x1 >= N) next_x1 = N - 1;
                    if (next_y1 < 0) next_y1 = 0; else if (next_y1 >= M) next_y1 = M - 1;
                   
                    x1 = next_x1; y1 = next_y1;

                    if (is_building1) {
                        if (y1 < minRow1) minRow1 = y1; if (y1 > maxRow1) maxRow1 = y1;
                        if (x1 < minCol1) minCol1 = x1; if (x1 > maxCol1) maxCol1 = x1;
                    }

                    if (grid[y1][x1] == 2 || grid[y1][x1] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player1_alive = false; dx1=0; dy1=0;
                    } else if (grid[y1][x1] == 0) {
                        if (!is_building1) {
                            move_count1++; is_building1 = true; captured_this_move1 = 0;
                            minRow1 = y1; maxRow1 = y1; minCol1 = x1; maxCol1 = x1;
                        }
                        grid[y1][x1] = 2; captured_this_move1++;
                    }
                }

                if (player2_alive) {
                    int next_x2 = x2 + dx2;
                    int next_y2 = y2 + dy2;

                    if (next_x2 < 0) next_x2 = 0; else if (next_x2 >= N) next_x2 = N - 1;
                    if (next_y2 < 0) next_y2 = 0; else if (next_y2 >= M) next_y2 = M - 1;

                    x2 = next_x2; y2 = next_y2;

                    if (is_building2) {
                        if (y2 < minRow2) minRow2 = y2; if (y2 > maxRow2) maxRow2 = y2;
                        if (x2 < minCol2) minCol2 = x2; if (x2 > maxCol2) maxCol2 = x2;
                    }
                    if (grid[y2][x2] == 2 || grid[y2][x2] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player2_alive = false; dx2=0; dy2=0;
                    } else if (grid[y2][x2] == 0) {
                        if (!is_building2) {
                            move_count2++; is_building2 = true; captured_this_move2 = 0;
                            minRow2 = y2; maxRow2 = y2; minCol2 = x2; maxCol2 = x2;
                        }
                        grid[y2][x2] = 3; captured_this_move2++;
                    }
                }
                timer = 0;
            }

            if (p1_freeze_active || p2_freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration) {
                    p1_freeze_active = false;
                    p2_freeze_active = false;
                }
            } else {
                for (int i = 0; i < enemyCount; i++) {
                    int gridX = int(a[i].x / ts);
                    int gridY = int(a[i].y / ts);
                    if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                        a[i].dx = -a[i].dx;
                        a[i].dy = -a[i].dy;
                        continue;
                    }

                    if (movementType[i] == 0) {
                        a[i].isCircular = false;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 1) {
                        a[i].isCircular = true;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 2) {
                        a[i].isCircular = false;
                        a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                        a[i].angle += 0.05f * enemySpeeds[i];
                        gridX = int(a[i].x / ts);
                        gridY = int(a[i].y / ts);
                        if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                            a[i].dx = -a[i].dx;
                            a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        }
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    }
                }
            }

            // Player 1 Capture & Scoring Logic
            if (player1_alive && grid[y1][x1] == 1 && is_building1 && captured_this_move1 > 0) {
                dx1 = 0; dy1 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 2) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move1; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player1_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter1 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter1 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier1 = 4;
                        } else {
                            bonus_multiplier1 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter1++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier1 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier1;
                    score1 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P1 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier1
                         << ", Bonus Counter: " << bonus_counter1 << ", Points Added: " << points_to_add << endl;

                    while (score1 >= next_power_up_score1) {
                        power_ups1++;
                        powerUpSound.play();
                        next_power_up_score1 = (next_power_up_score1 == 50) ? 70 : next_power_up_score1 + 30;
                    }
                }
                captured_this_move1 = 0; is_building1 = false;
                minRow1 = M - 1; maxRow1 = 0; minCol1 = N - 1; maxCol1 = 0;
            }

            // Player 2 Capture & Scoring Logic
            if (player2_alive && grid[y2][x2] == 1 && is_building2 && captured_this_move2 > 0) {
                dx2 = 0; dy2 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 3) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move2; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player2_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter2 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter2 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier2 = 4;
                        } else {
                            bonus_multiplier2 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter2++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier2 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier2;
                    score2 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P2 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier2
                         << ", Bonus Counter: " << bonus_counter2 << ", Points Added: " << points_to_add << endl;

                    while (score2 >= next_power_up_score2) {
                        power_ups2++;
                        powerUpSound.play();
                        next_power_up_score2 = (next_power_up_score2 == 50) ? 70 : next_power_up_score2 + 30;
                    }
                }
                captured_this_move2 = 0; is_building2 = false;
                minRow2 = M - 1; maxRow2 = 0; minCol2 = N - 1; maxCol2 = 0;
            }

            for (int i = 0; i < enemyCount; i++) {
                int ex_grid = static_cast<int>(a[i].x) / ts;
                int ey_grid = static_cast<int>(a[i].y) / ts;
                if (ex_grid >= 0 && ex_grid < N && ey_grid >= 0 && ey_grid < M) {
                    if (grid[ey_grid][ex_grid] == 2 && player1_alive) {
                        player1_alive = false;
                        is_building1 = false;
                    }
                    if (grid[ey_grid][ex_grid] == 3 && player2_alive) {
                        player2_alive = false;
                        is_building2 = false;
                    }
                }
            }

            if (!player1_alive && !player2_alive) {
                Game = false;
                if (!gameOverSoundPlayed) {
                    gameOverSound.play();
                    gameOverSoundPlayed = true;
                }
            }
        }

        if (p1_freeze_active || p2_freeze_active) {
            window.clear(Color::White);
        } else {
            window.clear(Color::Black);
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(36, 0, ts, ts));
                if (grid[i][j] == 3) sTile.setTextureRect(IntRect(72, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }
        }

        if (player1_alive) {
            sTile.setTextureRect(IntRect(36, 0, ts, ts));
            sTile.setPosition(x1*ts, y1*ts);
            window.draw(sTile);
        }
        if (player2_alive) {
            sTile.setTextureRect(IntRect(72, 0, ts, ts));
            sTile.setPosition(x2*ts, y2*ts);
            window.draw(sTile);
        }

        if (Game) sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            window.draw(sGameover);
            string winner_str;
            if (score1 > score2) winner_str = "Player 1 Wins!";
            else if (score2 > score1) winner_str = "Player 2 Wins!";
            else winner_str = "Tie!";
           
            Text winnerText;
            winnerText.setFont(font);
            winnerText.setString(winner_str);
            winnerText.setCharacterSize(30);
            winnerText.setFillColor(Color::Yellow);
            FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            winnerText.setPosition(N*ts/2.0f, M*ts/2.0f + 20);
            window.draw(winnerText);
        }
       
        if (isPaused) {
            Text pauseText("PAUSED", font, 50);
            FloatRect textRect = pauseText.getLocalBounds();
            pauseText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            pauseText.setPosition(N*ts/2.0f, M*ts/2.0f - 50);
            pauseText.setFillColor(Color::Red);
            window.draw(pauseText);
        }

        window.draw(timeText); window.draw(moveText1); window.draw(scoreText1); window.draw(powerUpText1); window.draw(bonusText1);
        window.draw(moveText2); window.draw(scoreText2); window.draw(powerUpText2); window.draw(bonusText2);
        window.display();
    }
}

void playTwoPlayer_hard() {
    

    // Enemy variables
    int enemyCount = 6; // Fixed at 4 for Mid
    bool scoreSaved = false;

    // Player 1 variables
    int score1 = 0, move_count1 = 0, power_ups1 = 0;
    int bonus_multiplier1 = 1, bonus_counter1 = 0;
    int captured_this_move1 = 0;
    bool is_building1 = false;
    int next_power_up_score1 = 50;
    bool player1_alive = true;
    int minRow1 = M-1, maxRow1 = 0, minCol1 = N-1, maxCol1 = 0;

    // Player 2 variables
    int score2 = 0, move_count2 = 0, power_ups2 = 0;
    int bonus_multiplier2 = 1, bonus_counter2 = 0;
    int captured_this_move2 = 0;
    bool is_building2 = false;
    int next_power_up_score2 = 50;
    bool player2_alive = true;
    int minRow2 = M-1, maxRow2 = 0, minCol2 = N-1, maxCol2 = 0;

    int bonus_threshold = 10;
    bool p1_freeze_active = false;
    bool p2_freeze_active = false;
    Clock freeze_clock;
    const float freeze_duration = 3.0f;

    Enemy a[50];
    float enemySpeeds[50];
    int movementType[50];
    bool movementAssigned = false;

    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
    Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false;

    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Mid Mode!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    Text timeText;
    timeText.setFont(font); timeText.setCharacterSize(25); timeText.setFillColor(Color::Red); timeText.setPosition(300, 20);
    Text moveText1;
    moveText1.setFont(font); moveText1.setCharacterSize(20); moveText1.setFillColor(Color::White); moveText1.setPosition(10, 40);
    Text scoreText1;
    scoreText1.setFont(font); scoreText1.setCharacterSize(20); scoreText1.setFillColor(Color::White); scoreText1.setPosition(10, 70);
    Text powerUpText1;
    powerUpText1.setFont(font); powerUpText1.setCharacterSize(20); powerUpText1.setFillColor(Color::White); powerUpText1.setPosition(10, 100);
    Text bonusText1;
    bonusText1.setFont(font); bonusText1.setCharacterSize(20); bonusText1.setFillColor(Color::White); bonusText1.setPosition(10, 130);
    Text moveText2;
    moveText2.setFont(font); moveText2.setCharacterSize(20); moveText2.setFillColor(Color::White); moveText2.setPosition(N*ts - 200, 40);
    Text scoreText2;
    scoreText2.setFont(font); scoreText2.setCharacterSize(20); scoreText2.setFillColor(Color::White); scoreText2.setPosition(N*ts - 200, 70);
    Text powerUpText2;
    powerUpText2.setFont(font); powerUpText2.setCharacterSize(20); powerUpText2.setFillColor(Color::White); powerUpText2.setPosition(N*ts - 200, 100);
    Text bonusText2;
    bonusText2.setFont(font); bonusText2.setCharacterSize(20); bonusText2.setFillColor(Color::White); bonusText2.setPosition(N*ts - 200, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f;
        a[i].x = (N/2 + i * 2) * ts;
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0;
    }

    bool Game = true;
    int x1 = 0, y1 = 0, dx1 = 0, dy1 = 0;
    int x2 = N - 1, y2 = M - 1, dx2 = 0, dy2 = 0;
    float timer = 0, delay = 0.07f;
    Clock clock;
    Clock gameClock;
    Clock pauseClock;
    float totalPausedTime = 0.0f;
    bool isPaused = false;
    float Totalseconds = 0.0f;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    int q_r[M*N];
    int q_c[M*N];
    bool visited[M][N];

    static float lastIncreaseTime = 0.0f;

    while (window.isOpen()) {
        float time_elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time_elapsed;

        if (!isPaused && Game) {
            Totalseconds = gameClock.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText1.setString("P1 Moves: " + to_string(move_count1));
            scoreText1.setString("P1 Score: " + to_string(score1));
            powerUpText1.setString("P1 PowerUps: " + to_string(power_ups1));
            bonusText1.setString("P1 Bonus x" + to_string(bonus_multiplier1) + " (" + to_string(bonus_counter1) + ")");
            moveText2.setString("P2 Moves: " + to_string(move_count2));
            scoreText2.setString("P2 Score: " + to_string(score2));
            powerUpText2.setString("P2 PowerUps: " + to_string(power_ups2));
            bonusText2.setString("P2 Bonus x" + to_string(bonus_multiplier2) + " (" + to_string(bonus_counter2) + ")");
        }

        if (!isPaused && Game && Totalseconds >= lastIncreaseTime + 20) {
            for (int i = 0; i < enemyCount; i++) {
                enemySpeeds[i] += 0.5f;
            }
            lastIncreaseTime += 20;
        }

        if (!isPaused && Game && Totalseconds >= 30 && !movementAssigned) {
            for (int i = 0; i < enemyCount; i++) {
                if (i == 0 || i == 1) movementType[i] = 0;
                else if (i == 2) movementType[i] = 1;
                else if (i == 3) movementType[i] = 2;
                else {
                    int mod = i % 4;
                    movementType[i] = (mod == 0 || mod == 1) ? 0 : (mod == 2 ? 1 : 2);
                }
            }
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (!isPaused && Game) {
                    if (e.key.code == Keyboard::Space && power_ups1 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p1_freeze_active = true;
                        freeze_clock.restart();
                        power_ups1--;
                        powerUpSound.play();
                    }
                    if (e.key.code == Keyboard::Enter && power_ups2 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p2_freeze_active = true;
                        freeze_clock.restart();
                        power_ups2--;
                        powerUpSound.play();
                    }
                }
            }
        }
       
        if (isPaused || !Game) {
            // Skip game logic updates but continue drawing
        } else {
            if (player1_alive && !p2_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::Left)) { dx1 = -1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Right)) { dx1 = 1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Up)) { dx1 = 0; dy1 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::Down)) { dx1 = 0; dy1 = 1; }
            } else {
                dx1 = 0; dy1 = 0;
            }

            if (player2_alive && !p1_freeze_active) {
                if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }
            } else {
                dx2 = 0; dy2 = 0;
            }

            if (timer > delay) {
                if (player1_alive) {
                    int next_x1 = x1 + dx1;
                    int next_y1 = y1 + dy1;

                    if (next_x1 < 0) next_x1 = 0; else if (next_x1 >= N) next_x1 = N - 1;
                    if (next_y1 < 0) next_y1 = 0; else if (next_y1 >= M) next_y1 = M - 1;
                   
                    x1 = next_x1; y1 = next_y1;

                    if (is_building1) {
                        if (y1 < minRow1) minRow1 = y1; if (y1 > maxRow1) maxRow1 = y1;
                        if (x1 < minCol1) minCol1 = x1; if (x1 > maxCol1) maxCol1 = x1;
                    }

                    if (grid[y1][x1] == 2 || grid[y1][x1] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player1_alive = false; dx1=0; dy1=0;
                    } else if (grid[y1][x1] == 0) {
                        if (!is_building1) {
                            move_count1++; is_building1 = true; captured_this_move1 = 0;
                            minRow1 = y1; maxRow1 = y1; minCol1 = x1; maxCol1 = x1;
                        }
                        grid[y1][x1] = 2; captured_this_move1++;
                    }
                }

                if (player2_alive) {
                    int next_x2 = x2 + dx2;
                    int next_y2 = y2 + dy2;

                    if (next_x2 < 0) next_x2 = 0; else if (next_x2 >= N) next_x2 = N - 1;
                    if (next_y2 < 0) next_y2 = 0; else if (next_y2 >= M) next_y2 = M - 1;

                    x2 = next_x2; y2 = next_y2;

                    if (is_building2) {
                        if (y2 < minRow2) minRow2 = y2; if (y2 > maxRow2) maxRow2 = y2;
                        if (x2 < minCol2) minCol2 = x2; if (x2 > maxCol2) maxCol2 = x2;
                    }
                    if (grid[y2][x2] == 2 || grid[y2][x2] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player2_alive = false; dx2=0; dy2=0;
                    } else if (grid[y2][x2] == 0) {
                        if (!is_building2) {
                            move_count2++; is_building2 = true; captured_this_move2 = 0;
                            minRow2 = y2; maxRow2 = y2; minCol2 = x2; maxCol2 = x2;
                        }
                        grid[y2][x2] = 3; captured_this_move2++;
                    }
                }
                timer = 0;
            }

            if (p1_freeze_active || p2_freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration) {
                    p1_freeze_active = false;
                    p2_freeze_active = false;
                }
            } else {
                for (int i = 0; i < enemyCount; i++) {
                    int gridX = int(a[i].x / ts);
                    int gridY = int(a[i].y / ts);
                    if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                        a[i].dx = -a[i].dx;
                        a[i].dy = -a[i].dy;
                        continue;
                    }

                    if (movementType[i] == 0) {
                        a[i].isCircular = false;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 1) {
                        a[i].isCircular = true;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 2) {
                        a[i].isCircular = false;
                        a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                        a[i].angle += 0.05f * enemySpeeds[i];
                        gridX = int(a[i].x / ts);
                        gridY = int(a[i].y / ts);
                        if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                            a[i].dx = -a[i].dx;
                            a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        }
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    }
                }
            }

            // Player 1 Capture & Scoring Logic
            if (player1_alive && grid[y1][x1] == 1 && is_building1 && captured_this_move1 > 0) {
                dx1 = 0; dy1 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 2) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move1; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player1_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter1 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter1 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier1 = 4;
                        } else {
                            bonus_multiplier1 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter1++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier1 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier1;
                    score1 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P1 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier1
                         << ", Bonus Counter: " << bonus_counter1 << ", Points Added: " << points_to_add << endl;

                    while (score1 >= next_power_up_score1) {
                        power_ups1++;
                        powerUpSound.play();
                        next_power_up_score1 = (next_power_up_score1 == 50) ? 70 : next_power_up_score1 + 30;
                    }
                }
                captured_this_move1 = 0; is_building1 = false;
                minRow1 = M - 1; maxRow1 = 0; minCol1 = N - 1; maxCol1 = 0;
            }

            // Player 2 Capture & Scoring Logic
            if (player2_alive && grid[y2][x2] == 1 && is_building2 && captured_this_move2 > 0) {
                dx2 = 0; dy2 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 3) { grid[r_path][c_path] = 1; }
                    }
                }
                for (int r_init = 0; r_init < M; ++r_init)
                    for (int c_init = 0; c_init < N; ++c_init)
                        visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    if (a[enemy_idx].x < 0 || a[enemy_idx].y < 0) continue;
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++; visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while (q_head < q_tail) {
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for (int i_bfs = 0; i_bfs < 4; ++i_bfs) {
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true; q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = captured_this_move2; // Include path tiles
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }

                if (captured_area_points > 0 && player2_alive) {
                    captureSound.play();
                    int points_to_add = captured_area_points; // Rule 1: 1 point per tile
                    int current_bonus_threshold = (bonus_counter2 >= 3) ? 5 : 10; // Rule 3a: Threshold 5 after 3 bonuses

                    if (captured_area_points > current_bonus_threshold) {
                        bonusSound.play();
                        if (bonus_counter2 >= 5) { // Rule 3b: ×4 after 5 bonuses
                            bonus_multiplier2 = 4;
                        } else {
                            bonus_multiplier2 = 2; // Rule 2: ×2 for >10 or >5 tiles
                        }
                        bonus_counter2++; // Rule 3: Increment reward counter
                    } else {
                        bonus_multiplier2 = 1; // No bonus
                    }

                    points_to_add *= bonus_multiplier2;
                    score2 += points_to_add;

                    // Debug logging to verify scoring
                    cout << "P2 Captured: " << captured_area_points << ", Multiplier: " << bonus_multiplier2
                         << ", Bonus Counter: " << bonus_counter2 << ", Points Added: " << points_to_add << endl;

                    while (score2 >= next_power_up_score2) {
                        power_ups2++;
                        powerUpSound.play();
                        next_power_up_score2 = (next_power_up_score2 == 50) ? 70 : next_power_up_score2 + 30;
                    }
                }
                captured_this_move2 = 0; is_building2 = false;
                minRow2 = M - 1; maxRow2 = 0; minCol2 = N - 1; maxCol2 = 0;
            }

            for (int i = 0; i < enemyCount; i++) {
                int ex_grid = static_cast<int>(a[i].x) / ts;
                int ey_grid = static_cast<int>(a[i].y) / ts;
                if (ex_grid >= 0 && ex_grid < N && ey_grid >= 0 && ey_grid < M) {
                    if (grid[ey_grid][ex_grid] == 2 && player1_alive) {
                        player1_alive = false;
                        is_building1 = false;
                    }
                    if (grid[ey_grid][ex_grid] == 3 && player2_alive) {
                        player2_alive = false;
                        is_building2 = false;
                    }
                }
            }

            if (!player1_alive && !player2_alive) {
                Game = false;
                if (!gameOverSoundPlayed) {
                    gameOverSound.play();
                    gameOverSoundPlayed = true;
                }
            }
        }

        if (p1_freeze_active || p2_freeze_active) {
            window.clear(Color::White);
        } else {
            window.clear(Color::Black);
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(36, 0, ts, ts));
                if (grid[i][j] == 3) sTile.setTextureRect(IntRect(72, 0, ts, ts));
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }
        }

        if (player1_alive) {
            sTile.setTextureRect(IntRect(36, 0, ts, ts));
            sTile.setPosition(x1*ts, y1*ts);
            window.draw(sTile);
        }
        if (player2_alive) {
            sTile.setTextureRect(IntRect(72, 0, ts, ts));
            sTile.setPosition(x2*ts, y2*ts);
            window.draw(sTile);
        }

        if (Game) sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            window.draw(sGameover);
            string winner_str;
            if (score1 > score2) winner_str = "Player 1 Wins!";
            else if (score2 > score1) winner_str = "Player 2 Wins!";
            else winner_str = "Tie!";
           
            Text winnerText;
            winnerText.setFont(font);
            winnerText.setString(winner_str);
            winnerText.setCharacterSize(30);
            winnerText.setFillColor(Color::Yellow);
            FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            winnerText.setPosition(N*ts/2.0f, M*ts/2.0f + 20);
            window.draw(winnerText);
        }
       
        if (isPaused) {
            Text pauseText("PAUSED", font, 50);
            FloatRect textRect = pauseText.getLocalBounds();
            pauseText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            pauseText.setPosition(N*ts/2.0f, M*ts/2.0f - 50);
            pauseText.setFillColor(Color::Red);
            window.draw(pauseText);
        }

        window.draw(timeText); window.draw(moveText1); window.draw(scoreText1); window.draw(powerUpText1); window.draw(bonusText1);
        window.draw(moveText2); window.draw(scoreText2); window.draw(powerUpText2); window.draw(bonusText2);
        window.display();
    }
}


void playTwoPlayer_continious() {
    // Player 1 variables
    int score1 = 0, move_count1 = 0, power_ups1 = 0;
    int bonus_multiplier1 = 1, bonus_counter1 = 0;
    int captured_this_move1 = 0;
    bool is_building1 = false;
    int next_power_up_score1 = 50;
    bool player1_alive = true;
    int minRow1 = M-1, maxRow1 = 0, minCol1 = N-1, maxCol1 = 0;

    // Player 2 variables
    int score2 = 0, move_count2 = 0, power_ups2 = 0;
    int bonus_multiplier2 = 1, bonus_counter2 = 0;
    int captured_this_move2 = 0;
    bool is_building2 = false;
    int next_power_up_score2 = 50;
    bool player2_alive = true;
    int minRow2 = M-1, maxRow2 = 0, minCol2 = N-1, maxCol2 = 0;

    int bonus_threshold = 10;
    bool p1_freeze_active = false; // Player 1's power-up (freezes Player 2 and enemies)
    bool p2_freeze_active = false; // Player 2's power-up (freezes Player 1 and enemies)
    Clock freeze_clock;
    const float freeze_duration = 3.0f;

    // Enemy variables
    int enemyCount = 2;
    Enemy a[50];
    float enemySpeeds[50];
    int movementType[50]; // 0 = linear, 1 = circular, 2 = sinusoidal
    bool movementAssigned = false;

    // Sound effects
    SoundBuffer captureBuffer, bonusBuffer, powerUpBuffer, gameOverBuffer;
    if (!captureBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/gameover.wav")) {
        cout << "Failed to load capture.wav!" << endl;
    }
    if (!bonusBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/bonus.wav")) {
        cout << "Failed to load bonus.wav!" << endl;
    }
    if (!powerUpBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/powerup.wav")) {
        cout << "Failed to load powerup.wav!" << endl;
    }
    if (!gameOverBuffer.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/audio/freeze.wav")) {
        cout << "Failed to load gameover.wav!" << endl;
    }
    Sound captureSound, bonusSound, powerUpSound, gameOverSound;
    captureSound.setBuffer(captureBuffer);
    bonusSound.setBuffer(bonusBuffer);
    powerUpSound.setBuffer(powerUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    bool gameOverSoundPlayed = false; // Track if game over sound has played

    srand(time(0));
    resetGrid();

    RenderWindow window(VideoMode(N*ts, M*ts), "Continuous Mode!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");

    Font font;
    if (!font.loadFromFile("/home/muhammad-faseeh-zafar/Desktop/project/fonts/alfasab.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    // Shared Timer HUD
    Text timeText;
    timeText.setFont(font); timeText.setCharacterSize(25); timeText.setFillColor(Color::Red); timeText.setPosition(300, 20);

    // Player 1 HUD
    Text moveText1;
    moveText1.setFont(font); moveText1.setCharacterSize(20); moveText1.setFillColor(Color::White); moveText1.setPosition(10, 40);
    Text scoreText1;
    scoreText1.setFont(font); scoreText1.setCharacterSize(20); scoreText1.setFillColor(Color::White); scoreText1.setPosition(10, 70);
    Text powerUpText1;
    powerUpText1.setFont(font); powerUpText1.setCharacterSize(20); powerUpText1.setFillColor(Color::White); powerUpText1.setPosition(10, 100);
    Text bonusText1;
    bonusText1.setFont(font); bonusText1.setCharacterSize(20); bonusText1.setFillColor(Color::White); bonusText1.setPosition(10, 130);

    // Player 2 HUD
    Text moveText2;
    moveText2.setFont(font); moveText2.setCharacterSize(20); moveText2.setFillColor(Color::White); moveText2.setPosition(N*ts - 200, 40);
    Text scoreText2;
    scoreText2.setFont(font); scoreText2.setCharacterSize(20); scoreText2.setFillColor(Color::White); scoreText2.setPosition(N*ts - 200, 70);
    Text powerUpText2;
    powerUpText2.setFont(font); powerUpText2.setCharacterSize(20); powerUpText2.setFillColor(Color::White); powerUpText2.setPosition(N*ts - 200, 100);
    Text bonusText2;
    bonusText2.setFont(font); bonusText2.setCharacterSize(20); bonusText2.setFillColor(Color::White); bonusText2.setPosition(N*ts - 200, 130);

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    // Initialize enemies
    for (int i = 0; i < enemyCount; i++) {
        enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f; // Speeds between 0.8 and 1.6
        a[i].x = (N/2 + i * 2) * ts; // Spread enemies
        a[i].y = (M/2) * ts;
        a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
        a[i].centerX = a[i].x;
        a[i].centerY = a[i].y;
        a[i].angle = 0;
        a[i].isCircular = false;
        movementType[i] = 0; // All start linear
    }

    bool Game = true;
    int x1 = 0, y1 = 0, dx1 = 0, dy1 = 0;
    int x2 = N - 1, y2 = M - 1, dx2 = 0, dy2 = 0;
    float timer = 0, delay = 0.07f;
    Clock clock;
    Clock gameClock;
    Clock pauseClock;
    float totalPausedTime = 0.0f;
    bool isPaused = false;
    float Totalseconds = 0.0f;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    int q_r[M*N];
    int q_c[M*N];
    bool visited[M][N];

    static float lastIncreaseTime = 0.0f;

    while (window.isOpen()) {
        float time_elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time_elapsed;

        if (!isPaused && Game) {
            Totalseconds = gameClock.getElapsedTime().asSeconds() - totalPausedTime;
            timeText.setString("Time: " + to_string((int)Totalseconds) + " s");
            moveText1.setString("P1 Moves: " + to_string(move_count1));
            scoreText1.setString("P1 Score: " + to_string(score1));
            powerUpText1.setString("P1 PowerUps: " + to_string(power_ups1));
            bonusText1.setString("P1 Bonus x" + to_string(bonus_multiplier1) + " (" + to_string(bonus_counter1) + ")");
            moveText2.setString("P2 Moves: " + to_string(move_count2));
            scoreText2.setString("P2 Score: " + to_string(score2));
            powerUpText2.setString("P2 PowerUps: " + to_string(power_ups2));
            bonusText2.setString("P2 Bonus x" + to_string(bonus_multiplier2) + " (" + to_string(bonus_counter2) + ")");
        }

        // Add 2 enemies and increase speed every 20 seconds
        if (!isPaused && Game && Totalseconds >= lastIncreaseTime + 20) {
            if (enemyCount < 50) {
                enemyCount += 2;
                // Initialize new enemies
                for (int i = enemyCount - 2; i < enemyCount; i++) {
                    enemySpeeds[i] = 0.8f + (rand() % 5) * 0.2f;
                    a[i].x = (N/2 + i * 2) * ts;
                    a[i].y = (M/2) * ts;
                    a[i].dx = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
                    a[i].dy = (rand() % 2 == 0 ? 1 : -1) * enemySpeeds[i];
                    a[i].centerX = a[i].x;
                    a[i].centerY = a[i].y;
                    a[i].angle = 0;
                    a[i].isCircular = false;
                    // Assign movement type if past 30 seconds
                    if (movementAssigned) {
                        int mod = i % 4;
                        movementType[i] = (mod == 0 || mod == 1) ? 0 : (mod == 2 ? 1 : 2);
                    } else {
                        movementType[i] = 0;
                    }
                }
                // Increase speeds for all enemies
                for (int i = 0; i < enemyCount; i++) {
                    enemySpeeds[i] += 0.5f;
                }
                lastIncreaseTime += 20;
            }
        }

        // Assign movement types after 30 seconds
        if (!isPaused && Game && Totalseconds >= 30 && !movementAssigned) {
            for (int i = 0; i < enemyCount; i++) {
                if (i == 0 || i == 1) movementType[i] = 0; // Linear
                else if (i == 2) movementType[i] = 1; // Circular
                else if (i == 3) movementType[i] = 2; // Sinusoidal
                else {
                    int mod = i % 4;
                    movementType[i] = (mod == 0 || mod == 1) ? 0 : (mod == 2 ? 1 : 2);
                }
            }
            movementAssigned = true;
        }

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    isPaused = true;
                    pauseClock.restart();
                    int pauseChoice = showPauseMenu();
                    if (pauseChoice == 1) {
                        isPaused = false;
                        totalPausedTime += pauseClock.getElapsedTime().asSeconds();
                    } else if (pauseChoice == 2) {
                        return;
                    } else if (pauseChoice == 3) {
                        exit(0);
                    }
                }
                if (!isPaused && Game) {
                    // Player 1 power-up (Space) only uses power_ups1
                    if (e.key.code == Keyboard::Space && power_ups1 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p1_freeze_active = true;
                        freeze_clock.restart();
                        power_ups1--;
                        powerUpSound.play();
                    }
                    // Player 2 power-up (Enter) only uses power_ups2
                    if (e.key.code == Keyboard::Enter && power_ups2 > 0 && !p1_freeze_active && !p2_freeze_active) {
                        p2_freeze_active = true;
                        freeze_clock.restart();
                        power_ups2--;
                        powerUpSound.play();
                    }
                }
            }
        }
        
        if (isPaused || !Game) {
            // Skip game logic updates but continue drawing
        } else {
            if (player1_alive && !p2_freeze_active) { // Player 1 stops if Player 2's power-up is active
                if (Keyboard::isKeyPressed(Keyboard::Left)) { dx1 = -1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Right)) { dx1 = 1; dy1 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::Up)) { dx1 = 0; dy1 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::Down)) { dx1 = 0; dy1 = 1; }
            } else {
                dx1 = 0; dy1 = 0;
            }

            if (player2_alive && !p1_freeze_active) { // Player 2 stops if Player 1's power-up is active
                if (Keyboard::isKeyPressed(Keyboard::A)) { dx2 = -1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::D)) { dx2 = 1; dy2 = 0; }
                if (Keyboard::isKeyPressed(Keyboard::W)) { dx2 = 0; dy2 = -1; }
                if (Keyboard::isKeyPressed(Keyboard::S)) { dx2 = 0; dy2 = 1; }
            } else {
                dx2 = 0; dy2 = 0;
            }

            if (timer > delay) {
                if (player1_alive) {
                    int next_x1 = x1 + dx1;
                    int next_y1 = y1 + dy1;

                    if (next_x1 < 0) next_x1 = 0; else if (next_x1 >= N) next_x1 = N - 1;
                    if (next_y1 < 0) next_y1 = 0; else if (next_y1 >= M) next_y1 = M - 1;
                    
                    x1 = next_x1; y1 = next_y1;

                    if (is_building1) {
                        if (y1 < minRow1) minRow1 = y1; if (y1 > maxRow1) maxRow1 = y1;
                        if (x1 < minCol1) minCol1 = x1; if (x1 > maxCol1) maxCol1 = x1;
                    }

                    if (grid[y1][x1] == 2 || grid[y1][x1] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player1_alive = false; dx1=0; dy1=0;
                    } else if (grid[y1][x1] == 0) {
                        if (!is_building1) {
                            move_count1++; is_building1 = true; captured_this_move1 = 0;
                            minRow1 = y1; maxRow1 = y1; minCol1 = x1; maxCol1 = x1;
                        }
                        grid[y1][x1] = 2; captured_this_move1++;
                    }
                }

                if (player2_alive) {
                    int next_x2 = x2 + dx2;
                    int next_y2 = y2 + dy2;

                    if (next_x2 < 0) next_x2 = 0; else if (next_x2 >= N) next_x2 = N - 1;
                    if (next_y2 < 0) next_y2 = 0; else if (next_y2 >= M) next_y2 = M - 1;

                    x2 = next_x2; y2 = next_y2;

                    if (is_building2) {
                        if (y2 < minRow2) minRow2 = y2; if (y2 > maxRow2) maxRow2 = y2;
                        if (x2 < minCol2) minCol2 = x2; if (x2 > maxCol2) maxCol2 = x2;
                    }
                    if (grid[y2][x2] == 2 || grid[y2][x2] == 3 || (x1 == x2 && y1 == y2 && (is_building1 || is_building2))) {
                        player2_alive = false; dx2=0; dy2=0;
                    } else if (grid[y2][x2] == 0) {
                        if (!is_building2) {
                            move_count2++; is_building2 = true; captured_this_move2 = 0;
                            minRow2 = y2; maxRow2 = y2; minCol2 = x2; maxCol2 = x2;
                        }
                        grid[y2][x2] = 3; captured_this_move2++;
                    }
                }
                timer = 0;
            }

            if (p1_freeze_active || p2_freeze_active) {
                if (freeze_clock.getElapsedTime().asSeconds() >= freeze_duration) {
                    p1_freeze_active = false;
                    p2_freeze_active = false;
                }
            } else {
                for (int i = 0; i < enemyCount; i++) {
                    // Bounds checking to prevent segmentation faults
                    int gridX = int(a[i].x / ts);
                    int gridY = int(a[i].y / ts);
                    if (gridX < 0 || gridX >= N || gridY < 0 || gridY >= M) {
                        // Clamp x to [ts, (N-2)*ts]
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        // Clamp y to [ts, (M-2)*ts]
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                        a[i].dx = -a[i].dx;
                        a[i].dy = -a[i].dy;
                        continue;
                    }

                    if (movementType[i] == 0) {
                        // Linear motion
                        a[i].isCircular = false;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 1) {
                        // Circular motion
                        a[i].isCircular = true;
                        a[i].move(enemySpeeds[i]);
                    } else if (movementType[i] == 2) {
                        // Sinusoidal motion
                        a[i].isCircular = false;
                        a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        a[i].y = a[i].centerY + 50 * sin(a[i].angle);
                        a[i].angle += 0.05f * enemySpeeds[i];
                        gridX = int(a[i].x / ts);
                        gridY = int(a[i].y / ts);
                        if (gridX >= 0 && gridX < N && gridY >= 0 && gridY < M && grid[gridY][gridX] == 1) {
                            a[i].dx = -a[i].dx;
                            a[i].x += a[i].dx * enemySpeeds[i] * time_elapsed;
                        }
                        // Clamp x to [ts, (N-2)*ts]
                        if (a[i].x < ts) a[i].x = ts;
                        else if (a[i].x > (N-2)*ts) a[i].x = (N-2)*ts;
                        // Clamp y to [ts, (M-2)*ts]
                        if (a[i].y < ts) a[i].y = ts;
                        else if (a[i].y > (M-2)*ts) a[i].y = (M-2)*ts;
                    }
                }
            }

            if (player1_alive && grid[y1][x1] == 1 && is_building1 && captured_this_move1 > 0) {
                dx1 = dy1 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 2) { grid[r_path][c_path] = 1; }
                    }
                }
                for(int r_init=0; r_init<M; ++r_init) for(int c_init=0; c_init<N; ++c_init) visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++;
                        visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while(q_head < q_tail){
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for(int i_bfs=0; i_bfs<4; ++i_bfs){
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = 0;
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }
                if (captured_area_points > 0) {
                    captureSound.play();
                    int points_to_add = captured_area_points;
                    if (captured_area_points > bonus_threshold) {
                        bonus_counter1++;
                        bonusSound.play();
                        if (bonus_counter1 >= 5) bonus_multiplier1 = 4;
                        else if (bonus_counter1 >= 3) bonus_multiplier1 = 2;
                        points_to_add *= bonus_multiplier1;
                    }
                    score1 += points_to_add;
                    while (score1 >= next_power_up_score1) {
                        power_ups1++;
                        next_power_up_score1 = (next_power_up_score1 == 50) ? 70 : next_power_up_score1 + 30;
                    }
                }
                captured_this_move1 = 0; is_building1 = false;
                minRow1 = M-1; maxRow1 = 0; minCol1 = N-1; maxCol1 = 0;
            }

            if (player2_alive && grid[y2][x2] == 1 && is_building2 && captured_this_move2 > 0) {
                dx2 = dy2 = 0;
                for (int r_path = 0; r_path < M; ++r_path) {
                    for (int c_path = 0; c_path < N; ++c_path) {
                        if (grid[r_path][c_path] == 3) { grid[r_path][c_path] = 1; }
                    }
                }
                for(int r_init=0; r_init<M; ++r_init) for(int c_init=0; c_init<N; ++c_init) visited[r_init][c_init] = false;
                int q_head = 0, q_tail = 0;
                for (int enemy_idx = 0; enemy_idx < enemyCount; ++enemy_idx) {
                    int ex = static_cast<int>(a[enemy_idx].x) / ts;
                    int ey = static_cast<int>(a[enemy_idx].y) / ts;
                    if (ex >= 0 && ex < N && ey >= 0 && ey < M && grid[ey][ex] == 0 && !visited[ey][ex]) {
                        q_r[q_tail] = ey; q_c[q_tail] = ex; q_tail++;
                        visited[ey][ex] = true;
                    }
                }
                int dr_bfs[] = {-1, 1, 0, 0}; int dc_bfs[] = {0, 0, -1, 1};
                while(q_head < q_tail){
                    int r_curr = q_r[q_head]; int c_curr = q_c[q_head]; q_head++;
                    for(int i_bfs=0; i_bfs<4; ++i_bfs){
                        int nr = r_curr + dr_bfs[i_bfs]; int nc = c_curr + dc_bfs[i_bfs];
                        if (nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] == 0 && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q_r[q_tail] = nr; q_c[q_tail] = nc; q_tail++;
                        }
                    }
                }
                int captured_area_points = 0;
                for (int r_fill = 0; r_fill < M; ++r_fill) {
                    for (int c_fill = 0; c_fill < N; ++c_fill) {
                        if (grid[r_fill][c_fill] == 0 && !visited[r_fill][c_fill]) {
                            grid[r_fill][c_fill] = 1; captured_area_points++;
                        }
                    }
                }
                if (captured_area_points > 0) {
                    captureSound.play();
                    int points_to_add = captured_area_points;
                    if (captured_area_points > bonus_threshold) {
                        bonus_counter2++;
                        bonusSound.play();
                        if (bonus_counter2 >= 5) bonus_multiplier2 = 4;
                        else if (bonus_counter2 >= 3) bonus_multiplier2 = 2;
                        points_to_add *= bonus_multiplier2;
                    }
                    score2 += points_to_add;
                    while (score2 >= next_power_up_score2) {
                        power_ups2++;
                        next_power_up_score2 = (next_power_up_score2 == 50) ? 70 : next_power_up_score2 + 30;
                    }
                }
                captured_this_move2 = 0; is_building2 = false;
                minRow2 = M-1; maxRow2 = 0; minCol2 = N-1; maxCol2 = 0;
            }

            for (int i = 0; i < enemyCount; i++) {
                int ex_grid = static_cast<int>(a[i].x) / ts;
                int ey_grid = static_cast<int>(a[i].y) / ts;
                if (ex_grid >= 0 && ex_grid < N && ey_grid >= 0 && ey_grid < M) {
                    if (grid[ey_grid][ex_grid] == 2 && player1_alive) {
                        player1_alive = false;
                        is_building1 = false;
                    }
                    if (grid[ey_grid][ex_grid] == 3 && player2_alive) {
                        player2_alive = false;
                        is_building2 = false;
                    }
                }
            }

            if (!player1_alive && !player2_alive) {
                Game = false;
                if (!gameOverSoundPlayed) {
                    gameOverSound.play();
                    gameOverSoundPlayed = true;
                }
            }
        }

        // Set background color based on power-up status
        if (p1_freeze_active || p2_freeze_active) {
            window.clear(Color::White); // White when power-up is active
        } else {
            window.clear(Color::Black); // Default black
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) continue;
                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts)); // Wall
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(36, 0, ts, ts)); // Player 1 red trail
                if (grid[i][j] == 3) sTile.setTextureRect(IntRect(72, 0, ts, ts)); // Player 2 golden trail
                sTile.setPosition(j*ts, i*ts);
                window.draw(sTile);
            }
        }

        if (player1_alive) {
            sTile.setTextureRect(IntRect(36, 0, ts, ts)); // Player 1 red cursor
            sTile.setPosition(x1*ts, y1*ts);
            window.draw(sTile);
        }
        if (player2_alive) {
            sTile.setTextureRect(IntRect(72, 0, ts, ts)); // Player 2 golden cursor
            sTile.setPosition(x2*ts, y2*ts);
            window.draw(sTile);
        }

        if (Game) sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++) {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) {
            window.draw(sGameover);
            string winner_str;
            if (score1 > score2) winner_str = "Player 1 Wins!";
            else if (score2 > score1) winner_str = "Player 2 Wins!";
            else winner_str = "Tie!";
            
            Text winnerText;
            winnerText.setFont(font);
            winnerText.setString(winner_str);
            winnerText.setCharacterSize(30);
            winnerText.setFillColor(Color::Yellow);
            FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            winnerText.setPosition(N*ts/2.0f, M*ts/2.0f + 20);
            window.draw(winnerText);
        }
        
        if (isPaused) {
            Text pauseText("PAUSED", font, 50);
            FloatRect textRect = pauseText.getLocalBounds();
            pauseText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            pauseText.setPosition(N*ts/2.0f, M*ts/2.0f - 50);
            pauseText.setFillColor(Color::Red);
            window.draw(pauseText);
        }

        window.draw(timeText); window.draw(moveText1); window.draw(scoreText1); window.draw(powerUpText1); window.draw(bonusText1);
        window.draw(moveText2); window.draw(scoreText2); window.draw(powerUpText2); window.draw(bonusText2);
        window.display();
    }
}
int main (){
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
                RenderWindow window(VideoMode(800, 600), "Xonix Game");
                showScoreboard(window);
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
                RenderWindow window(VideoMode(800, 600), "Xonix Game");
                showScoreboard(window);
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

