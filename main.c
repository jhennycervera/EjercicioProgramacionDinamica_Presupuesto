/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jhenn
 *
 * Created on 10 de diciembre de 2020, 08:30 PM
 */

#include <stdio.h>
#define MAX 30

int codPaneton;
int precioPaneton=9999;

//ordenando de menor a mayor
int ordenarProd(int arr[][2],int n){
    int temp, valor;
    for (int i=0; i < n; i++) 
       for(int j=i+1;j<n;j++)
           if (arr[i][0]>arr[j][0])
           {
               temp=arr[i][0];
               valor= arr[i][1];
               arr[i][0]=arr[j][0];
               arr[i][1]= arr[j][1];
               arr[j][0]=temp;
               arr[j][1]=valor;
           } 
    
}

void imprimir_matriz(int arr[][2], int n){
    
    for(int i=0; i<n; i++){
        printf("Producto %d: %4d    Precio:%2d \n",i+1, arr[i][0], arr[i][1]);
    }   
}

int escogerProductos(int matriz[][2], int matrizAux[][2], int n){
    int aux; /*tiene el primer digito del producto*/
    int a=0; /*contador para la matriz auxiliar */
    for(int i=0; i<n; i++){
        aux= matriz[i][0]/100000;   /*saco el primer digito para diferenciar el tipo de producto*/
        if (aux==7){
            if(matriz[i][1] <precioPaneton ){
                codPaneton= matriz[i][0];
                precioPaneton=  matriz[i][1];
            }  
            continue;
        }
        if (a==0){  /*coloco el primer producto en la matrizAux*/
            matrizAux[a][0]=matriz[i][0];
            matrizAux[a][1]=matriz[i][1];
            a++;
        }
        else{
            if(aux != (matrizAux[a-1][0]/100000)){  /*si no esta agrego a la matriz aux*/
                matrizAux[a][0]=matriz[i][0];
                matrizAux[a][1]=matriz[i][1];
                a++;
            }
            else{  /*comparo sus precios  y coloco el menor*/
                if(matriz[i][1] < matrizAux[a-1][1]){
                    matrizAux[a-1][0]=matriz[i][0];
                    matrizAux[a-1][1]=matriz[i][1];
                }
            }  
        }
    }
    return a;
}

void buscasuma(int arr[][2], int n,int sum){ 
    int i,j,temp, valor;
    printf("\n");
    /*Ordenando por valor de menor a mayor*/
    for (i=0; i < n; i++) 
        for(j=i+1;j<n;j++)
            if (arr[i][1]>arr[j][1]){
               temp=arr[i][0];
               valor= arr[i][1];
               arr[i][0]=arr[j][0];
               arr[i][1]= arr[j][1];
               arr[j][0]=temp;
               arr[j][1]=valor;
            } 
    int dp[n+1][sum+1]; 
    /*Llenado de valores iniciales*/
    for (i = 0; i <= n; i++)   /*llenando de 1 la columna 0*/
        dp[i][0] = 1; 
  
    for (i = 1; i <= sum; i++)  /*llenando de 0s la fila 0*/
        dp[0][i] = 0; 
  
    /*completo la matriz de 0s o 1s*/
    for (int i=1; i<=n; i++) { 
        for (int j=1; j<=sum; j++) { 
            dp[i][j] = dp[i-1][j]; 
            if (arr[i-1][1] <= j) 
                if(dp[i][j]==0)
		    dp[i][j] = dp[i-1][j-arr[i-1][1]]; 
            printf("%d ",dp[i][j]);
        } 
	printf("\n");
    } 
   
    /*Buscando en la ultima columna si el presupuesto es exacto*/   
    for (int j=0; j<=n;j++){ 
        if (dp[j][sum] == 1){ 
            printf("Se necesita S/.%d para la canasta\n", sum+precioPaneton);
            return ; 
        } 
    } 
    /* buscando en la ultima columna con 1s para el vuelto*/
    for(int i=sum; i>=0; i--){
        for(int j=1; j<=n; j++){
            if(dp[j][i]){
                printf("Se necesita S/.%d para la canasta", i);
                //printf("El vuelto es S/.%d \n", sum - i);
                return ;
            }
        }
    }
} 


int main(int argc, char** argv) {
    int tamMatrizAux, n,presupuesto ;
    n=10, presupuesto=5;
    int matriz[MAX][2]= { {500021, 2},
                        {500024, 3},
                        {500120, 4},
                        {300492, 4},
                        {300120, 3},
                        {700399, 10},
                        {700120, 8},
                        {800211, 3},
                        {800184, 5},
                        {900212, 5}
                        };
    
    int matrizAux[MAX][2]={};
    //int matriz[MAX][2]={};
    int producto, precio;
/*
    printf("Ingresar el numero de productos\n");
    scanf("%d", &n);
    printf("Ingresar los productos con sus precios respectivos\n");
    
    for(int i=0; i<n; i++){
        scanf("%d %d", &producto, &precio);
        matriz[i][0]=producto;
        matriz[i][1]=precio;
    }
    printf("Ingresar presupuesto\n");
    scanf("%d", &presupuesto);
*/
    ordenarProd(matriz,n);
    printf("\n");
    imprimir_matriz(matriz, n);
    printf("\n");
    tamMatrizAux=escogerProductos( matriz, matrizAux,n);
    printf("Se escogen %d productos\n",tamMatrizAux );
    imprimir_matriz(matrizAux, tamMatrizAux);
    printf("\n");
    buscasuma(matrizAux, tamMatrizAux,presupuesto); 
    
    printf("Los productos son:\n");
    printf("%d -%d\n",codPaneton, precioPaneton);
    
    
    
    return (0);
}

