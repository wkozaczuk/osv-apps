#include <string.h>
#include <sys/param.h>
#include <sys/statvfs.h>
#include <mntent.h>
#include <erl_driver.h>


struct driver_data {
  ErlDrvPort port;
  ErlDrvTermData port_term;
};


struct disk_data {
  char *disk_path;
  size_t disk_path_len;
  size_t disk_size;
  int disk_usage;
  struct disk_data *next;
};


struct async_data {
  struct disk_data *disk_data;
  size_t entries;
};


static ErlDrvData disksup_start(ErlDrvPort port, char *buff __attribute__((unused)) ) {
  struct driver_data *driver_data = (struct driver_data *)driver_alloc(sizeof(struct driver_data));
  driver_data->port = port;
  driver_data->port_term = driver_mk_port(port);
  return (ErlDrvData)driver_data;
}


static void disksup_stop(ErlDrvData handle) {
  driver_free((struct driver_data *)handle);
}


static void disksup_async(void *data) {
  struct async_data *async_data = (struct async_data *)data;
  async_data->disk_data = NULL;
  async_data->entries = 0;
  FILE *file = setmntent("/proc/mounts", "r");
  struct mntent mntent = {0};
  char buf[MAXPATHLEN * 4] = {0};

  while (getmntent_r(file, &mntent, buf, sizeof(buf))) {
    struct statvfs stat = {0};

    if (statvfs(mntent.mnt_dir, &stat))
      continue;
    if (!stat.f_files)
      continue;

    struct disk_data *disk_data = (struct disk_data *)driver_alloc(sizeof(struct disk_data));
    disk_data->disk_path_len = strlen(mntent.mnt_dir);
    disk_data->disk_path = (char *)driver_alloc(disk_data->disk_path_len);
    memcpy(disk_data->disk_path, mntent.mnt_dir, disk_data->disk_path_len);
    disk_data->disk_size = stat.f_blocks * stat.f_frsize / 1024;
    fsblkcnt_t used = (stat.f_blocks - stat.f_bfree) * 100;
    fsblkcnt_t total = stat.f_blocks - stat.f_bfree + stat.f_bavail;
    disk_data->disk_usage = (used / total) + (used % total > 0);

    disk_data->next = async_data->disk_data;
    async_data->disk_data = disk_data;
    async_data->entries++;
  }
}


static void disksup_output(ErlDrvData handle, char *buff __attribute__((unused)), ErlDrvSizeT bufflen __attribute__((unused))) {
  struct driver_data *driver_data = (struct driver_data *)handle;
  struct async_data *async_data = (struct async_data *)driver_alloc(sizeof(struct async_data));
  driver_async(driver_data->port, NULL, disksup_async, async_data, NULL);
}


static void disksup_ready_async(ErlDrvData handle, ErlDrvThreadData thread_data) {
  struct driver_data *driver_data = (struct driver_data *)handle;
  struct async_data *async_data = (struct async_data *)thread_data;
  struct disk_data *disk_data = async_data->disk_data;

  ErlDrvTermData term[(async_data->entries) * 9 + 7];
  int i = 0;
  term[i++] = ERL_DRV_PORT;
  term[i++] = driver_data->port_term;

  while(disk_data) {
    term[i++] = ERL_DRV_STRING;
    term[i++] = (ErlDrvTermData)disk_data->disk_path;
    term[i++] = disk_data->disk_path_len;
    term[i++] = ERL_DRV_UINT;
    term[i++] = disk_data->disk_size;
    term[i++] = ERL_DRV_INT;
    term[i++] = disk_data->disk_usage;
    term[i++] = ERL_DRV_TUPLE;
    term[i++] = 3;
    disk_data = disk_data->next;
  }
  term[i++] = ERL_DRV_NIL;
  term[i++] = ERL_DRV_LIST;
  term[i++] = async_data->entries + 1;
  term[i++] = ERL_DRV_TUPLE;
  term[i++] = 2;
  erl_drv_output_term(driver_data->port_term, term, sizeof(term)/sizeof(ErlDrvTermData));

  disk_data = async_data->disk_data;
  while(disk_data) {
    struct disk_data *next_disk_data = disk_data->next;
    driver_free(disk_data->disk_path);
    driver_free(disk_data);
    disk_data = next_disk_data;
  }
  driver_free(async_data);
}


ErlDrvEntry disksup_entry = {
  .init            = NULL,
  .start           = disksup_start,
  .stop            = disksup_stop,
  .output          = disksup_output,
  .ready_input     = NULL,
  .ready_output    = NULL,
  .driver_name     = "disksup",
  .finish          = NULL,
  .handle          = NULL,
  .control         = NULL,
  .timeout         = NULL,
  .outputv         = NULL,
  .ready_async     = disksup_ready_async,
  .flush           = NULL,
  .call            = NULL,
  .event           = NULL,
  .extended_marker = ERL_DRV_EXTENDED_MARKER,
  .major_version   = ERL_DRV_EXTENDED_MAJOR_VERSION,
  .minor_version   = ERL_DRV_EXTENDED_MINOR_VERSION,
  .driver_flags    = 0,
  .handle2         = NULL,
  .process_exit    = NULL,
  .stop_select     = NULL,
};


DRIVER_INIT(disksup) {
  return &disksup_entry;
}
