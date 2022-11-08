#include <cstdio>
#include <cinttypes>
#include <unordered_set>

using namespace std;

int8_t pandigits[410000][10];
//[start, end) indexes
int pandigitsEndIndexes[10]; 
int *pandigitsStartIndexes = pandigitsEndIndexes-1;

void fillpandigits();
int numfromdigits(int8_t *digitArr, int n)
{
    int num = digitArr[0];
    for(int i = 1; i < n; i++){
        num = num*10 + digitArr[i];
    }
    return num;
}

int main()
{ 
    fillpandigits();


    unordered_set<int> pandigsProds;
    int pandigsProdSum = 0;

    int pini = pandigitsStartIndexes[9];
    int pfin = pandigitsEndIndexes[9];
    int f1, f2, prod;
    pair<unordered_set<int>::iterator, bool> insRetVal;
    for(int i = pini; i < pfin; i++){
        //(*) x (****) = (****)
        f1 = pandigits[i][0];
        f2 = numfromdigits(pandigits[i]+1, 4);
        prod = numfromdigits(pandigits[i] + 5, 4);
        if(f1*f2 == prod){
            printf("%d x %d = %d\n", f1, f2, prod);
            insRetVal = pandigsProds.insert(prod);
            if(insRetVal.second){
                pandigsProdSum+=prod;
            }else{
                printf("\t---> Repetido :_(\n");
            }
        } 

        //(**) x (***) = (****)
        f1 = numfromdigits(pandigits[i], 2);;
        f2 = numfromdigits(pandigits[i]+2, 3);
        //prod = numfromdigits(pandigits[i] + 5, 4);
        if(f1*f2 == prod){
            printf("%d x %d = %d\n", f1, f2, prod);
            insRetVal = pandigsProds.insert(prod);
            if(insRetVal.second){
                pandigsProdSum+=prod;
            }else{
                printf("\t---> Repetido :_(\n");
            }
        } 
    }

    printf("%d\n", pandigsProdSum);
}

void fillpandigits() {
	
    int pcount = 0;
	pandigits[0][0] = 1;
	int pandigIni = 0;
	int pandigFin = 1;
    pandigitsEndIndexes[1] = 1;
	pcount = 1;

	for (int8_t n = 2; n < 10; n++) {
		for (int i = pandigIni; i < pandigFin; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < j; k++) {
					pandigits[pcount][k] = pandigits[i][k];
				}
				pandigits[pcount][j] = n;
				for (int k = j+1; k < n; k++) {
					pandigits[pcount][k] = pandigits[i][k-1];
				}
				pcount++;
			}
		}

		pandigIni = pandigFin;
		pandigFin = pcount;
        pandigitsEndIndexes[n] = pcount;
	}
}


