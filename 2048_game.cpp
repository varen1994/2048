            //        ////////    //          ////////
          //  //     //    //    //   //     //    //
            //      //    //     /////      ////////
          //       //    //        //      //    //
         ///////  ////////        //      ////////
          
          
/************************************
/*           HEADER FILES          */
/**********************************/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*******************************/
/*       PROTOTYPES           */
/******************************/
int start_game();
int menu();
void send_option_futher(int );
void new_game();
void make_all_elements_zero();
void make_boxes();
int fill_number_at_empty_place();
void fill_value_in_box();
void get_key_stroke();
int resolve_after_key_down(int );
int shift_elements_to_left(int );
int shift_elements_to_top(int );
void reverse_array(int *);
int combination_of_all_shifting(int [4]);
int color_belong_to_value(int );
int enter_number_in_arr(int );
void game_over();
void contine_last_game();
void write_values_score_in_file1();
int handle_continue_game();
void top_3_scores();
void new_game_part2();
void enter_score_in_file();
void sort_score_when_new_added(int [4]);
int count_number_of_zero();

/*****************************/
/*  GLOBAL VAIRIABLES        */
/****************************/
int arr[4][4] = {0,0,0,0,
                 0,0,0,0,
                 0,0,0,0,
                 0,0,0,0};
int score = 0;


/*<<<<<<<<<<< MAIN >>>>>>>>>>>*/
int main()
{
  start_game();
  handle_continue_game();
  getch();
  closegraph();
  return 0;    
}

/*<<<<<<<<< TO HANDLE CONTINUE >>>>>>>>>>*/
int handle_continue_game()
{
  int option;
  option = menu();
  send_option_futher(option);
  return 0;
}

/*<<<<<<<<  START GAME >>>>>>>*/
int start_game()
{
  int x= 151;  
  initwindow(800,400,"2048");   
  settextstyle(10,0,9);
  setcolor(RED);
  setfillstyle(3,BLUE);
  floodfill(100,100,WHITE);
  outtextxy(250,100,"2048");
  setcolor(WHITE);
  rectangle(150,220,650,230);
  setcolor(RED);
  settextstyle(10,0,2);
  outtextxy(320,250,"LOADING...");
  setcolor(GREEN);
  while(x<=649)
  {
    line(x,221,x,229);
    x +=1;
    delay(2);             
  }
  clearviewport();
}


/*<<<<<<<< MENU >>>>>>>>*/
int menu()
{
    int new_position = 1;
    int old_position;
    int ch;
    /************ LAYOUT OF MENU *******/
    setfillstyle(3,BLUE);
    floodfill(100,100,WHITE);
    setcolor(YELLOW);
    settextstyle(10,0,6); 
    outtextxy(300,100,"GAME MENU");
    setcolor(13);
    settextstyle(10,0,3);
    outtextxy(370,160,"NEW GAME");
    outtextxy(370,200,"CONTINUE");
    outtextxy(370,240," SCORES ");
    outtextxy(370,280,"  QUIT  ");
    setcolor(GREEN);
    rectangle(370,120+(40*new_position),480,140+(40*new_position)); 
    /********** SLIDING BAR **********/
    while(1)
    {         
       ch = getch();       
       old_position = new_position;        
       if(ch==0 || ch==224)
       {
           switch(getch())
           {
              case 80:              
              new_position = new_position+1;            
              break;           
                          
              case 77:              
              new_position = new_position+1;            
              break;  
              
              case 72:              
              new_position = new_position-1;            
              break;          
                          
                          
              case 75:              
              new_position = new_position-1;            
              break;                  
           }     
                
            if(new_position>4)
            {
              new_position = 1;                
            }             
            if(new_position<1)
            {
               new_position = 4;                
            }
       }
       if(ch==13)
       {
         return new_position;        
       }
       setcolor(BLACK);
       rectangle(370,120+(40*old_position),480,140+(40*old_position));
       setcolor(GREEN);
       rectangle(370,120+(40*new_position),480,140+(40*new_position));        
    } 
    clearviewport();    
}


/*<<<<<<<<< send option further it will call functions **********/
void send_option_futher(int option)
{
   int i,j;
   switch(option)
   {
      case 1:
      make_all_elements_zero();      
      new_game();
      break;
      
      case 2:
        contine_last_game();
        break;
      
      case 3:
        top_3_scores();
        break;   
      
      case 4:
        exit(0);         
        break;
   }         
}

