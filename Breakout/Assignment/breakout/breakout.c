//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height, width and y axis of the paddle
#define height_paddle 10
#define width_paddle 80
#define y_paddle 480

// height and width of bricks
#define height_brick 10
#define width_brick 35 

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial velocities
    double x_velocity = 2.0 * drand48();
    double y_velocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        /*-----> Movement of Paddle <------*/
        
        // Check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
         if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // moving the paddle along x axis
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, y_paddle);
            }
        }
        
        /*-----> Movement of Ball <-----*/
        
         move(ball, x_velocity, y_velocity);
        
         // bounce off right edge of window
        if (getX(ball) + RADIUS >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        
        //bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
       
        // If ball hits the bottom edge of window
        if (getY(ball) + RADIUS >= getHeight(window))
        {
            lives = lives - 1;
            waitForClick();
            double newx_ball = (getWidth(window) - RADIUS) / 2;
            double newy_ball = (getHeight(window) - RADIUS) / 2;
            setLocation(ball, newx_ball, newy_ball);
            double newx_paddle = (getWidth(window) - width_paddle) / 2;
            setLocation(paddle, newx_paddle, y_paddle);   
        }
        
        GObject object = detectCollision(window, ball);
        
        /*-----> Collision of ball with paddle <----*/
        
        // check if ball is coming down
        if (y_velocity >= 0)
        {
            // check if the collision is with paddle
            if (object == paddle)
            {
                y_velocity = -y_velocity;
                
            }
        }
      
   
        /*----> Collision with the bricks <-----*/
        
        if (object != NULL)
        {
          if (strcmp(getType(object), "GRect") == 0 && object != paddle)
          {
               y_velocity = -y_velocity;
               removeGWindow(window, object);
               bricks = bricks - 1;
               points = points + 1;
               updateScoreboard(window, label, points);
          }
        }
        
        // linger before moving again
        pause(10);      
    }

    // wait for click before exiting
    waitForClick();

     // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    
    string brick_color[5] = {"BLUE", "GREEN", "RED", "YELLOW", "CYAN"};
    
    for (int i = 0, y = 20; i < ROWS; i++, y = y + 15)
    {
        for (int j = 0, x = 1; j < COLS; j++, x = x + 40)
        {
            GRect brick = newGRect(x, y, width_brick, height_brick);
            setColor(brick, brick_color[i]);
            setFilled(brick, true);
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = (getWidth(window) - RADIUS) / 2;
    double y = (getHeight(window) - RADIUS) / 2;
    GOval ball = newGOval(x, y , RADIUS, RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (getWidth(window) - width_paddle) / 2;
    GRect paddle = newGRect(x, y_paddle, width_paddle, height_paddle);
    setColor(paddle, "BLUE");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-36");
    setLocation(label, 200, 530); 
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
