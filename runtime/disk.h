#define CMD_READ 0xc4 // 0xc4 0x20 read, 0x24 read ext, 0xc4 multiple
#define BSY_FLAG 0x80

#define sector_log 9

extern void *disktarget;
extern void diskcopy();

static inline void read_sectors(void *dest, u32 sector, u32 count)
{
    u16 max, base = 0x1f0;
    u8  drive = 0x40;
    u32 total = pad(count, (1<<sector_log));
    u32 ts = sector;

    disktarget = dest;

    while (total) {
        u32 secs = total>>sector_log;
        u16 xfer = (secs > 256)?256:secs;

        out8(base + 2, xfer);
        out8(base + 3, ts);
        out8(base + 4, ts >> 8);
        out8(base + 5, ts >> 16);
        out8(base + 6, (ts >> 24) | drive);
        out8(base + 7, CMD_READ);
        for(int index = 0; index < xfer; index++) {
            // its necessary..but slow.. to do this each time to get repeatable results
            // shouldn't be
            while(in8(base + 7) & BSY_FLAG);
            diskcopy();
        }
        total -= xfer<<sector_log;
        ts += xfer;
    }
}