/*<<<< If play from the start all arr element should be zero >>>>>*/
void make_all_elements_zero()
{
  int i,j;
  for(i=0;i<4;i++)
  {  
    for(j=0;j<4;j++)
    {
      arr[i][j] = 0;                
    }  
  } 
  score = 0;
} 

/*<<<<<<<< new _ game >>>>>>>>>>>>*/
void new_game()
{    
   int count = 1;  
   count = fill_number_at_empty_place();
   new_game_part2();   
}

/*<<<<<<<<< NEW GAME PART 2 >>>>>>>  
/*this is for handling new number when we return back*/
/*     to continue option                           */ 
void new_game_part2()
{
  int count = 1;
   int key;
   while(1)
   {
     make_boxes();        
     fill_value_in_box();
     get_key_stroke();
     fill_number_at_empty_place();  
   }  
}


/*<<<<<<< MAKE BOXES AND NECESSARY DESIGN >>>>>>>>>>*/
void make_boxes()
{
  char buff[20];   
  clearviewport();
  sprintf(buff,"%d",score);
  setcolor(GREEN);
  settextstyle(1,0,3);
  outtextxy(40,40,"score: ");
  setcolor(RED);
  outtextxy(160,42,buff);
  setcolor(WHITE);   
  line(0,70,getmaxx(),70);
  rectangle(198,98,602,262);
  rectangle(200,100,600,260);
  /***** VERTICAL LINES *********/  
  line(300,100,300,260);  
  line(400,100,400,260);
  line(500,100,500,260); 
  /***** HORIZONTAL LINES *****/
  line(200,140,600,140);  
  line(200,180,600,180);
  line(200,220,600,220); 
}

/*<<<<<<< CHECK FOR EMPTY SPACE TO FILL 2 >>>>>>>*/
int fill_number_at_empty_place()
{
  int count = 0;
  int x,y;
  int temp;
  int check_empty[16][2];
  
  for(x=0;x<=3;x++)
  {
    for(y=0;y<=3;y++)
    {
      if(arr[x][y]==0)
      {
          check_empty[count][1] = x;
          check_empty[count][2] = y;
          count = count+1;            
      }               
    }                 
  }  
  
  if(count-1==0)
  {
    x = check_empty[count-1][1];
    y = check_empty[count-1][2];
  }
  else
  {
      temp = rand()%(count-1);
      x = check_empty[temp][1];
      y = check_empty[temp][2]; 
  } 
  
   if(rand()%2==0)
   {  
     arr[x][y] = 2; 
   }
   else
   {
     arr[x][y] = 4;    
   }
return count-2; 
}

/*<<<<< FILL VALUE IN BOX >>>>>>>*/
void fill_value_in_box()
{
int x,y;
int pos_x,pos_y;
char buff[4];
int color = 1;
   for(x=0;x<4;x++)
   {
     for(y=0;y<4;y++)
     {   
         settextstyle(10,0,2);        
         if(arr[x][y]!=0)
         { 
            color = color_belong_to_value(arr[x][y]);
            setcolor(WHITE);             
            sprintf(buff,"%d",arr[x][y]);                    
            outtextxy(205+(y*100),110+(x*40),buff); 
            setfillstyle(1,color);
            floodfill(205+(y*100),105+(x*40),WHITE);
         }
     }                              
   }    
}

/*<<<<<<<<< FOR COLOR FULL VALUE >>>>>>>>>*/
int color_belong_to_value(int temp)
{
    int i = 1;
    int color;
    for(i=1;i<12;i++)
    {
      if(pow(2,i)==temp)
      {
        color = i;             
        return color;               
      }                 
    }
}

