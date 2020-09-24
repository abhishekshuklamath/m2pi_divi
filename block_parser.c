//
// Created by aks on 2020-09-08.
//

#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

typedef struct Block{
    uint32_t magic_number;
    uint32_t block_size;
    uint32_t version;
    uint8_t pr_blk_hash[32];
    uint8_t merkle_root[32];
    uint32_t time;
    uint32_t difficulty;
    uint32_t nonce;
    uint8_t pre_txcount;
   // std::vector<Transaction*> transactions;
    }Block;




void printblock(struct Block blk){
    int i;
    int rawtime=blk.time;
    int year= rawtime/(86400*365)+1970;
    int month= (rawtime%(86400*365))/(86400*30);
    int day= (rawtime%(86400*30))/86400;
    int hour=  (rawtime%86400)/3600;
    int minute= (rawtime%3600)/60;
    int seconds= rawtime%60;
    printf("\nMagic no:");
    //for(i=0;i<4;i++)
        printf("%02x", blk.magic_number);
    printf("\nSize:");
   // for(i=0;i<4;i++)
        printf("%02d bytes", blk.block_size);
    printf("\nVersion:");
    //for(i=0;i<4;i++)
        printf("%02x", blk.version);
    printf("\nPrevious block hash:");
    for(i=0;i<32;i++)
     printf("%02x", blk.pr_blk_hash[31-i]);
    printf("\nMerkle root:");
    for(i=0;i<32;i++)
        printf("%02x", blk.merkle_root[i]);
    printf("\nTimestamp:");
    // for(i=0;i<4;i++)
    printf("%02d:%02d:%02d %02d/%02d/%02d",hour, minute,seconds,year,month,day);
    printf("\nDifficulty:");
    // for(i=0;i<4;i++)
    printf("%02x", blk.difficulty);
    printf("\nNonce:");
    // for(i=0;i<4;i++)
    printf("%02x", blk.nonce);
   // printf("\nPreTransaction Count:");
    // for(i=0;i<4;i++)
    //printf("%02x", blk.pre_txcount);


}

int main(){
    Block block;
    int i=0;
    int j=0;
    uint16_t a;
    uint32_t b;
    uint64_t c;

    const char filename[]="blk02010.dat";
    FILE *f;
    f=fopen(filename,"rb");
    if (f == NULL)
        printf("File could not be opened, exiting program.\n");
    else printf("File opened %s\n",filename);


    while (fread(&block, sizeof(Block), 1, f)==1){
       // fread(&block, sizeof(Block), 1, f);
        printblock(block);
        printf("\nTransaction count:");
        switch(block.pre_txcount){
            case 0xfd:
                fseek(f, j+89, SEEK_SET);
                fread(&a, sizeof(a),1,f);
                printf("%02d",a);
                break;
            case 0xfe:
                fseek(f, j+89, SEEK_SET);
                fread(&b, 32,1,f);
                printf("%02x",b);
                break;
            case 0xff:
                fseek(f, j+89, SEEK_SET);
                fread(&a, 64,1,f);
                printf("%02lld",c);
                break;
            default:
                printf("%02x", block.pre_txcount);
        }

        printf("\n-----------\n");

        j += block.block_size + 8;
        fseek(f, j, SEEK_SET);
        i += 1;
    }


    fclose(f);
    printf("%d blocks in the file\n",i);
}