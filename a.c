#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  struct libevdev *dev = NULL;
  int fd;
  int rc = 1;

  fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
  rc = libevdev_new_from_fd(fd, &dev);
  if (rc < 0) {
    fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
    exit(1);
  }
  printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
  printf("Input device ID: bus %#x vendor %#x product %#x\n",
	 libevdev_get_id_bustype(dev),
	 libevdev_get_id_vendor(dev),
	 libevdev_get_id_product(dev));

  do {
    struct input_event ev;
    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    if (rc == 0) {
      if (ev.type == EV_KEY) {
	if (ev.value) {
	  switch (ev.code) {
	  case BTN_TR2:
	    printf("VOl up\n");
	    system("/usr/bin/amixer set Playback 5+");
	    break;
	  case BTN_TL2:
	    printf("VOl down\n");
	    system("/usr/bin/amixer set Playback 5-");
	    break;
	  default:
	    ;
	    /* printf("Event: %s %s %d\n", */
	    /* 	   libevdev_event_type_get_name(ev.type), */
	    /* 	   libevdev_event_code_get_name(ev.type, ev.code), */
	    /* 	   ev.value); */
	  }
	}
      }
    }
  } while (rc == 1 || rc == 0 || rc == -EAGAIN);

  return 0;
}