/*<<<<<< GET KEY STOKE LEFT RIGHT TO BOTTOM >>>>>>>*/
void get_key_stroke()
{ 
 if_no_change_get_key_again:   
 int ch;
 int count = 0;
 int change_occured = 0;
   ch = getch();
     if(ch==0 || ch==224)
     {      
       switch(getch())
       {
         case 72:
         change_occured = shift_elements_to_top(0);               
         break;
              
         case 80:
         change_occured = shift_elements_to_top(1);                    
         break;
              
         case 75:
         change_occured = shift_elements_to_left(0);                   
         break;
              
         case 77:
         change_occured = shift_elements_to_left(1);                    
         break;                 
       }
       count = count_number_of_zero();
      if(change_occured==0 && count==0)
       {
          game_over();                                      
       }
       else if(change_occured==0 && count!=0)
       { 
         goto if_no_change_get_key_again;
       }
     } 
    /********** for escape ********/     
     if(ch==27)
     {
       write_values_score_in_file1();        
       clearviewport();         
       handle_continue_game();  
     }
}

/*<<<<<<<<<<<< COUNT NUMBER OF ZEROS >>>>>>>>>*/
int count_number_of_zero()
{
 int i,j;
 int count = 0;
   for(i=0;i<4;i++)
   {
     for(j=0;j<4;j++)
     {
           if(arr[i][j]==0)
           {
             count = count+1;                
           }          
     }                              
   }   
 return count;   
}

/*<<<<<<<<<< SHIFT ELEMENTS TO RIGHT>>>>>>>>*/
int shift_elements_to_left(int temp)
{
int array[4];
int x,y;
int changes = 0;
  for(y=0;y<4;y++)
  {
    for(x=0;x<4;x++)
    {
       array[x] = arr[y][x];
    }
    if(temp==1)
    {
      reverse_array(array);           
    }
     changes = changes + combination_of_all_shifting(array); 
    if(temp==1)
    {
      reverse_array(array);           
    }
    for(x=0;x<4;x++)
    {
       arr[y][x] = array[x];             
    }                              
  }
return changes;  
}

/*<<<<<<<<<< SHIFT ELEMENTS TO TOP>>>>>>>>*/
int shift_elements_to_top(int temp)
{
int array[4];
int x,y;
int changes = 0;

  for(y=0;y<4;y++)
  {
    for(x=0;x<4;x++)
    {
       array[x] = arr[x][y];
    }
    if(temp==1) 
    {
      reverse_array(array); 
    }
      changes = changes+combination_of_all_shifting(array);
    if(temp==1) 
    {
      reverse_array(array); 
    }
    for(x=0;x<4;x++)
    {
      arr[x][y] = array[x];             
    }                             
  } 
return changes;  
}

/*<<<<<<<< reverse for right and bottom >>>>>>>>>*/
void reverse_array(int *array)
{
  int temp[4],i;
    for(i=0;i<4;i++)
    {
       temp[3-i] = *(array+i);          /******* inserting in temp in reverse *****/     
    }
    for(i=0;i<4;i++)
    {
       *(array+i) = temp[i];              
    }    
}

/*<<<<<<<<< COMMON FUNCTION FOR ALL SHIFTINGS >>>>>>>>*/
int combination_of_all_shifting(int array[4])  
{
  int temp_array[4] = {0,0,0,0};
  int temp2_array[4] ={0,0,0,0};
  int top = 0;
  int i,j;
  int changes = 0;
  
   /*************** copying array  to temp2 for changes ******/
  for(i=0;i<4;i++)
  {
    temp2_array[i] = array[i]; 
  }
  
  /******* counting non zero numbers and put them in temp_arr ******/
  for(i=0;i<4;i++)
  {
    if(array[i]!=0)
    {
      temp_array[top] = array[i];
      top = top+1;                        
    }           
  }
  /****** adding similar side by side ********/
  for(i=0;i<top;i++)
  {
    if(temp_array[i]==temp_array[i+1])
    {
      temp_array[i]= 2*temp_array[i];
      score = score+temp_array[i]; 
      for(j=i+1;j<top;j++)
      {
        temp_array[j] = temp_array[j+1];              
      }                          
      top = top-1;
    }               
  }
      
 /******** putting zeros and digits from temp_arr to temp >>>>>>>*/ 
 for(i=0;i<4;i++)
 {
    if(i<top)
    {
      array[i] = temp_array[i];            
    }    
    else
    {
      array[i] = 0;    
    }   
  }
  
  /************ by comapring temp2 and array find changes occured ******/
  for(i=0;i<4;i++)
  {
    if(array[i]!=temp2_array[i])
    {              
      changes = changes+1;  
    }
  }
return changes;
}

