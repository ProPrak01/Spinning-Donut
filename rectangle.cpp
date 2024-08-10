#include "bits/stdc++.h"
#include <chrono>
#include <thread>

using namespace std;

//test check: for rectangle
void print_rectangle(char rect_arr[][5]){
system("clear");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<rect_arr[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void put_light_rectangle(char rect_arr[][5], int pos_x, int pos_y ){
 //flow of light from high to low : #$%!:'.,
 for(int i=-4; i<5;i++){
     for(int j=-4; j<5;j++){
         if((i <= 4 && i >= -4) && (j <= 4 && j >= -4)){
             if(pos_x+i >= 0 && pos_x+i < 5 && pos_y+j >= 0 && pos_y+j < 5){
                    rect_arr[pos_x+i][pos_y+j] = '.';
             }
         }
         if((i <= 3 && i >= -3) && (j <= 3 && j >= -3)){
             if(pos_x+i >= 0 && pos_x+i < 5 && pos_y+j >= 0 && pos_y+j < 5){
                    rect_arr[pos_x+i][pos_y+j] = ':';
             }
         }
          if((i <= 2 && i >= -2) && (j <= 2 && j >= -2)){
              if(pos_x+i >= 0 && pos_x+i < 5 && pos_y+j >= 0 && pos_y+j < 5){
                     rect_arr[pos_x+i][pos_y+j] = '!';
              }
          }
         if((i <= 1 && i >= -1) && (j <= 1 && j >= -1)){
             if(pos_x+i >= 0 && pos_x+i < 5 && pos_y+j >= 0 && pos_y+j < 5){
                    rect_arr[pos_x+i][pos_y+j] = '$';
             }
         }
            if(i == 0 && j == 0){
                if(pos_x+i >= 0 && pos_x+i < 5 && pos_y+j >= 0 && pos_y+j < 5){
                        rect_arr[pos_x+i][pos_y+j] = '#';
                }
     }
 }}

}
void travel_light(char rect_arr[][5]){

    int x = 2, y = 2;
     int dx = 1, dy = 1;

     while (true) {
         put_light_rectangle(rect_arr, x, y);
         print_rectangle(rect_arr);
         this_thread::sleep_for(chrono::milliseconds(200));

         x += dx;
         y += dy;


         if (x == 0 || x == 4) dx = -dx;
         if (y == 0 || y == 4) dy = -dy;
     }

}
void rectangle_animation(){

    char rect_arr[5][5] = {{'#','#','#','#','#'},{'#','#','#','#','#'},{'#','#','#','#','#'},{'#','#','#','#','#'},{'#','#','#','#','#'}};
    travel_light(rect_arr);
   // put_light_rectangle(rect_arr,2,2);
   // print_rectangle(rect_arr);

}




int main(){

    rectangle_animation();





}
