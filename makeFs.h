void boot_sec(FILE *fs)
{
	rewind(fs);
	BOOT_SECTOR bs;
	bs.bytes_per_sector = 512;
	bs.sector_per_clusters = 1;
	bs.num_sectors = 65536;
	bs.reserved_sectors = 8;
	bs.max_files = 128;

	fwrite(&bs, sizeof(bs), 1, fs);
	char fill = 0;
	for (int i = 0; i < 501; i++) {
		fwrite(&fill, sizeof(fill), 1, fs);
    }
}


void make_dir(FILE *fs)
{
	fseek(fs, 512, SEEK_SET);
	directory root;
	for (int i = 0; i < 25; i++)
	{
		root.filename[i] = '.';
		if(i > 0) {
			root.filename[i] = 0x00;
		}
	}
	root.attribute = 1;
	root.initial_cluster = 2;
	root.size_file = 0;
	fwrite(&root, sizeof(root), 1, fs);
	char fill = 0;
	
	int RESERVED_SECTOR = 480 + (8 * 512);

	for (int i = 0; i < RESERVED_SECTOR; i++) {
		fwrite(&fill, sizeof(fill), 1, fs);
	}
}
