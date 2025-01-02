#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>
#include <string>

unsigned char asc2nibble(char c) {
  if ((c >= '0') && (c <= '9')) return c - '0';

  if ((c >= 'A') && (c <= 'F')) return c - 'A' + 10;

  if ((c >= 'a') && (c <= 'f')) return c - 'a' + 10;

  return 16; /* error */
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  int s;
  struct sockaddr_can addr;
  struct canfd_frame frame;
  struct ifreq ifr;

  std::string can_id = argv[2];
  std::string can_name = argv[1];

  memset(&frame, 0, sizeof(struct canfd_frame));

  canid_t tmp;
  if (3 == can_id.size()) {
    for (int i = 0; i < 3; i++) {
      if ((tmp = asc2nibble(can_id[i])) > 0x0F) {
        std::cerr << "can_id asc2nibble error" << std::endl;
        return 0;
      }
      frame.can_id |= (tmp << (2 - i) * 4);
    }
  } else if (8 == can_id.size()) {
    std::cerr << "can_id size not support" << std::endl;
    return 0;
  } else {
    std::cerr << "can_id error" << std::endl;
    return 0;
  }

  if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
    std::cerr << "socket error" << std::endl;
    return 0;
  }

  strncpy(ifr.ifr_name, can_name.c_str(), IFNAMSIZ - 1);
  ifr.ifr_name[IFNAMSIZ - 1] = '\0';
  ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
  if (!ifr.ifr_ifindex) {
    std::cerr << "if_nametoindex error" << std::endl;
    return 0;
  }

  memset(&addr, 0, sizeof(addr));
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);

  if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    std::cerr << "bind error" << std::endl;
    return 0;
  }
  std::cout << "bind success" << std::endl;

  std::string data;
  do {
    std::cout << std::endl << "please input data:" << std::endl;

    std::getline(std::cin, data);
    if (data.empty()) {
      continue;
    }

    int index = 0;
    char buffer[256] = {0};
    for (auto iter = data.begin(); iter != data.end(); iter++) {
      if (*iter == ' ') {
        continue;
      }

      if ((tmp = asc2nibble(*iter++)) > 0x0F) {
        std::cerr << "can_id asc2nibble error" << std::endl;
        return 0;
      }
      buffer[index] = (tmp << 4);
      if ((tmp = asc2nibble(*iter)) > 0x0F) {
        std::cerr << "can_id asc2nibble error" << std::endl;
        return 0;
      }
      buffer[index++] |= tmp;
    }

    int send_len = 0;
    do {
      int len = (index - send_len);
      len = len > 8 ? 8 : len;

      frame.len = len;
      memcpy(frame.data, buffer + send_len, len);
      auto ret = write(s, &frame, CAN_MTU);
      if (ret < 0) {
        std::cerr << "write error" << std::endl;
        return 0;
      }
      send_len += len;
    } while (send_len < index);

  } while (1);

  close(s);

  return 0;
}
