/** 
Usar enumeración de la ciudades para acceder a las distancias directas
Ejemplo: graph[lince][los_olivos] === dist(lince -> los olivos) = 17.5
**/
#include <float.h>
#include <iostream>
#include <iomanip>
#include <vector>

#define N 10
#define inf DBL_MAX

enum city {lima_centro, lince, miraflores,
            barranco, rimac, los_olivos, la_molina,
            la_victoria, madgalena, san_borja};

double route_graph[N][N] = {
    {inf, 5.3, 9.6, 11.4, 4.4, 16.6, 17.4, 4.3, 7.4, 9.8},
    {5.9, inf, 4.3, 7.7, 7.7, 17.5, 13.6, 2.8, 5.2, 5.8},
    {10.4, 5.4, inf, 2.9, 12.2, 23.7, 15.8, 8.3, 7.1, 7.2},
    {13.2, 9.0, 3.1, inf, 15.0, 24.8, 17.7, 9.4, 9.8, 9.9},
    {3.7, 7.8, 11.6, 14.6, inf, 12.5, 19.8, 7.6, 9.9, 13.1},
    {13.8, 17.1, 22.1, 23.9, 13.1, inf, 30.2, 18.0, 17.1, 27.9},
    {18.5, 14.0, 15.9, 17.7, 19.0, 28.7, inf, 12.2, 17.3, 9.3},
    {6.9, 3.5, 7.1, 9.2, 8.1, 17.9, 12.8, inf, 7.7, 4.7},
    {8.5, 5.1, 7.5, 9.1, 10.2, 16.7, 17.1, 7.2, inf, 9.5},
    {10.7, 6.2, 6.6, 9.9, 12.2, 27.0, 9.3, 4.6, 9.6, inf}
};

struct pile_elem{
    double reduced_value;
    double graph[N][N];
    int unvisited[N];
    int full_route[N];
    int city = 0;

    pile_elem(){
        reduced_value = 0;
    }

    pile_elem(double g[N][N]){
        reduced_value = 0;
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) graph[i][j] = g[i][j];
    }

    pile_elem(double g[N][N], int vi[N], int start){
        reduced_value = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) graph[i][j] = g[i][j];
            unvisited[i] = vi[i];
        }
        city = start;
    }

    pile_elem(pile_elem &parent, int route){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == parent.city || j == route || (i == route && j == city)) graph[i][j] = inf;
                else graph[i][j] = parent.graph[i][j];
            }
            if(i == route) unvisited[i] = -1;
            else unvisited[i] = parent.unvisited[i];
        }
        reduced_value = parent.reduced_value;
        city = route;
    }

    pile_elem(double rv){
        reduced_value = rv;
    }

    bool is_empty(){
        bool ans = true;
        for(int i = 0; i < N; i++) ans &= (unvisited[i] == -1);
        return ans;
    }
};
