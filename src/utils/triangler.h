#pragma once
#include "../header.h"
#define FOV M_PI/4
#define ASR 320/200
float pixels[3][2];
float vec[3][4];
float mvm_result[4] = {0,0,0,0};
float mvm_result_bckp[4] = {0,0,0,0};

const float viewMatrix[4][4] ={
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 1, 0, 1, 1 }
};
float projMatrix[4][4] = {
    { 2, 0, 0, 0 },
    { 0, 2, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};
void draw_line(int x0, int y0, int x1, int y1){
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while(1){
        int err2 = 2 * err;
        vga_plot_pixel(x0, y0, 4);
        if(x0 == x1 && y0 == y1)
            break;
        if (err2 > -dy){
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx){
            err += dx;
            y0 += sy;
        }
    }
}
void mvmp(int index){
    for(int i =0; i < 4;i++){
        float sum = 0;
        for(int j =0; j < 4;j++){
            sum += projMatrix[i][j] * vec[index][j];
            //printlnNumber("",projMatrix[i][j] * vec[index][j] * 1000);
        }mvm_result_bckp[i] = sum;
        
    }
}
void mvmv(){
    for(int i =0; i < 4;i++){
        float sum = 0;
        for(int j =0; j < 4;j++){
            sum += viewMatrix[i][j] * mvm_result_bckp[j];
        }mvm_result[i] = sum;   
    }   
}
void draw_triangle(){
    float *v[2] = {{0,0},{0,0},{0,0}};
    for(int i =0; i < 3;i++){
        mvmp(i);
        mvmv();
        //for(int i =0; i < 4;i++){
        //    printlnNumber("\t\t", mvm_result[i] * 1000);
        if(mvm_result[3] != 0){
            v[i][0] = abs(((mvm_result[0] / mvm_result[3] +1) * 400))/5;
            v[i][1] = abs(((-mvm_result[1] / mvm_result[3] +1) * 300))/5;
            
            printlnNumber("|--", v[i][0]);
            printlnNumber(" --", v[i-1][0]);
            printlnNumber(" --", v[i][1]);
            printlnNumber(" --", v[i-1][1]);
            pixels[i][0] = v[i][0];
            pixels[i][1] = v[i][1];
            //vga_plot_pixel(v[i][0],v[i][1],4);
        }else{
            v[i][0] = abs(((mvm_result[0]) * 400))/2;
            v[i][1] = abs(((-mvm_result[1]) * 300))/2;
        }
        //printlnNumber("Thingy:", v[i][0]);
        //printlnNumber("Thingy:", v[i][1]);
        //if(i == 2){
        //    draw_line(v[0][0],v[0][1],v[1][0],v[1][1]);
        //    draw_line(v[1][0],v[1][1],v[2][0],v[2][1]);
        //    draw_line(v[2][0],v[2][1],v[0][0],v[0][1]);
        //}
    }
    draw_line(pixels[0][0],pixels[0][1],pixels[1][0],pixels[1][1]);
    draw_line(pixels[1][0],pixels[1][1],pixels[2][0],pixels[2][1]);
    draw_line(pixels[2][0],pixels[2][1],pixels[0][0],pixels[0][1]);
}
void traingler_init(){
    projMatrix[0][0] = 1/(ASR * ft_tan(FOV/2));
    projMatrix[1][1] = 1/(ft_tan(FOV/2));
}
void run(){
    float a[3][4] = {
        {0.001f, 0.101f, 0.45f,0.001f},
        {0.45f, -0.501f, 0.001f,0.001f},
        {0.001f, 0.17f, 0.001f,0.201f}
    };
    for(int i =0; i < 3;i++)
        for(int j = 0; j < 4;j++)
            vec[i][j] = a[i][j];
    console_setup();
    vga_init();
    traingler_init();
    printlnNumber("Vecs:",a[0][0]* 1000);
    printlnNumber("NVec:",vec[0][0] * 1000);
    draw_triangle();
    while (1);
}