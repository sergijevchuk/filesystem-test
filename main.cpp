#include "fs.h"
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
struct superblock super;
struct inode root;
int debug;
void load(FILE *f);
void shell();
void new_file();
void save();
void writeUintArray(uint8_t *buffer,size_t size,FILE *stream) {
	if (fwrite(buffer,sizeof(uint8_t),size,stream) != size) {
		printf("Write failed!\n");
		fclose(stream);
		exit(1);
	}
}
void readUintArray(uint8_t *buffer,size_t size,FILE *stream) {
	fread(buffer,sizeof(uint8_t),size,stream);
}
void printDebug(char *msg) {
	if(debug) {
		printf("%s\n",msg);
	}
}
int hasEntity(char *name) {
	//no
}
FILE *f;
int main(int argc,char *argv[]) {
	f = fopen("test.fs" ,"r+");
	if (f == NULL) {
		printf("...\n");
		return 1;
	}
	load(f);
	shell();
}
void load(FILE *f) {
	fread(&super,sizeof(super),1,f);
	if (super.magic == MAGIC) {
		readUintArray((uint8_t *)&root,sizeof(root),f);
		if (strcmp(root.name,"/") != 0) {
			printf("CRITICAL: No root found!\n");
			fclose(f);
			exit(1);
		}
	} else {
		printf("S!\n");
	}
}
void shell() {
	while(1) {
	printf(">");
	char command[256];
	scanf("%s",command);
	if (strcmp(command,"exit") == 0) {
		fclose(f);
		break;
	} else if (strcmp(command,"ls") == 0) {
		int address = sizeof(super)+sizeof(root);
		fseek(f,address+0,0);
		for(int i = 0; i < super.used_inodes-1; i++) {
			struct inode file;
			readUintArray((uint8_t *)&file,sizeof(file),f);
			printf("%s\n",file.name);
			//fseek(f,sizeof(file),0);
		}
		fseek(f,0L,SEEK_END);
	} else if (strcmp(command,"touch") == 0) {
		printf("Enter file name: ");
		new_file();
	} else {
		printf("Unknown command %s\n",command);
		}
	}
}
void new_file() {
	if(super.used_inodes >= super.inodes) {
		printf("No enough space to create file!\n");
		exit(1);
	}
	char name[12];
scanf("%s",name);
	struct inode new_file;
	strcpy(new_file.name,name);
	new_file.type = 0;
	new_file.size = 0;
	new_file.uid = root.uid;
	new_file.gid = root.gid;
	new_file.data_address = -1;
	//write a inode
    writeUintArray((uint8_t *)&new_file,sizeof(new_file),f);
    super.used_inodes = super.used_inodes+1;
    save();
}
void save() {
	fseek(f,0L,SEEK_SET);
	fwrite(&super,sizeof(super),1,f);
	fseek(f,0L,SEEK_END);
}