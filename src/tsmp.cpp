/** 
Usar enumeración de la ciudades para acceder a las distancias directas
Ejemplo: graph[lince][los_olivos] === dist(lince -> los olivos) = 17.5
**/

#define N 10

enum city {lima_centro, lince, miraflores,
            barranco, rimac, los_olivos, la_molina,
            la_victoria, madgalena, san_borja};

double graph[N][N] = {
    {0, 5.3, 9.6, 11.4, 4.4, 16.6, 17.4, 4.3, 7.4, 9.8},
    {5.9, 0, 4.3, 7.7, 7.7, 17.5, 13.6, 2.8, 5.2, 5.8},
    {10.4, 5.4, 0, 2.9, 12.2, 23.7, 15.8, 8.3, 7.1, 7.2},
    {13.2, 9.0, 3.1, 0, 15.0, 24.8, 17.7, 9.4, 9.8, 9.9},
    {3.7, 7.8, 11.6, 14.6, 0, 12.5, 19.8, 7.6, 9.9, 13.1},
    {13.8, 17.1, 22.1, 23.9, 13.1, 0, 30.2, 18.0, 17.1, 27.9},
    {18.5, 14.0, 15.9, 17.7, 19.0, 28.7, 0, 12.2, 17.3, 9.3},
    {6.9, 3.5, 7.1, 9.2, 8.1, 17.9, 12.8, 0, 7.7, 4.7},
    {8.5, 5.1, 7.5, 9.1, 10.2, 16.7, 17.1, 7.2, 0, 9.5},
    {10.7, 6.2, 6.6, 9.9, 12.2, 27.0, 9.3, 4.6, 9.6, 0}
};