#include <stdio.h> //画面出力のため
#include <stdlib.h> //乱数生成のため
#include <time.h> //関数にかかる時間測定のため

#include "my_sort.h"

int *generate_array(int length, int seed){
    //入力：配列の長さ(int)
    //処理：指定された長さのランダムな配列を作成し、先頭ポインタを返す
    //出力：配列の先頭ポインタ(int *)

    //配列の領域を確保
    int *head = (int *)malloc(length * sizeof(int));

    //配列をランダムに生成
    srand(seed); //シードを固定して乱数生成
    for(int i=0; i<length; i++){
        head[i] = rand();
    }
    
    //先頭ポインタを返す
    return head;
}

int check_if_success_sort(int *array, int length){
    //入力：配列、配列の長さ
    //処理：配列が昇順か降順であることを確認する
    //出力：整列済みであると確認できたら1を返し、整列できていなければ0を返す

    printf("check_if_success_sort(): ");
    
    int i;
    //昇順チェック
    for(i=1; i<length; i++){
        if(array[i-1] > array[i]) break; //降順が混ざっていればbreak
    }
    if(i == length){
        printf("昇順に整列されていることを確認\n");
        return 1;//整列済みを確認
    }
    //降順チェック
    for(i=1; i<length; i++){
        if(array[i-1] < array[i]){
            printf("整列されていません\n");
            return 0; //昇順が混ざっていればreturn 0
        }
    }
    if(i == length){
        printf("降順に整列されていることを確認\n");
        return 1;//整列済みを確認
    }
}

void get_time_sort(void (*pf)(int *, int), int *array, int length){
    //入力：対象のsort関数名とその関数の引数
    //処理：sort関数にかかる時間を測定する
    //出力：なし

    printf("get_time_sort(): ");

    int start_time, end_time;

    start_time = clock();
    pf(array, length);
    end_time = clock();

    printf("並び替えにかかった時間は %f [s]\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
}

void swap(int *a, int *b){
    //入力：int*変数a, b
    //処理：変数を入れ替える
    //出力：なし
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_array(int *array, int length){
    //入力：配列、配列の長さ
    //処理：配列を逆順に並べ変える
    //出力：なし
    for(int i=0; i<length/2; i++){
        swap(array+i, array+length-1-i); //両端から順にswapしていく
    }
}

void display_array(int *array, int length){
    for(int i=0; i<length; i++){
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void bubble_sort(int *array, int length){
    //入力：配列、配列の長さ
    //処理：渡された配列をバブルソートで昇順に整列する
    //出力：なし

    for(int i=0; i<length-1; i++){
        for(int j=0; j<(length-i-1); j++){
            if(array[j] > array[j+1]) swap(array+j, array+j+1);
        }
    }
}

void quick_sort(int *array, int length){
    //入力：配列、配列の長さ
    //処理：渡された配列をクイックソートで昇順に整列する
    //出力：なし

    //長さが１以下ならば整列の必要性がないため関数を抜ける
    if(length <= 1){
        return;
    }

    //pivot(基準値)として配列番号が一番小さいものの値を採用する
    int pivot = array[0];
    int i,j=1;
    for(i=1; i<length; i++){
        if(array[i] < pivot){
            swap(array+i, array+j);
            j++;
        }
    }

    //pivotを移動させる
    swap(array+j-1, array+0);

    //再帰呼び出し
    quick_sort(array, j-1);
    quick_sort(array+j, length-j);
}

void merge_sort(int *array, int length){
    //入力：配列、配列の長さ
    //処理：渡された配列をマージソートで昇順に整列する
    //出力：なし

    //長さが１以下ならば整列の必要性がないため関数を抜ける
    if(length <= 1){
        return;
    }

    //再帰呼び出し
    int *left_array = array, left_length = length/2;
    int *right_array = array+left_length, right_length = length-left_length;
    merge_sort(left_array, left_length);
    merge_sort(right_array, right_length);

    //一時的な配列tmpに左配列と右配列をmergeする
    int i=0,j=0;
    int *tmp = (int *)malloc(sizeof(int)*length);
    while(i<left_length && j<right_length){
        if(left_array[i] < right_array[j]){
            tmp[i+j] = left_array[i];
            i++;
        }else{
            tmp[i+j] = right_array[j];
            j++;
        }
    }
    if(i<left_length){
        for(int k=i+j; k<length; k++,i++){
            tmp[k] = left_array[i];
        }
    }else{
        for(int k=i+j; k<length; k++,j++){
            tmp[k] = right_array[j];
        }
    }

    //一時的に用意した配列をもとの配列に反映させる
    for(int k=0; k<length; k++){
        array[k] = tmp[k];
    }

    //一時的な配列の開放
    free(tmp);
}