
// structure for mercenary

typedef struct Mercenary Mercenary;
struct Mercenary{
  int Id;
  int CoordX;
  int CoordY;
  char status[20]; // can be "free" or "dead" or "ask" "jail"
  int villager; // boolean if carry a villager, id of the villager (-1 else)
  int score;
};


//  getter and setter

int get_Id_M(Mercenary* mercenary){
  return (*mercenary).Id;
}

void change_ID_M(Mercenary* mercenary, int value){
  (*mercenary).Id = value;
}

// change position
void change_position_M(Mercenary* mercenary,int x, int y){
  (*mercenary).CoordX = x;
  (*mercenary).CoordY = y;
}

int get_CoordX_M(Mercenary* mercenary){
  return (*mercenary).CoordX;
}

int get_CoordY_M(Mercenary* mercenary){
  return (*mercenary).CoordY;
}

char* get_Status_M(Mercenary* mercenary){
  return (*mercenary).status;
}

void set_Status_M(Mercenary* mercenary, char new_status[]){
    strcpy((*mercenary).status , new_status);
}

int get_Villager_M(Mercenary* mercenary){
  return (*mercenary).villager;
}

void set_Villager_M(Mercenary* mercenary, int value){
  (*mercenary).villager = value;
}

int get_Score_M(Mercenary* mercenary){
  return (*mercenary).score;
}

void up_Score_M(Mercenary* mercenary){
  (*mercenary).score =  (*mercenary).score + 1;
}
