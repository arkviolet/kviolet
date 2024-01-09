

#include <kviolet/kviolet.h>
#include <kviolet_3rd/kviolet_3rd.h>

int main(int argc, char** argv) {
  std::cout << "please input .wav format audio file" << std::endl;
  auto pulseaudio = std::make_shared<kviolet::PulseAudioManager>();

  std::string video0 = argv[1];

  sleep(1);

  std::cout << std::endl << "===play===" << std::endl;
  pulseaudio->Play("1", video0, 100);

  sleep(5);
  std::cout << std::endl << "===pause===" << std::endl;
  pulseaudio->Pause("1");

  sleep(5);
  std::cout << std::endl << "===resume===" << std::endl;
  pulseaudio->Resume("1");

  sleep(5);
  std::cout << std::endl << "===cancel===" << std::endl;
  pulseaudio->Cancel("1");

  sleep(1);

  pulseaudio = nullptr;

  return 0;
}
