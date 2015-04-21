#include <sys/sysinfo.h>
#include <erl_driver.h>
#include "memsup.h"


struct driver_data {
  ErlDrvPort port;
  ErlDrvTermData port_term;
};

struct async_data {
  int type;
  unsigned long mem_total;
  unsigned long mem_free;
  unsigned long mem_buffers;
  unsigned long mem_shared;
  unsigned long swap_total;
  unsigned long swap_free;
};


static ErlDrvData memsup_start(ErlDrvPort port, char *buff __attribute__((unused))) {
  struct driver_data *driver_data = (struct driver_data *)driver_alloc(sizeof(struct driver_data));
  driver_data->port = port;
  driver_data->port_term = driver_mk_port(port);
  return (ErlDrvData)driver_data;
}


static void memsup_stop(ErlDrvData handle) {
  driver_free((struct driver_data *)handle);
}


static void memsup_async(void *data) {
  struct async_data *async_data = (struct async_data *)data;
  struct sysinfo info = {0};
  sysinfo(&info);
  async_data->mem_total   = info.totalram;
  async_data->mem_free    = info.freeram;
  async_data->mem_buffers = info.bufferram;
  async_data->mem_shared  = info.sharedram;
  async_data->swap_total  = info.totalswap;
  async_data->swap_free   = info.freeswap;
}


static void memsup_output(ErlDrvData handle, char *buff, ErlDrvSizeT bufflen) {
  struct driver_data *driver_data = (struct driver_data *)handle;

  if (bufflen == 0)
    return;

  struct async_data *async_data = (struct async_data *)driver_alloc(sizeof(struct async_data));
  async_data->type = buff[0];
  driver_async(driver_data->port, NULL, memsup_async, async_data, NULL);
}


static void memsup_ready_async(ErlDrvData handle, ErlDrvThreadData thread_data) {
  struct driver_data *driver_data = (struct driver_data *)handle;
  struct async_data *async_data = (struct async_data *)thread_data;
  int i;

  switch(async_data->type) {
  case SHOW_MEM: {
    ErlDrvTermData term[][6] = {
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_total - async_data->mem_free,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_total,
       ERL_DRV_TUPLE, 2}
    };

    for(i=0;i<2;i++) {
      erl_drv_output_term(driver_data->port_term, term[i], 6);
    }
    break;
  }
  case SHOW_SYSTEM_MEM: {
    ErlDrvTermData term[][6] = {
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, MEM_TOTAL,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_total,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, MEM_FREE,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_free,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, MEM_BUFFERS,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_buffers,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, MEM_SHARED,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_shared,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, SWAP_TOTAL,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->swap_total,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, SWAP_FREE,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->swap_free,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, MEM_SYSTEM_TOTAL,
       ERL_DRV_TUPLE, 2},
      {ERL_DRV_PORT, driver_data->port_term,
       ERL_DRV_UINT, async_data->mem_total,
       ERL_DRV_TUPLE, 2},
    };

    for(i=0;i<14;i++) {
      erl_drv_output_term(driver_data->port_term, term[i], 6);
    }

    ErlDrvTermData end_term[] = {
      ERL_DRV_PORT, driver_data->port_term,
      ERL_DRV_UINT, SHOW_SYSTEM_MEM_END,
      ERL_DRV_TUPLE, 2};

    erl_drv_output_term(driver_data->port_term, end_term, 6);
    break;
  }
  default:
    break;
  }
}


ErlDrvEntry memsup_entry = {
  .init            = NULL,
  .start           = memsup_start,
  .stop            = memsup_stop,
  .output          = memsup_output,
  .ready_input     = NULL,
  .ready_output    = NULL,
  .driver_name     = "memsup",
  .finish          = NULL,
  .handle          = NULL,
  .control         = NULL,
  .timeout         = NULL,
  .outputv         = NULL,
  .ready_async     = memsup_ready_async,
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


DRIVER_INIT(memsup) {
  return &memsup_entry;
}
