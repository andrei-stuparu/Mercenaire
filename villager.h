
// structure for an villager

typedef struct Villager Villager;
struct Villager{
  int id;
  int CoordX;
  int CoordY;
  int carried; // if he carried by a mercenary, id of the mercenary ( -1 else)
};

// getter and setter 

int get_Id_V(Villager* villager){
  return (*villager).id;
}

void change_ID_V(Villager* villager, int value){
  (*villager).id = value;
}

// change position
void change_position_V(Villager* villager,int x, int y){
  (*villager).CoordX = x;
  (*villager).CoordY = y;
}

int get_CoordX_V(Villager* villager){
  return (*villager).CoordX;
}

int get_CoordY_V(Villager* villager){
  return (*villager).CoordY;
}

int get_carried(Villager* villager){
  return (*villager).carried;
}

void set_carried(Villager* villager, int value){
    (*villager).carried = value;
}
