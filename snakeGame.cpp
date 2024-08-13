#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void init()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  timeout(100);
}

#define WIDTH 40
#define HEIGHT 20

struct position
{
   int x, y;
};

class Snake
{
   vector<position> body;
   int length;

public:
   Snake()
   {
      length = 3;
      for(int i = 0; i < length; ++i)
      {
         body.push_back({WIDTH / 4 - i, HEIGHT / 2});
      }
   }

   void move(position newHead)
   { 
      body.insert(body.begin(), newHead);
      body.pop_back();
   }

   void grow(position newHead)
   {
      body.insert(body.begin(), newHead);
      ++length;
   }

   bool collides(position pos)
   {
      for(const auto& part : body)
      {
         if(part.x == pos.x && part.y == pos.y)
         {
            return true;
         }
      }
      return false;
   }
};

struct Food
{
   position pos;

   void placeFood(const Snake& snake)
   {
      do {
         pos.x = rand() % WIDTH;
         pos.y = rand() % HEIGHT;
      } while(snake.collides(pos));
   }
};

position get_newHead(position head, int direction)
{
  position newHead = head;
  switch (direction)
  {
      case KEY_UP:
           --newHead.y;
           break;
      case KEY_DOWN:
           ++newHead.y;
           break;
      case KEY_LEFT:
           --newHead.x;
           break;
      case KEY_RIGHT:
           ++newHead.x;
           break;
  }
  return newHead;
}

bool check_collision(const Snake& snake)
{
  position head = snake.body.front();
  if(head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT)
  {
      return true;
  }
  for(size_t i = 1; i < snake.body.size(); ++i)
  {
      if(head.x == snake.body[i].x && head.y == snake.body[i].y)
      {
         return true;
      }
  }
  return false;
}

void render(const Snake& snake, const Food& food)
{
  clear();
  for(const auto& part : snake.body)
  {
    mvprintw(part.y, part.x, "O");
  }
  mvprintw(food.pos.y, food.pos.x, "X");
  refresh();
}

int main()
{
  srand(time(0));
  init();
   
  Snake snake;
  Food food;
  food.placeFood(snake);

  int direction = KEY_RIGHT;
  while(true)
  {
    int next_key = getch();
    if(next_key != ERR)
    {
      direction = next_key;
    }
    position newHead = get_newHead(snake.body.front(), direction);
    if(newHead.x == food.pos.x && newHead.y == food.pos.y)
    {
      snake.grow(newHead);
      food.placeFood(snake);
    }
    else
    {
      snake.move(newHead);
    }
    if(check_collision(snake))
    {
      break;
    }
    render(snake, food);
  }
  endwin();
  return 0;
}
