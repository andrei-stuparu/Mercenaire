


//Structure for Oedipe and Sphinx

typedef struct Entity Entity;
struct Entity{
  char name[20];
  int CoordX;
  int CoordY;
};

// getter and setter

char* get_Name_E(Entity* entity){
  return (*entity).name;
}

void change_Name_E(Entity* entity, char new_name[]){
    strcpy((*entity).name , new_name);
}

void change_position_E(Entity* entity,int x, int y){
  (*entity).CoordX = x;
  (*entity).CoordY = y;
}

int get_CoordX_E(Entity* entity){
  return (*entity).CoordX;
}

int get_CoordY_E(Entity* entity){
  return (*entity).CoordY;
}
