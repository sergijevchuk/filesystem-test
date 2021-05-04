#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include "test.h"
uint8_t memory[2048];
struct t {
	char name[256];
	int type;
	int files[512];
	char *data;
	int uid;
	int gid;
	int permissions;
};
void mem_write(uint8_t address,uint8_t *data,size_t size) {
	int size_i = (int)size;
	printf("Data size is: %d\n",size_i);
	for (int i = 0; i < size_i; i++) {
		memory[address+i] = data[i];
	}
}
void mem_read(uint8_t address,uint8_t *buff,size_t s) {
	int size_i = (int)s;
	for (int i = 0; i < size_i; i++) {
		buff[i] = memory[address+i];
	}
}
void mem_print(uint8_t address,size_t a) {
	printf("Memory map is:\n");
	int s = (int)a;
	for (int i = 0; i < s; i++) {
		printf("%d ",memory[address+i]);
	}
	printf("\n");
}
void mem_write_to_file(FILE *f) {
	fwrite(memory,sizeof(uint8_t),sizeof(memory),f);
}
void mem_read_from_file(FILE *f) {
	fread(memory,sizeof(uint8_t),sizeof(memory),f);
}
int main(void) {
	FILE *f = fopen("t","r");
	mem_read_from_file(f);
	fclose(f);
	struct t w;
	mem_read(0,(uint8_t *)&w,sizeof(w));
    printf("%s\n",w.name);
}