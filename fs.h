#define MAGIC 0x1568
struct superblock {
	int magic; //indificator
    int size;
    int inodes;
    int used_inodes;
};
struct inode {
	char name[256];
	int type;
	int files[512];
	char data[1024];
	int uid;
	int gid;
	int permissions;
};