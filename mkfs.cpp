#include "fs.h"
#include<stdio.h>
#include<stdint.h>
struct superblock super;
struct inode root;
void mkfs(FILE *f);
void load(FILE *f);
void shell();
int check(FILE *f);
void writeUintArray(uint8_t *buffer,size_t size,FILE *stream) {
	fwrite(buffer,sizeof(uint8_t),size,stream);
}
void readUintArray(uint8_t *buffer,size_t size,FILE *stream) {
	fread(buffer,sizeof(uint8_t),size,stream);
}
int main(int argc,char *argv[]) {
	FILE *f = fopen("test.fs" ,"w");
	if (f == NULL) {
		printf("...\n");
		return 1;
	}
	mkfs(f);
	shell();
}
void mkfs(FILE *f) {
	struct inode r = {"/",1};
	r.uid = 0;
	r.gid = 0;
	r.permissions = 0777;
	root = r;
	super.magic = MAGIC;
	super.size = 1024;
	super.inodes = 512;
	super.used_inodes = 1;
	writeUintArray((uint8_t *)&super,sizeof(super),f);
	writeUintArray((uint8_t *)&root,sizeof(root),f);
	fclose(f);
}
void load(FILE *f) {
	readUintArray((uint8_t *)&super,sizeof(super),f);
	if (super.magic == MAGIC) {
		readUintArray((uint8_t *)&root,sizeof(root),f);
	} else {
		printf("S!\n");
	}
	fclose(f);
}
void shell() {
	printf("2-2\n");
	printf("Who are you?\n");
}