/*<<<<<<<<<<< VOID END GAME  >>>>>>>>>>>>>>*/
void game_over()
{
    int x,y;
    delay(3000);
    clearviewport();
    setfillstyle(3,GREEN);
    floodfill(100,100,WHITE);
    setcolor(RED);
    settextstyle(1,0,5);
    outtextxy(200,180,"GAME OVER");    
    delay(3000);
    enter_score_in_file();
    make_all_elements_zero();
    handle_continue_game();        
}

/*<<<< store value if escape is pressed >>>>*/
void write_values_score_in_file1()
{
  FILE *fp;
  int i;
  fp = fopen("store_details.txt","w");
  for(i=0;i<4;i++)
  {
    fprintf(fp,"%d\t",arr[i][0]);              
    fprintf(fp,"%d\t",arr[i][1]);
    fprintf(fp,"%d\t",arr[i][2]);
    fprintf(fp,"%d\t",arr[i][3]); 
    printf("\n");             
  }
  fprintf(fp,"%d",score);
  fclose(fp);
}

/*<<<<<<<<<<< CONTINUE LAST GAME >>>>>>>>>>>>>>*/
void contine_last_game()
{
  FILE *fp;
  int i;
  fp = fopen("store_details.txt","r");
  for(i=0;i<4;i++)
  {
    fscanf(fp,"%d\t",&arr[i][0]);              
    fscanf(fp,"%d\t",&arr[i][1]);
    fscanf(fp,"%d\t",&arr[i][2]);
    fscanf(fp,"%d\t",&arr[i][3]); 
    printf("\n");             
  }
  fscanf(fp,"%d",&score);
  fclose(fp);    
  new_game_part2();
}

/*<<<<<<<<<< TOP THREE SCORES >>>>>>>>>*/
void top_3_scores()
{
  int score_[4];
  char ch,buff[4];
  FILE *fp;
  FILE *fo;
  int i,number_of_times =0;
  /********* if game not been played once ********/
  fo = fopen("number_of_times_played.txt","r");
  fscanf(fo,"%d\t",&number_of_times);
  fclose(fo);
  
  if(number_of_times>1000 || number_of_times<=0)
  {
    fp = fopen("scores.txt","w");
    for(i=0;i<4;i++)
    {
      fprintf(fp,"%d\t",0);
    }  
    number_of_times = 0;
    fclose(fp);
  }  
  number_of_times +=1;
  fo = fopen("number_of_times_played.txt","w");
  fprintf(fo,"%d\t",number_of_times);
  fclose(fo); 
  
  /********* reading scores from score.txt *******/
  fp = fopen("scores.txt","r");
  for(i=0;i<4;i++)
  {
        fscanf(fp,"%d\t",&score_[i]);
  }  
  fclose(fp);
  
  /******** showing score in game ********/
  clearviewport();
  setcolor(RED);
  outtextxy(300,30,"TOP SCORES");
  setcolor(GREEN);
  for(i=0;i<3;i++)
  {
       sprintf(buff,"%d",score_[i]);
       outtextxy(300,70+(i*30),buff);                 
  }
  while(ch!=27)
  {
    ch = getch(); 
  }   
  handle_continue_game();   
}


/*<<<<<<<<<< enter score in the file >>>>>>>*/
void enter_score_in_file()
{
  int score_[4];   
  FILE *fp;
  int i;
  fp = fopen("scores.txt","r");
  for(i=0;i<3;i++)
  {
    fscanf(fp,"%d\t",&score_[i]);
  }  
  fclose(fp);
  score_[3] = score;
  sort_score_when_new_added(score_);
  FILE *fs;
  fs = fopen("scores.txt","w");
  for(i=0;i<3;i++)
  {
    fprintf(fs,"%d\t",score_[i]);
  }
  fclose(fs);
}

/*<<<<<<< SORT SCORE WHEN ADDED NEW SCORE ********/
void sort_score_when_new_added(int score_[4])
{
  int i,j;   
  for(j=3;j>0;j--)
  {                              
    for(i=0;i<j;i++)
    {
      if(score_[i+1]>score_[i])
      {
           int temp = score_[i+1];
           score_[i+1] = score_[i];
           score_[i] = temp;                                           
      }                              
    }                            
  }                           
}
