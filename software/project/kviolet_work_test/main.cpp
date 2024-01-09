

#include <kviolet/kviolet.h>
#include <kviolet_3rd/kviolet_3rd.h>

int main(int argc, char** argv) {
  std::cout << "please input .wav format audio file" << std::endl;
  auto pulseaudio = std::make_shared<kviolet::PulseAudioManager>();

  std::string video0 = argv[1];

  sleep(1);

  pulseaudio->Play("1", video0, 100);

  sleep(10000);

  return 0;
}
