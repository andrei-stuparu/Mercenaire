
// structure map : an array of characters

typedef struct Map Map;
struct Map{
  char mappy[5][5]; // maybe need a dynamic allocation
};

// filled the map at the beginning of the game
// init_map(&map,data);
// remains to implement the Oedipus and Sphinx position
void init_map(Map* map, char data[]){
  int i = 0;
  int j = 0;
  int k = 0;
  while (data[i] != '\0' || j < 5){
    while (k < 5){
      (*map).mappy[j][k] = data[i];
      i++;
      k++;
    }
    k = 0;
    j++;
  }
}

void print_map(Map* map){
  int i = 0;
  int j = 0;
  while ( i < 5){
    while (j < 5){
      printf("%c ",(*map).mappy[i][j]);
      j++;
    }
    printf("\n");
    j = 0;
    i++;
  }
}

// getter and setter

char get_Case(Map* map,int x,int y){
  return (*map).mappy[x][y];
}

void set_Case(Map* map,int x,int y, char object){
   (*map).mappy[x][y] = object;
}
