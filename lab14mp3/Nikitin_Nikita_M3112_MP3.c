#include <stdio.h>
#include <string.h>

typedef struct{
    char id3[3];
    unsigned char ver[2];
    unsigned char flags;
    unsigned char metaLength[4];
}ID3v2Header;


typedef struct{
    unsigned char name[4];
    unsigned char size[4];
    unsigned char flags[2];
    unsigned char encode;
}ID3v2Frame;


int StrCmp(unsigned char * s1, char * s2, int n){
    for(int i = 0; i < n; i++){
        if (s1[i] != s2[i]){
            return 0;
        }
    }
    return 1;
}

int StrLen(char * s){
    int i = 0;
    while (s[i] != '\0'){
        i++;
    }
    return i;
}


int FromID3v2FormatToLength(unsigned char * length){
    int res = 0;
    for (int i = 0; i < 4; i++){
        res += length[i] << (7 * (3 - i));
    }
    return res;
}


void FromLengthToID3v2Format(int size, unsigned char * res){
    for (int i = 0; i < 4; i++) {
        res[i] = size >> (7 * (3 - i)) ;
        size -= res[i] << (7 * (3 - i));
    }
}


void ReadAllFrames(char * file) {

    ID3v2Header header;
    ID3v2Frame frame;
    FILE * f = fopen(file, "rb");
    fread(&header, sizeof(header), 1, f);
    int headerLn = FromID3v2FormatToLength(header.metaLength);

    if(header.flags & 0x40){
        fseek(f, 6, SEEK_CUR);
        headerLn -= 6;
    }

    while (headerLn > 0) {

        fread(&frame, sizeof(frame), 1, f);
        int ln = FromID3v2FormatToLength(frame.size) - 1;
        headerLn -= (11 + ln);

        if (StrCmp(frame.name, "APIC", 4)){
            fseek(f, ln, SEEK_CUR);
        }

        else if (frame.name[0] >= 65 && frame.name[0] <= 91) {
            printf("%s:\t", frame.name);
            while (ln > 0) {
                char sym = fgetc(f);
                if (sym >= 32 && sym <= 126) {
                    printf("%c", sym);
                }
                ln--;
            }
            printf("\n");
        }
    }
}


void ReadOneFrame(char * file, char * searchingName){

    ID3v2Header header;
    ID3v2Frame frame;
    FILE * f = fopen(file, "rb");
    fread(&header, sizeof(header), 1, f);
    int headerLn = FromID3v2FormatToLength(header.metaLength);

    if(header.flags & 0x40){
        unsigned char length[4];
        fread(length, sizeof(length), 1, f);
        int size = FromID3v2FormatToLength(length);
        unsigned char tmp[size-4];
        fread(tmp, sizeof(tmp), 1, f);
        headerLn -= 6;
    }

    while (headerLn > 0) {

        fread(&frame, sizeof(frame), 1, f);
        int ln = FromID3v2FormatToLength(frame.size) - 1;
        headerLn -= (11 + ln);

        if (StrCmp(frame.name, searchingName, 4)) {
            printf("%s:\t", frame.name);
            while (ln > 0) {
                char sym = fgetc(f);
                if (sym >= 32 && sym <= 126) {
                    printf("%c", sym);
                }
                ln--;
            }
            printf("\n");
        }
        else{
            fseek(f, ln, SEEK_CUR);
        }
    }
}


void CopyFile(FILE * file, FILE * tmpFile, long offset, long end){
    fseek(file, offset, SEEK_SET);
    for (long i = 0; i < end - offset; i++){
        unsigned char buffer;
        fread(&buffer, 1, 1, file);
        fwrite(&buffer, 1, 1, tmpFile);
    }
}


long LenFile(FILE * file){
    long fdiosng = ftell(file);
    fseek(file, 0, SEEK_END);
    long res = ftell(file);
    fseek(file, fdiosng, SEEK_SET);
    return res;
}


void SetFrame(char * file, char * changingName, char * changingValue){

    ID3v2Header header;
    ID3v2Frame frame;
    FILE * f = fopen(file, "rb");
    fread(&header, sizeof(header), 1, f);
    int headerLn = FromID3v2FormatToLength(header.metaLength);

    FILE * tmpFile = fopen("tmp.mp3", "wb");
    unsigned char headerLnChanged[4];
    FromLengthToID3v2Format(headerLn - StrLen(changingValue), headerLnChanged);
    unsigned char frameLn[4];
    FromLengthToID3v2Format(StrLen(changingValue) + 1, frameLn);
    for (int i = 0; i < 4; i++){
        header.metaLength[i] = headerLnChanged[i];
    }
    fwrite(&header, sizeof(header), 1, tmpFile);

    if(header.flags & 0x40){
        unsigned char length[4];
        fread(length, sizeof(length), 1, f);
        fwrite(length, sizeof(length), 1, tmpFile);
        int size = FromID3v2FormatToLength(length);
        unsigned char tmp[size-4];
        fread(tmp, sizeof(tmp), 1, f);
        fwrite(tmp, sizeof(tmp), 1, tmpFile);
        headerLn -= 6;
    }

    while (headerLn > 0) {

        fread(&frame, sizeof(frame), 1, f);
        int ln = FromID3v2FormatToLength(frame.size) - 1;
        headerLn -= (10 + ln);

        if (StrCmp(frame.name, changingName, 4)) {
            fseek(f, ln, SEEK_CUR);
            fwrite(&frame.name, 4, 1, tmpFile);
            fwrite(frameLn, 4, 1, tmpFile);
            fwrite(&frame.flags, 2, 1, tmpFile);
            fwrite(&frame.encode, 1, 1, tmpFile);
            fwrite(changingValue, StrLen(changingValue), 1, tmpFile);
            break;
        }
        else{
            fwrite(&frame.name, 4, 1, tmpFile);
            fwrite(&frame.size, 4, 1, tmpFile);
            fwrite(&frame.flags, 2, 1, tmpFile);
            fwrite(&frame.encode, 1, 1, tmpFile);
            unsigned char data[ln];
            fread(data, ln, 1, f);
            fwrite(data, ln, 1, tmpFile);
        }
    }

    CopyFile(f, tmpFile, ftell(f), LenFile(f));

    fclose(tmpFile);
    fclose(f);

    remove(file);
    rename("tmp.mp3", file);

}


int main(int argc, char * argv[]) {

    char * filename = NULL;
    char * searchingTag = NULL;
    char * changingTag = NULL;
    char * changingValue = NULL;


    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--show") == 0){
            ReadAllFrames(filename);
        }
        else if (strncmp(argv[i], "--get", 5) == 0){
            searchingTag = argv[i] + 6;
            ReadOneFrame(filename, searchingTag);
        }
        else if (strncmp(argv[i], "--set", 5) == 0){
            changingTag = argv[i] + 6;
        }
        else if (strncmp(argv[i], "--value", 7) == 0){
            changingValue = argv[i] + 8;
            SetFrame(filename, changingTag, changingValue);
        }
        else if (strncmp(argv[i], "--filepath", 10) == 0){
            filename = argv[i] + 11;
        }
    }

    return 0;
}
