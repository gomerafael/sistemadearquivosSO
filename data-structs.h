typedef struct boot_sector 
{
	unsigned short bytes_per_sector;
	unsigned char sector_per_clusters;
	unsigned short reserved_sectors;
	unsigned short max_files;
	unsigned int num_sectors;

} __attribute__((packed)) BOOT_SECTOR;

typedef struct directory 
{
	unsigned char filename[25];
	unsigned char attribute;
	unsigned short initial_cluster;
	unsigned int size_file;
} __attribute__((packed)) directory;

typedef struct reader 
{
	unsigned char r;
} __attribute__((packed)) reader_t;