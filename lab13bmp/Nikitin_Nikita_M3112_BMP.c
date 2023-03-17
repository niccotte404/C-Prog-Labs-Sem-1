#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct{unsigned char type[2];
    unsigned char fileSize[4];
    unsigned char reservedWord1[2];
    unsigned char reservedWord2[2];
    unsigned char offset[4];
}Header;


typedef struct{
    unsigned char structSize[4];
    unsigned char width[4];
    unsigned char height[4];
    unsigned char planes[2];
    unsigned char bitForPix[2];
    unsigned char compression[4];
    unsigned char imgSize[4];
    unsigned char pixPerMeterWidth[4];
    unsigned char pixPerMeterHeight[4];
    unsigned char amnOfUsedColours[4];
    unsigned char amnOfImportantColours[4];
}ImgInfo;


int FromByteToInt(unsigned char * size){
    int res = 0;
    for (int i = 0; i < 4; i++){
        res += size[i];
    }
    return res;
}


void FromIntToByte(int size, unsigned char * res){
    for (int i = 0; i < 4; i++){
        res[i] = size;
        size -= res[i];
    }
}


int GameRules(int aliveAmn, int elem){
    if (aliveAmn >= 2 && aliveAmn <= 3 && elem == 0){
        return 0;
    }
    else if (aliveAmn == 3 && elem == 765){
        return 0;
    }
    else{
        return 765;
    }
}


int ReadBmp(char * filename, char * filepath, int gen){

    Header header;
    ImgInfo imgInfo;
    FILE * f = fopen(filename, "rb");
    fread(&header, sizeof(header), 1, f);
    fread(&imgInfo, sizeof(imgInfo), 1, f);
    int width = FromByteToInt(imgInfo.width);
    int height = FromByteToInt(imgInfo.height);
    int offset = FromByteToInt(header.offset);

    int p = 0;
    while ((width * 3 + p) % 4 != 0){
        p++;
    }

    // Reading the file
    int imgMatrix[height + 2][width + 2];
    for (int h = 0; h < height + 2; h++){
        for (int w = 0; w < width + 2; w++){
            if (h == 0 || h == height + 1 || w == 0 || w == width + 1){
                imgMatrix[h][w] = -10;
            }
            else{
                int elem = 0;
                unsigned char tmp[3];
                fread(tmp, 3, 1, f);
                for (int i = 0; i < 3; i++) {
                    elem += tmp[i];
                }
                imgMatrix[h][w] = elem;
            }
            imgMatrix[0][w] = -10;
            imgMatrix[height + 1][w] = -10;
        }
        if (h != 0 && h != height + 1){
            fseek(f, p, SEEK_CUR);
        }
        imgMatrix[h][0] = -10;
        imgMatrix[h][width + 1] = -10;
    }


    // Writing to the file
    char name[PATH_MAX + 1];
    snprintf(name, PATH_MAX, "\\gen_%d.bmp", gen);
    char fname[strlen(filepath) + strlen(name)];
    strcpy(fname, filepath);
    strcat(fname, name);
    FILE * fw = fopen(fname, "wb");

    fwrite(&header, sizeof(header), 1, fw);
    fwrite(&imgInfo, sizeof(imgInfo), 1, fw);

    int x, wt = 0, same = 0;
    for (int i = 1; i < height + 1; i++){
        for (int j = 1; j < width + 1; j++){

            int aliveAmn = 0;
            for (int a = i - 1; a < i + 2; a++){
                for (int b = j - 1; b < j + 2; b++){
                    if (i == a && j == b){
                        continue;
                    }
                    if (imgMatrix[a][b] == 0){
                        aliveAmn++;
                    }
                }
            }

            x = GameRules(aliveAmn, imgMatrix[i][j]);

            unsigned char elem[3];
            if (x == 765) {
                for (int k = 0; k < 3; k++) {
                    elem[k] = 255;
                }
            }
            else if (x == 0) {
                for (int k = 0; k < 3; k++) {
                    elem[k] = 0;
                }
                wt++;
            }

            if (x == imgMatrix[i][j]){
                same++;
            }

            fwrite(elem, 3, 1, fw);
        }

        unsigned char extendedBytes[p];
        for (int bt = 0; bt < p; bt++){
            extendedBytes[bt] = 0;
        }
        fwrite(extendedBytes, p, 1, fw);
    }

    fclose(f);
    fclose(fw);

    printf("created generation %d\n", gen);

    if (same == width * height || wt == width * height){
        return 1;
    }
    else{
        return 0;
    }

}



int main(int argc, char * argv[]) {

    char * filename = NULL;
    char * filepath = NULL;
    int dumpFreq;
    char * dumpFreqArg = NULL;
    int maxIter;
    char * maxIterArg = NULL;

    for (int i = 0; i < argc - 1; i++){
        if (strcmp(argv[i], "--input") == 0){
            filename = argv[i + 1];
        }
        else if (strcmp(argv[i], "--output") == 0){
            filepath = argv[i + 1];
        }
        else if (strcmp(argv[i], "--max_iter") == 0){
            maxIterArg = argv[i + 1];
        }
        else if (strcmp(argv[i], "--dump_freq") == 0){
            dumpFreqArg = argv[i + 1];
        }
    }

    if (maxIterArg != NULL){
        maxIter = atoi(maxIterArg);
    }
    else{
        maxIter = -1;
    }

    if (dumpFreqArg != NULL){
        dumpFreq = atoi(dumpFreqArg);
    }
    else{
        dumpFreq = 1;
    }

    ReadBmp(filename, "C:\\CProj\\bmp\\cmake-build-debug", 1);

    int g = 1;
    while(1) {
        if (g == maxIter){
            break;
        }
        char name[PATH_MAX + 1];
        snprintf(name, PATH_MAX, "gen_%d.bmp", g);
        int toExit = ReadBmp(name, filepath, g + 1);

        if(toExit){
            break;
        }

        if (g % dumpFreq != 0){
            remove(name);
        }

        g++;
    }

}
