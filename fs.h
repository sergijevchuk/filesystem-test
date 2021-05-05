#define MAGIC 0x1568
struct superblock {
	int magic; //indificator
    int size;
    int inodes;
    int used_inodes;
};
struct inode {
	char name[12];
	int type;
	int size;
	int data_address;
	int uid;
	int gid;
	int permissions;
};