#include <stdio.h>
#include <math.h>
//int fortify_soldiers(int y, int x, int m, int l,const int countries[][6]);

int main() {
//    int y, x, m, l, countries[7][6] = {{0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0},
//                                           {0, 0, 0, 0, 0, 0}};
//    scanf("%d %d %d %d", &y, &x, &m, &l);
////    for (int i = 0; i < 7; ++i) {
////        for (int j = 0; j < 6; ++j) {
////            scanf("%d", &countries[i][j]);
////        }
////    }
//    if (fortify_soldiers(y, x, m, l, countries) == 1) {
//        printf("Piruzi\n");
//    } else if (fortify_soldiers(y, x, m, l, countries) == 0){
//        printf("Shekast\n");
//
//    }
    float p;
    float n = 1.5 ;
     p = floor(n);
    printf("floor of n is  : %f \n" , p);
    return 0;
}
//
//int fortify_soldiers(int y, int x, int m, int l,const int countries[][6]) {
//    int i, j, Hist[200][2];
//    int k = 0;
//    int fortify_countries[9][8];
//    for (i = 0; i < 9; i++) {
//        for (j = 0; j < 8; j++) {
//            fortify_countries[i][j] = 10; //The Sea
//        }
//    }
//    for (i = 0; i < 7; i++) {
//        for (j = 0; j < 6; j++) {
//            fortify_countries[i + 1][j + 1] = countries[i][j];
//        }
//    }
//    //start finding a way !
//    while (y != m || x != l) {
//        //UP
//        if (countries[y - 1][x] == countries[y][x]) {
//            fortify_countries[y][x] = 4;//investigated(flag)
//            Hist[k][0] = y;
//            Hist[k][1] = x;
//            k++;//shmarande history
//            y--;
//            continue;
//        }
//        //DOWN
//        if (countries[y + 1][x] == countries[y][x]) {
//            fortify_countries[y][x] = 4;//investigated(flag)
//            Hist[k][0] = y;
//            Hist[k][1] = x;
//            k++;//shomarande history
//            y++;
//            continue;
//        }
//        //RIGHT
//        if (countries[y][x + 1] == countries[y][x]) {
//            fortify_countries[y][x] = 4;//investigated(flag)
//            Hist[k][0] = y;
//            Hist[k][1] = x;
//            k++;//shomarande history
//            x++;
//            continue;
//        }
//        //LEFT
//        if (countries[y][x - 1] == countries[y][x]) {
//            fortify_countries[y][x] = 4;//investigated(flag)
//            Hist[k][0] = y;
//            Hist[k][1] = x;
//            k++;//shomarande history
//            x--;
//            continue;
//        }
//        //go back to perevious block
//        k--;
//        if (k < 0) {
//            //The Shekast
//            return 0;
//        }
//        //New The Sea (flag)
//        fortify_countries[y][x] = 10;
//        y = Hist[k][0];
//        x = Hist[k][1];
//    }
//    //The Pirouzi
//    return 1;
//}

